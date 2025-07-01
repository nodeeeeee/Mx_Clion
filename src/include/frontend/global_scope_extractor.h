//
// Created by zhang-kai on 6/13/25.
//

#pragma once
#include "ast/util/scope.h"
#include "ast/visit_control.h"
#include "ast/root_node.h"
#include "ast/stat_node/def_node/class_def_node.h"
class GlobalScopeExtractor {
public:
  std::shared_ptr<Scope> current_scope;
  std::shared_ptr<RootNode> root_node;
  GlobalScopeExtractor(const std::shared_ptr<Scope> &current_scope, const std::shared_ptr<RootNode> root_node) : current_scope(current_scope), root_node(root_node) {};
  void extract_root_node(std::shared_ptr<RootNode> root_node);  //interface
  // void extract_func_def();
  // void extract_class_def(std::shared_ptr<RootNode> root_node);
  // void extract_main_func();
private:

};
