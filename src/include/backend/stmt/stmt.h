#pragma once

#include<string>


class Stmt {
public:
  Stmt() = default;
  virtual ~Stmt() = default;
  virtual std::string commit() const = 0;
};
