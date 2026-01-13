//
// Created by zhangkai on 2026/1/11.
//

#pragma once
#include <cassert>
#include <utility>
#include <vector>

#include "asm_instruction.h"
//
// class GlobalInstruction : public std::enable_shared_from_this<GlobalInstruction>{
//   public:
//   GlobalInstruction() = default;
// };

class RodataInstruction : public AsmInstruction {
public:
  RodataInstruction(std::string name, int align, std::string str_const) : name_(std::move(name)), align_(align) {
    for (int i = 0; i < str_const.size(); i++) {
      if (str_const[i] == '\\' && str_const[i + 1] == '2' && str_const[i + 2] == '2') {
        str_const_ += "\\\"";
        i += 2;
      } else {
        str_const_ += str_const[i];
      }
    }
    assert(align == 0);
  };
  [[nodiscard]] std::string GetName() const {
    return name_;
  }
  [[nodiscard]] int GetAlign() const {
    return align_;
  }
  [[nodiscard]] std::string commit() override {
    // std::string ret;
    return name_ + ": \n\t" + ".asciz \"" + str_const_+ "\"";
  }
private:
  std::string name_;
  int align_;
  std::string str_const_;
};


class DataInstruction : public AsmInstruction {
public:
  DataInstruction(std::string name, int align, std::vector<int> init_vals) : name_(std::move(name)), align_(align), init_vals_(std::move(init_vals)) {
  };
  [[nodiscard]] std::string GetName() const {
    return name_;
  }
  [[nodiscard]] int GetAlign() const {
    return align_;
  }
  [[nodiscard]] std::string commit() override {
    std::string result = name_ + ": \n\t" + ".word ";
    bool is_first = true;
    for (auto val : init_vals_) {
      if (is_first) {
        is_first = false;
      } else {
        result += ", ";
      }
      result += std::to_string(val);
    }
    return result;
  }
private:
  std::string name_;
  int align_;
  std::vector<int> init_vals_;
};

class BssInstruction : public AsmInstruction {
public:
  BssInstruction(std::string name, int align) : name_(std::move(name)), align_(align) {
  };
  [[nodiscard]] std::string GetName() const {
    return name_;
  }
  [[nodiscard]] int GetAlign() const {
    return align_;
  }
  [[nodiscard]] std::string commit() override {
    return name_ + ": \n\t" +  ".zero 4";
  }
private:
  std::string name_;
  int align_;
};
