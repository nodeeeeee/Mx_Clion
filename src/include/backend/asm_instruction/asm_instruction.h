//
// Created by zhangkai on 2026/1/6.
//

#pragma once
#include <string>

class AsmInstruction {
  public:
  AsmInstruction() = default;

  virtual ~AsmInstruction() = default;
  virtual std::string commit();
};
