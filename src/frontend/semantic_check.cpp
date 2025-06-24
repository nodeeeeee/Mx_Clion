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
  auto block_node = node-> GetBlockNode();
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
  } else if (rhs->getExprType() != lhs){
    throw(std::runtime_error("expression has type mismatch"));
  }
}

void SemanticCheck::visit(std::shared_ptr<ArrayConstNode> node) {
  
}



void SemanticCheck::createScope(const std::shared_ptr<ASTNode> &node) {
  auto new_scope = std::make_shared<Scope>(current_scope, node);
  current_scope->addChildScope(new_scope);
  current_scope = new_scope;
}

void SemanticCheck::exitScope() {
  current_scope = current_scope->getParent();
}

