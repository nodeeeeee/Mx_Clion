//
// Created by zhang-kai on 6/16/25.
//
#include "frontend/ast/semantic_check.h"

#include "frontend/global_scope_extractor.h"
#include "frontend/ast/all_ast_nodes.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/ternary_expr_node.h"


void SemanticCheck::visit(std::shared_ptr<RootNode> node) {
  auto global_scope_extractor = std::make_shared<GlobalScopeExtractor>(current_scope, node);
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

void SemanticCheck::visit(std::shared_ptr<FuncDefNode> node) {
  auto block_node = node->getFuncBlock();
  auto var_defs = node->getVarDefs();
  createScope(node);
  for (const auto& varDef : var_defs) {
    current_scope->declare(varDef);
  }
  block_node->accept(this);
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<ClassDefNode> node) {
  auto block_node = node->getBlockNode();
  current_scope = current_scope->findClass(node->getIdNode()->getIdName());
  // block_node->accept(this);
  auto stats = block_node->getStatNodes();
  for (const auto& stat_node : stats) {
    if (auto func_def = std::dynamic_pointer_cast<FuncDefNode> (stat_node)) {
      func_def->accept(this);
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

  auto rhs = node->getExpr();
  if (rhs == nullptr) {
    current_scope->declare(node);
    return ;
  }

  rhs->accept(this); //update the expression type in visit(ExprNode)
  if (rhs->getExprType() == nullptr) {
    throw(std::runtime_error("expression has no type"));
  } else if (*(rhs->getExprType()) != *lhs) {
    throw(std::runtime_error("expression has type mismatch"));
  }
  current_scope->declare(node);
}

void SemanticCheck::visit(std::shared_ptr<ArrayConstNode> node) {
  node->determineArrayType();
}

void SemanticCheck::visit(std::shared_ptr<BinaryExprNode> node) {
  auto lhs = node->getLhs();
  auto rhs = node->getRhs();
  lhs->accept(this);
  rhs->accept(this);
  auto lhs_type = lhs->getExprType();
  auto rhs_type = rhs->getExprType();
  if (!node->getLhs()->isValid() || !node->getRhs()->isValid()) {
    node->setValid(false);
    return;
  }
  if (lhs_type != rhs_type) {
    throw std::runtime_error("binary expression has type mismatch");
  } else {
    switch (node->getOp()) {
      //for int or string
      case BinaryExprNode::BinaryOp::kADD: {
        if (lhs_type != k_string || lhs_type != k_int) {
          throw(std::runtime_error("add cannot be applied to the type"));
        }
        node->setExprType(lhs_type);
        break;
      }
      case BinaryExprNode::BinaryOp::kMUL: {
        //todo
        //string * int
      }
      case BinaryExprNode::BinaryOp::kDIV:
      case BinaryExprNode::BinaryOp::kMOD:
      case BinaryExprNode::BinaryOp::kSUB:
      case BinaryExprNode::BinaryOp::kSRL:
      case BinaryExprNode::BinaryOp::kSLL:
      case BinaryExprNode::BinaryOp::kAND:
      case BinaryExprNode::BinaryOp::kXOR:
      case BinaryExprNode::BinaryOp::kOR: {
        if (lhs_type != k_int) {
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
        if (lhs_type != k_bool) {
          throw(std::runtime_error("the operator only applies to booleans"));
        }
        node->setExprType(lhs_type);
        node->setAssignable(false);
      }
    }
    node->setExprType(lhs_type);
  }
}

void SemanticCheck::visit(std::shared_ptr<DotExprNode> node) {
  auto lhs = node->getLhs();
  auto rhs = node->getRhs();
  std::shared_ptr<IdNode> lhs_id;
  std::shared_ptr<TypeType> lhs_type;
  std::string lhs_class;
  if (auto id_tmp = std::dynamic_pointer_cast<IdNode>(lhs)) {
    lhs_id = std::dynamic_pointer_cast<IdNode>(id_tmp);
    lhs_type = current_scope->findVar(lhs_id->getIdName());
    lhs_class = lhs_type->getTypeName();
  } else if (auto this_tmp =  std::dynamic_pointer_cast<ThisExprNode>(lhs)) {
    auto tmp_scope = current_scope;
    while (true) {
      if (auto class_def = dynamic_pointer_cast<ClassDefNode>(tmp_scope->getScopeOwner())) {
        lhs_id = class_def->getIdNode();
        break;
      }
      if (tmp_scope->getParent() == nullptr) {
        throw(std::runtime_error("'this' refers to nothing"));
      }
      tmp_scope = tmp_scope->getParent();
    }
    lhs_class= lhs_id->getIdName();
  }else {
    throw std::runtime_error("lhs not id");
  }
  auto class_scope = current_scope->findClass(lhs_id->getIdName());
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
    node->setExprType(rhs_type);
  } else if (auto func_tmp = std::dynamic_pointer_cast<FuncCallNode>(rhs)) {
    auto rhs_func = class_scope->findFunc(func_tmp->getName());
    auto rhs_type = rhs_func->getReturnType();
    if (rhs_type == nullptr) {
      throw std::runtime_error("rhs not found");
      node->setValid(false);
    }
    node->setExprType(rhs_type);

  }else {
    throw std::runtime_error("rhs not id or funccall");
  }



}

void SemanticCheck::visit(std::shared_ptr<FormatStringNode> node) {
  for (auto& expr : node->getExprNodes()) {
    expr->accept(this);
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
      throw std::runtime_error("function arguments invalid") ;
    }
  }
  auto func_param_types = func->getParamTypes();
  if (func_param_types.size() != args.size()) {
    throw std::runtime_error("function arguments number mismatch");
  }
  for (size_t i = 0; i < func_param_types.size(); ++i) {
    if (func_param_types[i] != args[i]->getExprType()) {
      throw std::runtime_error("function argument type mismatch");
    }
  }
  node->setExprType(func->getReturnType());
}

void SemanticCheck::visit(std::shared_ptr<IndexExprNode> node) {
  auto base = node->getBase();
  auto index = node->getIndex();
  base->accept(this);
  index->accept(this);
  if (!base->isValid() || !index->isValid()) {
    node->setValid(false);
  }
  std::shared_ptr<TypeType> base_type = checkType(base);
  std::shared_ptr<TypeType> index_type = checkType(index);

  if (base_type->getDimension() == 0) {
    node->setValid(false);
    throw std::runtime_error("not an array");
  }
  node->setExprType(std::make_shared<TypeType>(base->getExprType(), -1));
}

void SemanticCheck::visit(std::shared_ptr<InitArrayNode> node) {
  size_t dim = node->getRangeNode().size();
  node->setExprType(std::make_shared<TypeType>(node->getType(), dim));
  auto default_array = node->getDefaultArray();
  if (default_array != nullptr) {
    default_array->accept(this);
    if (default_array->getExprType() != node->getExprType()) {
      throw std::runtime_error("default array is incompatible");
    }
  }
}

void SemanticCheck::visit(std::shared_ptr<InitObjectNode> node) {
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
      if (expr->getExprType() != k_int) {
        throw(std::runtime_error("unary op is not int"));
      } else if (expr->isPrvalue()) {
        node->setValid(false);
        throw std::runtime_error("++/-- cannot be applied to prvalues");
      }
      node->setPrvalue(false);
      break;
    }
    case UnaryExprNode::UnaryOp::kPOST_PP:
    case UnaryExprNode::UnaryOp::kPOST_MM: {
      if (expr->getExprType() != k_int) {
        throw std::runtime_error("unary op is not int");
      } else if (expr->isPrvalue()) {
        node->setValid(false);
        throw std::runtime_error("++/-- cannot be applied to prvalues");
      }
      break;
    }
    case UnaryExprNode::UnaryOp::kADD:
    case UnaryExprNode::UnaryOp::kSUB:
    case UnaryExprNode::UnaryOp::kWAVE: {
      if (expr->getExprType() != k_int) {
        throw std::runtime_error("unary expression type mismatch");
      }
      node->setExprType(k_int);
      break;
    }
    case UnaryExprNode::UnaryOp::kEXCLAIMER: {
      if (expr->getExprType() != k_bool) {
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
  if (predicate->getExprType() != k_bool) {
    throw std::runtime_error("predicate type error");
  }
  if (then_expr->getExprType() != else_expr->getExprType()) {
    throw std::runtime_error("then and else are not in the same type");
  }

  node->setExprType(then_expr->getExprType());
}


void SemanticCheck::visit(std::shared_ptr<AssignStatNode> node) {
  auto lhs = node->getLhs();
  auto rhs = node->getRhs();
  lhs->accept(this);
  rhs->accept(this);
  std::shared_ptr<TypeType> lhs_type;
  std::shared_ptr<TypeType> rhs_type;
  if (auto lhs_id = std::dynamic_pointer_cast<IdNode>(lhs)) {
    lhs_type = current_scope->findVar(lhs_id->getIdName());
  } else {
    lhs_type = lhs->getExprType();
  }
  if (auto rhs_id = std::dynamic_pointer_cast<IdNode>(rhs)) {
    rhs_type = current_scope->findVar(rhs_id->getIdName());
  } else {
    rhs_type = rhs->getExprType();
  }
  if (*lhs_type != *rhs_type) {
    throw(std::runtime_error("assignment statement type mismatch"));
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
  if (initial_var != nullptr) {initial_var->accept(this);}
  if (initial_expr != nullptr) {
    initial_expr->accept(this);
  }
  if (for_cond != nullptr) {for_cond->accept(this);}
  if (update_assign != nullptr) {update_assign->accept(this);}
  if (update_expr != nullptr) {update_expr->accept(this);}
  block->accept(this);
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<IfStatNode> node) {
  auto predicate = node->getPredicate();
  auto then_block = node->getThenBlock();
  auto else_block = node->getElseBlock();
  predicate->accept(this);
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
  return_expr->accept(this);
  if (auto id_expr = std::dynamic_pointer_cast<IdNode>(return_expr)) {
    return_expr->setExprType(current_scope->findVar(id_expr->getIdName()));
  }
  auto tmp_scope = current_scope;
  while (true) {
    if (auto func = dynamic_pointer_cast<FuncDefNode>(tmp_scope->getScopeOwner())) {
      if (*(func->getReturnType()) != *(return_expr->getExprType())) {
        auto tmpa = func->getReturnType();
        auto tmpb = return_expr->getExprType();
        // auto equal = tmpa->getTypeName() == tmpb;
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

void SemanticCheck::visit(std::shared_ptr<WhileStatNode> node) {
  auto cond = node->getWhileCondExprNode();
  auto block = node->getBlockNode();
  cond->accept(this);
  block->accept(this);
  if (cond->getExprType() != k_bool) {
    throw(std::runtime_error("condition statement type mismatch"));
  }
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
      throw(std::runtime_error("no enclosing functions, return statement should not exist"));
    }
    tmp_scope = tmp_scope->getParent();
  }
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
  if (auto expr_id = std::dynamic_pointer_cast<IdNode>(expr)) {
    expr_type = current_scope->findVar(expr_id->getIdName());
  } else {
    expr_type = expr->getExprType();
  }
  return expr_type;
}