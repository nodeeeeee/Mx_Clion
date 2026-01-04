//
// Created by zhang-kai on 6/16/25.
//
#include "frontend/ast/semantic_check.h"

#include "frontend/global_scope_extractor.h"
#include "frontend/ast/all_ast_nodes.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/paren_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/ternary_expr_node.h"


void SemanticCheck::visit(std::shared_ptr<RootNode> node) {
  auto global_scope_extractor = std::make_shared<GlobalScopeExtractor>(current_scope, node);
  node->sort_def_nodes();
  global_scope_extractor->extract_root_node(node);

  for (const auto& def_node : node->getDefNodes()) {
    def_node->accept(this);
  }
}

void SemanticCheck::visit(std::shared_ptr<MainFuncNode> node) {
  createScope(node);
  node->getBody()->accept(this);
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<BlockNode> node) {
  for (const auto& stat_node : node->getStatNodes()) {
    stat_node->accept(this);
  }
}

void SemanticCheck::visit(std::shared_ptr<BlockStatNode> node) {
  createScope(node);
  node->getBlockNode()->accept(this);
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<FuncDefNode> node) {
  auto func_name = node->getIdNode()->getIdName();
  if (auto class_scope = dynamic_pointer_cast<ClassDefNode>(current_scope->getScopeOwner())) {
    if (func_name == class_scope->getIdNode()->getIdName()) {
      throw std::runtime_error(
        "this function has the same name as the enclosing class, but is not a constructor function");
    }
  }
  auto block_node = node->getFuncBlock();
  auto var_defs = node->getVarDefs();
  createScope(node);
  for (const auto& varDef : var_defs) {
    current_scope->declare(varDef);
  }
  block_node->accept(this);
  if (!current_scope->getHasReturn() && *node->getIdNode()->getType() != *k_void) {
    throw std::runtime_error("this function has no return statement");
  }
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<ClassDefNode> node) {
  auto block_node = node->getBlockNode();
  current_scope = current_scope->findClass(node->getIdNode()->getIdName());
  // block_node->accept(this);
  auto stats = block_node->getStatNodes();
  for (const auto& stat_node : stats) {
    if (auto func_def = std::dynamic_pointer_cast<FuncDefNode>(stat_node)) {
      func_def->accept(this);
    } else if (auto class_func_def = std::dynamic_pointer_cast<ClassFuncDefNode>(stat_node)) {
      class_func_def->accept(this);
    }
  }
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<ClassFuncDefNode> node) {
  auto func_name = node->getIdNode()->getIdName();
  auto tmp_scope = current_scope;
  while (true) {
    if (auto class_node = dynamic_pointer_cast<ClassDefNode>(tmp_scope->getScopeOwner())) {
      if (class_node->getIdNode()->getIdName() == func_name) {
        break;
      } else {
        throw std::runtime_error("class_func and class mismatch");
      }
    }
    if (tmp_scope->getParent() == nullptr) {
      throw(std::runtime_error("no enclosing classes, return statement should not exist"));
    }
    tmp_scope = tmp_scope->getParent();
  }
  createScope(node);
  auto block_node = node->getBlockNode();
  block_node->accept(this);
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<VarDefNode> node) {
  auto lhs = std::shared_ptr<TypeType>(node->getIdNode()->getType());
  if (*lhs == *k_void || lhs->compareBase(*k_void)) {
    throw std::runtime_error("variable cannot be void type");
  }
  auto rhs = node->getExpr();

  if (rhs == nullptr) {
    current_scope->declare(node);
    return;
  }

  rhs->accept(this); //update the expression type in visit(ExprNode)
  auto rhs_type = checkType(rhs);
  auto lhs_type = lhs;
  if (rhs_type == nullptr) {
    throw(std::runtime_error("expression has no type"));
  } else if (*checkType(rhs) != *lhs && *rhs_type != *k_null) {
    throw(std::runtime_error("expression has type mismatch"));
  }
  if (*rhs_type == *k_null && (*lhs_type == *k_int || *lhs_type == *k_bool)) {
    throw std::runtime_error("rhs is null, cannot be assigned to simple primitive on the lhs");
  }
  current_scope->declare(node);
}

void SemanticCheck::visit(std::shared_ptr<ArrayConstNode> node) {
  // if (node->)
  node->determineArrayType();
}

void SemanticCheck::visit(std::shared_ptr<BinaryExprNode> node) {
  auto lhs = node->getLhs();
  auto rhs = node->getRhs();
  lhs->accept(this);
  rhs->accept(this);
  auto lhs_type = checkType(lhs);
  auto rhs_type = checkType(rhs);
  if (!node->getLhs()->isValid() || !node->getRhs()->isValid()) {
    node->setValid(false);
    return;
  }
  if (*lhs_type != *rhs_type) {
    if (*rhs_type == *k_null && (node->getOp() == BinaryExprNode::BinaryOp::kNET || node->getOp() ==
      BinaryExprNode::BinaryOp::kET)) {
    } else {
      throw std::runtime_error("binary expression has type mismatch");
    }
  }
  switch (node->getOp()) {
    //for int or string
    case BinaryExprNode::BinaryOp::kADD: {
      if (*lhs_type != *k_string && *lhs_type != *k_int) {
        throw(std::runtime_error("add cannot be applied to the type"));
      }
      node->setExprType(lhs_type);
      break;
    }
    case BinaryExprNode::BinaryOp::kMUL:
    case BinaryExprNode::BinaryOp::kDIV:
    case BinaryExprNode::BinaryOp::kMOD:
    case BinaryExprNode::BinaryOp::kSUB:
    case BinaryExprNode::BinaryOp::kSRL:
    case BinaryExprNode::BinaryOp::kSLL:
    case BinaryExprNode::BinaryOp::kAND:
    case BinaryExprNode::BinaryOp::kXOR:
    case BinaryExprNode::BinaryOp::kOR: {
      if (*lhs_type != *k_int) {
        throw(std::runtime_error("the operator only applies to integers"));
      }
      node->setExprType(lhs_type);
      break;
    }
    case BinaryExprNode::BinaryOp::kBT:
    case BinaryExprNode::BinaryOp::kLT:
    case BinaryExprNode::BinaryOp::kBEQ:
    case BinaryExprNode::BinaryOp::kLEQ:
    case BinaryExprNode::BinaryOp::kET:
    case BinaryExprNode::BinaryOp::kNET: {
      node->setExprType(k_bool);
      node->setAssignable(false);
      break;
    }
    case BinaryExprNode::BinaryOp::kAND_AND:
    case BinaryExprNode::BinaryOp::kOR_OR: {
      if (*lhs_type != *k_bool) {
        throw(std::runtime_error("the operator only applies to booleans"));
      }
      node->setExprType(lhs_type);
      node->setAssignable(false);
    }
  }
}

void SemanticCheck::visit(std::shared_ptr<DotExprNode> node) {
  auto lhs = node->getLhs();
  auto rhs = node->getRhs();
  lhs->accept(this);
  std::shared_ptr<IdNode> lhs_id;
  std::shared_ptr<TypeType> lhs_type;
  std::string lhs_class;
  if (auto id_tmp = std::dynamic_pointer_cast<IdNode>(lhs)) {
    lhs_id = std::dynamic_pointer_cast<IdNode>(id_tmp);
    lhs_type = current_scope->findVar(lhs_id->getIdName());
    lhs_class = lhs_type->getTypeName();
  } else if (auto this_tmp = std::dynamic_pointer_cast<ThisExprNode>(lhs)) {
    auto tmp_scope = current_scope;
    while (true) {
      if (auto class_def = dynamic_pointer_cast<ClassDefNode>(tmp_scope->getScopeOwner())) {
        lhs_id = class_def->getIdNode();
        lhs_class = lhs_id->getIdName();
        break;
      }
      if (tmp_scope->getParent() == nullptr) {
        throw(std::runtime_error("'this' refers to nothing"));
      }
      tmp_scope = tmp_scope->getParent();
    }
    lhs_class = lhs_id->getIdName();
  } else {
    lhs_type = checkType(lhs);
    lhs_class = lhs_type->getTypeName();
  }
  auto class_scope = current_scope->findClass(lhs_class);
  if (class_scope == nullptr) {
    node->setValid(false);
    throw(std::runtime_error("lhs not found"));
  }

  if (auto id_tmp = std::dynamic_pointer_cast<IdNode>(rhs)) {
    auto rhs_type = class_scope->findVar(id_tmp->getIdName());
    if (rhs_type == nullptr) {
      throw std::runtime_error("rhs not found");
      node->setValid(false);
    }
    node->setPrvalue(false);
    node->setExprType(rhs_type);
  } else if (auto func_tmp = std::dynamic_pointer_cast<FuncCallNode>(rhs)) {
    std::shared_ptr<Function> rhs_func;
    if (lhs_type->getDimension() > 0) {
      rhs_func = global_scope->findClass("0Array")->findFunc(func_tmp->getName());
    } else {
      rhs_func = class_scope->findFunc(func_tmp->getName());
    }
    auto rhs_type = rhs_func->getReturnType();
    if (rhs_type == nullptr) {
      throw std::runtime_error("rhs not found");
      node->setValid(false);
    }
    node->setExprType(rhs_type);
  } else {
    throw std::runtime_error("rhs not id or funccall");
  }
}

void SemanticCheck::visit(std::shared_ptr<FormatStringNode> node) {
  for (auto& expr : node->getExprNodes()) {
    expr->accept(this);
    if (*checkType(expr) != *k_string && *checkType(expr) != *k_bool && *checkType(expr) != *k_int) {
      throw std::runtime_error("format string only supports string, bool, int expression");
    }
    if (!expr->isValid()) {
      node->setValid(false);
      throw(std::runtime_error("format string expressions invalid"));
    }
  }
  node->setExprType(k_string);
}

void SemanticCheck::visit(std::shared_ptr<FuncCallNode> node) {
  auto func = current_scope->findFunc(node->getName());
  auto args = node->getArgs();
  for (auto& arg : args) {
    arg->accept(this);
    if (!arg->isValid()) {
      node->setValid(false);
      throw std::runtime_error("function arguments invalid");
    }
  }
  auto func_param_types = func->getParamTypes();
  if (func_param_types.size() != args.size()) {
    throw std::runtime_error("function arguments number mismatch");
  }
  for (size_t i = 0; i < func_param_types.size(); ++i) {
    if (!compare_type(func_param_types[i], checkType(args[i]))) {
      throw std::runtime_error("function argument type mismatch");
    }
  }
  node->setExprType(func->getReturnType());
}

void SemanticCheck::visit(std::shared_ptr<IndexExprNode> node) {
  auto base = node->getBase();
  if (auto init_array_expr = std::dynamic_pointer_cast<InitArrayNode>(base)) {
    throw std::runtime_error("cannot get index for initarray");
  }
  auto index = node->getIndex();
  base->accept(this);
  index->accept(this);
  if (!base->isValid() || !index->isValid()) {
    node->setValid(false);
  }
  std::shared_ptr<TypeType> base_type = checkType(base);
  std::shared_ptr<TypeType> index_type = checkType(index);
  if (*index_type != *k_int) {
    throw std::runtime_error("index type not int");
  }
  if (base_type->getDimension() == 0) {
    node->setValid(false);
    throw std::runtime_error("not an array");
  }
  auto expr_type = checkType(base);
  node->setExprType(std::make_shared<TypeType>(expr_type, -1));
  if (!node->getBase()->isPrvalue()) {
    node->setPrvalue(false);
  }
}

void SemanticCheck::visit(std::shared_ptr<InitArrayNode> node) {
  int dim = node->getRangeNode().size();
  if (node->getType()->getDimension() != 0) {
    throw std::runtime_error("first index of init array is vacant");
  }
  auto ranges = node->getRangeNode();
  //ranges can be nullptr or expr
  for (auto range : ranges) {
    if (range != nullptr) {
      range->accept(this);
      if (*checkType(range) != *k_int) {
        throw std::runtime_error("index type not int");
      }
    }
  }
  node->setExprType(std::make_shared<TypeType>(node->getType(), dim));
  auto default_array = node->getDefaultArray();
  if (default_array != nullptr) {
    default_array->accept(this);
    if (*(default_array->getArrayType()) != *(node->getExprType())) {
      throw std::runtime_error("default array is incompatible");
    }
  }
  node->setPrvalue(false);
}

void SemanticCheck::visit(std::shared_ptr<InitObjectNode> node) {
  auto node_type = node->getType();
  if (current_scope->findClass(node_type->getTypeName())) {
    node->setExprType(node->getType());
  }
  node->setPrvalue(false);
}

void SemanticCheck::visit(std::shared_ptr<NullExprNode> node) {
}

void SemanticCheck::visit(std::shared_ptr<UnaryExprNode> node) {
  auto op = node->getOp();
  auto expr = node->getExpr();
  expr->accept(this);
  if (!expr->isValid()) {
    node->setValid(false);
  }
  switch (op) {
    case UnaryExprNode::UnaryOp::kPRE_PP:
    case UnaryExprNode::UnaryOp::kPRE_MM: {
      if (*(checkType(expr)) != *k_int) {
        throw(std::runtime_error("unary op is not int"));
      } else if (expr->isPrvalue()) {
        node->setValid(false);
        throw std::runtime_error("++/-- cannot be applied to prvalues");
      }
      node->setExprType(k_int);
      node->setPrvalue(false);
      break;
    }
    case UnaryExprNode::UnaryOp::kPOST_PP:
    case UnaryExprNode::UnaryOp::kPOST_MM: {
      if (*checkType(expr) != *k_int) {
        throw std::runtime_error("unary op is not int");
      } else if (expr->isPrvalue()) {
        node->setValid(false);
        throw std::runtime_error("++/-- cannot be applied to prvalues");
      }
      node->setExprType(k_int);
      node->setPrvalue(true);
      break;
    }
    case UnaryExprNode::UnaryOp::kADD:
    case UnaryExprNode::UnaryOp::kSUB:
    case UnaryExprNode::UnaryOp::kWAVE: {
      auto expr_type = checkType(expr);
      if (*expr_type != *k_int) {
        throw std::runtime_error("unary expression type mismatch");
      }
      node->setExprType(k_int);
      break;
    }
    case UnaryExprNode::UnaryOp::kEXCLAIMER: {
      auto expr_type = checkType(expr);
      if (*expr_type != *k_bool) {
        throw(std::runtime_error("unary expression type mismatch"));
      }
      node->setExprType(k_bool);
      break;
    }
  }
}

void SemanticCheck::visit(std::shared_ptr<TernaryExprNode> node) {
  auto predicate = node->getPredicateNode();
  auto then_expr = node->getThenExprNode();
  auto else_expr = node->getElseExprNode();
  predicate->accept(this);
  then_expr->accept(this);
  else_expr->accept(this);
  if (*checkType(predicate) != *k_bool) {
    throw std::runtime_error("predicate type error");
  }
  if (!compare_type(checkType(then_expr), checkType(else_expr))) {
    throw std::runtime_error("then and else are not in the same type");
  }

  node->setExprType(checkType(then_expr));
}


void SemanticCheck::visit(std::shared_ptr<AssignStatNode> node) {
  auto lhs = node->getLhs();
  auto rhs = node->getRhs();
  lhs->accept(this);
  if (auto lhs_literal = std::dynamic_pointer_cast<LiteralNode>(lhs)) {
    throw std::runtime_error("lhs should not be literal");
  }
  if (lhs->isPrvalue()) {
    throw std::runtime_error("lhs should not be prvalue");
  }
  rhs->accept(this);
  std::shared_ptr<TypeType> lhs_type = checkType(lhs);
  std::shared_ptr<TypeType> rhs_type = checkType(rhs);
  if (*lhs_type != *rhs_type && *rhs_type != *k_null) {
    throw(std::runtime_error("assignment statement type mismatch"));
  }
  if (*rhs_type == *k_null && (*lhs_type == *k_int || *lhs_type == *k_bool)) {
    throw std::runtime_error("rhs is null, cannot be assigned to simple primitive on the lhs");
  }
  // if rhs == k_null,
  // set rhs type as lhs
  if (*rhs_type == *k_null) {
    rhs->setExprType(lhs_type);
  }
}

void SemanticCheck::visit(std::shared_ptr<ForStatNode> node) {
  auto initial_var = node->getInitialVarDefNode();
  auto initial_expr = node->getInitialExprNode();
  auto for_cond = node->getForCondExprNode();
  auto update_assign = node->getUpdateAssignStatNode();
  auto update_expr = node->getUpdateExprNode();
  auto block = node->getBlockNode();
  createScope(node);
  if (initial_var != nullptr) { initial_var->accept(this); }
  if (initial_expr != nullptr) {
    initial_expr->accept(this);
  }
  if (for_cond != nullptr) {
    for_cond->accept(this);
    if (*checkType(for_cond) != *k_bool) {
      throw std::runtime_error("for_cond type is not bool");
    }
  }
  if (update_assign != nullptr) { update_assign->accept(this); }
  if (update_expr != nullptr) { update_expr->accept(this); }
  block->accept(this);
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<IfStatNode> node) {
  auto predicate = node->getPredicate();
  auto then_block = node->getThenBlock();
  auto else_block = node->getElseBlock();
  predicate->accept(this);
  if (*checkType(predicate) != *k_bool) {
    throw std::runtime_error("predicate type not bool");
  }
  createScope(node);
  then_block->accept(this);
  exitScope();
  if (else_block != nullptr) {
    createScope(node);
    else_block->accept(this);
    exitScope();
  }
}

void SemanticCheck::visit(std::shared_ptr<ReturnStatNode> node) {
  //find the first typed owner of the scope,match it.
  auto return_expr = node->getReturnExpr();
  if (return_expr == nullptr) {
    auto tmp_scope = current_scope;
    while (true) {
      if (auto func = dynamic_pointer_cast<FuncDefNode>(tmp_scope->getScopeOwner())) {
        if (*(func->getReturnType()) != *k_void) {
          throw std::runtime_error("return statement type mismatch");
        } else {
          tmp_scope->setHasReturn(true);
          break;
        }
      }
      if (auto class_func = dynamic_pointer_cast<ClassFuncDefNode>(tmp_scope->getScopeOwner())) {
        if (*(class_func->getReturnType()) != *k_void) {
          throw std::runtime_error("class_func is not void");
        } else {
          tmp_scope->setHasReturn(true);
          break;
        }
      }
      if (tmp_scope->getParent() == nullptr) {
        throw(std::runtime_error("no enclosing functions, return statement should not exist"));
      }
      tmp_scope = tmp_scope->getParent();
    }
  } else {
    return_expr->accept(this);
    auto return_expr_type = checkType(return_expr);
    auto tmp_scope = current_scope;
    while (true) {
      if (auto func = dynamic_pointer_cast<FuncDefNode>(tmp_scope->getScopeOwner())) {
        if (*(func->getReturnType()) != *return_expr_type) {
          // auto tmpa = func->getReturnType();
          // auto tmpb = return_expr->getExprType();
          // auto equal = tmpa->getTypeName() == tmpb;
          if (func->getReturnType()->is_customized() && *return_expr_type == *k_null) {
          } else {
            throw std::runtime_error("return statement type mismatch");
          }
        }
        tmp_scope->setHasReturn(true);
        break;
      }
      if (auto func = dynamic_pointer_cast<MainFuncNode>(tmp_scope->getScopeOwner())) {
        if (*(k_int) != *(return_expr_type)) {
          throw std::runtime_error("return statement type mismatch");
        } else {
          break;
        }
      }
      if (tmp_scope->getParent() == nullptr) {
        throw(std::runtime_error("no enclosing functions, return statement should not exist"));
      }
      tmp_scope = tmp_scope->getParent();
    }
  }
}

void SemanticCheck::visit(std::shared_ptr<WhileStatNode> node) {
  auto cond = node->getWhileCondExprNode();
  auto block = node->getBlockNode();
  createScope(node);
  cond->accept(this);
  block->accept(this);
  if (*checkType(cond) != *k_bool) {
    throw(std::runtime_error("condition statement type mismatch"));
  }
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<LiteralNode> node) {
  node->setExprType(node->getLiteralType());
}

void SemanticCheck::visit(std::shared_ptr<TerminalNode> node) {
  auto tmp_scope = current_scope;
  while (true) {
    if (auto for_loop = dynamic_pointer_cast<ForStatNode>(tmp_scope->getScopeOwner())) {
      break;
    } else if (auto while_loop = dynamic_pointer_cast<WhileStatNode>(tmp_scope->getScopeOwner())) {
      break;
    }
    if (tmp_scope->getParent() == nullptr) {
      throw(std::runtime_error("no enclosing functions, break/continue statement should not exist"));
    }
    tmp_scope = tmp_scope->getParent();
  }
}

void SemanticCheck::visit(std::shared_ptr<ThisExprNode> node) {
  auto tmp_scope = current_scope;
  while (true) {
    if (auto class_def_node = dynamic_pointer_cast<ClassDefNode>(tmp_scope->getScopeOwner())) {
      auto class_name = class_def_node->getIdNode()->getIdName();
      node->setExprType(std::make_shared<TypeType>(class_name));
      break;
    }
    if (tmp_scope->getParent() == nullptr) {
      throw(std::runtime_error("no enclosing class, 'this' is not legal"));
    }
    tmp_scope = tmp_scope->getParent();
  }
}

void SemanticCheck::visit(std::shared_ptr<ParenExprNode> node) {
  auto inner_expr = node->getInnerExpr();
  inner_expr->accept(this);
  node->setExprType(checkType(inner_expr));
  node->setPrvalue(inner_expr->isPrvalue());
  node->setValid(inner_expr->isValid());
}


void SemanticCheck::createScope(const std::shared_ptr<ASTNode>& node) {
  auto new_scope = std::make_shared<Scope>(current_scope, node);
  current_scope->addChildScope(new_scope);
  current_scope = new_scope;
}

void SemanticCheck::exitScope() {
  current_scope = current_scope->getParent();
}

std::shared_ptr<TypeType> SemanticCheck::checkType(std::shared_ptr<ExprNode> expr) {
  std::shared_ptr<TypeType> expr_type;
  if (auto index_expr = std::dynamic_pointer_cast<IndexExprNode>(expr)) {
    return std::make_shared<TypeType>(checkType(index_expr->getBase()), -1);
  }
  if (auto expr_id = std::dynamic_pointer_cast<IdNode>(expr)) {
    expr_type = current_scope->findVar(expr_id->getIdName());
    expr->setExprType(expr_type);
    expr->setPrvalue(false);
  } else if (auto const_array_expr = std::dynamic_pointer_cast<ArrayConstNode>(expr)) {
    expr_type = const_array_expr->getArrayType();
  }
  else {
    expr_type = expr->getExprType();
  }
  return expr_type;
}

bool SemanticCheck::compare_type(std::shared_ptr<TypeType> a, std::shared_ptr<TypeType> b) {
  bool a_is_object = a->is_customized() | a->getDimension() > 0;
  bool b_is_object = b->is_customized() | b->getDimension() > 0;
  if ((*a == *k_null && b_is_object) || (a_is_object && *b == *k_null) || (*a == *k_null && *b == *k_null)) {
    return true;
  }
  return *a == *b;
}
