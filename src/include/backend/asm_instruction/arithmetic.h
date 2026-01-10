//
// Created by zhangkai on 2026/1/6.
//

#pragma once
#include "backend/util/physical_register.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/literal_node.h"

class RTypeInstruction : public AsmInstruction {
public:
  enum Op {
    kADD, kSUB, kMUL, kDIV, kMOD, kAND, kOR, kXOR, kSLL, kSRL, kSLT, kSLTU
  };
  RTypeInstruction(Op op, PhysicalRegister rd, PhysicalRegister rs, PhysicalRegister rt) : op_(op), rd_(rd), rs_(rs), rt_(rt) {}
  std::string commit() {
    std::string ret;
    switch (op_) {
      case kADD:
        ret += "add";
        break;
      case kSUB:
        ret += "sub";
        break;
        case kMUL:
        ret += "mul";
        break;
        case kDIV:
        ret += "div";
        break;
        case kMOD:
        ret += "rem";
        break;
        case kAND:
        ret += "and";
        break;
        case kOR:
        ret += "or";
        break;
        case kXOR:
        ret += "xor";
        break;
        case kSLL:
        ret += "sll";
        break;
        case kSRL:
        ret += "srl";
        break;
        case kSLT:
        ret += "slt";
        break;
        case kSLTU:
        ret += "sltu";
        break;
    }
    ret += " " + rd_.GetName() + " " + rs_.GetName() + " " + rt_.GetName();
    return ret;
  }
private:
  Op op_;
  PhysicalRegister rd_;
  PhysicalRegister rs_;
  PhysicalRegister rt_;
};

class ITypeInstruction : public AsmInstruction {
public:
  enum Op {
    kADDI, kXORI, kORI, kANDI, kSLLI, kSRLI, kSLTI, kSLTIU
  };
  ITypeInstruction(Op op, PhysicalRegister rd, PhysicalRegister rs, int rt) : op_(op), rd_(rd), rs_(rs), rt_(rt) {}
  std::string commit() {
    std::string ret;
    switch (op_) {
      case kADDI:
        ret += "addi";
        break;
      case kXORI:
        ret += "xori";
        break;
      case kORI:
        ret += "ori";
        break;
      case kANDI:
        ret += "andi";
        break;
      case kSLLI:
        ret += "slli";
        break;
      case kSRLI:
        ret += "srli";
        break;
      case kSLTI:
        ret += "slti";
        break;
      case kSLTIU:
        ret += "sltiu";
        break;
    }
    ret += " " + rd_.GetName() + " " + rs_.GetName() + " " + std::to_string(rt_);
    return ret;
  }
private:
  Op op_;
  PhysicalRegister rd_;
  PhysicalRegister rs_;
  int rt_;
};

class LoadImmediate : public AsmInstruction {
  public:
  enum Op {
    kLI
  };
  LoadImmediate(Op op, PhysicalRegister rd, int immd) : op_(op), rd_(rd), immd_(immd) {
  }
  std::string commit() {
    std::string ret;
    switch (op_) {
      case kLI:
        ret += "li";
        break;
    }
    ret += " " + rd_.GetName() + " " + std::to_string(immd_);
    return ret;
  }
private:
  Op op_;
  PhysicalRegister rd_;
  int immd_;
};

class CmpInstruction : public AsmInstruction {
  public:
  enum Op {
    kSEQZ, kSNEZ, kSLTZ, kSGTZ
  };
  CmpInstruction(Op op, PhysicalRegister rd, PhysicalRegister rs) : op_(op), rd_(rd), rs_(rs) {}
  std::string commit() {
    std::string ret;
    switch (op_) {
      case kSEQZ:
        ret += "seqz";
        break;
      case kSNEZ:
        ret += "snez";
        break;
      case kSLTZ:
        ret += "sltz";
        break;
      case kSGTZ:
        ret += "sgtz";
        break;
    }
    ret += " " + rd_.GetName() + " " + rs_.GetName();
    return ret;
  }
private:
  Op op_;
  PhysicalRegister rd_;
  PhysicalRegister rs_;
};