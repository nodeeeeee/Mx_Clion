//
// Created by zhangkai on 2026/1/16.
//

# pragma once
#include <memory>

#include "backend/util/asm_function.h"

class CFGConstruction {
  public:
  CFGConstruction(std::shared_ptr<IRFunction> ir_func) : ir_func_(ir_func) {
    for (const auto& basic_block : ir_func->GetBlocks()) {
      calc_block(basic_block);
    }
  }


  private:
  std::pair<std::set<std::variant<int, std::string>>, std::set<std::variant<int, std::string>>> calc_block(std::shared_ptr<Block> basic_block) {
    for (auto stmt : basic_block->GetStmts()) {
      if ()
    }
  }

  std::shared_ptr<IRFunction> ir_func_;
  std::map<std::string, std::set<std::variant<int, std::string>>> in_;
  std::map<std::string, std::set<std::variant<int, std::string>>> out_;
  std::map<std::string, std::set<std::variant<int, std::string>>> use_;
  std::map<std::string, std::set<std::variant<int, std::string>>> def_;
};
