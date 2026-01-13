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
  std::string commit() override {
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
      ret += std::get<std::string>(target_pos_);
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
  JInstruction(std::string label) : label_(std::move(label)) {}
  std::string commit() override {
    return "j " + label_;
  }
private:
  std::string label_;
};

class RetInstruction : public AsmInstruction {
  public:
  RetInstruction() = default;
  std::string commit() override {
    return "ret";
  }
};

class CallInstruction : public AsmInstruction {
  public:
  CallInstruction(std::string func_name) : func_name_(std::move(func_name)) {
  }
  std::string commit() override {
    return "call " + func_name_;
  }
private:
  std::string func_name_;
};

class HelperBranchLabel : public AsmInstruction {
  public:
  HelperBranchLabel() : AsmInstruction() {
    label_num_ = label_count_++;
  }
  std::string commit() override {
    return ".L" + std::to_string(label_num_) + ":";
  }
  static int GetLabelCount() {
    return label_count_;
  }
private:
  int label_num_;
  inline static int label_count_ = 0;
};