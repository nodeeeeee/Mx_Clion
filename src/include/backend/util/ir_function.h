#pragma once
#include <string>
#include <vector>

#include "block.h"
#include "ir_scope.h"
#include "register.h"
#include "frontend/ast/stat_node/def_node/func_def_node.h"
#include "type/ir_type.h"

class IRFunction {
public:
  explicit IRFunction(const std::shared_ptr<FuncDefNode>& func_def_node) {
    is_main_ = false;
    func_name_ = func_def_node->getIdNode()->getIdName();
    return_type_ = std::make_shared<IRType>(func_def_node->getReturnType());
    func_scope_ = std::make_shared<IRScope>();
    // param_types_ = std::make_shared<IRType>(func_def_node->getVarDefs());
    auto var_defs = func_def_node->getVarDefs();
    for (const auto& var_def : var_defs) {
      param_types_.push_back(std::make_shared<IRType>(var_def->getIdNode()->getType()));
    }
  }

  explicit IRFunction(const std::shared_ptr<MainFuncNode>& main_func_node) {
    is_main_ = true;
    func_name_ = "main";
    return_type_ = std::make_shared<IRType>(IRType::kINT);
    func_scope_ = std::make_shared<IRScope>();
  }

  void AddBlock(const std::shared_ptr<Block>& block) {
    blocks_.push_back(block);
  }

  void SetIndex(int value) {
    index_counter_ = value;
  }

  [[nodiscard]] int GetIndex() const {
    return index_counter_;
  }

  std::shared_ptr<Register> CreateRegister(const std::shared_ptr<IRType>& reg_type) {
    auto new_reg = std::make_shared<Register>(index_counter_, reg_type);
    index_counter_++;
    return new_reg;
  }

  [[nodiscard]] std::shared_ptr<IRScope> GetScope() const {
    return func_scope_;
  }

  std::shared_ptr<Block> CreateBlock(const std::string& block_name) {
    auto new_block = Block::CreateBlock(block_name);
    blocks_.push_back(new_block);
    return new_block;
  }

private:
  std::string func_name_;
  std::vector<std::shared_ptr<IRType>> param_types_;
  std::shared_ptr<IRType> return_type_;
  std::vector<std::shared_ptr<Block>> blocks_;// the first one is entry block
  bool is_main_;
  std::shared_ptr<IRScope> func_scope_;
  int index_counter_ = 0;
};
