//
// Created by zhang-kai on 6/16/25.
//
#include "frontend/ast/semantic_check.h"


void SemanticCheck::visit(std::shared_ptr<RootNode> node) {
  auto global_scope_extractor = std::make_shared<GlobalScopeExtractor>(current_scope);
  global_scope_extractor->extract_root_node(node);
  for (auto def_node : node->getDefNodes()) {
    def_node->accept(this);
  }
}

void SemanticCheck::visit(std::shared_ptr<MainFuncNode> node) {
  createScope(node);
  node->getBody()->accept(this);
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<BlockNode> node) {
  for (auto stat_node : node->getStatNodes()) {
    stat_node->accept(this);
  }
}

void SemanticCheck::visit(std::shared_ptr<FuncDefNode> node) {
  auto block_node = node->getFuncBlock();
  auto var_defs = node->getVarDefs();
  createScope(block_node);
  for (auto varDef : var_defs) {
    current_scope->declare(varDef);
  }
  block_node->accept(this);
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<ClassDefNode> node) {
  auto block_node = node->GetBlockNode();
  createScope(node);
  block_node->accept(this);
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<ClassFuncDefNode> node) {
  createScope(node);
  auto block_node = node->getBlockNode();
  block_node->accept(this);
  exitScope();
}

void SemanticCheck::visit(std::shared_ptr<VarDefNode> node) {
  auto lhs = node->getIdNode()->getType();
  auto rhs = node->getExpr();
  rhs->accept(this); //update the expression type in visit(ExprNode)

  if (rhs->getExprType() == nullptr) {
    throw(std::runtime_error("expression has no type"));
  } else if (rhs->getExprType() != lhs) {
    throw(std::runtime_error("expression has type mismatch"));
  }
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
      case BinaryExprNode::BinaryOp::kMUL:
      case BinaryExprNode::BinaryOp::kDIV:
      case BinaryExprNode::BinaryOp::kMOD:
      case BinaryExprNode::BinaryOp::kSUB:
      case BinaryExprNode::BinaryOp::kSRL:
      case BinaryExprNode::BinaryOp::kSLL:
      case BinaryExprNode::BinaryOp::kBT:
      case BinaryExprNode::BinaryOp::kLT:
      case BinaryExprNode::BinaryOp::kBEQ:
      case BinaryExprNode::BinaryOp::kLEQ:
      case BinaryExprNode::BinaryOp::kAND:
      case BinaryExprNode::BinaryOp::kXOR:
      case BinaryExprNode::BinaryOp::kOR: {
        if (lhs_type != k_int) {
          throw(std::runtime_error("the operator only applies to integers"));
        }
        node->setExprType(lhs_type);
        break;
      }
      case BinaryExprNode::BinaryOp::kET:
      case BinaryExprNode::BinaryOp::kNET: {
        node->setExprType(k_bool);
        node->setAssignable(false);
        break;
      }
      case BinaryExprNode::BinaryOp::kAND_AND:
      case BinaryExprNode::BinaryOp::kOR_OR: {
        if (lhs != k_bool) {
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
  if (auto tmp = std::dynamic_pointer_cast<IdNode>(lhs)) {
  } else {
    throw std::runtime_error("lhs not id");
  }
  if (auto tmp = std::dynamic_pointer_cast<IdNode>(rhs)) {
  } else {
    throw std::runtime_error("rhs not id");
  }
  lhs->accept(this);
  rhs->accept(this);
  auto class_scope = current_scope->findClass(lhs->getIdName());
  if (class_scope == nullptr) {
    node->setValid(false);
    throw(std::runtime_error("lhs not found"));
  }
  auto rhs_type = class_scope->findVar(rhs->getIdName());
  if (rhs_type == nullptr) {
    node->setValid(false);
  }
  node->setExprType(rhs_type);
}

void SemanticCheck::visit(std::shared_ptr<FormatStringNode> node) {
  for (auto &expr : node->getExprNodes()) {
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
  for (auto &arg : args) {
    arg->accept(this);
    if (!arg->isValid()) {
      throw(std::runtime_error("function arguments invalid"));
    }
  }
  auto func_param_types = func->getParamTypes();
  if (func_param_types.size() != args.size()) {
    throw(std::runtime_error("function arguments number mismatch"));
  }
  for (size_t i = 0; i < func_param_types.size(); ++i) {
    if (func_param_types[i] != args[i]->getExprType()) {
      throw(std::runtime_error("function argument type mismatch"));
    }
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
