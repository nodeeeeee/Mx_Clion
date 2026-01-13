//
// Created by zhangkai on 2026/1/6.
//

#include "backend/asm_generator.h"

#include <cmath>
#include <syncstream>
#include <utility>

#include "backend/asm_instruction/arithmetic.h"
#include "backend/asm_instruction/arithmetic.h"
#include "backend/asm_instruction/control_flow.h"
#include "backend/asm_instruction/mem.h"
#include "backend/stmt/alloca_stmt.h"
#include "backend/stmt/gep_stmt.h"
#include "backend/stmt/icmp_stmt.h"
#include "backend/stmt/load_stmt.h"
#include "backend/stmt/store_stmt.h"
#include "backend/stmt/br_stmt/br_conditional_stmt.h"
#include "backend/util/asm_rep.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/binary_expr_node.h"


int FuncCallMaxArg(std::shared_ptr<ASMFunction> asm_func);
RTypeInstruction::Op StmtOpToRInstOp (BinaryStmt::BinaryOp op);
ITypeInstruction::Op StmtOpToIInstOp (BinaryStmt::BinaryOp op);
int HandlePureImmd(BinaryStmt::BinaryOp op, int rs, int rt);


void AsmGenerator::Build() {
  // ClassTypeTranslator();
  GlobalStmtTranslator();
  std::string func_str;
  for (const auto& func : ir_funcs_) {
    ScanFunction(func.second);
  }
  std::cout << std::endl;
  std::cout << ".section .text\n\t.align2\n" << std::endl;
  for (const auto& func : asm_funcs_) {
    BuildFunction(func);
  }
}

void AsmGenerator::GlobalStmtTranslator() {
  for (auto stmt : global_stmts_) {
    auto curr_instruction = stmt->ToInstruction();
    if (auto bss_instruction = std::dynamic_pointer_cast<BssInstruction>(curr_instruction)) {
      bss_.emplace_back(bss_instruction);
    } else if (auto rodata_instruction = std::dynamic_pointer_cast<RodataInstruction>(curr_instruction)) {
      rodata_.emplace_back(rodata_instruction);
    } else if (auto data_instruction = std::dynamic_pointer_cast<DataInstruction>(curr_instruction)) {
      data_.emplace_back(data_instruction);
    }
  }
  std::cout << "\t.section .rodata\n\t.align 2" << std::endl;
  for (auto rodata : rodata_) {
    std::cout << rodata->commit() << std::endl;
  }
  std::cout << "\t.section .data\n\t.align 2" << std::endl;
  for (auto data : data_) {
    std::cout << data->commit() << std::endl;
  }
  std::cout << "\t.section .bss\n\t.align 2" << std::endl;
  for (auto bss : bss_) {
    std::cout << bss->commit() << std::endl;
  }
}

// void AsmGenerator::ClassTypeTranslator() {
//
// }

void AsmGenerator::ScanFunction(std::shared_ptr<IRFunction> ir_func) {
  /** generate a ASMFunction and store into ASMGenerator
   */
  if (!ir_func->is_builtin()) {
    auto asm_func = std::make_shared<ASMFunction>(ir_func);
    asm_funcs_.emplace_back(asm_func);
  }

}

void AsmGenerator::BuildFunction(std::shared_ptr<ASMFunction> asm_func) {
  // update sp
  // store ra
  // store s0/fp
  //
  curr_function_ = asm_func;
  int max_arg = FuncCallMaxArg(asm_func);
  curr_function_->UpdateMaxArg(max_arg);
  curr_reg_frame_ = std::make_shared<RegFrame>();
  if (max_arg != -1) {
    curr_reg_frame_->UpdateOffset(8);
  } else {
    curr_reg_frame_->UpdateOffset(4);
  }
  for (auto& basic_block : asm_func->GetBlocks()) {
    curr_block_ = basic_block;
    BuildBlock(basic_block);
  }





  if (asm_func->IsMain()) {
    std::cout << ".globl main" << std::endl;
  }
  std::cout << asm_func->GetName() + ":" << std::endl;
  int frame_size = curr_reg_frame_->GetOffset() + max_arg * 4;
  frame_size = (int)std::ceil((double)frame_size / 16) * 16;
  bool out_of_bound = false;
  if (frame_size > 2047 || frame_size <= -2048) {
    out_of_bound = true;
    std::cout << "li t0, " + std::to_string(frame_size) << std::endl;
  }
  if (out_of_bound) {
    std::cout << "sub sp, sp, t0" << std::endl;
    if (max_arg != -1) {
      std::cout << "addi t1, t0, -4" << std::endl;
      std::cout << "add t1, t1, sp" << std::endl;
      std::cout << "sw ra, 0(t1)" << std::endl;
      std::cout << "addi t1, t1, -4" << std::endl;
      std::cout << "add t1, t1, sp" << std::endl;
      std::cout << "sw s0, 0(t1)" << std::endl;
      // curr_reg_frame_->UpdateOffset(8);
    } else {
      std::cout << "addi t1, t0, -4" << std::endl;
      std::cout << "add t1, t1, sp" << std::endl;
      std::cout << "sw s0, 0(t1)" << std::endl;
      // curr_reg_frame_->UpdateOffset(4);
    }
    std::cout << "add s0, sp, t0" << std::endl;
  } else {
    std::cout << "addi sp, sp, -" + std::to_string(frame_size) << std::endl;
    if (max_arg != -1) {
      std::cout << "sw ra, " + std::to_string(frame_size - 4) + "(sp)" << std::endl;
      std::cout << "sw s0, " + std::to_string(frame_size - 8) + "(sp)" << std::endl;
      // curr_reg_frame_->UpdateOffset(8);
    } else {
      std::cout << "sw s0, " + std::to_string(frame_size - 4) + "(sp)" << std::endl;
      // curr_reg_frame_->UpdateOffset(4);
    }
    std::cout << "addi s0, sp, " + std::to_string(frame_size) << std::endl;
  }
  //store first 8 params
  // auto params = asm_func->GetParamTypes();
  // for (int i = 0; i < std::min((int)params.size(), 8); i++) {
  //   curr_reg_frame_->CreateRegister((int)params.size() + i, params[i]);
  //   int offset = curr_reg_frame_->GetOffset();
  //   if (offset > 2047 || offset <= -2048) {
  //     std::cout << "li t0, " + std::to_string(-offset);
  //     std::cout << "sw a" + std::to_string(i) + ", t0(s0)" << std::endl;
  //   } else {
  //     std::cout << "sw a" + std::to_string(i) + ", " + "-" + std::to_string(curr_reg_frame_->GetOffset()) + "(s0)"<< std::endl;
  //   }
  // }

  // for (const auto& basic_block : asm_func->GetBlocks()) {
  //   auto stmt = basic_block->GetStmts().back();
  //   if (auto return_stmt = std::dynamic_pointer_cast<ReturnStmt>(stmt)) {
  //     auto return_rep = return_stmt->GetRetVal();
  //     if (std::holds_alternative<std::shared_ptr<Register>>(return_rep)) {
  //       auto return_reg = std::get<std::shared_ptr<Register>>(return_rep);
  //       auto virtual_reg = curr_reg_frame_->FindVirtualRegister(return_reg);
  //       // LoadRegister(std::get<std::shared_ptr<Register>>(return_rep), a(0));
  //       basic_block->AddInstruction(std::make_shared<LoadInstruction>(a(0), s(0), -virtual_reg->GetOffset()));
  //     } else {
  //       int ret_val = std::make_shared<AsmRep>(return_rep)->GetRepVal();
  //       basic_block->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, a(0), ret_val));
  //     }
  //
  //     if (out_of_bound) {
  //       if (max_arg != -1) {
  //         basic_block->AddInstruction(std::make_shared<ITypeInstruction>(ITypeInstruction::Op::kADDI, t(1), t(0), -4));
  //         // std::cout << "sub t1, t0, 4" << std::endl;
  //         basic_block->AddInstruction(std::make_shared<LoadInstruction>(ra, t(0), sp));
  //         // std::cout << "lw ra, t0(sp)" << std::endl;
  //         basic_block->AddInstruction(std::make_shared<ITypeInstruction>(ITypeInstruction::Op::kADDI, t(1), t(1), -4));
  //         std::cout << "sub t1, t1, 4" << std::endl;
  //         std::cout << "lw s0, t1(sp)" << std::endl;
  //       } else {
  //         std::cout << "sub t1, t0, 4" << std::endl;
  //         std::cout << "lw s0, t1(sp)" << std::endl;
  //       }
  //       std::cout << "addi sp, sp, t0" << std::endl;
  //     } else {
  //       if (max_arg != -1) {
  //         std::cout << "lw ra, " + std::to_string(frame_size - 4) + "(sp)" << std::endl;
  //         std::cout << "lw s0, " + std::to_string(frame_size - 8) + "(sp)" << std::endl;
  //       } else {
  //         std::cout << "lw s0, " + std::to_string(frame_size - 4) + "(sp)" << std::endl;
  //       }
  //       std::cout << "addi sp, sp, " + std::to_string(frame_size) << std::endl;
  //     }
  //     std::cout << "ret" << std::endl;
  //
  //
  //   }
  // }



  for (const auto& basic_block : asm_func->GetBlocks()) {
    std::cout << curr_function_->GetName() + "_" + basic_block->getBlockName() << ": \n";
    std::cout << basic_block->GenerateAsmCode();
  }






}

void AsmGenerator::BuildBlock(std::shared_ptr<Block> block) {
  for (auto stmt : block->GetStmts()) {
    if (auto alloca_stmt = std::dynamic_pointer_cast<AllocaStmt>(stmt)) {
      // no need to do anything, because we store every update into mem
      // create virt reg
      //
      if (alloca_stmt->GetReg()->GetIndexNum() < curr_function_->GetParamTypes().size()) {
        //handled elsewhere
        continue;
      }
      curr_reg_frame_->CreateRegister(alloca_stmt->GetReg());
      curr_reg_frame_->UpdateOffset(4);
      ITypeHandler(ITypeInstruction::kADDI, t(2), s(0), -curr_reg_frame_->GetOffset());
      StoreRegister(alloca_stmt->GetReg(), t(2));
    } else if (auto binary_stmt = std::dynamic_pointer_cast<BinaryStmt>(stmt)) {
      auto rd = binary_stmt->GetDest();
      auto rs = binary_stmt->GetLhs();
      auto rt = binary_stmt->GetRhs();
      auto op = binary_stmt->GetOp();
      curr_reg_frame_->CreateRegister(rd);
      if (std::holds_alternative<std::shared_ptr<Register>>(rs) && std::holds_alternative<std::shared_ptr<Register>>(rt)) {
        LoadRegister(rs, t(0));
        LoadRegister(rt, t(1));
        curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(StmtOpToRInstOp(op), t(2), t(0), t(1)));
        StoreRegister(rd, t(2));
      } else if (std::holds_alternative<std::shared_ptr<Register>>(rs)) {
        LoadRegister(rs, t(0));
        int rt_rep = std::make_shared<AsmRep>(rt)->GetRepVal();
        if (op != BinaryStmt::BinaryOp::kDIV && op != BinaryStmt::BinaryOp::kMOD && op != BinaryStmt::BinaryOp::kMUL && op != BinaryStmt::BinaryOp::kSUB && rt_rep <= 2047 && rt_rep >= -2048) {
          curr_block_->AddInstruction(std::make_shared<ITypeInstruction>(StmtOpToIInstOp(op), t(2), t(0), rt_rep));
        } else if (op == BinaryStmt::BinaryOp::kSUB && rt_rep <= 2047 && rt_rep >= -2048) {
          curr_block_->AddInstruction(std::make_shared<ITypeInstruction>(ITypeInstruction::Op::kADDI, t(2), t(0), -rt_rep));
        } else {
          curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(1), rt_rep));
          curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(StmtOpToRInstOp(op), t(2), t(0), t(1)));
        }
        StoreRegister(rd, t(2));
      } else if (std::holds_alternative<std::shared_ptr<Register>>(rt)) {
        int rs_val = std::make_shared<AsmRep>(rs)->GetRepVal();
        curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(0), rs_val));
        LoadRegister(rt, t(1));
        curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(StmtOpToRInstOp(op), t(2), t(0), t(1)));
        StoreRegister(rd, t(2));
      }
      else { // both are immediate
        int rs_rep = std::make_shared<AsmRep>(rs)->GetRepVal();
        int rt_rep = std::make_shared<AsmRep>(rt)->GetRepVal();
        int result = HandlePureImmd(op, rs_rep, rt_rep);
        curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(2), result));
        StoreRegister(rd, t(2));
      }
    } else if (auto call_stmt = std::dynamic_pointer_cast<CallStmt>(stmt)) {
      auto args = call_stmt->GetParams();
      if (args.size() <= 8) {
        for (int i = 0; i < args.size(); i++) {
          if (std::holds_alternative<int>(args[i]) || std::holds_alternative<bool>(args[i]) || std::holds_alternative<std::shared_ptr<LiteralNode>> (args[i])) {
            auto asm_arg = std::make_shared<AsmRep>(args[i])->GetRepVal();
            curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, a(i), asm_arg));
          } else {
            LoadRegister(std::get<std::shared_ptr<Register>>(args[i]), a(i));
          }
        }
      } else {
        for (int i = 0; i < 8; i++) {
          if (std::get<int>(args[i]) || std::get<bool>(args[i]) || std::get<std::shared_ptr<LiteralNode>> (args[i])) {
            auto asm_arg = std::make_shared<AsmRep>(args[i])->GetRepVal();
            curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, a(i), asm_arg));
          } else {
            LoadRegister(std::get<std::shared_ptr<Register>>(args[i]), a(i));
          }
        }
        // the rest are stored at the top of the stack, we can use sp
        for (int i = 8; i < args.size(); i++) {
          if (std::holds_alternative<std::shared_ptr<Register>>(args[i])) {
            // virt_reg -> int(phy_reg)
            LoadRegister(std::get<std::shared_ptr<Register>>(args[i]), t(0));
            curr_block_->AddInstruction(std::make_shared<StoreInstruction>(t(0), sp, (i - 8) * 4));
          } else {
            auto asm_arg = std::make_shared<AsmRep>(args[i])->GetRepVal();
            curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(0), asm_arg));
            curr_block_->AddInstruction(std::make_shared<StoreInstruction>(t(0), sp, (i - 8) * 4));
          }
        }
      }
      curr_block_->AddInstruction(std::make_shared<CallInstruction>(call_stmt->GetFunc()->GetName()));
      if (call_stmt->GetDestRegister() != nullptr) {
        // store back
        curr_reg_frame_->CreateRegister(call_stmt->GetDestRegister());
        StoreRegister(call_stmt->GetDestRegister(), a(0));
      }
    } else if (auto gep_stmt = std::dynamic_pointer_cast<GEPStmt>(stmt)) {
      // here we assume every var takes 4 bytes

      auto dest_reg = gep_stmt->GetDestPtr();
      auto base_reg = gep_stmt->GetBasePtr();
      auto indices = gep_stmt->GetIndices();
      curr_reg_frame_->CreateRegister(dest_reg);
      assert(indices.size() <= 2);
      auto base_reg_type = base_reg->GetType();
      if (base_reg_type->is_customized() && indices.size() == 2) {
        int type_size = class_types_[base_reg_type->GetTypeName()]->GetClassSize() * 4;
        //first

        LoadRegister(base_reg, t(0));
        std::shared_ptr<AsmInstruction> first_add_instruction;
        if (std::holds_alternative<std::shared_ptr<Register>>(indices[0])) {
          LoadRegister(std::get<std::shared_ptr<Register>>(indices[0]), t(1));
          curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(2), type_size));
          curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kMUL, t(1), t(1), t(2)));
          curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kADD, t(2), t(0), t(1)));
        } else {
          auto index_val = std::make_shared<AsmRep>(indices[0])->GetRepVal();
          ITypeHandler(ITypeInstruction::Op::kADDI, t(0), t(0), index_val * type_size);
        }
        // curr_reg_frame_->CreateRegister(dest_reg);
        // StoreRegister(base_reg, t(1));
        //second
        std::shared_ptr<AsmInstruction> second_add_instruction;
        if (std::holds_alternative<std::shared_ptr<Register>>(indices[1])) {
          LoadRegister(std::get<std::shared_ptr<Register>>(indices[1]), t(1));
          curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(2), 4));
          curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kMUL, t(2), t(2), t(1)));
          curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kADD, t(2), t(2), t(0)));
        } else {
          auto index_val = std::make_shared<AsmRep>(indices[1])->GetRepVal() * 4;
          ITypeHandler(ITypeInstruction::Op::kADDI, t(2), t(0), index_val);
        }
        // curr_reg_frame_->CreateRegister(dest_reg);
        StoreRegister(dest_reg, t(2));
      } else {
        // pointer    gep ... , i32 0, i32 %10
        std::shared_ptr<AsmInstruction> add_instruction;
        LoadRegister(base_reg, t(0));
        // assert(std::holds_alternative<int>(indices[0]) && std::get<int>(indices[0]) == 0);
        if (std::holds_alternative<std::shared_ptr<Register>>(indices[0])) {
          LoadRegister(std::get<std::shared_ptr<Register>>(indices[0]), t(1));
          curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(2), 4));
          curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kMUL, t(1), t(1), t(2)));
          curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kADD, t(2), t(0), t(1)));
        } else {
          auto index_val = std::make_shared<AsmRep>(indices[0])->GetRepVal() * 4;
          ITypeHandler(ITypeInstruction::Op::kADDI, t(2), t(0), index_val);
        }
        StoreRegister(dest_reg, t(2));
      }
    } else if (auto icmp_stmt = std::dynamic_pointer_cast<IcmpStmt>(stmt)) {
      auto op = icmp_stmt->GetOp();
      auto rd = icmp_stmt->GetDestReg();
      curr_reg_frame_->CreateRegister(rd);
      auto rs = icmp_stmt->GetLhs();
      auto rt = icmp_stmt->GetRhs();
      if (std::holds_alternative<std::shared_ptr<Register>>(rs) && std::holds_alternative<std::shared_ptr<Register>>(rt)) {
        LoadRegister(rs, t(0));
        LoadRegister(rt, t(1));
        curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kSUB, t(1), t(0), t(1)));
      } else if (std::holds_alternative<std::shared_ptr<Register>>(rs)) {
        auto rt_val = std::make_shared<AsmRep>(rt)->GetRepVal();
        LoadRegister(rs, t(0));
        ITypeHandler(ITypeInstruction::Op::kADDI, t(1), t(0), -rt_val);
      } else if (std::holds_alternative<std::shared_ptr<Register>>(rt)) {
        auto rs_val = std::make_shared<AsmRep>(rs)->GetRepVal();
        LoadRegister(rt, t(1));
        curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(0), rs_val));
        curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kSUB, t(1), t(0), t(1)));
      } else {
        auto rs_val = std::make_shared<AsmRep>(rs)->GetRepVal();
        auto rt_val = std::make_shared<AsmRep>(rt)->GetRepVal();
        switch (op) {
          case IcmpStmt::IcmpOp::kET:
            curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(2), (rs_val == rt_val)));
            break;
          case IcmpStmt::IcmpOp::kNET:
            curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(2), (rs_val != rt_val)));
            break;
          case IcmpStmt::IcmpOp::kBT:
            curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(2), (rs_val > rt_val)));
            break;
          case IcmpStmt::IcmpOp::kLT:
            curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(2), (rs_val < rt_val)));
            break;
          case IcmpStmt::IcmpOp::kBEQ:
            curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(2), (rs_val >= rt_val)));
            break;
          case IcmpStmt::IcmpOp::kLEQ:
            curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(2), (rs_val <= rt_val)));
            break;
        }
      }
      if (std::holds_alternative<std::shared_ptr<Register>>(rs) || std::holds_alternative<std::shared_ptr<Register>>(rt)) {
        switch (op) {
          case IcmpStmt::IcmpOp::kET:
            curr_block_->AddInstruction(std::make_shared<CmpInstruction>(CmpInstruction::Op::kSEQZ, t(2), t(1)));
            break;
          case IcmpStmt::IcmpOp::kNET:
            curr_block_->AddInstruction(std::make_shared<CmpInstruction>(CmpInstruction::Op::kSNEZ, t(2), t(1)));
            break;
          case IcmpStmt::IcmpOp::kBT:
            curr_block_->AddInstruction(std::make_shared<CmpInstruction>(CmpInstruction::Op::kSGTZ, t(2), t(1)));
            break;
          case IcmpStmt::IcmpOp::kLT:
            curr_block_->AddInstruction(std::make_shared<CmpInstruction>(CmpInstruction::Op::kSLTZ, t(2), t(1)));
            break;
          case IcmpStmt::IcmpOp::kLEQ: // t0 <= t1
            curr_block_->AddInstruction(std::make_shared<CmpInstruction>(CmpInstruction::Op::kSGTZ, t(2), t(1)));
            ITypeHandler(ITypeInstruction::Op::kXORI, t(2), t(2), 1);
            break;
          case IcmpStmt::IcmpOp::kBEQ:
            curr_block_->AddInstruction(std::make_shared<CmpInstruction>(CmpInstruction::Op::kSLTZ, t(2), t(1)));
            ITypeHandler(ITypeInstruction::Op::kXORI, t(2), t(2), 1);
            break;
        }
      }
      StoreRegister(rd, t(2));
    } else if (auto load_stmt = std::dynamic_pointer_cast<LoadStmt>(stmt)) {
      auto dest_reg = load_stmt->GetDestReg();
      auto addr_reg = load_stmt->GetAddrReg();
      curr_reg_frame_->CreateRegister(dest_reg);
      LoadRegister(addr_reg, t(0), true);
      curr_block_->AddInstruction(std::make_shared<LoadInstruction>(t(2), t(0), 0));
      StoreRegister(dest_reg, t(2));
    }
    else if (auto store_stmt = std::dynamic_pointer_cast<StoreStmt>(stmt)) {
      auto addr_reg = store_stmt->GetAddr();
      auto val_reg = store_stmt->GetValue();
      int param_num = curr_function_->GetParamTypes().size();

      if (std::holds_alternative<std::shared_ptr<Register>>(val_reg) && !std::get<std::shared_ptr<Register>>(val_reg)->IsGlobal()
        && std::get<std::shared_ptr<Register>>(val_reg)->GetIndexNum() >= 0 && std::get<std::shared_ptr<Register>>(val_reg)->GetIndexNum() <param_num) {
        // this is used for loading parameter
        auto params = curr_function_->GetParamTypes();
        int addr_reg_idx = addr_reg->GetIndexNum();
        if (addr_reg_idx < param_num + 8) {
          curr_reg_frame_->CreateRegister((int)params.size() + addr_reg_idx - param_num, params[addr_reg_idx - param_num]);
          // int offset = curr_reg_frame_->FindVirtualRegister(addr_reg)->GetOffset();
          // if (offset > 2047 || offset <= -2048) {
          //   curr_block_->AddInstruction(std::make_shared<ITypeInstruction>(ITypeInstruction::Op::kADDI, t(0), s(0), -offset));
          //   // std::cout << "li t0, " + std::to_string(-offset);
          //   curr_block_->AddInstruction(std::make_shared<StoreInstruction>(a(addr_reg_idx - param_num), t(0), 0));
          //   // std::cout << "sw a" + std::to_string(addr_reg_idx - param_num) + ", t0(s0)" << std::endl;
          // } else {
            LoadRegister(addr_reg, t(0));
            curr_block_->AddInstruction(std::make_shared<StoreInstruction>(a(addr_reg_idx - param_num), t(0), 0));
            // std::cout << "sw a" + std::to_string(addr_reg_idx - param_num) + ", " + "-" + std::to_string(curr_reg_frame_->GetOffset()) + "(s0)"<< std::endl;
          // }
        }
        continue;
      }
      if (std::holds_alternative<std::shared_ptr<Register>>(val_reg)) {
        LoadRegister(val_reg, t(0));
      } else {
        int val = std::make_shared<AsmRep>(val_reg)->GetRepVal();
        curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(0), val));
      }
      LoadRegister(addr_reg, t(2), true);

      curr_block_->AddInstruction(std::make_shared<StoreInstruction>(t(0), t(2), 0));
    }
    else if (auto br_conditional_stmt = std::dynamic_pointer_cast<BrConditionalStmt>(stmt)) {
      //beq
      //next line: j ?
      //next line: j ?
      auto true_label = br_conditional_stmt->GetTrueLabel();
      auto false_label = br_conditional_stmt->GetFalseLabel();
      auto cond_reg = br_conditional_stmt->GetBrReg();
      if (std::holds_alternative<std::shared_ptr<Register>>(cond_reg)) {
        LoadRegister(cond_reg, t(0));
      } else {
        auto cond_val = std::make_shared<AsmRep>(cond_reg)->GetRepVal();
        curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(0), cond_val));
      }
      curr_block_->AddInstruction(std::make_shared<BranchInstruction>(BranchInstruction::Op::kBEQ, t(0), zero, ".L" + std::to_string(HelperBranchLabel::GetLabelCount())));
      curr_block_->AddInstruction(std::make_shared<JInstruction>(curr_function_->GetName() + "_" + true_label));
      curr_block_->AddInstruction(std::make_shared<HelperBranchLabel>());
      curr_block_->AddInstruction(std::make_shared<JInstruction>(curr_function_->GetName() + "_" + false_label));
    } else if (auto br_unconditional_stmt = std::dynamic_pointer_cast<BrUnconditionalStmt>(stmt)) {
      curr_block_->AddInstruction(std::make_shared<JInstruction>(curr_function_->GetName() + "_" + br_unconditional_stmt->GetLabel()));
    }
    else if (auto ret_stmt = std::dynamic_pointer_cast<ReturnStmt>(stmt)) {
      // curr_block_->AddInstruction(std::make_shared<RetInstruction>());
      auto return_rep = ret_stmt->GetRetVal();
      if (std::holds_alternative<std::shared_ptr<Register>>(return_rep)) {
        auto return_reg = std::get<std::shared_ptr<Register>>(return_rep);
        auto virtual_reg = curr_reg_frame_->FindVirtualRegister(return_reg);
        // LoadRegister(std::get<std::shared_ptr<Register>>(return_rep), a(0));
        curr_block_->AddInstruction(std::make_shared<LoadInstruction>(a(0), s(0), -virtual_reg->GetOffset()));
      } else {
        int ret_val = std::make_shared<AsmRep>(return_rep)->GetRepVal();
        curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, a(0), ret_val));
      }
      ITypeHandler(ITypeInstruction::Op::kADDI, sp, s(0), 0);
      if (curr_function_->GetMaxArg() != -1) {
        curr_block_->AddInstruction(std::make_shared<LoadInstruction>(ra, s(0), -4));
        curr_block_->AddInstruction(std::make_shared<LoadInstruction>(s(0), s(0), -8));
      } else {
        curr_block_->AddInstruction(std::make_shared<LoadInstruction>(s(0), s(0), -4));
      }
      curr_block_->AddInstruction(std::make_shared<RetInstruction>());

    }
  }
}


void AsmGenerator::StoreRegister(std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> reg, PhysicalRegister src_reg) {
  // phy_reg -> int(virt_reg)
  if (std::holds_alternative<std::shared_ptr<Register>>(reg)) {
    auto ir_reg = std::get<std::shared_ptr<Register>>(reg);
    if (ir_reg->IsGlobal()) {
      if (ir_reg->GetType()->is_customized() || *ir_reg->GetType() == *k_ir_string) {
        curr_block_->AddInstruction(std::make_shared<LoadAddress>(src_reg, ir_reg));
      } else {
        curr_block_->AddInstruction(std::make_shared<LoadAddress>(t(1), ir_reg));
        curr_block_->AddInstruction(std::make_shared<StoreInstruction>(src_reg, t(1), 0));
      }
    } else {
      auto virtual_reg = curr_reg_frame_->FindVirtualRegister(std::get<std::shared_ptr<Register>>(reg));
      if (virtual_reg->GetOffset() > 2047 || virtual_reg->GetOffset() < -2048) {
        curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(1), -virtual_reg->GetOffset()));
        curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kADD, t(1), t(1), s(0)));
        curr_block_->AddInstruction(std::make_shared<StoreInstruction>(src_reg, t(1), 0));
      } else {
        curr_block_->AddInstruction(std::make_shared<StoreInstruction>(src_reg, s(0), -virtual_reg->GetOffset()));
      }
    }
  } else {
    throw std::runtime_error("must be a reg");
  }
}

void AsmGenerator::LoadRegister(std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> reg, PhysicalRegister dest_reg, bool is_addr) {
  if (std::holds_alternative<std::shared_ptr<Register>>(reg)) {
    auto ir_reg = std::get<std::shared_ptr<Register>>(reg);
    if (ir_reg->IsGlobal()) {
      if (ir_reg->GetType()->is_customized() || *ir_reg->GetType() == *k_ir_string || is_addr) {
        curr_block_->AddInstruction(std::make_shared<LoadAddress>(dest_reg, ir_reg));
      } else {
        curr_block_->AddInstruction(std::make_shared<LoadAddress>(t(1), ir_reg));
        curr_block_->AddInstruction(std::make_shared<LoadInstruction>(dest_reg, t(1), 0));
      }
    } else {
      auto virtual_reg = curr_reg_frame_->FindVirtualRegister(std::get<std::shared_ptr<Register>>(reg));
      // if (is_addr) {
      //   curr_block_->AddInstruction(std::make_shared<ITypeInstruction>(ITypeInstruction::Op::kADDI, dest_reg, s(0), -virtual_reg->GetOffset()));
      // } else {
      if (virtual_reg->GetOffset() > 2047 || virtual_reg->GetOffset() < -2048) {
        curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(1), -virtual_reg->GetOffset()));
        curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kADD, t(1), t(1), s(0)));
        curr_block_->AddInstruction(std::make_shared<LoadInstruction>(dest_reg, t(1), 0));
      } else {
        curr_block_->AddInstruction(std::make_shared<LoadInstruction>(dest_reg, s(0), -virtual_reg->GetOffset()));
      }
      // }

    }



  } else {
    throw std::runtime_error("must be a reg");
  }
}

int FuncCallMaxArg(std::shared_ptr<ASMFunction> asm_func) {
  int max_arg = -1;
  auto basic_blocks = asm_func->GetBlocks();
  for (auto basic_block : basic_blocks) {
    for (auto &stmt: basic_block->GetStmts()) {
      if (auto call_stmt = std::dynamic_pointer_cast<CallStmt>(stmt)) {
        max_arg = std::max(max_arg, (int)call_stmt->GetParams().size());
      }
    }
  }
  return max_arg;
}

RTypeInstruction::Op StmtOpToRInstOp (BinaryStmt::BinaryOp op) {
  switch (op) {
    case BinaryStmt::BinaryOp::kADD:
      return RTypeInstruction::Op::kADD;
    case BinaryStmt::BinaryOp::kSUB:
      return RTypeInstruction::Op::kSUB;
    case BinaryStmt::BinaryOp::kAND:
      return RTypeInstruction::Op::kAND;
    case BinaryStmt::BinaryOp::kDIV:
      return RTypeInstruction::Op::kDIV;
    case BinaryStmt::BinaryOp::kMUL:
      return RTypeInstruction::Op::kMUL;
    case BinaryStmt::BinaryOp::kMOD:
      return RTypeInstruction::Op::kMOD;
    case BinaryStmt::BinaryOp::kOR:
      return RTypeInstruction::Op::kOR;
    case BinaryStmt::BinaryOp::kXOR:
      return RTypeInstruction::Op::kXOR;
    case BinaryStmt::BinaryOp::kSLL:
      return RTypeInstruction::Op::kSLL;
    case BinaryStmt::BinaryOp::kSRL:
      return RTypeInstruction::Op::kSRL;
  }
}
ITypeInstruction::Op StmtOpToIInstOp (BinaryStmt::BinaryOp op) {
  switch (op) {
    case BinaryStmt::BinaryOp::kADD:
      return ITypeInstruction::Op::kADDI;
    case BinaryStmt::BinaryOp::kSUB:
      throw std::runtime_error("i-type inst cannot handle sub");
    case BinaryStmt::BinaryOp::kAND:
      return ITypeInstruction::Op::kANDI;
    case BinaryStmt::BinaryOp::kDIV:
      throw std::runtime_error("i-type inst cannot handle div");
    case BinaryStmt::BinaryOp::kMUL:
      throw std::runtime_error("i-type inst cannot handle mul");
    case BinaryStmt::BinaryOp::kMOD:
      throw std::runtime_error("i-type inst cannot handle mod");
    case BinaryStmt::BinaryOp::kOR:
      return ITypeInstruction::Op::kORI;
    case BinaryStmt::BinaryOp::kXOR:
      return ITypeInstruction::Op::kXORI;
    case BinaryStmt::BinaryOp::kSLL:
      return ITypeInstruction::Op::kSLLI;
    case BinaryStmt::BinaryOp::kSRL:
      return ITypeInstruction::Op::kSRLI;
  }
}

int HandlePureImmd(BinaryStmt::BinaryOp op, int rs, int rt) {
  switch (op) {
    case BinaryStmt::BinaryOp::kADD:
      return rs + rt;
    case BinaryStmt::BinaryOp::kSUB:
      return rs - rt;
    case BinaryStmt::BinaryOp::kAND:
      return rs & rt;
    case BinaryStmt::BinaryOp::kDIV:
      return rs / rt;
    case BinaryStmt::BinaryOp::kMUL:
      return rs * rt;
    case BinaryStmt::BinaryOp::kMOD:
      return rs % rt;
    case BinaryStmt::BinaryOp::kOR:
      return rs | rt;
    case BinaryStmt::BinaryOp::kXOR:
      return rs ^ rt;
    case BinaryStmt::BinaryOp::kSLL:
      return rs << rt;
    case BinaryStmt::BinaryOp::kSRL:
      return rs >> rt;
  }
}

void AsmGenerator::ITypeHandler(ITypeInstruction::Op op, PhysicalRegister rd, PhysicalRegister rs, int rt) {
  RTypeInstruction::Op r_type_op;
  switch (op) {
    case ITypeInstruction::kADDI:
      r_type_op = RTypeInstruction::Op::kADD;
      break;
    case ITypeInstruction::kANDI:
      r_type_op = RTypeInstruction::Op::kAND;
      break;
    case ITypeInstruction::kORI:
      r_type_op = RTypeInstruction::Op::kOR;
      break;
    case ITypeInstruction::kXORI:
      r_type_op = RTypeInstruction::Op::kXOR;
      break;
    case ITypeInstruction::kSLLI:
      r_type_op = RTypeInstruction::Op::kSLL;
      break;
    case ITypeInstruction::kSRLI:
      r_type_op = RTypeInstruction::Op::kSRL;
      break;
    case ITypeInstruction::kSLTI:
      r_type_op = RTypeInstruction::Op::kSLT;
      break;
    case ITypeInstruction::kSLTIU:
      r_type_op = RTypeInstruction::Op::kSLT;
  }
  if (rt > 2047 || rt < -2048) {
    curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(1), rt));
    curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(r_type_op, rd, rs, t(1)));
  } else {
    curr_block_->AddInstruction(std::make_shared<ITypeInstruction>(op, rd, rs, rt));
  }
}
