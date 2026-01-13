//
// Created by zhang-kai on 6/16/25.
//
#include "frontend/global_scope_extractor.h"
#include "frontend/ast/stat_node/def_node/class_def_node.h"
#include "frontend/ast/stat_node/def_node/func_def_node.h"

void GlobalScopeExtractor::extract_root_node(std::shared_ptr<RootNode> root_node) {
  auto defs = root_node->getDefNodes();
  auto main_func = root_node->getMainNode();
  for (const auto &def : defs) {
    if (auto func_def = dynamic_pointer_cast<FuncDefNode>(def)) {
      current_scope->declare(func_def);
    } else if (auto class_def = dynamic_pointer_cast<ClassDefNode>(def)) {
      current_scope->declare(class_def);
    }
  }
}

