//
// Created by zhang-kai on 6/16/25.
//
#include "frontend/ast/semantic_check.h"



void SemanticCheck::visit(std::shared_ptr<RootNode> node) {
  auto global_scope_extractor = std::make_shared<GlobalScopeExtractor>(current_scope);
  global_scope_extractor->extract_root_node(node);
  for (auto def_node : node->getDefNodes()) {
    def_node->accept
    if (auto func_def_node = dynamic_pointer_cast<FuncDefNode>(def_node)) {

    } else if (auto main_func_node = dynamic_pointer_cast<MainFuncNode>(node)) {
      visit(main_func_node);
    }
  }
}

void SemanticCheck::visit(std::shared_ptr<MainFuncNode> node) {
  visit(node->getBody(), node);
}

void SemanticCheck::visit(std::shared_ptr<BlockNode> node, std::shared_ptr<ASTNode> block_owner) {
  auto new_scope = std::make_shared<Scope>(current_scope, block_owner);
  current_scope->addChildScope(new_scope);
  current_scope = new_scope;
  for (auto stat_node : node->getStatNodes()) {
    if (auto stat_node = dynamic_pointer_cast<>)
  }
  current_scope = current_scope->getParent();
}
