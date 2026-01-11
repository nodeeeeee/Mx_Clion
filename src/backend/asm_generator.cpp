//
// Created by zhangkai on 2026/1/6.
//

#include "backend/asm_generator.h"

#include <syncstream>
#include <utility>

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


int FuncCallMaxArg(std::shared_ptr<ASMFunction> asm_func);
RTypeInstruction::Op StmtOpToRInstOp (BinaryStmt::BinaryOp op);
ITypeInstruction::Op StmtOpToIInstOp (BinaryStmt::BinaryOp op);
int HandlePureImmd(BinaryStmt::BinaryOp op, int rs, int rt);


void AsmGenerator::Build() {
  // ClassTypeTranslator();
  GlobalStmtTranslator();
  std::string func_str;
  for (const auto& func : ir_funcs_) {
    ScanFunction(func);
  }
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
  std::cout << "\t.section .bss\n\t.align 0" << std::endl;
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
  auto asm_func = std::make_shared<ASMFunction>(ir_func);
  asm_funcs_.emplace_back(asm_func);
}

void AsmGenerator::BuildFunction(std::shared_ptr<ASMFunction> asm_func) {
  // update sp
  // store ra
  // store s0/fp
  //
  int max_arg = FuncCallMaxArg(asm_func);
  curr_reg_frame_ = std::make_shared<RegFrame>();
  // if (max_arg != -1) {
  //   //store ra
  //   auto store_ra = std::make_shared<StoreInstruction>(ra, sp, 0);
  //   curr_reg_frame_->UpdateOffset(4);
  //   asm_instructions_.emplace_back(store_ra);
  // }
  for (auto& basic_block : asm_func->GetBlocks()) {
    curr_block_ = basic_block;
    BuildBlock(basic_block);
  }
  int frame_size = curr_reg_frame_->GetOffset() + max_arg * 4;
  std::cout << "addi sp, sp, -" + std::to_string(frame_size) << std::endl;
  if (max_arg != -1) {
    std::cout << "sw ra, " + std::to_string(frame_size - 4) + "(sp)" << std::endl;
    std::cout << "sw s0, " + std::to_string(frame_size - 8) + "(sp)" << std::endl;
    curr_reg_frame_->UpdateOffset(8);

  } else {
    std::cout << "sw s0, " + std::to_string(frame_size - 4) + "(sp)" << std::endl;
    curr_reg_frame_->UpdateOffset(4);
  }
  std::cout << "addi s0, sp, " + std::to_string(frame_size) << std::endl;
  //store first 8 params
  auto params = asm_func->GetParamTypes();
  for (int i = 0; i < std::min((int)params.size(), 8); i++) {
    curr_reg_frame_->CreateRegister((int)params.size() + i, params[i]);
    std::cout << "sw a" + std::to_string(i) + ", " + "-" + std::to_string(curr_reg_frame_->GetOffset()) << std::endl;
  }

  for (const auto& basic_block : asm_func->GetBlocks()) {
    std::cout << basic_block->getBlockName() << ": \n";
    std::cout << basic_block->GenerateAsmCode();
  }
  if (max_arg != -1) {
    std::cout << "lw ra, " + std::to_string(frame_size - 4) + "(sp)" << std::endl;
    std::cout << "lw s0, " + std::to_string(frame_size - 8) + "(sp)" << std::endl;
  } else {
    std::cout << "lw s0, " + std::to_string(frame_size - 4) + "(sp)" << std::endl;
  }
  std::cout << "addi sp, sp, " + std::to_string(frame_size) << std::endl;
  std::cout << "ret" << std::endl;


}

void AsmGenerator::BuildBlock(std::shared_ptr<Block> block) {
  for (auto stmt : block->GetStmts()) {
    if (auto alloca_stmt = std::dynamic_pointer_cast<AllocaStmt>(stmt)) {
      // no need to do anything, because we store every update into mem
      // create virt reg
      //
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
        auto li_inst = std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(2), result);
        StoreRegister(rd, t(2));
      }
    } else if (auto call_stmt = std::dynamic_pointer_cast<CallStmt>(stmt)) {
      auto args = call_stmt->GetParams();
      if (args.size() <= 8) {
        for (int i = 0; i < args.size(); i++) {
          if (std::get<int>(args[i]) || std::get<bool>(args[i]) || std::get<std::shared_ptr<LiteralNode>> (args[i])) {
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
      if (call_stmt->GetDestRegister() != nullptr) {
        // store back
        curr_reg_frame_->CreateRegister(call_stmt->GetDestRegister());
        StoreRegister(call_stmt->GetDestRegister(), t(0));
      }
    } else if (auto gep_stmt = std::dynamic_pointer_cast<GEPStmt>(stmt)) {
      auto dest_reg = gep_stmt->GetBasePtr();
      auto base_reg = gep_stmt->GetBasePtr();
      auto indices = gep_stmt->GetIndices();
      curr_reg_frame_->CreateRegister(base_reg);
      assert(indices.size() <= 2);
      auto base_reg_type = base_reg->GetType();
      if (base_reg_type->is_customized()) {
        int type_size = class_types_[base_reg_type->GetTypeName()]->GetClassSize();
        //first

        LoadRegister(base_reg, t(0));
        std::shared_ptr<AsmInstruction> first_add_instruction;
        if (std::holds_alternative<std::shared_ptr<Register>>(indices[0])) {
          LoadRegister(std::get<std::shared_ptr<Register>>(indices[0]), t(1));
          curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(2), type_size));
          curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kMUL, t(1), t(1), t(2)));
          curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kADD, t(2), t(0), t(1)));
        } else {
          auto base_val = std::make_shared<AsmRep>(base_reg)->GetRepVal();
          curr_block_->AddInstruction(std::make_shared<ITypeInstruction>(ITypeInstruction::Op::kADDI, t(2), t(0), base_val * type_size));
        }
        curr_reg_frame_->CreateRegister(dest_reg);
        StoreRegister(base_reg, t(2));
        //second
        std::shared_ptr<AsmInstruction> second_add_instruction;
        if (std::holds_alternative<std::shared_ptr<Register>>(indices[1])) {
          LoadRegister(std::get<std::shared_ptr<Register>>(indices[1]), t(1));
          curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kADD, t(2), t(2), t(1)));
        } else {
          auto base_val = std::make_shared<AsmRep>(base_reg)->GetRepVal();
          curr_block_->AddInstruction(std::make_shared<ITypeInstruction>(ITypeInstruction::Op::kADDI, t(2), t(2), base_val));
        }
        curr_reg_frame_->CreateRegister(dest_reg);
        StoreRegister(base_reg, t(2));
      } else {
        // pointer    gep ... , i32 0, i32 %10
        std::shared_ptr<AsmInstruction> add_instruction;
        assert(std::holds_alternative<int>(indices[0]) && std::get<int>(indices[0]) == 0);
        if (std::holds_alternative<std::shared_ptr<Register>>(indices[1])) {
          LoadRegister(std::get<std::shared_ptr<Register>>(indices[1]), t(1));
          curr_block_->AddInstruction(std::make_shared<RTypeInstruction>(RTypeInstruction::Op::kADD, t(2), t(0), t(1)));
        } else {
          auto base_val = std::make_shared<AsmRep>(base_reg)->GetRepVal();
          curr_block_->AddInstruction(std::make_shared<ITypeInstruction>(ITypeInstruction::Op::kADDI, t(2), t(0), base_val));
        }

        curr_reg_frame_->CreateRegister(dest_reg);
        StoreRegister(base_reg, t(2));
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
        curr_block_->AddInstruction(std::make_shared<ITypeInstruction>(ITypeInstruction::Op::kADDI, t(1), t(0), -rt_val));
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
            curr_block_->AddInstruction(std::make_shared<ITypeInstruction>(ITypeInstruction::Op::kXORI, t(2), t(2), 1));
            break;
          case IcmpStmt::IcmpOp::kBEQ:
            curr_block_->AddInstruction(std::make_shared<CmpInstruction>(CmpInstruction::Op::kSGTZ, t(2), t(1)));
            curr_block_->AddInstruction(std::make_shared<ITypeInstruction>(ITypeInstruction::Op::kXORI, t(2), t(2), 1));
            break;
        }
      }
      StoreRegister(rd, t(2));
    } else if (auto load_stmt = std::dynamic_pointer_cast<LoadStmt>(stmt)) {
      auto dest_reg = load_stmt->GetDestReg();
      auto addr_reg = load_stmt->GetAddrReg();
      curr_reg_frame_->CreateRegister(dest_reg);
      LoadRegister(addr_reg, t(0));
      curr_block_->AddInstruction(std::make_shared<LoadInstruction>(t(2), t(0), 0));
      StoreRegister(dest_reg, t(0));
    } else if (auto store_stmt = std::dynamic_pointer_cast<StoreStmt>(stmt)) {
      auto val_reg = store_stmt->GetValue();
      if (std::holds_alternative<std::shared_ptr<Register>>(val_reg)) {
        LoadRegister(val_reg, t(0));
      } else {
        int val = std::make_shared<AsmRep>(val_reg)->GetRepVal();
        curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(0), val));
      }
      LoadRegister(store_stmt->GetAddr(), t(2));
      curr_block_->AddInstruction(std::make_shared<StoreInstruction>(t(0), t(2), 0));
    } else if (auto br_conditional_stmt = std::dynamic_pointer_cast<BrConditionalStmt>(stmt)) {
      //beq
      //next line: j .?
      //next line: j .?
      auto true_label = br_conditional_stmt->GetTrueLabel();
      auto false_label = br_conditional_stmt->GetFalseLabel();
      auto cond_reg = br_conditional_stmt->GetBrReg();
      if (std::holds_alternative<std::shared_ptr<Register>>(cond_reg)) {
        LoadRegister(cond_reg, t(0));
      } else {
        auto cond_val = std::make_shared<AsmRep>(cond_reg)->GetRepVal();
        curr_block_->AddInstruction(std::make_shared<LoadImmediate>(LoadImmediate::Op::kLI, t(0), cond_val));
      }
      curr_block_->AddInstruction(std::make_shared<BranchInstruction>(BranchInstruction::Op::kBEQ, t(0), zero, 4));
      curr_block_->AddInstruction(std::make_shared<JInstruction>(true_label));
      curr_block_->AddInstruction(std::make_shared<JInstruction>(false_label));
    } else if (auto br_unconditional_stmt = std::dynamic_pointer_cast<BrUnconditionalStmt>(stmt)) {
      curr_block_->AddInstruction(std::make_shared<JInstruction>(br_unconditional_stmt->GetLabel()));
    }
    // else if (auto ret_stmt = std::dynamic_pointer_cast<ReturnStmt>(stmt)) {
    //   curr_block_->AddInstruction(std::make_shared<RetInstruction>());
    // }
  }
}


void AsmGenerator::StoreRegister(std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> reg, PhysicalRegister src_reg){
  // phy_reg -> int(virt_reg)
  if (std::holds_alternative<std::shared_ptr<Register>>(reg)) {
    auto virtual_reg = curr_reg_frame_->FindVirtualRegister(std::get<std::shared_ptr<Register>>(reg));
    auto store_instruction = std::make_shared<StoreInstruction>(src_reg, s(0), virtual_reg->GetOffset());
    curr_block_->AddInstruction(store_instruction);
  } else {
    throw std::runtime_error("must be a reg");
  }
}

void AsmGenerator::LoadRegister(std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> reg, PhysicalRegister dest_reg) {
  if (std::holds_alternative<std::shared_ptr<Register>>(reg)) {
    auto virtual_reg = curr_reg_frame_->FindVirtualRegister(std::get<std::shared_ptr<Register>>(reg));
    auto load_instruction = std::make_shared<LoadInstruction>(dest_reg, s(0), virtual_reg->GetOffset());
    curr_block_->AddInstruction(load_instruction);
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