#pragma once
#include <string>
#include <utility>
#include <vector>

#include "backend/stmt/stmt.h"

class Block : public std::enable_shared_from_this<Block> {
public:
  Block() = default;

  explicit Block(std::string block_name) : block_name_(std::move(block_name)) {
  }

  void AddStmt(const std::shared_ptr<Stmt>& stmt) {
    stmts_.push_back(stmt);
  }

  // void CreateAlloca() {
  //   //todo
  // }
  // void CreateLoad() {
  //   //TODO
  // }
  // void CreateStore() {
  //   //TODO
  // }

  static std::shared_ptr<Block> CreateBlock(const std::string& block_name, bool is_for_block = false) {
  return make_shared<Block>(block_name);
  }
  [[nodiscard]] std::string getBlockName() const { return block_name_; }
private:
  std::vector<std::shared_ptr<Stmt>> stmts_;
  std::string block_name_;
};
