#pragma once
#include <string>
#include <utility>
#include <vector>

#include "backend/asm_instruction/asm_instruction.h"
#include "backend/stmt/stmt.h"
#include "backend/stmt/br_stmt/br_unconditional_stmt.h"
#include "backend/stmt/br_stmt/ret_stmt.h"

class Block : public std::enable_shared_from_this<Block> {
public:
  Block() = default;

  explicit Block(std::string block_name) : block_name_(std::move(block_name)) {
  }

  void AddStmt(const std::shared_ptr<Stmt>& stmt) {
    stmts_.push_back(stmt);
  }

  std::vector<std::shared_ptr<Stmt>>& GetStmts() {
    return stmts_;
  }

  static std::shared_ptr<Block> CreateBlock(const std::string& block_name, bool is_for_block = false) {
  return make_shared<Block>(block_name);
  }
  [[nodiscard]] std::string getBlockName() const { return block_name_; }

  [[nodiscard]] std::string commit() {
    std::string str;
    str += block_name_ + ": \n";
    for (int i = 0; i < stmts_.size(); i++) {
      auto stmt = stmts_[i];
      str += stmt->commit() + "\n";
      if (auto ret_stmt = std::dynamic_pointer_cast<ReturnStmt>(stmt)) {
        stmts_.erase(stmts_.begin() + i + 1, stmts_.end());
        return str;
      } else if (auto br_uncond_stmt = std::dynamic_pointer_cast<BrUnconditionalStmt>(stmt)) {
        stmts_.erase(stmts_.begin() + i + 1, stmts_.end());
        return str;
      }
    }
    return str;
  }

  void AddInstruction(std::shared_ptr<AsmInstruction> instruction) {
    instructions_.push_back(instruction);
  }

  std::vector<std::shared_ptr<AsmInstruction>>& GetInstructions() {
    return instructions_;
  }

  std::string GenerateAsmCode() {
    std::string ret;
    for (auto instruction : instructions_) {
      ret += instruction->commit() + "\n";
    }
    return ret;
  }


private:
  std::vector<std::shared_ptr<Stmt>> stmts_;
  std::string block_name_;
  std::vector<std::shared_ptr<AsmInstruction>> instructions_;
};
