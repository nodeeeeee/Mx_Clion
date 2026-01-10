//
// Created by zhangkai on 2026/1/6.
//

#pragma once
#include <utility>

#include "stmt/global_stmt.h"
#include "util/asm_function.h"
#include "util/class_type.h"
#include "util/ir_function.h"
#include "util/virtual_register.h"

#include <memory>

#include "backend/asm_instruction/asm_instruction.h"
#include "backend/stmt/call_stmt.h"
#include "backend/stmt/global_stmt.h"
#include "backend/util/ir_function.h"
#include "backend/util/physical_register.h"

class AsmGenerator {
public:
  AsmGenerator(std::vector<std::shared_ptr<IRFunction>> ir_funcs, std::vector<std::shared_ptr<GlobalStmt>> global_stmts, std::map<std::string, std::shared_ptr<ClassType>> class_types)
  : ir_funcs_(std::move(ir_funcs)), global_stmts_(std::move(global_stmts)), class_types_(std::move(class_types)) {
    Build();
  }

  void Build();

  void GlobalStmtTranslator();

  void ClassTypeTranslator();

  void ScanFunction(std::shared_ptr<IRFunction> ir_func);

  void BuildFunction(std::shared_ptr<ASMFunction> asm_func);

  void StoreRegister(std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> reg, PhysicalRegister src_reg);

  void LoadRegister(std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> reg, PhysicalRegister dest_reg);

  void BuildBlock(std::shared_ptr<Block> block);

  // void HandlePureImmd(BinaryStmt::BinaryOp op, int rs, int rt);

private:
  std::vector<std::shared_ptr<IRFunction>> ir_funcs_;
  std::vector<std::shared_ptr<GlobalStmt>> global_stmts_;
  std::map<std::string, std::shared_ptr<ClassType>> class_types_;
  std::vector<std::shared_ptr<ASMFunction>> asm_funcs_;
  std::shared_ptr<RegFrame> curr_reg_frame_;
  std::vector<std::shared_ptr<AsmInstruction>> asm_instructions_;
  std::shared_ptr<Block> curr_block_;
};
