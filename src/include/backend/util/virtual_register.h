//
// Created by zhangkai on 2026/1/6.
//
#pragma once

#include "register.h"
#include "type/ir_type.h"

class VirtualRegister {
public:
  VirtualRegister(int len, int offset) : len_(len), offset_(offset + 4) {
  }

  [[nodiscard]] int GetLength() const {
    return len_;
  }
  [[nodiscard]] int GetOffset() const {
    return offset_;
  }

private:
  int len_;
  int offset_;


};

class RegFrame {
  public:
  RegFrame() = default;
  void CreateRegister(const std::shared_ptr<Register>& reg) {
    int reg_len;
    if (*reg->GetType() == *k_ir_bool) {
      // reg_len = 1;
      reg_len = 4;
    } else {
      reg_len = 4;
    }
    auto virt_reg = std::make_shared<VirtualRegister>(reg_len, offset_);
    int reg_num = reg->GetIndexNum();
    regs_.emplace(reg_num, virt_reg);
    offset_ += virt_reg->GetLength();
  }

  void CreateRegister(int reg_idx, const std::shared_ptr<IRType>& reg_type) {
    int reg_len;
    if (*reg_type == *k_ir_int) {
      reg_len = 4;
    } else {
      // reg_len = 1;
      reg_len = 4;
    }
    auto virt_reg = std::make_shared<VirtualRegister>(reg_len, offset_);
    assert(reg_len = 4);
    regs_.emplace(reg_idx, virt_reg);
    offset_ += reg_len;
  }

  void CreateRegister(const std::shared_ptr<Register>& reg, int offset) {
    assert(offset < 0);
    int reg_len;
    if (*reg->GetType() == *k_ir_bool) {
      reg_len = 4;
      // reg_len = 1;
    } else {
      reg_len = 4;
    }
    auto virt_reg = std::make_shared<VirtualRegister>(reg_len, offset);
    int reg_num = reg->GetIndexNum();
    regs_.emplace(reg_num, virt_reg);
  }

  void UpdateOffset(int n) {
    offset_ += n;
  }

  [[nodiscard]] int GetOffset() const {
    return offset_;
  }

  std::shared_ptr<VirtualRegister> FindVirtualRegister(const std::shared_ptr<Register>& reg) {
    int reg_num = reg->GetIndexNum();
    return regs_.at(reg_num);
  }

private:
  int offset_ = 0;
  std::unordered_map<int, std::shared_ptr<VirtualRegister>> regs_;
  const std::shared_ptr<IRType> k_ir_int = std::make_shared<IRType>(IRType::BasicType::kINT);
  const std::shared_ptr<IRType> k_ir_bool = std::make_shared<IRType>(IRType::BasicType::kBOOL);
};