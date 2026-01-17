//
// Created by zhangkai on 2026/1/16.
//

# pragma once
#include <memory>
#include <bits/regex_constants.h>

#include "backend/stmt/br_stmt/br_conditional_stmt.h"
#include "backend/util/asm_function.h"

class CFGConstruction {
  public:
  CFGConstruction(const std::shared_ptr<IRFunction>& ir_func) : ir_func_(ir_func) {
    for (const auto& basic_block : ir_func->GetBlocks()) {
      CalcBlock(basic_block);
      CreateCfg();
    }
    for (const auto& exit_block : exit_block_) {
      BlockLevelLiveness(exit_block);
    }
    for (const auto& basic_block : ir_func->GetBlocks()) {
      StmtLevelLiveness(basic_block);
    }
  }




  private:
  std::pair<std::set<std::variant<int, std::string>>, std::set<std::variant<int, std::string>>> calc_block(std::shared_ptr<Block> basic_block) {
    /** do basic_block level analysis
     */
    std::set<std::shared_ptr<Register>> block_use;
    std::set<std::shared_ptr<Register>> block_def;
    for (const auto& stmt : basic_block->GetStmts()) {
      auto stmt_use = stmt->GetUse();
      auto stmt_def = stmt->GetDef();
      //use[n] - def[p]
      std::set<std::shared_ptr<Register>> middle;
      std::set_difference(stmt_use.begin(), stmt_use.end(), block_def.begin(), block_def.end(), std::inserter(middle, middle.begin()));
      block_use.merge(middle);
      block_def.merge(stmt_def);
    }
    basic_block->SetUse(block_use);
    basic_block->SetDef(block_def);
    // block_use_[basic_block->getBlockName()] = block_use;
    // block_def_[basic_block->getBlockName()] = block_def;
  }

  void CreateCfg() {
    for (const auto& basic_block : ir_func_->GetBlocks()) {
      auto cf_stmt = basic_block->GetStmts().back();
      // brcond, bruncond
      // return means sink
      if (auto br_cond_stmt = std::dynamic_pointer_cast<BrConditionalStmt>(cf_stmt)) {
        auto br_true = ir_func_->FindBlock(br_cond_stmt->GetTrueLabel());
        auto br_false = ir_func_->FindBlock(br_cond_stmt->GetFalseLabel());
        basic_block->AddCFGSuccessor(br_true);
        basic_block->AddCFGSuccessor(br_false);
        br_true->AddCFGPredecessor(basic_block);
        br_false->AddCFGPredecessor(basic_block);

      } else if (auto br_uncond_stmt = std::dynamic_pointer_cast<BrUnconditionalStmt>(cf_stmt)) {
        auto br = ir_func_->FindBlock(br_uncond_stmt->GetLabel());
        basic_block->AddCFGSuccessor(br);
        br->AddCFGPredecessor(basic_block);
      } else {
        exit_block_.push_back(basic_block);
        basic_block->SetOut();
      }
    }
  }

  void BlockLevelLiveness(const std::shared_ptr<Block>& basic_block) {
    std::set<std::shared_ptr<Register>> block_in = basic_block->GetUse();
    std::set<std::shared_ptr<Register>> block_out;
    for (const auto& suc : basic_block->GetSuccessors()) {
      block_out.merge(suc->GetIn());
    }
    std::set<std::shared_ptr<Register>> middle;
    std::set_difference(block_out.begin(), block_out.end(), basic_block->GetDef().begin(), basic_block->GetDef().end(), std::inserter(middle, middle.begin()));
    block_in.merge(middle);
    if (basic_block->GetIn() != block_in || basic_block->GetOut() != block_out) {
      basic_block->SetIn(block_in);
      basic_block->SetOut(block_out);
      for (const auto& pred : basic_block->GetPredecessors()) {
        BlockLevelLiveness(pred);
      }
    }
  }

  void StmtLevelLiveness(const std::shared_ptr<Block>& basic_block) {
    auto stmts = basic_block->GetStmts();
    stmts[stmts.size() - 1]->SetOut(basic_block->GetOut());
    for (int i = stmts.size() - 1; i >= 0; i--) {
      if (i != stmts.size() - 1) {
        stmts[i]->SetOut(stmts[i + 1]->GetIn());
      }
      auto stmt_out = stmts[i]->GetOut();
      auto stmt_def = stmts[i]->GetDef();
      auto stmt_in = stmts[i]->GetUse();
      std::set<std::shared_ptr<Register>> middle;
      std::set_difference(stmt_out.begin(), stmt_out.end(), stmt_def.begin(), stmt_def.end(), std::inserter(middle, middle.begin()));
      stmt_in.merge(middle);
      stmts[i]->SetIn(stmt_in);
    }
  }



  std::shared_ptr<IRFunction> ir_func_;
  // std::map<std::string, std::set<std::variant<int, std::string>>> block_in_;
  // std::map<std::string, std::set<std::variant<int, std::string>>> block_out_;
  // std::map<std::string, std::set<std::variant<int, std::string>>> block_use_;
  // std::map<std::string, std::set<std::variant<int, std::string>>> block_def_;
  std::vector<std::shared_ptr<Block>> exit_block_;
};

