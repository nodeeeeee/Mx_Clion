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

  explicit IRScope(std::shared_ptr<IRScope> parent) : parent_(std::move(parent)) {}

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

  static std::shared_ptr<IRScope> CreateScope(const std::shared_ptr<IRScope>& parent) {
    return std::make_shared<IRScope>(parent);
  }

  std::shared_ptr<IRScope> GetParent() {
    return parent_;
  }

private:
  std::shared_ptr<IRScope> parent_;
  std::map<std::string, std::shared_ptr<Register>> regs_;

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
