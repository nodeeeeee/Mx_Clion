#pragma once
#include <string>
#include <vector>

#include "block.h"
#include "frontend/ast/stat_node/def_node/func_def_node.h"
#include "type/ir_type.h"

class IRFunction {
public:
  IRFunction(std::shared_ptr<FuncDefNode> func_def_node) {
    func_name_ = func_def_node->getIdNode()->getIdName();
    return_type_ = std::make_shared<IRType>(func_def_node->getReturnType());
    // param_types_ = std::make_shared<IRType>(func_def_node->getVarDefs());
    auto var_defs = func_def_node->getVarDefs();
    for (const auto& var_def : var_defs) {
      param_types_.push_back(std::make_shared<IRType>(var_def->getIdNode()->getType()));
    }
  }
private:
  std::string func_name_;
  std::vector<std::shared_ptr<IRType>> param_types_;
  std::shared_ptr<IRType> return_type_;
  std::vector<std::shared_ptr<Block>> blocks_;
};
