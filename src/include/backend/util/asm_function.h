//
// Created by zhangkai on 2026/1/6.
//

#include "ir_function.h"

class ASMFunction {
public:
  ASMFunction(std::shared_ptr<IRFunction> ir_func) {
    func_name_ = ir_func->GetName();
    param_types_ = ir_func->ASMGetParamTypes();
    param_registers_ = ir_func->ASMGetParamReg();
    return_type_ = ir_func->GetReturnType();
    blocks_ = ir_func->GetBlocks();
    is_main_ = ir_func->ASMIsMain();
    belong_ = ir_func->GetBelong();
    in_class_ = ir_func->IsInClass();
    builtin_ = ir_func->is_builtin();
  }
  std::vector<std::shared_ptr<Block>> GetBlocks() {
    return blocks_;
  }
  std::string GetName() {
    return func_name_;
  }
  std::vector<std::shared_ptr<Register>> GetRegisters() {
    return param_registers_;
  }
  std::vector<std::shared_ptr<IRType>> GetParamTypes() {
    return param_types_;
  }
  std::shared_ptr<IRType> GetReturnType() {
    return return_type_;
  }
  bool IsInClass() {
    return in_class_;
  }
  bool IsBuiltin() {
    return builtin_;
  }
  bool IsMain() {
    return is_main_;
  }
  std::string GetBelong() {
    if (belong_.has_value()) {
      return belong_.value();
    }
    // assert(belong_.has_value());
    return "";
  }

  [[nodiscard]] int GetMaxArg() {
    return max_arg_;
  }

  void UpdateMaxArg(int max_arg) {
    max_arg_ = max_arg;
  }

private:
  std::string func_name_;
  // normal function: func_name
  // class funcs: <class_name>_<func_name>
  std::vector<std::shared_ptr<IRType>> param_types_;
  std::vector<std::shared_ptr<Register>> param_registers_; // to store param registers in advance
  std::shared_ptr<IRType> return_type_;
  std::vector<std::shared_ptr<Block>> blocks_;// the first one is entry block
  bool is_main_;
  std::optional<std::string> belong_;
  bool in_class_ = false; // if in class, it will automatically be assigned a first parameter as ptr
  bool builtin_ = false;
  int max_arg_;

};
