//
// Created by zhangkai on 2026/1/6.
//

#pragma once
#include "asm_instruction.h"
#include "backend/asm_generator.h"
#include "backend/util/physical_register.h"


class StoreInstruction : public AsmInstruction {
public:
  StoreInstruction(PhysicalRegister val_reg, PhysicalRegister base_reg, int offset) : val_reg_(val_reg), base_reg_(base_reg), offset_(offset) {}
  std::string commit() override {
    return "sw " + val_reg_.GetName() + ", " + std::to_string(offset_) + "(" + base_reg_.GetName() + ")";
  }
private:
  PhysicalRegister val_reg_;
  PhysicalRegister base_reg_;
  int offset_;
};

class LoadInstruction : public AsmInstruction {
public:
  LoadInstruction(PhysicalRegister dest_reg, PhysicalRegister base_reg, int offset) : dest_reg_(dest_reg), base_reg_(base_reg), offset_(offset) {}
  std::string commit() override {
      return "lw " + dest_reg_.GetName() + ", " + std::to_string(offset_) + "(" + base_reg_.GetName() + ")";
  }
private:
  PhysicalRegister dest_reg_;
  PhysicalRegister base_reg_;
  int offset_;
};

class LoadAddress : public AsmInstruction {
public:
  LoadAddress(PhysicalRegister dest_reg, std::shared_ptr<Register> ir_reg) : dest_reg_(dest_reg), ir_reg_(ir_reg) {
    assert(ir_reg->IsGlobal());
}
  std::string commit() override {
    return "la " + dest_reg_.GetName() + ", " + ir_reg_->GetName();
  }
private:
  PhysicalRegister dest_reg_;
  std::shared_ptr<Register> ir_reg_;
};