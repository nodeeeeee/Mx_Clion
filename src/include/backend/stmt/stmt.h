#pragma once

#include <memory>
#include <set>
#include<string>


class Register;

class Stmt {
public:
  Stmt() = default;
  virtual ~Stmt() = default;
  virtual std::string commit() const = 0;
  virtual std::set<std::shared_ptr<Register>> GetUse = 0;
  virtual std::set<std::shared_ptr<Register>> GetDef = 0;

};
