#pragma once

#include <backend/util/block.h>



class Stmt {
public:
  Stmt() = default;
  virtual ~Stmt() = default;
  virtual std::string commit() const = 0;
};
