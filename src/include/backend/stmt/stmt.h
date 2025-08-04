#pragma once
#include <../util/block.h>

class Stmt {
public:
  Stmt() = default;
  virtual ~Stmt() = default;
  explicit Stmt(std::shared_ptr<Block> block) : block_(std::move(block)) {}
protected:
  std::shared_ptr<Block> block_;
};
