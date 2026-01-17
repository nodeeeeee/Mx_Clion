#include "backend/ir_generator.h"

#include "backend/stmt/alloca_stmt.h"
#include "backend/stmt/binary_stmt.h"
#include "backend/stmt/call_stmt.h"
#include "backend/stmt/gep_stmt.h"
#include "backend/stmt/global_stmt.h"
#include "backend/stmt/icmp_stmt.h"
#include "backend/stmt/load_stmt.h"
#include "backend/stmt/store_stmt.h"
#include "backend/stmt/br_stmt/br_conditional_stmt.h"
#include "backend/stmt/br_stmt/br_unconditional_stmt.h"
#include "backend/stmt/br_stmt/ret_stmt.h"
#include "frontend/ast/stat_node/def_node/func_def_node.h"
#include "frontend/ast/stat_node/def_node/main_func_node.h"
#include "frontend/ast/stat_node/def_node/var_def_node.h"
#include "frontend/ast/stat_node/regular_stat_node/assign_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/block_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/for_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/if_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/return_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/while_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/array_const_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/binary_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/dot_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/format_string_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/func_call_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/index_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/init_object_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/paren_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/ternary_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/this_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/unary_expr_node.h"
#include "frontend/ast/terminal_node/terminal_node.h"


void IRGenerator::visit(std::shared_ptr<RootNode> root_node) {
  current_scope_ = global_scope_;
  ForwardDeclare(root_node);
  auto def_nodes = root_node->getDefNodes();
  for (const auto def_node : def_nodes) {
    if (auto var_def = std::dynamic_pointer_cast<VarDefNode>(def_node)) {
      auto var_type = var_def->getIdNode()->getType();
      if (var_type->getDimension() != 0 || var_type->is_customized() || (var_type->getDimension() == 0 && var_type->compareBase(*k_string))) {
        global_var_def_.emplace_back(var_def);
      }
      std::shared_ptr<IRType> reg_type;
      // if (var_type->compareBase(*k_string)) {
      //   reg_type = std::make_shared<IRType>(k_string, var_type->getDimension() + 2);
      // } else {
        reg_type = std::make_shared<IRType>(var_def->getIdNode()->getType(), var_type->getDimension() + 1);
      // }
      // auto reg_type = std::make_shared<IRType>(var_def->getIdNode()->getType(), var_type->getDimension() + 1);
      std::shared_ptr<Register> reg = std::make_shared<Register>(var_def->getIdNode()->getIdName(), reg_type, true);
      global_scope_->declare(reg->GetName(), reg);
      // if (!ImmediateInitialize(var_def->getExpr())) {
      //   global_var_def_.emplace_back(var_def);
      // }
      global_scope_->AddGlobalStmt(std::make_shared<GlobalStmt>(var_def));

    } else if (auto func_def = std::dynamic_pointer_cast<FuncDefNode>(def_node)) {
      auto func = FindFunction(func_def->getIdNode()->getIdName());
      current_func_ = func;
      current_scope_ = func->GetScope();
      current_scope_->SetParent(global_scope_);
      func_def->accept(this);
      current_scope_ = current_scope_->GetParent();

    } else if (auto main_func_def = std::dynamic_pointer_cast<MainFuncNode>(def_node)) {
      std::shared_ptr<IRFunction> main_func = std::make_shared<IRFunction>(main_func_def);
      current_func_ = main_func;
      current_scope_ = main_func->GetScope();
      current_scope_->SetParent(global_scope_);
      main_func_def->accept(this);
      current_scope_->GetParent();
      funcs_["main"] = main_func;
    } else if (auto class_def = std::dynamic_pointer_cast<ClassDefNode>(def_node)) {
      auto class_type = GetClassType(class_def->getIdNode()->getIdName());
      class_def->accept(this);
    }
  }

#ifndef testall
  for (auto& type : types_) {
    printf("%s\n", type.second->commit().c_str());
  }
  printf("%s", global_scope_->commit().c_str()); // \n included in the method
  for (auto& func : funcs_) { // first declare
    auto func_obj = func.second;
    if (func_obj->is_builtin()) {
      printf("%s\n", func_obj->commit().c_str());
    }
  }
  for (auto& func : funcs_) { // then define
    auto func_obj = func.second;
    if (!func_obj->is_builtin()) {
      printf("%s\n", func_obj->commit().c_str());
    }
  }
#endif

}

void IRGenerator::visit(std::shared_ptr<FuncDefNode> node) {
  auto func_block = node->getFuncBlock();
  auto entry_block = current_func_->CreateBlock(node->getIdNode()->getIdName() + ".entry");
  current_basic_block_ = entry_block;
  // if (current_func_->IsInClass()) {
  //   current_func_->SetIndex(node->getVarDefs().size() + 1);
  // } else {
  //   current_func_->SetIndex(node->getVarDefs().size());
  // }
  InitFuncParam(node);
  for (const auto &var_def : node->getInBlockVarDef()) {
    auto var_def_type = std::make_shared<IRType>(var_def->getIdNode()->getType(), var_def->getIdNode()->getType()->getDimension() + 1);
    std::shared_ptr<Register> var_reg = current_func_->CreateRegister(var_def_type);
    std::shared_ptr<Stmt> alloca_stmt = std::static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(var_reg));
    current_basic_block_->AddStmt(alloca_stmt);
    var_def->SetPreAllocatedReg(var_reg);
  }
  func_block->accept(this);
  bool has_return = false;
  for (auto& stat_node : func_block->getStatNodes()) {
    if (auto ret_node = std::dynamic_pointer_cast<ReturnStatNode>(stat_node)) {
      has_return = true;
    }
  }
  if (!has_return) {
    std::shared_ptr<Stmt> ret_stmt = std::static_pointer_cast<Stmt>(std::make_shared<ReturnStmt>(std::make_shared<IRType>(node->getReturnType())));
    current_basic_block_->AddStmt(ret_stmt);
  }
}

void IRGenerator::visit(std::shared_ptr<BlockNode> node) {
  auto stats = node->getStatNodes();
  for (auto stat : stats) {
    if (auto literal_node = std::dynamic_pointer_cast<LiteralNode>(stat)) {
      continue;
    }
    stat->accept(this);
  }
}


void IRGenerator::visit(std::shared_ptr<MainFuncNode> node) {
  auto main_block = node->getBody();
  auto entry_block = current_func_->CreateBlock("main.entry");
  current_basic_block_ = entry_block;
  //assign_stat_node  global vardef
  for (auto &global_var_def : global_var_def_) {
    GlobalVarDefInit(global_var_def);
  }
  for (const auto &var_def : node->getInBlockVarDef()) {
    auto var_def_type = std::make_shared<IRType>(var_def->getIdNode()->getType(), var_def->getIdNode()->getType()->getDimension() + 1);
    std::shared_ptr<Register> var_reg = current_func_->CreateRegister(var_def_type);
    std::shared_ptr<Stmt> alloca_stmt = std::static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(var_reg));
    current_basic_block_->AddStmt(alloca_stmt);
    var_def->SetPreAllocatedReg(var_reg);
  }

  main_block->accept(this);
  bool has_return = false;
  for (auto& stat_node : main_block->getStatNodes()) {
    if (auto ret_node = std::dynamic_pointer_cast<ReturnStatNode>(stat_node)) {
      has_return = true;
    }
  }
  if (!has_return) {
    std::shared_ptr<Stmt> ret_stmt = std::static_pointer_cast<Stmt>(std::make_shared<ReturnStmt>(0));
    current_basic_block_->AddStmt(ret_stmt);
  }
}

void IRGenerator::visit(std::shared_ptr<ClassDefNode> node) {
  auto block_node = node->getBlockNode();
  auto stats = block_node->getStatNodes();
  bool has_class_func = false;
  bool has_var = false;
  //add 'this' to class_type_

  for (const auto& stat : stats) {
    if (auto var_def = std::dynamic_pointer_cast<VarDefNode>(stat)) {
      //add to type
      // has_var = true;
      // std::shared_ptr<IRType> var_type = std::make_shared<IRType>(var_def->getIdNode()->getType());
      // current_class_type_->AddElement(var_def->getIdNode()->getIdName(), var_type); // declared type in RootNode
    } else if (auto func_def = std::dynamic_pointer_cast<FuncDefNode>(stat)) {
      std::shared_ptr<IRFunction> func = FindFunction(node->getIdNode()->getIdName() + "_" + func_def->getIdNode()->getIdName());
      current_func_ = func;
      current_scope_ = func->GetScope();
      current_scope_->SetParent(global_scope_);
      func_def->accept(this);
    } else if (auto class_func_def = std::dynamic_pointer_cast<ClassFuncDefNode>(stat)) {
      std::shared_ptr<IRFunction> func = FindFunction(node->getIdNode()->getIdName() + "_" + class_func_def->getIdNode()->getIdName());
      current_func_ = func;
      current_scope_ = func->GetScope();
      current_scope_->SetParent(global_scope_);
      class_func_def->accept(this);
    }
  }

}

void IRGenerator::visit(std::shared_ptr<ClassFuncDefNode> node) {
  // "this" is the #1 reg in llvm ir
  // ClassFuncDefNode has only one parameter, which is 'this' pointer
  auto func_block = node->getBlockNode();
  auto entry_block = current_func_->CreateBlock(node->getIdNode()->getIdName() + ".entry");
  current_basic_block_ = entry_block;
  // std::shared_ptr<IRType> param_type = std::make_shared<IRType>(IRType::kPTR);;
  // std::shared_ptr<IRType> reg_type = std::make_shared<IRType>(node->getIdNode()->getIdName(), 2);
  // std::shared_ptr<Register> reg = current_func_->CreateRegister(reg_type); // though it is passed in, we still need to declare this reg in scope
  // std::shared_ptr<Register> param_reg = current_func_->CreateRegister(param_type);
  // std::shared_ptr<Stmt> alloca_stmt = std::static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(reg));
  // std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(param_reg, reg));
  // current_basic_block_->AddStmt(alloca_stmt);
  // current_basic_block_->AddStmt(store_stmt);
  // current_scope_->declare("this", reg); //name the self pointer "this"
  std::shared_ptr<IRType> reg_type = std::make_shared<IRType>(node->getIdNode()->getIdName(), 1); // 'this' is stored as a reg
  std::shared_ptr<Register> reg = current_func_->CreateRegister(reg_type);
  std::shared_ptr<Register> param_reg = current_func_->GetParamReg(0);
  std::shared_ptr<Stmt> alloca_stmt = static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(reg));
  std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(param_reg, reg));
  current_basic_block_->AddStmt(alloca_stmt);
  current_basic_block_->AddStmt(store_stmt);
  current_scope_->declare("this", reg); //name the self pointer "this"
  func_block->accept(this);
  bool has_return = false;
  for (auto& stat_node : func_block->getStatNodes()) {
    if (auto ret_node = std::dynamic_pointer_cast<ReturnStatNode>(stat_node)) {
      has_return = true;
    }
  }
  if (!has_return) {
    std::shared_ptr<Stmt> ret_stmt = std::static_pointer_cast<Stmt>(std::make_shared<ReturnStmt>());
    current_basic_block_->AddStmt(ret_stmt);
  }
}

void IRGenerator::visit(std::shared_ptr<VarDefNode> node) {
  std::shared_ptr<IRType> node_type;
  node_type = std::make_shared<IRType>(node->getIdNode()->getType(), node->getIdNode()->getType()->getDimension() + 1);
  // std::shared_ptr<Register> var_reg = current_func_->CreateRegister(node_type);
  // std::shared_ptr<Stmt> alloca_stmt = std::static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(var_reg));
  // current_basic_block_->AddStmt(alloca_stmt);
  // current_scope_->declare(node->getIdNode()->getIdName(), var_reg);


  auto var_reg = node->GetPreAllocatedReg();
  current_scope_->declare(node->getIdNode()->getIdName(), var_reg);


  //visit expr
  auto expr = node->getExpr();
  if (expr != nullptr) {
    if (auto init_array = std::dynamic_pointer_cast<InitArrayNode>(expr)) {
      // an array def
      auto array_const = init_array->getDefaultArray();
      if (array_const != nullptr) {
        InitializeArray(var_reg, array_const);
      } else {
        init_array->accept(this);
        auto array_obj_reg = current_func_->GetReturnReg();
        auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(array_obj_reg, var_reg));
        current_basic_block_->AddStmt(store_stmt);
      }
      return ;
    } else if (auto array_const = std::dynamic_pointer_cast<ArrayConstNode>(expr)) {
      InitializeArray(var_reg, array_const);
    }
    else if (auto init_object = std::dynamic_pointer_cast<InitObjectNode>(expr)) {
      //malloc, save the pointer to a reg
      //call ClassFuncDefNode with the reg
      std::string type_name = node_type->GetTypeName();
      auto malloc_func = FindFunction("Builtin_malloc");
      auto pointer_reg = current_func_->CreateRegister(k_ir_void_star);
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> malloc_params;
      auto type_size = GetClassType(type_name)->GetClassSize();
      malloc_params.push_back(type_size);
      std::shared_ptr<Stmt> malloc_call = std::static_pointer_cast<Stmt>(std::make_shared<CallStmt>(malloc_func, pointer_reg, malloc_params));

      std::string class_func_name = type_name + "_" + type_name;
      auto class_func = FindFunction(class_func_name);
      // auto return_reg = current_func_->CreateRegister(std::make_shared<IRType>(IRType::BasicType::kVOID));
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> class_func_params;
      class_func_params.emplace_back(pointer_reg);
      std::shared_ptr<Stmt> class_func_call = std::static_pointer_cast<Stmt>(std::make_shared<CallStmt>(class_func, class_func_params));
      current_basic_block_->AddStmt(malloc_call);
      current_basic_block_->AddStmt(class_func_call);
      //store back
      auto store_reg = FindRegister(node->getIdNode()->getIdName());
      std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(pointer_reg, store_reg)); // store the array address into the alloca address
      current_basic_block_->AddStmt(store_stmt);
      return ;
    } else {
      //store back to id_reg
      auto expr_reg = LiteralResolver(expr);
      std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
            std::make_shared<StoreStmt>(expr_reg, var_reg)); // store the array address into the alloca address
      current_basic_block_->AddStmt(store_stmt);
    }

    // auto store_val = LiteralResolver(expr);
    // std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
    //   std::make_shared<StoreStmt>(store_val, var_reg)); // last reg is where i store the result
    // current_basic_block_->AddStmt(store_stmt);
  }
  //store back
}

void IRGenerator::visit(std::shared_ptr<InitArrayNode> node) {
  auto array_const = node->getDefaultArray();
  if (array_const == nullptr) {
    // auto array_type = node->getType();
    // auto result_reg = current_func_->CreateRegister(std::make_shared<IRType>(array_type));
    auto range_vec = node->getRangeNode();
    DeclareArray(node, range_vec, 0);
  } else if (array_const != nullptr) {
    auto result_type = std::make_shared<IRType>(array_const->getArrayType());
    auto result_reg = current_func_->CreateRegister(result_type);
    InitializeArray(result_reg, array_const);
  }
}
//
// void IRGenerator::visit(std::shared_ptr<LiteralNode> node) {
//   auto literal_type = node->getLiteralType();
//   auto literal_reg = current_func_->CreateRegister(std::make_shared<IRType>(literal_type));
//   auto init_stmt = std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, 0, node, literal_reg);
//   current_basic_block_->AddStmt(init_stmt);
// }

void IRGenerator::visit(std::shared_ptr<BinaryExprNode> node) {
  auto lhs = node->getLhs();
  auto rhs = node->getRhs();
  if (node->getOp() == BinaryExprNode::BinaryOp::kAND_AND) {
    /** a && b
     * create reg for a result, save_reg = result_reg
     * eval(a)
     * br a == true b : false
     * b:
     * eval(b)
     * result = last_reg
     * br end
     * false:
     * result = false
     * br end
     * end:
     */
    auto res_reg = current_func_->CreateRegister(std::make_shared<IRType>(k_ir_bool, 1));
    auto alloca_res = std::make_shared<AllocaStmt>(res_reg);
    current_basic_block_->AddStmt(alloca_res);
    // lhs->accept(this);
    // auto a_result = current_func_->GetReturnReg();
    auto a_result = LiteralResolver(lhs);
    auto b_block_name = current_func_->CreateBlockName("a_true", false);
    auto a_false_block_name = current_func_->CreateBlockName("a_false", false);
    auto end_block_name = current_func_->CreateBlockName("end_block_for_and_and", false);

    auto br_a = std::make_shared<BrConditionalStmt>(a_result, b_block_name, a_false_block_name);
    current_basic_block_->AddStmt(br_a);
    auto to_end = std::make_shared<BrUnconditionalStmt>(end_block_name);

    //b:
    auto b_block = current_func_->CreateBlock(b_block_name);
    current_basic_block_ = b_block;
    auto b_result = LiteralResolver(rhs);
    auto store_b_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(b_result, res_reg));
    current_basic_block_->AddStmt(store_b_stmt);
    current_basic_block_->AddStmt(to_end);
    //false:
    auto a_false_block = current_func_->CreateBlock(a_false_block_name);
    current_basic_block_ = a_false_block;
    auto store_false_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(false, res_reg));
    current_basic_block_->AddStmt(store_false_stmt);
    current_basic_block_->AddStmt(to_end);
    auto end_block = current_func_->CreateBlock(end_block_name);
    current_basic_block_ = end_block;
    auto res_val_reg = current_func_->CreateRegister(std::make_shared<IRType>(res_reg->GetType(), -1));
    auto load_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<LoadStmt>(res_val_reg, res_reg));
    current_basic_block_->AddStmt(load_stmt);
    current_func_->SetReturnReg(res_val_reg);
    return ;
  } else if (node->getOp() == BinaryExprNode::BinaryOp::kOR_OR) {
    /** a || b
      * eval(a)
      * create reg for a result
      * br a == false b : a_true
      * b:
      * eval(b)
      * result_reg = ret
      * br end
      * a_true:
      * result_reg = true
      * end:
      * next take last reg
      */
    auto res_reg = current_func_->CreateRegister(std::make_shared<IRType>(k_ir_bool, 1));
    auto alloca_res = std::make_shared<AllocaStmt>(res_reg);
    current_basic_block_->AddStmt(alloca_res);
    auto a_result = LiteralResolver(lhs);
    auto b_block_name = current_func_->CreateBlockName("a_false", false);
    auto a_true_block_name = current_func_->CreateBlockName("a_true", false);
    auto end_block_name = current_func_->CreateBlockName("end_block_for_and_and", false);
    auto br_a = std::make_shared<BrConditionalStmt>(a_result, a_true_block_name, b_block_name);
    auto to_end = std::make_shared<BrUnconditionalStmt>(end_block_name);
    current_basic_block_->AddStmt(br_a);
    //a_false:
    auto b_block = current_func_->CreateBlock(b_block_name);
    current_basic_block_ = b_block;
    // rhs->accept(this);
    // auto b_result = current_func_->GetReturnReg();
    auto b_result = LiteralResolver(rhs);
    auto store_b_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(b_result, res_reg));
    current_basic_block_->AddStmt(store_b_stmt);
    current_basic_block_->AddStmt(to_end);
    // a_true:
    auto a_true_block = current_func_->CreateBlock(a_true_block_name);
    current_basic_block_ = a_true_block;
    auto store_true_stmt = std::static_pointer_cast<Stmt>(
     std::make_shared<StoreStmt>(true, res_reg));
    current_basic_block_->AddStmt(store_true_stmt);
    current_basic_block_->AddStmt(to_end);
    auto end_block = current_func_->CreateBlock(end_block_name);
    current_basic_block_ = end_block;
    auto res_val_reg = current_func_->CreateRegister(std::make_shared<IRType>(res_reg->GetType(), -1));
    auto load_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<LoadStmt>(res_val_reg, res_reg));
    current_basic_block_->AddStmt(load_stmt);
    current_func_->SetReturnReg(res_val_reg);
    return ;
  }
  // lhs->accept(this);
  // auto lhs_rep = FetchExprReg(lhs);
  // rhs->accept(this);
  // auto rhs_rep = FetchExprReg(rhs);
  auto lhs_rep = LiteralResolver(lhs);
  auto rhs_rep = LiteralResolver(rhs);
  // auto lhs_type = lhs->getExprType();
  // auto rhs_type = rhs->getExprType();
  auto lhs_ir_type = GetVariantType(lhs_rep);
  auto rhs_ir_type = GetVariantType(rhs_rep);
  switch (node->getOp()) {
    case BinaryExprNode::BinaryOp::kADD: {
      if (*lhs_ir_type == *k_ir_string) {
        auto concat_func = FindFunction("Builtin_strcat");
        std::shared_ptr<IRType> dest_reg_type = k_ir_string;
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
        params.push_back(lhs_rep);
        params.push_back(rhs_rep);
        std::shared_ptr<Stmt> call_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<CallStmt>(concat_func, dest_reg, params));
        current_basic_block_->AddStmt(call_stmt);
      } else if (*lhs_ir_type == *k_ir_int) {
        std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
        std::shared_ptr<Stmt> add_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, lhs_rep, rhs_rep, dest_reg));
        current_basic_block_->AddStmt(add_stmt);
      } else {
        throw std::runtime_error("binary operation type mismatch");
      }
      break;
    }
    case BinaryExprNode::BinaryOp::kMUL: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> mul_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kMUL, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(mul_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kDIV: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> div_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kDIV, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(div_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kMOD: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> mod_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kMOD, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(mod_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kSUB: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> sub_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSUB, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(sub_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kSRL: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> srl_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSRL, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(srl_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kSLL: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> sll_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSLL, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(sll_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kAND: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> and_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kAND, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(and_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kXOR: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> xor_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kXOR, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(xor_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kOR: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> or_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kOR, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(or_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kBT: {
      if (*lhs_ir_type != *k_ir_int && *lhs_ir_type != *k_ir_string) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);

      if (*lhs_ir_type == *k_ir_string) {
        auto strcmp_func = FindFunction("Builtin_strcmp");
        auto strcmp_ret_reg = current_func_->CreateRegister(k_ir_int);
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
        params.emplace_back(lhs_rep);
        params.emplace_back(rhs_rep);
        auto call_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<CallStmt>(strcmp_func, strcmp_ret_reg, params));
        current_basic_block_->AddStmt(call_stmt);
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
        auto bt_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kBT, strcmp_ret_reg, 0, dest_reg));
        current_basic_block_->AddStmt(bt_stmt);
      } else {
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
        std::shared_ptr<Stmt> bt_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kBT, lhs_rep, rhs_rep, dest_reg));
        current_basic_block_->AddStmt(bt_stmt);
      }
      break;
    }
    case BinaryExprNode::BinaryOp::kLT: {
      if (*lhs_ir_type != *k_ir_int && *lhs_ir_type != *k_ir_string) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      if (*lhs_ir_type == *k_ir_string) {
        auto strcmp_func = FindFunction("Builtin_strcmp");
        auto strcmp_ret_reg = current_func_->CreateRegister(k_ir_int);
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
        params.emplace_back(lhs_rep);
        params.emplace_back(rhs_rep);
        auto call_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<CallStmt>(strcmp_func, strcmp_ret_reg, params));
        current_basic_block_->AddStmt(call_stmt);
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
        auto lt_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kLT, strcmp_ret_reg, 0, dest_reg));
        current_basic_block_->AddStmt(lt_stmt);
      } else{
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
          std::shared_ptr<Stmt> lt_stmt = std::static_pointer_cast<Stmt>(
            std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kLT, lhs_rep, rhs_rep, dest_reg));
          current_basic_block_->AddStmt(lt_stmt);
        }
      break;
    }
    case BinaryExprNode::BinaryOp::kBEQ: {
      if (*lhs_ir_type != *k_ir_int && *lhs_ir_type != *k_ir_string) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      if (*lhs_ir_type == *k_ir_string) {
        auto strcmp_func = FindFunction("Builtin_strcmp");
        auto strcmp_ret_reg = current_func_->CreateRegister(k_ir_int);
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
        params.emplace_back(lhs_rep);
        params.emplace_back(rhs_rep);
        auto call_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<CallStmt>(strcmp_func, strcmp_ret_reg, params));
        current_basic_block_->AddStmt(call_stmt);
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);

        auto beq_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kBEQ, strcmp_ret_reg, 0, dest_reg));
        current_basic_block_->AddStmt(beq_stmt);
      } else {
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);

        std::shared_ptr<Stmt> beq_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kBEQ, lhs_rep, rhs_rep, dest_reg));
        current_basic_block_->AddStmt(beq_stmt);
      }
      break;
    }
    case BinaryExprNode::BinaryOp::kLEQ: {
      if (*lhs_ir_type != *k_ir_int && *lhs_ir_type != *k_ir_string) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      if (*lhs_ir_type == *k_ir_string) {
        auto strcmp_func = FindFunction("Builtin_strcmp");
        auto strcmp_ret_reg = current_func_->CreateRegister(k_ir_int);
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
        params.emplace_back(lhs_rep);
        params.emplace_back(rhs_rep);
        auto call_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<CallStmt>(strcmp_func, strcmp_ret_reg, params));
        current_basic_block_->AddStmt(call_stmt);
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
        auto leq_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kLEQ, strcmp_ret_reg, 0, dest_reg));
        current_basic_block_->AddStmt(leq_stmt);
      } else {
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
        std::shared_ptr<Stmt> leq_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kLEQ, lhs_rep, rhs_rep, dest_reg));
        current_basic_block_->AddStmt(leq_stmt);
      }
      break;
    }
    case BinaryExprNode::BinaryOp::kET: {
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      if (*lhs_ir_type == *k_ir_string) {
        auto strcmp_func = FindFunction("Builtin_strcmp");
        auto strcmp_ret_reg = current_func_->CreateRegister(k_ir_int);
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
        params.emplace_back(lhs_rep);
        params.emplace_back(rhs_rep);
        auto call_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<CallStmt>(strcmp_func, strcmp_ret_reg, params));
        current_basic_block_->AddStmt(call_stmt);
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
        auto et_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kET, strcmp_ret_reg, 0, dest_reg));
        current_basic_block_->AddStmt(et_stmt);
      } else {
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
        std::shared_ptr<Stmt> et_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kET, lhs_rep, rhs_rep, dest_reg));
        current_basic_block_->AddStmt(et_stmt);
      }
      break;
    }
    case BinaryExprNode::BinaryOp::kNET: {
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
       if (*lhs_ir_type == *k_ir_string) {
        auto strcmp_func = FindFunction("Builtin_strcmp");
        auto strcmp_ret_reg = current_func_->CreateRegister(k_ir_int);
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
        params.emplace_back(lhs_rep);
        params.emplace_back(rhs_rep);
        auto call_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<CallStmt>(strcmp_func, strcmp_ret_reg, params));
        current_basic_block_->AddStmt(call_stmt);
         std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
        auto net_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kNET, strcmp_ret_reg, 0, dest_reg));
        current_basic_block_->AddStmt(net_stmt);
      } else {
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
        std::shared_ptr<Stmt> net_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kNET, lhs_rep, rhs_rep, dest_reg));
        current_basic_block_->AddStmt(net_stmt);
      }
      break;
    }
    default: {
      throw std::runtime_error("unknown binary operation type");
      break;
    }
  }
  current_func_->SetReturnReg(current_func_->GetLastReg());
}

void IRGenerator::visit(std::shared_ptr<IdNode> node) {
  auto var_addr_reg = FindRegister(node->getIdName());
  auto val_reg = current_func_->CreateRegister(var_addr_reg->GetType()->DecreaseDimension());
  std::shared_ptr<Stmt> load_stmt = std::static_pointer_cast<Stmt>(
            std::make_shared<LoadStmt>(val_reg, var_addr_reg));
  current_basic_block_->AddStmt(load_stmt);
  current_func_->SetReturnReg(val_reg);
  return ;
}

void IRGenerator::visit(std::shared_ptr<TernaryExprNode> node) {
  auto pred = node->getPredicateNode();
  auto if_node = node->getThenExprNode();
  auto else_node = node->getElseExprNode();
  pred->accept(this);
  auto pred_reg = current_func_->GetReturnReg();
  auto result_type = node->getThenExprNode()->getExprType();
  std::shared_ptr<Register> result_reg;
  if (!result_type->compareBase(*k_void) || result_type->getDimension() != 0) {
    result_reg = current_func_->CreateRegister(std::make_shared<IRType>(result_type, result_type->getDimension() + 1)); // a ptr
    auto alloca_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<AllocaStmt>(result_reg));
    current_basic_block_->AddStmt(alloca_stmt);
  }

  auto br_then_name = current_func_->CreateBlockName("a_then", false);
  auto br_else_name = current_func_->CreateBlockName("a_else", false);
  auto br_end_name = current_func_->CreateBlockName("end", false);
  auto to_end = std::make_shared<BrUnconditionalStmt>(br_end_name);
  auto curr_block_tmp = current_basic_block_;
  auto br_cond_stmt = std::static_pointer_cast<Stmt>(
    std::make_shared<BrConditionalStmt>(pred_reg, br_then_name, br_else_name));
  current_basic_block_->AddStmt(br_cond_stmt);
  //a_then:
  auto br_then = current_func_->CreateBlock(br_then_name);
  current_basic_block_ = br_then;
  // if_node->accept(this);
  // auto if_ret_reg = current_func_->GetReturnReg();
  auto if_ret_reg = LiteralResolver(if_node);
  if (!result_type->compareBase(*k_void) || result_type->getDimension() != 0) {
    auto store_if_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(if_ret_reg, result_reg));
    current_basic_block_->AddStmt(store_if_stmt);
  }
  current_basic_block_->AddStmt(to_end);
  //a_else:
  auto br_else = current_func_->CreateBlock(br_else_name);
  current_basic_block_ = br_else;
  // else_node->accept(this);
  // auto else_ret_reg = current_func_->GetReturnReg();
  auto else_ret_reg = LiteralResolver(else_node);
  if (!result_type->compareBase(*k_void) || result_type->getDimension() != 0) {
    auto store_else_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(else_ret_reg, result_reg));
    current_basic_block_->AddStmt(store_else_stmt);
  }
  current_basic_block_->AddStmt(to_end);
  //end:
  auto br_end = current_func_->CreateBlock(br_end_name);
  current_basic_block_ = br_end;
  if (!result_type->compareBase(*k_void) || result_type->getDimension() != 0) {
    auto ternary_val_reg = current_func_->CreateRegister(std::make_shared<IRType>(result_reg->GetType(), -1));
    auto load_result_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<LoadStmt>(ternary_val_reg, result_reg));
    current_basic_block_->AddStmt(load_result_stmt);
    current_func_->SetReturnReg(ternary_val_reg);
  }
}

void IRGenerator::visit(std::shared_ptr<ForStatNode> node) {
  std::shared_ptr<StatNode> init_stat;
  std::shared_ptr<StatNode> update_stat;
  if (node->getInitialExprNode() != nullptr) {
    init_stat = node->getInitialExprNode();
  } else if (node->getInitialVarDefNode() != nullptr) {
    init_stat = std::dynamic_pointer_cast<StatNode>(node->getInitialVarDefNode());
  } else if (node->getInitialAssignStatNode() != nullptr) {
    init_stat = std::dynamic_pointer_cast<StatNode>(node->getInitialAssignStatNode());
  }
  if (node->getUpdateAssignStatNode() != nullptr) {
    update_stat = node->getUpdateAssignStatNode();
  } else if (node->getUpdateExprNode() != nullptr) {
    update_stat = std::dynamic_pointer_cast<StatNode>(node->getUpdateExprNode());
  }
  auto cond_stat = node->getForCondExprNode();
  auto body_stat = node->getBlockNode();

  auto loop_block_name = current_func_->CreateBlockName("loop", false);
  auto loop_body_block_name = current_func_->CreateBlockName("body", false);
  auto update_block_name = current_func_->CreateBlockName("update", false);
  auto end_block_name = current_func_->CreateBlockName("end_loop", false);
  auto new_scope = IRScope::CreateScope(current_scope_, update_block_name, end_block_name);
  current_scope_ = new_scope;
  if (init_stat != nullptr) { // otherwise we don't need init_stmt
    init_stat->accept(this);
  }
  auto j_loop = std::static_pointer_cast<Stmt>(
    std::make_shared<BrUnconditionalStmt>(loop_block_name));
  current_basic_block_->AddStmt(j_loop);
  auto curr_block_tmp = current_basic_block_;
  //loop:
  auto loop_block = current_func_->CreateBlock(loop_block_name);
  current_basic_block_ = loop_block;
  // cond_stmt->accept(this);
  // auto cond_reg = current_func_->GetReturnReg();

  //if reg = 0 end
  if (cond_stat != nullptr) {
    auto cond_rep = LiteralResolver(cond_stat);
    auto cond_br = std::make_shared<BrConditionalStmt>(cond_rep, loop_body_block_name, end_block_name);
    current_basic_block_->AddStmt(cond_br);
  } else {
    auto cond_br = std::make_shared<BrUnconditionalStmt>(loop_body_block_name);
    current_basic_block_->AddStmt(cond_br);
  }
  //loop_body:
  auto loop_body_block = current_func_->CreateBlock(loop_body_block_name);
  current_basic_block_ = loop_body_block;
  body_stat->accept(this);
  auto br_update_stmt = std::static_pointer_cast<Stmt>(
    std::make_shared<BrUnconditionalStmt>(update_block_name));
  current_basic_block_->AddStmt(br_update_stmt);
  //update:
  auto update_block = current_func_->CreateBlock(update_block_name);
  current_basic_block_ = update_block;
  if (update_stat != nullptr) {
    update_stat->accept(this);
  }
  auto loop_back = std::make_shared<BrUnconditionalStmt>(loop_block->getBlockName());
  current_basic_block_->AddStmt(loop_back);
  current_scope_ = current_scope_->GetParent();// back to previous scope
  // auto br_end_stmt = std::static_pointer_cast<Stmt>(
  //   std::make_shared<BrUnconditionalStmt>(end_block->getBlockName()));
  // current_basic_block_->AddStmt(br_end_stmt);
  auto end_block = current_func_->CreateBlock(end_block_name);
  current_basic_block_ = end_block;

}

void IRGenerator::visit(std::shared_ptr<WhileStatNode> node) {
  auto cond_stmt = node->getWhileCondExprNode();
  auto body_stmt = node->getBlockNode();
  auto loop_block_name = current_func_->CreateBlockName("loop", false);
  auto loop_body_block_name = current_func_->CreateBlockName("body", false);
  auto end_block_name = current_func_->CreateBlockName("end_loop", false);
  auto new_scope = IRScope::CreateScope(current_scope_, loop_block_name, end_block_name);
  current_scope_ = new_scope;
  auto curr_block_tmp = current_basic_block_;
  //loop:
  auto enter_loop = std::make_shared<BrUnconditionalStmt>(loop_block_name);
  current_basic_block_->AddStmt(enter_loop);
  auto loop_block = current_func_->CreateBlock(loop_block_name);
  current_basic_block_ = loop_block;;
  // cond_stmt->accept(this);
  // auto cond_reg = current_func_->GetLastReg();
  auto cond_rep = LiteralResolver(cond_stmt);
  //if reg = 0 end
  auto cond_br = std::make_shared<BrConditionalStmt>(cond_rep, loop_body_block_name, end_block_name);
  current_basic_block_->AddStmt(cond_br);
  //loop_body:
  auto loop_body_block = current_func_->CreateBlock(loop_body_block_name);
  current_basic_block_ = loop_body_block;
  body_stmt->accept(this);
  current_basic_block_->AddStmt(enter_loop);
  // current_basic_block_ = curr_block_tmp;
  // auto br_end_stmt = std::static_pointer_cast<Stmt>(
  // std::make_shared<BrUnconditionalStmt>(end_block->getBlockName()));
  // current_basic_block_->AddStmt(br_end_stmt);
  auto end_block = current_func_->CreateBlock(end_block_name);
  current_basic_block_ = end_block;
}


void IRGenerator::visit(std::shared_ptr<ReturnStatNode> node) {
  //handled expr return, func call return, void return
  auto ret_expr = node->getReturnExpr();
  auto ret_func_call = node->getFuncCall();
  std::shared_ptr<ReturnStmt> ret_stmt;
  if (ret_expr != nullptr) {
    // ret_expr->accept(this);
    // auto ret_reg = current_func_->GetLastReg();
    auto ret_rep = LiteralResolver(ret_expr);
    ret_stmt = std::make_shared<ReturnStmt>(ret_rep);
  } else if (ret_func_call != nullptr) {
    ret_func_call->accept(this);
    auto ret_reg = current_func_->GetReturnReg();
    ret_stmt = std::make_shared<ReturnStmt>(ret_reg);
  } else {
    ret_stmt = std::make_shared<ReturnStmt>();
  }
  current_basic_block_->AddStmt(ret_stmt);
}

void IRGenerator::visit(std::shared_ptr<TerminalNode> node) {
  std::string jump_block_name;
  if (node->GetType() == TerminalNode::TerminalType::kCONTINUE) {
    jump_block_name = current_scope_->GetLoopStart();
  } else {
    jump_block_name = current_scope_->GetLoopEnd();
  }
  auto jump_stmt = std::make_shared<BrUnconditionalStmt>(jump_block_name);
  current_basic_block_->AddStmt(jump_stmt);
}

void IRGenerator::visit(std::shared_ptr<ThisExprNode> node) {
  auto this_reg = FindRegister("this");
  auto this_val_reg = current_func_->CreateRegister(this_reg->GetType()->DecreaseDimension());
  auto load_stmt = std::static_pointer_cast<Stmt>(
    std::make_shared<LoadStmt>(this_val_reg, this_reg));
  current_basic_block_->AddStmt(load_stmt);
  current_func_->SetReturnReg(this_val_reg);
}

void IRGenerator::visit(std::shared_ptr<ArrayConstNode> node) {
  //don't want to implement, it will be processed in the def
}

void IRGenerator::visit(std::shared_ptr<DotExprNode> node) {
  auto lhs = node->getLhs();
  auto rhs = node->getRhs();
  // lhs->accept(this);
  // auto lhs_rep = FetchExprReg(lhs);
  if (auto lhs_this = std::dynamic_pointer_cast<ThisExprNode>(lhs)) {
    lhs = lhs;
  }
  auto lhs_rep = LiteralResolver(lhs);
  std::shared_ptr<IRType> lhs_type;
  if (std::holds_alternative<std::shared_ptr<LiteralNode>>(lhs_rep)) {
    lhs_type = std::make_shared<IRType>(std::get<std::shared_ptr<LiteralNode>>(lhs_rep)->getLiteralType());
  } else {
    lhs_type = std::get<std::shared_ptr<Register>>(lhs_rep)->GetType();
  }
  if (auto func_call = std::dynamic_pointer_cast<FuncCallNode>(rhs)) {

    std::string func_name;
    if (lhs_type->GetDim() == 0 || (lhs_type->GetDim() == 1 && lhs_type->is_customized()) || *lhs_type == *k_ir_string) {
      func_name = lhs_type->GetTypeName() + "_" + func_call->getName();
    } else { // var is dim 1
      func_name = "Array_" + func_call->getName();
    }
    std::shared_ptr<IRFunction> func = FindFunction(func_name);
    auto args = func_call->getArgs();
    std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> arg_reps;
    arg_reps.push_back(lhs_rep); // pass lhs as 'this' param
    for (const auto& arg : args) {
      // arg->accept(this);
      // auto arg_rep = FetchExprReg(arg);
      auto arg_rep = LiteralResolver(arg);
      arg_reps.push_back(arg_rep);
    }
    auto return_type = func->GetReturnType();
    if (*return_type != *k_ir_void) {
      auto dest_reg = current_func_->CreateRegister(func->GetReturnType());
      std::shared_ptr<Stmt> call_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(func, dest_reg, arg_reps));
      current_basic_block_->AddStmt(call_stmt);
      current_func_->SetReturnReg(dest_reg);
    } else {
      std::shared_ptr<Stmt> call_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(func, arg_reps));
      current_basic_block_->AddStmt(call_stmt);
    }
  } else if (auto field = std::dynamic_pointer_cast<IdNode>(rhs)) {
    /* store address of the class in a reg(Type**)
     * load on use
     */
    std::string var_name = field->getIdName();
    std::pair<std::shared_ptr<IRType>, int> element = GetElementInStruct(lhs_type->GetTypeName(), var_name);
    auto gep_dest_reg = current_func_->CreateRegister(element.first);
    // auto base_reg_type = types_[lhs_type->GetTypeName()]->GetElementType();
    // auto base_reg = current_func_->CreateRegister(base_reg_type);
    //gep
    auto base_reg = std::get<std::shared_ptr<Register>>(lhs_rep);
    std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> offsets;
    offsets.push_back(0);
    offsets.push_back(element.second);
    std::shared_ptr<Stmt> gep_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<GEPStmt>(gep_dest_reg, base_reg, offsets, true));
    current_basic_block_->AddStmt(gep_stmt);
    auto dest_reg_type = std::make_shared<IRType>(gep_dest_reg->GetType(), -1);
    auto dest_reg = current_func_->CreateRegister(dest_reg_type);
    auto load_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<LoadStmt>(dest_reg, gep_dest_reg));
    current_basic_block_->AddStmt(load_stmt);
    current_func_->SetReturnReg(dest_reg);
  }
}

void IRGenerator::visit(std::shared_ptr<FormatStringNode> node) {
  /* first need to create a register to store the result of the string
   * if literal node, store the literal into a string reg, and then +
   * if expr node, first evaluate the expression, get the result, then +
   */
  std::shared_ptr<Register> result_string_reg;
  auto all_nodes = node->get_all_nodes();
  for (const auto& child_node : all_nodes) {
    if (std::holds_alternative<std::shared_ptr<LiteralNode>>(child_node)) {
      auto literal = std::get<std::shared_ptr<LiteralNode>>(child_node);
      auto init_string = CreateString(literal);
      if (result_string_reg == nullptr) {
        result_string_reg = init_string;
        continue;
      }
      auto last_result = result_string_reg;
      result_string_reg = current_func_->CreateRegister(k_ir_string);
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
      params.push_back(init_string);
      params.push_back(last_result);
      auto add_string_func = FindFunction("Builtin_strcat");
      auto call_add_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(add_string_func, result_string_reg, params));
      current_basic_block_->AddStmt(call_add_stmt);
    } else {
      auto expr = std::get<std::shared_ptr<ExprNode>>(child_node);
      // expr->accept(this);
      // auto expr_result = current_func_->GetReturnReg(); // by doing this, we need to ensure that the result of expr is stored at the last reg it creates.
      auto expr_result = std::get<std::shared_ptr<Register>>(LiteralResolver(expr));
      if (result_string_reg == nullptr) {
          result_string_reg = expr_result;
        continue;
      }
      auto last_result = result_string_reg;
      result_string_reg = current_func_->CreateRegister(k_ir_string);
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
      params.push_back(expr_result);
      params.push_back(last_result);
      auto add_string_func = FindFunction("Builtin_strcat");
      auto call_add_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(add_string_func, result_string_reg, params));
      current_basic_block_->AddStmt(call_add_stmt);
    }
  }
  current_func_->SetReturnReg(result_string_reg);
}

void IRGenerator::visit(std::shared_ptr<FuncCallNode> node) {
  auto func_name = node->getName();
  auto func = FindFunction(func_name);
  auto args = node->getArgs();
  std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
  if (func->IsInClass()) {
    auto this_reg = FindRegister("this");
    auto this_val_reg = current_func_->CreateRegister(this_reg->GetType()->DecreaseDimension());
    auto load_this_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<LoadStmt>(this_val_reg, this_reg));
    current_basic_block_->AddStmt(load_this_stmt);
    params.emplace_back(this_val_reg);
  }
  for (const auto& arg : args) {
    // arg->accept(this);
    // auto arg_reg = current_func_->GetLastReg();
    auto arg_rep = LiteralResolver(arg);
    params.emplace_back(arg_rep);
  }
  if (*func->GetReturnType() == *k_ir_void) {
    auto func_call_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(func, params));
    current_basic_block_->AddStmt(func_call_stmt);
  } else {
    auto result_reg = current_func_->CreateRegister(func->GetReturnType());
    auto func_call_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<CallStmt>(func, result_reg, params));
    current_basic_block_->AddStmt(func_call_stmt);
    current_func_->SetReturnReg(result_reg);
  }
}

void IRGenerator::visit(std::shared_ptr<IndexExprNode> node) {
  auto base = node->getBase();
  auto index = node->getIndex();
  base->accept(this);
  auto base_reg = current_func_->GetReturnReg();
  auto index_rep = LiteralResolver(index);
  auto gep_dest_reg = current_func_->CreateRegister(base_reg->GetType());
  std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;

  params.push_back(index_rep);
  auto gep_stmt = std::static_pointer_cast<Stmt>(std::make_shared<GEPStmt>(gep_dest_reg, base_reg, params));
  current_basic_block_->AddStmt(gep_stmt);
  auto dest_reg = current_func_->CreateRegister(gep_dest_reg->GetType()->DecreaseDimension());
  auto load_stmt = std::static_pointer_cast<Stmt>(
    std::make_shared<LoadStmt>(dest_reg, gep_dest_reg));
  current_basic_block_->AddStmt(load_stmt);
  current_func_->SetReturnReg(dest_reg);

}

void IRGenerator::visit(std::shared_ptr<InitObjectNode> node) {
  std::string type_name = node->getType()->getTypeName();
  auto malloc_func = FindFunction("Builtin_malloc");
  auto pointer_reg = current_func_->CreateRegister(std::make_shared<IRType>(type_name, 0));
  std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> malloc_params;
  auto type_size = GetClassType(type_name)->GetClassSize();
  malloc_params.emplace_back(type_size);
  std::shared_ptr<Stmt> malloc_call = std::static_pointer_cast<Stmt>(std::make_shared<CallStmt>(malloc_func, pointer_reg, malloc_params));

  std::string class_func_name = type_name + "_" + type_name;
  auto class_func = FindFunction(class_func_name);
  // auto return_reg = current_func_->CreateRegister(std::make_shared<IRType>(IRType::BasicType::kVOID));
  std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> class_func_params;
  class_func_params.emplace_back(pointer_reg);
  std::shared_ptr<Stmt> class_func_call = std::static_pointer_cast<Stmt>(std::make_shared<CallStmt>(class_func, class_func_params));
  current_basic_block_->AddStmt(malloc_call);
  current_basic_block_->AddStmt(class_func_call);
  current_func_->SetReturnReg(pointer_reg);
}

void IRGenerator::visit(std::shared_ptr<UnaryExprNode> node) {
  auto expr = node->getExpr();
  auto op = node->getOp();
  auto operand_rep = LiteralResolver(expr);
  // expr->accept(this);
  // auto operand = current_func_->GetLastReg();
  switch (op) {
    case UnaryExprNode::UnaryOp::kSUB: {
      auto dest_reg = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSUB, 0, operand_rep, dest_reg));
      current_basic_block_->AddStmt(binary_stmt);
      current_func_->SetReturnReg(dest_reg);
      break;
    }
    case UnaryExprNode::UnaryOp::kWAVE: {
      auto dest_reg = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kXOR, -1, operand_rep, dest_reg));
      current_basic_block_->AddStmt(binary_stmt);
      current_func_->SetReturnReg(dest_reg);
      break;
    }
    case UnaryExprNode::UnaryOp::kEXCLAIMER: {
      auto dest_reg = current_func_->CreateRegister(k_ir_bool);
      auto binary_stmt = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kXOR, true, operand_rep, dest_reg));
      current_basic_block_->AddStmt(binary_stmt);
      current_func_->SetReturnReg(dest_reg);
      break;
    }
    case UnaryExprNode::UnaryOp::kPOST_PP: {
      // the design here is that, the last register in each sub expression is to be used in the outer expression.
      /**
       * load
       * create reg1
       * reg1 = i + 1
       * store back
       * create reg2
       * reg2 = i
       */
      auto operand_reg = std::get<std::shared_ptr<Register>>(operand_rep);
      // auto id_node = std::dynamic_pointer_cast<IdNode>(expr);
      // auto id_reg = FindRegister(id_node->getIdName()); // get ptr
      LvalVisit(expr);
      auto id_reg = current_func_->GetReturnReg();
      // auto load_dest = current_func_->CreateRegister(k_ir_int);
      // auto load_stmt = std::static_pointer_cast<Stmt>(std::make_shared<LoadStmt>(load_dest, id_reg));
      auto reg1 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt1 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand_rep, 1, reg1));
      auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(reg1, id_reg));
      // auto reg2 = current_func_->CreateRegister(k_ir_int);
      // auto binary_stmt2 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand_rep, 0, reg2));
      // current_basic_block_->AddStmt(load_stmt);
      current_basic_block_->AddStmt(binary_stmt1);
      current_basic_block_->AddStmt(store_stmt);
      // current_basic_block_->AddStmt(binary_stmt2);
      current_func_->SetReturnReg(operand_reg);
      break;
    }
    case UnaryExprNode::UnaryOp::kPRE_PP: {
      // the design here is that, the last register in each sub expression is to be used in the outer expression.
      /**
       * load
       * create reg1
       * reg1 = i + 1
       * store back
       */
      // auto id_node = std::dynamic_pointer_cast<IdNode>(expr);
      // auto id_reg = FindRegister(id_node->getIdName());
      LvalVisit(expr);
      auto id_reg = current_func_->GetReturnReg();
      // auto load_dest = current_func_->CreateRegister(k_ir_int);
      // auto load_stmt = std::static_pointer_cast<Stmt>(std::make_shared<LoadStmt>(load_dest, id_reg));
      auto reg1 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt1 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand_rep, 1, reg1));
      auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(reg1, id_reg));
      // current_basic_block_->AddStmt(load_stmt);
      current_basic_block_->AddStmt(binary_stmt1);
      current_basic_block_->AddStmt(store_stmt);
      current_func_->SetReturnReg(reg1);
      break;
    }
    case UnaryExprNode::UnaryOp::kPOST_MM: {
      // auto id_node = std::dynamic_pointer_cast<IdNode>(expr);
      // auto id_reg = FindRegister(id_node->getIdName());
      LvalVisit(expr);
      auto id_reg = current_func_->GetReturnReg();
      auto operand_reg = std::get<std::shared_ptr<Register>>(operand_rep);
      // auto load_dest = current_func_->CreateRegister(k_ir_int);
      // auto load_stmt = std::static_pointer_cast<Stmt>(std::make_shared<LoadStmt>(load_dest, id_reg));
      auto reg1 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt1 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSUB, operand_rep, 1, reg1));
      auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(reg1, id_reg));
      // auto reg2 = current_func_->CreateRegister(k_ir_int);
      // auto binary_stmt2 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand_rep, 0, reg2));
      // current_basic_block_->AddStmt(load_stmt);
      current_basic_block_->AddStmt(binary_stmt1);
      current_basic_block_->AddStmt(store_stmt);
      // current_basic_block_->AddStmt(binary_stmt2);
      current_func_->SetReturnReg(operand_reg);
      break;
    }
    case UnaryExprNode::UnaryOp::kPRE_MM: {
      // the design here is that, the last register in each sub expression is to be used in the outer expression.
      /**
       * load
       * create reg1
       * reg1 = i + 1
       * store back
       */
      // auto id_node = std::dynamic_pointer_cast<IdNode>(expr);
      // auto id_reg = FindRegister(id_node->getIdName());
      LvalVisit(expr);
      auto id_reg = current_func_->GetReturnReg();
      // auto load_dest = current_func_->CreateRegister(k_ir_int);
      // auto load_stmt = std::static_pointer_cast<Stmt>(std::make_shared<LoadStmt>(load_dest, id_reg));
      auto reg1 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt1 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSUB, operand_rep, 1, reg1));
      auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(reg1, id_reg));
      // current_basic_block_->AddStmt(load_stmt);
      current_basic_block_->AddStmt(binary_stmt1);
      current_basic_block_->AddStmt(store_stmt);
      current_func_->SetReturnReg(reg1);
      break;
    }
    case UnaryExprNode::UnaryOp::kADD: {
      auto dest_reg = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand_rep, 0, dest_reg));
      current_basic_block_->AddStmt(binary_stmt);
      current_func_->SetReturnReg(dest_reg);
      break;
    }
    default: {
      break;
    }

  }
}

void IRGenerator::visit(std::shared_ptr<AssignStatNode> node) {
  if (auto lhs_id = dynamic_pointer_cast<IdNode>(node->getLhs())) {
    auto id_reg = FindRegister(lhs_id->getIdName());
    auto node_type = id_reg->GetType();
    //visit expr
    auto expr = node->getRhs();
    if (expr != nullptr) {
      if (auto array_const = std::dynamic_pointer_cast<ArrayConstNode>(expr)) {
        // an array def
        InitializeArray(id_reg, array_const);
        return ;
      } else if (auto init_object = std::dynamic_pointer_cast<InitObjectNode>(expr)) {
        //malloc, save the pointer to a reg
        //call ClassFuncDefNode with the reg

        // std::string type_name = node_type->GetTypeName();
        // auto malloc_func = FindFunction("Builtin_malloc");
        // auto pointer_reg = current_func_->CreateRegister(std::make_shared<IRType>(type_name, 1));
        // std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> malloc_params;
        // auto type_size = GetClassType(type_name)->GetClassSize();
        // malloc_params.emplace_back(type_size);
        // std::shared_ptr<Stmt> malloc_call = std::static_pointer_cast<Stmt>(std::make_shared<CallStmt>(malloc_func, pointer_reg, malloc_params));
        //
        // std::string class_func_name = type_name + "_" + type_name;
        // auto class_func = FindFunction(class_func_name);
        // // auto return_reg = current_func_->CreateRegister(std::make_shared<IRType>(IRType::BasicType::kVOID));
        // std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> class_func_params;
        // class_func_params.emplace_back(pointer_reg);
        // std::shared_ptr<Stmt> class_func_call = std::static_pointer_cast<Stmt>(std::make_shared<CallStmt>(class_func, class_func_params));
        // current_basic_block_->AddStmt(malloc_call);
        // current_basic_block_->AddStmt(class_func_call);

        auto pointer_reg = LiteralResolver(init_object);
        std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<StoreStmt>(pointer_reg, id_reg)); // store the array address into the alloca address
        current_basic_block_->AddStmt(store_stmt);
        return ;
      } else {
        //store back to id_reg
        // if (auto literal_expr = std::dynamic_pointer_cast<LiteralNode>(expr)) {
        //   std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
        //       std::make_shared<StoreStmt>(literal_expr, id_reg)); // store the array address into the alloca address
        //   current_basic_block_->AddStmt(store_stmt);
        // } else {
        //   auto expr_reg = current_func_->GetLastReg();
        //   std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
        //         std::make_shared<StoreStmt>(expr_reg, id_reg)); // store the array address into the alloca address
        //   current_basic_block_->AddStmt(store_stmt);
        // }
        auto expr_rep = LiteralResolver(expr);
        auto store_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<StoreStmt>(expr_rep, id_reg));
        current_basic_block_->AddStmt(store_stmt);
      }
    }
  } else {
    LvalVisit(node->getLhs());
    auto addr_reg = current_func_->GetReturnReg();
    auto rhs_expr = node->getRhs();
    // rhs_expr->accept(this);
    // auto rhs_reg = current_func_->GetLastReg();
    auto rhs_rep = LiteralResolver(rhs_expr);
    std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(rhs_rep, addr_reg));
    current_basic_block_->AddStmt(store_stmt);

  }
  // //lhs is not necessarily an idnode, can also be array node or object.x
  // else if (auto lhs_index_expr = std::dynamic_pointer_cast<IndexExprNode>(node->getLhs())) {
  //   // gep
  //   // store
  //   // IndexExprGEP(lhs_index_expr, true);
  //   LhsIndexExpr(lhs_index_expr);
  //   //compute rhs, store
  //   auto addr_reg = current_func_->GetReturnReg();
  //   auto rhs_expr = node->getRhs();
  //   // rhs_expr->accept(this);
  //   // auto rhs_reg = current_func_->GetLastReg();
  //   auto rhs_rep = LiteralResolver(rhs_expr);
  //   std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
  //     std::make_shared<StoreStmt>(rhs_rep, addr_reg));
  //   current_basic_block_->AddStmt(store_stmt);
  //
  // } else if (auto lhs_dot_expr = std::dynamic_pointer_cast<DotExprNode>(node->getLhs())) {
  //   // find offset
  //   // gep
  //   // store
  //   LhsDotExpr(lhs_dot_expr);
  //   // lhs_dot_expr->accept(this);
  //   auto addr_reg = current_func_->GetReturnReg();
  //   auto rhs_expr = node->getRhs();
  //   // rhs_expr->accept(this);
  //   // auto rhs_reg = current_func_->GetLastReg();
  //   auto rhs_rep = LiteralResolver(rhs_expr);
  //   std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
  //     std::make_shared<StoreStmt>(rhs_rep, addr_reg));
  //   current_basic_block_->AddStmt(store_stmt);
  // } else if (auto lhs_this_expr = std::dynamic_pointer_cast<ThisExprNode>(node->getLhs())) {
  //   LhsThisExpr(lhs_this_expr);
  //   auto store_addr_reg = current_func_->GetReturnReg();
  //   auto rhs_expr = node->getRhs();
  //   auto rhs_rep = LiteralResolver(rhs_expr);
  //
  //
  // }
}

void IRGenerator::visit(std::shared_ptr<BlockStatNode> node) {
  auto new_scope = IRScope::CreateScope(current_scope_);
  current_scope_ = new_scope;
  auto stmts = node->getBlockNode()->getStatNodes();
  for (auto stmt : stmts) {
    stmt->accept(this);
  }
  current_scope_ = current_scope_->GetParent();
}

void IRGenerator::visit(std::shared_ptr<ParenExprNode> node) {
  auto expr = node->getInnerExpr();
  LiteralResolver(expr);
}

void IRGenerator::visit(std::shared_ptr<IfStatNode> node) {
  auto pred = node->getPredicate();
  // pred->accept(this);
  // auto pred_reg = current_func_->GetReturnReg();
  auto pred_reg = LiteralResolver(pred);

  auto then_ast_block = node->getThenBlock();
  auto else_ast_block = node->getElseBlock();

  auto then_block_name = current_func_->CreateBlockName("then_block", false);
  auto end_block_name = current_func_->CreateBlockName("end_block", false);
  // auto to_then = std::make_shared<BrUnconditionalStmt>(then_block->getBlockName());
  // current_basic_block_->AddStmt(to_then);
  auto to_end = std::make_shared<BrUnconditionalStmt>(end_block_name);
  //predicate evaluation
  auto curr_block_tmp = current_basic_block_;
  if (else_ast_block == nullptr) {
    auto if_stmt = std::static_pointer_cast<Stmt>(
    std::make_shared<BrConditionalStmt>(pred_reg, then_block_name, end_block_name));
    current_basic_block_->AddStmt(if_stmt);
    auto then_block = current_func_->CreateBlock(then_block_name);
    current_basic_block_ = then_block;
    then_ast_block->accept(this);
    current_basic_block_->AddStmt(to_end);
    auto end_block = current_func_->CreateBlock(end_block_name);
    current_basic_block_ = end_block;
  } else {
    auto else_block_name = current_func_->CreateBlockName("else_block", false);
    auto if_stmt = std::static_pointer_cast<Stmt>(
    std::make_shared<BrConditionalStmt>(pred_reg, then_block_name, else_block_name));
    current_basic_block_->AddStmt(if_stmt);
    auto then_block = current_func_->CreateBlock(then_block_name);
    current_basic_block_ = then_block;
    then_ast_block->accept(this);
    current_basic_block_->AddStmt(to_end);
    current_basic_block_ = curr_block_tmp;
    auto else_block = current_func_->CreateBlock(else_block_name);
    current_basic_block_ = else_block;
    else_ast_block->accept(this);
    current_basic_block_->AddStmt(to_end);
    auto end_block = current_func_->CreateBlock(end_block_name);

    current_basic_block_ = end_block;
    //jump end block
  }
}

void IRGenerator::InitFuncParam(std::shared_ptr<FuncDefNode> func_def_node) {
  //store all params to corresponding address
  int param_count = 0;
  if (current_func_->IsInClass()) { // store "this" reg
    // std::shared_ptr<IRType> param_type = std::make_shared<IRType>(current_func_->GetBelong(), 1); //'this' is passed as a param
    std::shared_ptr<IRType> reg_type = std::make_shared<IRType>(current_func_->GetBelong(), 1); // 'this' is stored as a reg
    std::shared_ptr<Register> reg = current_func_->CreateRegister(reg_type);
    std::shared_ptr<Register> param_reg = current_func_->GetParamReg(param_count++);
    std::shared_ptr<Stmt> alloca_stmt = static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(reg));
    std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(param_reg, reg));
    current_basic_block_->AddStmt(alloca_stmt);
    current_basic_block_->AddStmt(store_stmt);
    current_scope_->declare("this", reg); //name the self pointer "this"
  }
  for (auto param : func_def_node->getVarDefs()) {
    std::shared_ptr<IRType> reg_type = std::make_shared<IRType>(param->getIdNode()->getType(), param->getIdNode()->getType()->getDimension() + 1);
    // std::shared_ptr<IRType> param_type = std::make_shared<IRType>(param->getIdNode()->getType(), 0);
    std::shared_ptr<Register> reg = current_func_->CreateRegister(reg_type);
    std::shared_ptr<Register> param_reg = current_func_->GetParamReg(param_count++);
    std::shared_ptr<Stmt> alloca_stmt = static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(reg));
    std::shared_ptr<Stmt> store_stmt = static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(param_reg, reg));
    current_basic_block_->AddStmt(alloca_stmt);
    current_basic_block_->AddStmt(store_stmt);
    current_scope_->declare(param->getIdNode()->getIdName(), reg);
    //whenever there is an alloca, we need to add it to scope
  }
}



std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> IRGenerator::FetchExprReg(
  std::shared_ptr<ExprNode> expr) {
  // must be directly after accept
  // if (auto id = std::dynamic_pointer_cast<IdNode>(expr)) {
  //   return current_scope_->FindRegister(id->getIdName());
  // } else
  if (auto literal = std::dynamic_pointer_cast<LiteralNode>(expr)) {
    if (*literal->getLiteralType() != *k_string) {
      return literal;
    } else {
      std::shared_ptr<Register> string_reg = CreateString(literal);
      return string_reg;
      //global
    }
  } else {
    return current_func_->GetLastReg();
  }
}



std::shared_ptr<Register> IRGenerator::CreateString(std::shared_ptr<LiteralNode> string_literal) {
  // auto string_type = std::make_shared<IRType>(IRType::kSTRING);
  // auto string_reg = std::make_shared<Register>(string_literal->ToString(), string_type, true);
  // auto stmt = std::make_shared<GlobalStmt>(string_literal->ToString());
  // global_scope_->AddGlobalStmt(stmt->commit());
  // global_scope_->declare(string_literal->ToString(), string_reg);
  // return string_reg;
  auto string_val = std::get<std::string>(string_literal->GetValue());
  std::hash<std::string> hasher;
  auto hashed_val = static_cast<unsigned int>(hasher(string_val));
  if (!str_reg_counter.contains(hashed_val)) {
    str_reg_counter[hashed_val].emplace_back(string_val);
  } else {
    for (int i = 0; i < str_reg_counter[hashed_val].size(); i++) {
      if (str_reg_counter[hashed_val][i] == string_val) {
        return global_scope_->FindRegister(".str." + std::to_string(hashed_val) + "." + std::to_string(i));
      }
    }
    str_reg_counter[hashed_val].emplace_back(string_val);
  }
  auto reg_name = ".str." + std::to_string(hashed_val) + "." + std::to_string(str_reg_counter[hashed_val].size() - 1);
  auto string_reg = std::make_shared<Register>(reg_name, k_ir_string, true);
  global_scope_->declare(reg_name, string_reg);
  auto str_declare_stmt = std::make_shared<GlobalStmt>(reg_name, string_val);
  global_scope_->AddGlobalStmt(str_declare_stmt);
  return string_reg;
}

std::shared_ptr<Register> IRGenerator::ToRightVal(std::shared_ptr<Register> reg) {
  auto rval_reg = current_func_->CreateRegister(reg->GetType()->DecreaseDimension());
  auto stmt = std::make_shared<LoadStmt>(rval_reg, reg);
  return rval_reg;
}

std::shared_ptr<Register> IRGenerator::FindRegister(const std::string& var_name) {
  auto result_reg = current_scope_->FindRegister(var_name);
  if (result_reg != nullptr && !result_reg->IsGlobal()) {
    return result_reg;
  } else if (current_func_->IsInClass()) {
    //search this.var_name
    auto this_reg = current_scope_->FindRegister("this");
    auto obj_reg_type = std::make_shared<IRType>(this_reg->GetType(), -1);
    auto obj_reg = current_func_->CreateRegister(obj_reg_type);
    auto load_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<LoadStmt>(obj_reg, this_reg));

    auto obj_type = obj_reg->GetType();
    auto obj_type_name = obj_type->GetTypeName();
    auto offset = GetElementInStruct(obj_type_name, var_name).second;
    std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
    params.push_back(offset);
    auto gep_dest_reg_type = GetElementInStruct(obj_type_name, var_name).first;
    if (gep_dest_reg_type == nullptr) {
      result_reg =  global_scope_->FindRegister(var_name);
      if (result_reg == nullptr) {
        throw std::runtime_error("cannot find register");
      }
      return result_reg;
    }
    auto gep_dest_reg = current_func_->CreateRegister(gep_dest_reg_type);
    auto gep_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<GEPStmt>(gep_dest_reg, obj_reg, params));
    current_basic_block_->AddStmt(load_stmt);
    current_basic_block_->AddStmt(gep_stmt);
    return gep_dest_reg;
  } else {
    result_reg =  global_scope_->FindRegister(var_name);
    if (result_reg == nullptr) {
      throw std::runtime_error("cannot find register");
    }
    return result_reg;
  }

}

std::shared_ptr<IRFunction> IRGenerator::FindFunction(const std::string& func_name) {
  // auto ret_func = funcs_[func_name];
  if (funcs_.contains(func_name)) {
    return funcs_[func_name];

  } else {
    auto class_name = current_func_->GetBelong();
    if (funcs_.contains(class_name + "_" + func_name)) {
      return funcs_[class_name + "_" + func_name];
    } else {
      throw std::runtime_error("cannot find function");
    }
  }
}

std::pair<std::shared_ptr<IRType>, int> IRGenerator::GetElementInStruct(std::string type_name, std::string field_name) {
  //get the index in a struct
  if (types_.contains(type_name)) {
    return types_[type_name]->GetElement(field_name);
  } else {
    return std::pair<std::shared_ptr<IRType>, int>(nullptr, -1);
  }
}

/**
 * automatically generate gep and store stmt for a specific array.
 */

/**
 * for the last layer, we store the data
 * for the previous layers, we store the addresses
 * that means, we need to fetch address info from reg for every next-level array
 * and store the info into current level array
 *
 * 1. last level array, a reg storing address
 * 2. current level array: store the reg
 * 3. current level array: store the reg info
 *
 * at runtime, the calloc will trigger a memory allocation, returning the address to the reg
 */
void IRGenerator::InitializeArray(std::shared_ptr<Register> base, std::shared_ptr<ArrayConstNode> array_const) { //use when array_const exists.


  if (!array_const->GetLiteralElements().empty()) {  // there are literals, meaning this is the last layer
    auto literal_elements = array_const->GetLiteralElements();
    auto literal_type = literal_elements[0]->getLiteralType();
    std::shared_ptr<Register> base_reg;
    if (*literal_type == *k_string) { //just allocate space
      auto addr_type = std::make_shared<IRType>(k_ir_string, 1);// if it is a string, then it is a 2-dimensional array
      base_reg = current_func_->CreateRegister(addr_type);
      auto array_alloc_func = FindFunction("Array_Alloc");
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
      int element_length = literal_elements.size();
      params.push_back(element_length);
      auto array_alloc_call_stmt = std::make_shared<CallStmt>(array_alloc_func, base_reg, params);
      current_basic_block_->AddStmt(array_alloc_call_stmt);
      /**
     * gep
     * store
     */
      for (int i = 0; i < literal_elements.size(); i++) {
        //fetch position
        auto reg_type = std::make_shared<IRType>(k_ir_string, 1);
        auto addr_reg = current_func_->CreateRegister(reg_type);
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices;
        indices.emplace_back(i);
        auto str = std::get<std::string>(literal_elements[i]->GetValue());
        auto global_str_reg = global_scope_->FindRegister(str);
        //find the reg that stores this str
        std::shared_ptr<Stmt> gep_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<GEPStmt>(addr_reg, base_reg, indices)); // fetch i_th addr    warning: how to compute offset?
        std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<StoreStmt>(global_str_reg, addr_reg));//the reg that stores this str
        current_basic_block_->AddStmt(gep_stmt);
        current_basic_block_->AddStmt(store_stmt);
      }
    } else { // not string
      auto addr_type = std::make_shared<IRType>(literal_type, 1);// if it is a string, then it is a 2-dimensional array
      base_reg = current_func_->CreateRegister(addr_type);
      auto array_alloc_func = FindFunction("Array_Alloc");
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
      int element_length = literal_elements.size();
      params.emplace_back(element_length);
      auto array_alloc_call_stmt = std::make_shared<CallStmt>(array_alloc_func, base_reg, params);
      current_basic_block_->AddStmt(array_alloc_call_stmt);
      /**
     * gep
     * store
     */
      for (int i = 0; i < literal_elements.size(); i++) {
        //fetch position
        auto addr_reg = current_func_->CreateRegister(addr_type);
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices;
        indices.emplace_back(i);
        std::shared_ptr<Stmt> gep_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<GEPStmt>(addr_reg, base_reg, indices)); // fetch i_th addr    warning: how to compute offset?
        std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<StoreStmt>(literal_elements[i], addr_reg));
        current_basic_block_->AddStmt(gep_stmt);
        current_basic_block_->AddStmt(store_stmt);

      }
    }

  } else {

    // for each element:
    // fetch previous registers
    // allocate memory (builtin_calllocArray)
    // for each element:
    // gep + store
    int depth = -1;
    std::shared_ptr<IRType> curr_type;
    std::vector<std::shared_ptr<Register>> ptr_regs;
    for (int i = 0; i < array_const->GetArrayElements().size(); i++) {
      InitializeArray(base, array_const->GetArrayElements()[i]);
      ptr_regs.push_back(current_func_->GetLastReg());
    }
    if (!ptr_regs.empty()) {
      depth = current_func_->GetLastReg()->GetType()->GetDim() + 1;
      curr_type = std::make_shared<IRType>(current_func_->GetLastReg()->GetType(), 1);
    }
    // auto addr_type = std::make_shared<IRType>();
    auto base_reg = current_func_->CreateRegister(curr_type);
    auto array_alloc_func = FindFunction("Array_Alloc");
    std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
    int element_length = array_const->GetArrayElements().size();
    assert(element_length == ptr_regs.size());
    params.emplace_back(element_length);
    auto array_alloc_call_stmt = std::make_shared<CallStmt>(array_alloc_func, base_reg, params);
    current_basic_block_->AddStmt(array_alloc_call_stmt);
    for (int i = 0; i <element_length; i++) {
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices;
      indices.emplace_back(i);
      auto addr_reg = current_func_->CreateRegister(curr_type);
      std::shared_ptr<Stmt> gep_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<GEPStmt>(addr_reg, base_reg, indices)); // fetch i_th addr    warning: how to compute offset?
      std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<StoreStmt>(ptr_regs[i], addr_reg));
    }
  }
}

void IRGenerator::DeclareArray(std::shared_ptr<InitArrayNode> node, std::vector<std::shared_ptr<ExprNode>> range_vec, int pos) {
  //remains some problems about new int[5][5][]

  //recursively allocate space
  auto array_alloc_func = FindFunction("Array_Alloc");
  if (pos == static_cast<int>(range_vec.size() - 1) || range_vec[pos + 1] == nullptr) {
    if (auto range_literal = std::dynamic_pointer_cast<LiteralNode>(range_vec[pos])) {
      int range_val = std::get<int>(std::dynamic_pointer_cast<LiteralNode>(range_vec[pos])->GetValue());
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> alloc_params;
      alloc_params.emplace_back(range_val);
      auto base_type = std::make_shared<IRType>(node->getType(), range_vec.size() - pos);
      auto dest_reg = current_func_->CreateRegister(base_type);
      auto array_alloc_call_stmt = std::make_shared<CallStmt>(array_alloc_func, dest_reg, alloc_params);
      current_basic_block_->AddStmt(array_alloc_call_stmt);
      current_func_->SetReturnReg(dest_reg);
    } else {
      const auto& curr_range = range_vec[pos];
      curr_range->accept(this);
      auto range_reg = current_func_->GetLastReg();
      // auto size_reg = current_func_->CreateRegister(range_reg->GetType());
      // auto mul_stmt = std::static_pointer_cast<Stmt>(
      //   std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kMUL, range_reg, 4, size_reg));
      // current_basic_block_->AddStmt(mul_stmt);
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
      params.emplace_back(range_reg);
      auto malloc_dest_type = std::make_shared<IRType>(k_ir_void, range_vec.size() - pos);
      auto malloc_dest_reg = current_func_->CreateRegister(malloc_dest_type);
      auto malloc_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(array_alloc_func, malloc_dest_reg, params));
      current_basic_block_->AddStmt(malloc_stmt);
      current_func_->SetReturnReg(malloc_dest_reg);
    }
  } else {
    if (auto range_literal = std::dynamic_pointer_cast<LiteralNode>(range_vec[pos])) {
      //call, store (here we only consider cases where ranges are all constants)
      int range_val = std::get<int>(std::dynamic_pointer_cast<LiteralNode>(range_vec[pos])->GetValue());
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> alloc_params;
      alloc_params.emplace_back(range_val);

      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> addr_regs;
      for (int i = 0; i < range_val; i++) {
        DeclareArray(node, range_vec, pos + 1);
        addr_regs.emplace_back(current_func_->GetReturnReg());
      }
      auto dest_type = std::make_shared<IRType>(std::get<std::shared_ptr<Register>>(addr_regs[0])->GetType(), 1);
      auto dest_reg = current_func_->CreateRegister(dest_type);
      auto array_alloc_call_stmt = std::make_shared<CallStmt>(array_alloc_func, dest_reg, alloc_params);
      current_basic_block_->AddStmt(array_alloc_call_stmt);
      for (int i = 0; i < range_val; i++) {
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices;
        indices.emplace_back(i);
        auto dest_addr_reg = current_func_->CreateRegister(dest_type);
        std::shared_ptr<Stmt> gep_stmt = std::static_pointer_cast<Stmt>(
            std::make_shared<GEPStmt>(dest_addr_reg, dest_reg, indices)); // fetch i_th addr    warning: how to compute offset?
        std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<StoreStmt>(std::get<std::shared_ptr<Register>>(addr_regs[i]), dest_addr_reg));
        current_basic_block_->AddStmt(gep_stmt);
        current_basic_block_->AddStmt(store_stmt);
      }
      current_func_->SetReturnReg(dest_reg);
    } else {
      //if range is a variable
      auto range_loop_start_block_name = current_func_->CreateBlockName("init_array_start" + std::to_string(pos), false);
      auto range_loop_body_block_name = current_func_->CreateBlockName("init_array_body" + std::to_string(pos), false);
      auto end_block_name = current_func_->CreateBlockName("init_array_end" + std::to_string(pos), false);
      auto counter_reg_type = std::make_shared<IRType>(k_ir_int, 1);
      auto counter_reg = current_func_->CreateRegister(counter_reg_type);
      auto alloca_counter_reg_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<AllocaStmt>(counter_reg));
      current_basic_block_->AddStmt(alloca_counter_reg_stmt);
      auto store_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<StoreStmt>(0, counter_reg));
      current_basic_block_->AddStmt(store_stmt);
      const auto& curr_range = range_vec[pos];
      curr_range->accept(this);
      auto range_reg = current_func_->GetReturnReg();
      // auto size_reg = current_func_->CreateRegister(range_reg->GetType());
      // auto mul_stmt = std::static_pointer_cast<Stmt>(
        // std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kMUL, range_reg, 4, size_reg));
      // current_basic_block_->AddStmt(mul_stmt);
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
      params.emplace_back(range_reg);
      auto malloc_dest_type = std::make_shared<IRType>(k_ir_void, range_vec.size() - pos);
      auto malloc_dest_reg = current_func_->CreateRegister(malloc_dest_type);
      auto malloc_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(array_alloc_func, malloc_dest_reg, params));
      current_basic_block_->AddStmt(malloc_stmt);
      auto br_layer_a_start_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BrUnconditionalStmt>(range_loop_start_block_name));
      current_basic_block_->AddStmt(br_layer_a_start_stmt);
      //loop_layer_a_start:
      // auto tmp_block = current_basic_block_;
      auto range_loop_start_block = current_func_->CreateBlock(range_loop_start_block_name);
      current_basic_block_ = range_loop_start_block;

      auto counter_val_reg = current_func_->CreateRegister(k_ir_int);
      auto load_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<LoadStmt>(counter_val_reg, counter_reg));
      current_basic_block_->AddStmt(load_stmt);
      auto cmp_reg = current_func_->CreateRegister(k_ir_bool);
      auto cmp_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kLT, counter_val_reg, range_reg, cmp_reg));
      current_basic_block_->AddStmt(cmp_stmt);
      auto br_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BrConditionalStmt>(cmp_reg, range_loop_body_block_name, end_block_name));
      current_basic_block_->AddStmt(br_stmt);

      //loop_layer_a_body:
      auto range_loop_body_block = current_func_->CreateBlock(range_loop_body_block_name);
      current_basic_block_ = range_loop_body_block;
      // current_basic_block_->AddStmt(malloc_stmt);
      DeclareArray(node, range_vec, pos + 1);
      auto next_layer_reg = current_func_->GetReturnReg();
      auto gep_dest_reg = current_func_->CreateRegister(malloc_dest_type);
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> gep_params;
      gep_params.emplace_back(counter_val_reg);
      auto gep_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<GEPStmt>(gep_dest_reg, malloc_dest_reg, gep_params));
      current_basic_block_->AddStmt(gep_stmt);

      auto store_array_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<StoreStmt>(next_layer_reg, gep_dest_reg));
      current_basic_block_->AddStmt(store_array_stmt);
      auto counter_val_updated_reg = current_func_->CreateRegister(k_ir_int);
      auto add_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, counter_val_reg, 1, counter_val_updated_reg));
      current_basic_block_->AddStmt(add_stmt);
      auto store_updated_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<StoreStmt>(counter_val_updated_reg, counter_reg));
      current_basic_block_->AddStmt(store_updated_stmt);
      auto br_start_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BrUnconditionalStmt>(range_loop_start_block_name));
      current_basic_block_->AddStmt(br_start_stmt);
      auto end_block = current_func_->CreateBlock(end_block_name);
      current_basic_block_ = end_block;
      current_func_->SetReturnReg(malloc_dest_reg);
    }
  }
}


std::shared_ptr<ClassType> IRGenerator::GetClassType(const std::string& type_name) {
  return types_[type_name];
}

// void IRGenerator::IndexExprGEP(std::shared_ptr<IndexExprNode> expr, bool is_lval) {
//   //solves recursion better than visit
//   //a: int*
//   //a[i]:
//   std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices;
//   while (1) {
//     if (auto id_node = std::dynamic_pointer_cast<IdNode>(expr->getBase())) {
//       auto base_reg_star = FindRegister(id_node->getIdName());
//       auto base_reg = current_func_->CreateRegister(std::make_shared<IRType>(base_reg_star->GetType(), -1));
//       auto load_id_stmt = std::static_pointer_cast<Stmt>(
//         std::make_shared<LoadStmt>(base_reg, base_reg_star));
//       current_basic_block_->AddStmt(load_id_stmt);
//       auto index_expr_node = expr->getIndex();
//       auto index_rep = LiteralResolver(index_expr_node);
//       indices.emplace_back(index_rep);
//       //gep
//       reverse(indices.begin(), indices.end());
//
//       for (int i = 0; i < indices.size(); i++) {
//         const auto& idx = indices[i];
//         std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
//         params.emplace_back(idx);
//         const auto& gep_dest_reg = current_func_->CreateRegister(base_reg->GetType());
//         auto gep_stmt = std::static_pointer_cast<Stmt>(
//           std::make_shared<GEPStmt>(gep_dest_reg, base_reg, params));
//         current_basic_block_->AddStmt(gep_stmt);
//         current_func_->SetReturnReg(gep_dest_reg);
//         if (i != indices.size() - 1 || !is_lval) {
//           auto dest_reg = current_func_->CreateRegister(std::make_shared<IRType>(base_reg->GetType(), -1));
//           auto load_stmt = std::static_pointer_cast<Stmt>(
//           std::make_shared<LoadStmt>(dest_reg, gep_dest_reg));
//           current_basic_block_->AddStmt(load_stmt);
//           base_reg = dest_reg;
//           current_func_->SetReturnReg(dest_reg);
//         }
//
//
//       }
//       break;
//     } else {
//       auto index_expr_node = expr->getIndex();
//       auto index_rep = LiteralResolver(index_expr_node);
//       indices.emplace_back(index_rep);
//       expr = std::dynamic_pointer_cast<IndexExprNode>(expr->getBase());
//     }
//   }
// }


void IRGenerator::LhsIndexExpr(std::shared_ptr<IndexExprNode> expr) {
  auto base = expr->getBase();
  auto index = expr->getIndex();
  base->accept(this);
  auto base_reg = current_func_->GetReturnReg();
  std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
  auto index_rep = LiteralResolver(index);
  auto result_reg = current_func_->CreateRegister(base_reg->GetType());
  params.push_back(index_rep);
  auto gep_stmt = std::static_pointer_cast<Stmt>(std::make_shared<GEPStmt>(result_reg, base_reg, params));
  current_basic_block_->AddStmt(gep_stmt);
  current_func_->SetReturnReg(result_reg);
}

// void IRGenerator::DotExprGEP(std::shared_ptr<DotExprNode> expr, bool is_lval) {
//
//   std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices;
//   std::vector<std::shared_ptr<IRType>> element_types;
//   while (1) {
//     if (auto id_node = std::dynamic_pointer_cast<DotExprNode>(expr->getLhs())) {
//       auto base_type = std::make_shared<IRType>(expr->getLhs()->getExprType());
//       auto dot_id_node = std::dynamic_pointer_cast<IdNode>(expr->getRhs());
//       auto dot_index = types_[base_type->GetTypeName()]->GetElementIndex(dot_id_node->getIdName());
//       auto dot_type = types_[base_type->GetTypeName()]->GetElementType(dot_id_node->getIdName());
//       indices.emplace_back(dot_index);
//       element_types.emplace_back(dot_type);
//       expr = std::dynamic_pointer_cast<DotExprNode>(expr->getLhs());
//     } else {
//       // auto lhs_rep = LiteralResolver(expr->getLhs());
//       auto lhs = expr->getLhs();
//       lhs->accept(this);
//       auto lhs_reg = current_func_->GetReturnReg();
//       auto id_type = lhs_reg->GetType();
//       // auto id_type = FindRegister(id_node->getIdName())->GetType();
//       // auto base_reg_star = current_scope_->FindRegister(id_node->getIdName());
//       // auto base_reg = current_func_->CreateRegister(std::make_shared<IRType>(base_reg_star->GetType(), -1));
//       auto dot_id_node = std::dynamic_pointer_cast<IdNode>(expr->getRhs());
//       // auto load_id_stmt = std::static_pointer_cast<Stmt>(
//       //   std::make_shared<LoadStmt>(base_reg, base_reg_star));
//       // current_basic_block_->AddStmt(load_id_stmt);
//       //find dot id
//       auto dot_index = types_[id_type->GetTypeName()]->GetElementIndex(dot_id_node->getIdName());
//       auto dot_type = types_[id_type->GetTypeName()]->GetElementType(dot_id_node->getIdName());
//       indices.emplace_back(dot_index);
//       element_types.emplace_back(dot_type);
//       // auto dest_reg = current_func_->CreateRegister(base_reg->GetType());
//       //gep
//       reverse(indices.begin(), indices.end());
//
//       // std::shared_ptr<Stmt> gep_stmt = std::static_pointer_cast<Stmt>(
//       //       std::make_shared<GEPStmt>(dest_reg, base_reg, indices));
//       // current_basic_block_->AddStmt(gep_stmt);
//       for (int i = 0; i < indices.size(); i++) {
//         const auto& idx = indices[i];
//         std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
//         params.emplace_back(0);
//         params.emplace_back(idx);
//         const auto& gep_dest_reg = current_func_->CreateRegister(base_reg->GetType());
//         auto gep_stmt = std::static_pointer_cast<Stmt>(
//           std::make_shared<GEPStmt>(gep_dest_reg, base_reg, params));
//         current_basic_block_->AddStmt(gep_stmt);
//         current_func_->SetReturnReg(gep_dest_reg);
//         if (i != indices.size() - 1 || !is_lval) {
//           auto dest_reg = current_func_->CreateRegister(element_types[i]);
//           auto load_stmt = std::static_pointer_cast<Stmt>(
//           std::make_shared<LoadStmt>(dest_reg, gep_dest_reg));
//           current_basic_block_->AddStmt(load_stmt);
//           base_reg = dest_reg;
//           current_func_->SetReturnReg(dest_reg);
//         }
//       }
//
//
//       break;
//     }
//   }
// }

void IRGenerator::LhsDotExpr(std::shared_ptr<DotExprNode> expr) {
  auto lhs = expr->getLhs();
  auto rhs = expr->getRhs();
  // lhs->accept(this);
  // auto lhs_rep = FetchExprReg(lhs);
  auto lhs_rep = LiteralResolver(lhs);
  std::shared_ptr<IRType> lhs_type;
  if (std::holds_alternative<std::shared_ptr<LiteralNode>>(lhs_rep)) {
    lhs_type = std::make_shared<IRType>(std::get<std::shared_ptr<LiteralNode>>(lhs_rep)->getLiteralType());
  } else {
    lhs_type = std::get<std::shared_ptr<Register>>(lhs_rep)->GetType();
  }
  if (auto func_call = std::dynamic_pointer_cast<FuncCallNode>(rhs)) {

    std::string func_name;
    if (lhs_type->GetDim() == 0 || *lhs_type == *k_ir_string) {
      func_name = lhs_type->GetTypeName() + "_" + func_call->getName();
    } else if (lhs_type->GetDim() >= 1) {
      func_name = "Array_" + func_call->getName();
    }
    std::shared_ptr<IRFunction> func = FindFunction(func_name);
    auto args = func_call->getArgs();
    std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> arg_reps;
    arg_reps.push_back(lhs_rep); // pass lhs as 'this' param
    for (const auto& arg : args) {
      // arg->accept(this);
      // auto arg_rep = FetchExprReg(arg);
      auto arg_rep = LiteralResolver(arg);
      arg_reps.push_back(arg_rep);
    }
    auto return_type = func->GetReturnType();
    if (*return_type == *k_ir_void) {
      auto dest_reg = current_func_->CreateRegister(func->GetReturnType());
      std::shared_ptr<Stmt> call_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(func, dest_reg, arg_reps));
      current_basic_block_->AddStmt(call_stmt);
      current_func_->SetReturnReg(dest_reg);
    } else {
      std::shared_ptr<Stmt> call_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(func, arg_reps));
      current_basic_block_->AddStmt(call_stmt);
    }


  } else if (auto field = std::dynamic_pointer_cast<IdNode>(rhs)) {
    /* store address of the class in a reg(Type**)
     * load on use
     */
    std::string var_name = field->getIdName();
    std::pair<std::shared_ptr<IRType>, int> element = GetElementInStruct(lhs_type->GetTypeName(), var_name);
    auto dest_reg = current_func_->CreateRegister(element.first);
    // auto base_reg_type = types_[lhs_type->GetTypeName()]->GetElementType();
    // auto base_reg = current_func_->CreateRegister(base_reg_type);
    //gep
    auto base_reg = std::get<std::shared_ptr<Register>>(lhs_rep);
    std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> offsets;
    offsets.push_back(0);
    offsets.push_back(element.second);
    std::shared_ptr<Stmt> gep_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<GEPStmt>(dest_reg, base_reg, offsets, true));
    current_basic_block_->AddStmt(gep_stmt);
    current_func_->SetReturnReg(dest_reg);
  }
}

void IRGenerator::LhsThisExpr(std::shared_ptr<ThisExprNode> expr) {
  auto this_reg = FindRegister("this");
  current_func_->SetReturnReg(this_reg);
}

void IRGenerator::LhsParenExpr(std::shared_ptr<ParenExprNode> node) {
  auto expr = node->getInnerExpr();
  LvalVisit(expr);
}

std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register> > IRGenerator::LiteralResolver(std::shared_ptr<ExprNode> expr) {
  if (auto literal_node = std::dynamic_pointer_cast<LiteralNode>(expr)) {
    if (literal_node->getLiteralType()->compareBase(*k_string)) {
      // define the string in global scope reg
      // return the reg
      return CreateString(literal_node);
    } else {
      return literal_node;
    }
  } else {
    expr->accept(this);
    return current_func_->GetReturnReg();
  }
}

std::shared_ptr<IRType> IRGenerator::GetVariantType(std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register> > var) {
  if (std::holds_alternative<int>(var)) {
    return k_ir_int;
  } else if (std::holds_alternative<bool>(var)) {
    return k_ir_bool;
  } else if (std::holds_alternative<std::shared_ptr<LiteralNode>>(var)) {
    auto literal_var = std::get<std::shared_ptr<LiteralNode>>(var);
    return literal_var->getLiteralIRType();
  } else {
    auto reg_var = std::get<std::shared_ptr<Register>>(var);
    return reg_var->GetType();
  }
}

void IRGenerator::GlobalVarDefInit(std::shared_ptr<VarDefNode> var_def_node) {
  auto lhs = var_def_node->getIdNode();
  auto rhs = var_def_node->getExpr();
  auto assign_node = std::make_shared<AssignStatNode>(lhs, rhs, var_def_node->getPosition());
  assign_node->accept(this);
}

void IRGenerator::ForwardDeclare(std::shared_ptr<RootNode> root_node) {
  auto def_nodes = root_node->getDefNodes();
  for (const auto& def : def_nodes) {
    if (auto func_def_node = std::dynamic_pointer_cast<FuncDefNode>(def)) {
      std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(func_def_node);
      funcs_[func->GetName()] = func;
    }
    else if (const auto &class_def_node = std::dynamic_pointer_cast<ClassDefNode>(def)) {
      bool has_class_func = false;
      bool has_var = false;
      std::shared_ptr<ClassType> class_type = std::make_shared<ClassType>(class_def_node->getIdNode()->getIdName());
      types_[class_def_node->getIdNode()->getIdName()] = class_type;
      current_class_type_ = class_type;
      for (const auto& in_class_stat : class_def_node->getBlockNode()->getStatNodes()) {
        if (auto var_def = std::dynamic_pointer_cast<VarDefNode>(in_class_stat)) {
          //add to type
          has_var = true;
          std::shared_ptr<IRType> var_type = std::make_shared<IRType>(var_def->getIdNode()->getType(), var_def->getIdNode()->getType()->getDimension() + 1);
          current_class_type_->AddElement(var_def->getIdNode()->getIdName(), var_type); // declared type in RootNode
        } else if (auto func_def = std::dynamic_pointer_cast<FuncDefNode>(in_class_stat)) {
          std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(func_def, class_def_node->getIdNode()->getIdName());
          funcs_[func->GetName()] = func;
        } else if (auto class_func_def = std::dynamic_pointer_cast<ClassFuncDefNode>(in_class_stat)) {
          std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(class_func_def);
          funcs_[func->GetName()] = func;
          has_class_func = true;
        }
      }
      //if no vars, add a dummy var
      if (!has_var) {
        auto dummy_type = std::make_shared<IRType>(k_bool, 0);
        current_class_type_->AddElement("_dummy", dummy_type);
      }

      if (!has_class_func) { // if no class func def, automatically generate one.
        auto func_name = class_def_node->getIdNode()->getIdName();
        auto this_type = std::make_shared<IRType>(func_name, 2);
        std::vector<std::shared_ptr<IRType>> param_type;
        param_type.push_back(this_type);
        std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(func_name, param_type, k_ir_void, func_name);
        current_basic_block_ = func->CreateBlock(func_name + ".entry");
        std::shared_ptr<Stmt> ret_stmt = std::static_pointer_cast<Stmt>(std::make_shared<ReturnStmt>());
        current_basic_block_->AddStmt(ret_stmt);
        funcs_[func_name + "_" + func_name] = func;
      }
      current_class_type_ = nullptr;

    }
  }
}

void IRGenerator::LvalVisit( std::shared_ptr<ExprNode> expr) {
 if (auto lhs_id = dynamic_pointer_cast<IdNode>(expr)) {
    auto id_reg = FindRegister(lhs_id->getIdName());
    auto node_type = id_reg->GetType();
    //visit expr
   current_func_->SetReturnReg(id_reg);
  }
  //lhs is not necessarily an idnode, can also be array node or object.x
  else if (auto lhs_index_expr = std::dynamic_pointer_cast<IndexExprNode>(expr)) {
    // IndexExprGEP(lhs_index_expr, true);
    LhsIndexExpr(lhs_index_expr);
    auto addr_reg = current_func_->GetReturnReg();
    current_func_->SetReturnReg(addr_reg);
  } else if (auto lhs_dot_expr = std::dynamic_pointer_cast<DotExprNode>(expr)) {
    LhsDotExpr(lhs_dot_expr);
    auto addr_reg = current_func_->GetReturnReg();
    current_func_->SetReturnReg(addr_reg);
  } else if (auto this_expr = std::dynamic_pointer_cast<ThisExprNode>(expr)) {
    LhsThisExpr(this_expr);
  } else if (auto paren_expr = std::dynamic_pointer_cast<ParenExprNode>(expr)) {
    LhsParenExpr(paren_expr);
  }
}
bool IRGenerator::ImmediateInitialize(std::shared_ptr<ExprNode> expr) {
  if (auto literal_expr = std::dynamic_pointer_cast<LiteralNode>(expr)) {
    return true;
  } else if (auto paren_expr = std::dynamic_pointer_cast<ParenExprNode>(expr)) {
    return ImmediateInitialize(paren_expr->getInnerExpr());
  } else {
    return false;
  }
}


