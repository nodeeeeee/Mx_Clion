#pragma once
#include <string>
#include <vector>

class Block {
public:
  Block() = default;

  void AddStmt(std::string stmt) {
    stmts_.push_back(stmt);
  }

  void CreateAlloca() {
    //todo
  }
  void CreateLoad() {
    //TODO
  }
  void CreateStore() {
    //TODO
  }
  std::shared_ptr<Block> CreateBlock(std::string block_name) {
    return make_shared<Block>(block_name);
  }
private:
  std::vector<std::string> stmts_;
  std::string block_name_;
};
