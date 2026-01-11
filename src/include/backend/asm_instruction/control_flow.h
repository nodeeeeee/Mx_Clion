//
// Created by zhangkai on 2026/1/10.
//

#pragma once
#include <utility>

#include "asm_instruction.h"
#include "backend/util/physical_register.h"

class BranchInstruction : public AsmInstruction {
public:
  enum Op {
    kBEQ, kBNE, kBLT, kBGE, kBLTU, kBGEU
  };
  BranchInstruction(Op op, PhysicalRegister rs, PhysicalRegister rt, std::variant<int, std::string> target_pos) : op_(op), rs_(rs), rt_(rt), target_pos_(std::move(target_pos)) {
  }
  std::string commit() {
    std::string ret;
    switch (op_) {
      case kBEQ:
        ret = "beq";
        break;
      case kBNE:
        ret = "bne";
        break;
      case kBLT:
        ret = "blt";
        break;
      case kBGE:
        ret = "bge";
        break;
      case kBLTU:
        ret = "bltu";
        break;
      case kBGEU:
        ret = "bgeu";
        break;
    }
    ret += " " + rs_.GetName() + ", " + rt_.GetName() + ", ";
    if (std::holds_alternative<int>(target_pos_)) {
      ret += std::to_string(std::get<int>(target_pos_));
    } else {
      ret += "L." + std::get<std::string>(target_pos_);
    }
    return ret;
  }
private:
  PhysicalRegister rs_;
  PhysicalRegister rt_;
  Op op_;
  std::variant<int, std::string> target_pos_; // block index
};

class JInstruction : public AsmInstruction {
public:
  JInstruction(std::string label) : label_(label) {}
  std::string commit() {
    return "j ." + label_;
  }
private:
  std::string label_;
};

class RetInstruction : public AsmInstruction {
  public:
  RetInstruction() = default;
  std::string commit() {
    return "ret";
  }
};