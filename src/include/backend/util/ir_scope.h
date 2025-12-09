#pragma once
#include <map>
#include <memory>
#include <utility>

#include "register.h"
#include "type/ir_type.h"

/* every function has its own scope, these scopes do not belong to global scope
 * and there is no global scope
 * but within each function, enter scope and pop scope is required
 */

class IRScope : public std::enable_shared_from_this<IRScope> {
public:
  IRScope() : parent_(nullptr) {
  }

  explicit IRScope(std::shared_ptr<IRScope> parent, const std::shared_ptr<Block>& loop_start, const std::shared_ptr<Block>& loop_end) : parent_(std::move(parent)) {
    if (loop_start != nullptr) {
      loop_start_ = loop_start;
      loop_end_ = loop_end;
    } else {
      loop_start_ = parent_->loop_start_;
      loop_end_ = parent_->loop_end_;
    }
  }

  explicit IRScope(std::nullptr_t null);

  std::shared_ptr<Register> FindRegister(const std::string& var_name) {
    while (true) {
      if (regs_.contains(var_name)) {
        return regs_[var_name];
      } else {
        if (this->parent_ == nullptr) {
        } else {
          return this->parent_->FindRegister(var_name);
        }
      }
    }
    // try {
    //   return index_[var_name];
    // } catch (const std::exception &e) {
    //   throw std::runtime_error("var not found exception");
    // }
  }
  void declare(const std::string& reg_name, std::shared_ptr<Register> reg) {
    regs_[reg_name] = std::move(reg);
  }

  static std::shared_ptr<IRScope> CreateScope(const std::shared_ptr<IRScope>& parent, const std::shared_ptr<Block>& loop_start = nullptr, const std::shared_ptr<Block>&loop_end = nullptr) {
    return std::make_shared<IRScope>(parent, loop_start, loop_end);
  }

  std::shared_ptr<IRScope> GetParent() {
    return parent_;
  }

  std::shared_ptr<Block> GetLoopStart() {
    return loop_start_;
  }
  std::shared_ptr<Block> GetLoopEnd() {
    return loop_end_;
  }

private:
  std::shared_ptr<IRScope> parent_;
  std::map<std::string, std::shared_ptr<Register>> regs_;
  std::shared_ptr<Block> loop_end_;
  std::shared_ptr<Block> loop_start_;

};

class IRGlobalScope : public IRScope {
public:
  explicit IRGlobalScope() : IRScope(nullptr) {}
  void AddGlobalStmt(std::string stmt) {
    global_stmts.push_back(std::move(stmt));
  }

private:
  std::vector<std::string> global_stmts;
};
