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
  auto def_nodes = root_node->getDefNodes();
  for (const auto def_node : def_nodes) {
    if (auto var_def = std::dynamic_pointer_cast<VarDefNode>(def_node)) {
      auto reg_type = std::make_shared<IRType>(var_def->getIdNode()->getType(), 1);
      std::shared_ptr<Register> reg = std::make_shared<Register>(var_def->getIdNode()->getIdName(), reg_type, true);
      global_scope_->declare(reg->GetName(), reg);
      global_scope_->AddGlobalStmt(std::make_shared<GlobalStmt>(var_def)->commit());
    } else if (auto func_def = std::dynamic_pointer_cast<FuncDefNode>(def_node)) {
      std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(func_def);
      current_func_ = func;
      current_scope_ = func->GetScope();
      current_scope_->SetParent(global_scope_);
      func_def->accept(this);
      current_scope_ = current_scope_->GetParent();
      funcs_[func->GetName()] = func;
    } else if (auto main_func_def = std::dynamic_pointer_cast<MainFuncNode>(def_node)) {
      std::shared_ptr<IRFunction> main_func = std::make_shared<IRFunction>(main_func_def);
      current_func_ = main_func;
      current_scope_ = main_func->GetScope();
      current_scope_->SetParent(global_scope_);
      main_func_def->accept(this);
      current_scope_->GetParent();
      funcs_["main"] = main_func;
    } else if (auto class_def = std::dynamic_pointer_cast<ClassDefNode>(def_node)) {
      std::shared_ptr<ClassType> class_type = std::make_shared<ClassType>(class_def->getIdNode()->getIdName());
      current_class_type_ = class_type;
      class_def->accept(this);
      types_[class_def->getIdNode()->getIdName()] = class_type;
      current_class_type_ = nullptr;
    }
  }
  for (auto& type : types_) {
    printf("%s\n", type.second->commit().c_str());
  }
  printf("%s", global_scope_->GetGlobalStmt().c_str()); // \n included in the method
  for (auto& func : funcs_) {
    auto func_obj = func.second;
    if (!func_obj->is_builtin()) {
      printf("%s\n", func_obj->commit().c_str());

    }
  }
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

void IRGenerator::visit(std::shared_ptr<BlockNode> node) {
  auto stats = node->getStatNodes();
  for (auto stat : stats) {
    stat->accept(this);
  }
}


void IRGenerator::visit(std::shared_ptr<MainFuncNode> node) {
  auto main_block = node->getBody();
  auto entry_block = current_func_->CreateBlock("main.entry");
  current_basic_block_ = entry_block;
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
      has_var = true;
      std::shared_ptr<IRType> var_type = std::make_shared<IRType>(var_def->getIdNode()->getType());
      current_class_type_->AddElement(var_def->getIdNode()->getIdName(), var_type); // declared type in RootNode
    } else if (auto func_def = std::dynamic_pointer_cast<FuncDefNode>(stat)) {
      std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(func_def, node->getIdNode()->getIdName());
      current_func_ = func;
      current_scope_ = func->GetScope();
      current_scope_->SetParent(global_scope_);
      func_def->accept(this);
      funcs_[node->getIdNode()->getIdName() + "_" + func->GetName()] = func;
    } else if (auto class_func_def = std::dynamic_pointer_cast<ClassFuncDefNode>(stat)) {
      std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(class_func_def);
      current_func_ = func;
      current_scope_ = func->GetScope();
      current_scope_->SetParent(global_scope_);
      class_func_def->accept(this);
      funcs_[node->getIdNode()->getIdName() + "_" + func->GetName()] = func;
      has_class_func = true;
    }
  }
  //if no vars, add a dummy var
  if (!has_var) {
    auto dummy_type = std::make_shared<IRType>(k_bool, 0);
    current_class_type_->AddElement("_dummy", dummy_type);
  }

  if (!has_class_func) { // if no class func def, automatically generate one.
    auto func_name = node->getIdNode()->getIdName();
    auto this_type = std::make_shared<IRType>(func_name, 1);
    std::vector<std::shared_ptr<IRType>> param_type;
    param_type.push_back(this_type);
    std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(func_name, param_type, k_ir_void, func_name);
    current_basic_block_ = func->CreateBlock(func_name + ".entry");
    std::shared_ptr<Stmt> ret_stmt = std::static_pointer_cast<Stmt>(std::make_shared<ReturnStmt>());
    current_basic_block_->AddStmt(ret_stmt);
    funcs_[func_name + "_" + func_name] = func;
  }
}

void IRGenerator::visit(std::shared_ptr<ClassFuncDefNode> node) {
  // "this" is the #1 reg in llvm ir
  // ClassFuncDefNode has only one parameter, which is 'this' pointer
  auto func_block = node->getBlockNode();
  auto entry_block = current_func_->CreateBlock(node->getIdNode()->getIdName() + ".entry");
  current_basic_block_ = entry_block;
  // std::shared_ptr<IRType> param_type = std::make_shared<IRType>(IRType::kPTR);;
  std::shared_ptr<IRType> reg_type = std::make_shared<IRType>(node->getIdNode()->getIdName(), 1);
  std::shared_ptr<Register> reg = current_func_->CreateRegister(reg_type); // though it is passed in, we still need to declare this reg in scope
  // std::shared_ptr<Register> param_reg = current_func_->CreateRegister(param_type);
  // std::shared_ptr<Stmt> alloca_stmt = std::static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(reg));
  // std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(param_reg, reg));
  // current_basic_block_->AddStmt(alloca_stmt);
  // current_basic_block_->AddStmt(store_stmt);
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
  if (node->getIdNode()->getType()->is_customized()) {
    node_type = std::make_shared<IRType>(node->getIdNode()->getType(), node->getIdNode()->getType()->getDimension() + 2);
  } else {
    node_type = std::make_shared<IRType>(node->getIdNode()->getType(), node->getIdNode()->getType()->getDimension() + 1);
  }
  std::shared_ptr<Register> var_reg = current_func_->CreateRegister(node_type);
  std::shared_ptr<Stmt> alloca_stmt = std::static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(var_reg));
  current_basic_block_->AddStmt(alloca_stmt);
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
    } else if (auto init_object = std::dynamic_pointer_cast<InitObjectNode>(expr)) {
      //malloc, save the pointer to a reg
      //call ClassFuncDefNode with the reg
      std::string type_name = node_type->GetTypeName();
      auto malloc_func = FindFunction("builtin_malloc");
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
      auto store_reg = current_scope_->FindRegister(node->getIdNode()->getIdName());
      std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(pointer_reg, store_reg)); // store the array address into the alloca address
      current_basic_block_->AddStmt(store_stmt);
      return ;
    } else {
      //store back to id_reg
      auto expr_reg = current_func_->GetLastReg();
      std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
            std::make_shared<StoreStmt>(expr_reg, var_reg)); // store the array address into the alloca address
      current_basic_block_->AddStmt(store_stmt);
    }

    expr->accept(this);
    std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(current_func_->GetLastReg(), var_reg)); // last reg is where i store the result
    current_basic_block_->AddStmt(store_stmt);
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
    current_func_->SetReturnReg(res_reg);
    current_basic_block_->AddStmt(alloca_res);
    lhs->accept(this);
    auto a_result = current_func_->GetReturnReg();
    auto b_block = current_func_->CreateBlock("a_true", false);
    auto a_false_block = current_func_->CreateBlock("a_false", false);
    auto end_block = current_func_->CreateBlock("end_block_for_and_and", false);
    auto br_a = std::make_shared<BrConditionalStmt>(a_result, b_block->getBlockName(), a_false_block->getBlockName());
    current_basic_block_->AddStmt(br_a);
    auto to_end = std::make_shared<BrUnconditionalStmt>(end_block->getBlockName());

    //b:
    current_basic_block_ = b_block;
    rhs->accept(this);
    auto b_result = current_func_->GetReturnReg();
    auto store_b_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(b_result, res_reg));
    current_basic_block_->AddStmt(store_b_stmt);
    current_basic_block_->AddStmt(to_end);
    //false:
    current_basic_block_ = a_false_block;
    auto store_false_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(false, res_reg));
    current_basic_block_->AddStmt(store_false_stmt);
    current_basic_block_ = end_block;
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
    auto a_result = current_func_->GetLastReg();

    auto b_block = current_func_->CreateBlock("a_false", false);
    auto end_block = current_func_->CreateBlock("end_block_for_and_and", false);
    auto br_a = std::make_shared<BrConditionalStmt>(a_result, end_block->getBlockName(), b_block->getBlockName());
    auto to_end = std::make_shared<BrUnconditionalStmt>(end_block->getBlockName());
    current_basic_block_->AddStmt(br_a);
    //b:
    auto curr_block_tmp = current_basic_block_;
    current_basic_block_ = b_block;
    rhs->accept(this);
    auto b_result = current_func_->GetLastReg();
    current_basic_block_->AddStmt(to_end);
    current_basic_block_ = curr_block_tmp;
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
        auto concat_func = FindFunction("builtin_strcat");
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
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
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
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
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
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> or_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kOR, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(or_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kBT: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> bt_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kBT, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(bt_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kLT: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> lt_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kLT, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(lt_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kBEQ: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> beq_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kBEQ, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(beq_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kLEQ: {
      if (*lhs_ir_type != *k_ir_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> leq_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kLEQ, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(leq_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kET: {
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> et_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kET, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(et_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kNET: {
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> net_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kNET, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(net_stmt);
      break;
    }
    default: {
      break;
    }
  }
}

void IRGenerator::visit(std::shared_ptr<IdNode> node) {
  auto var_addr_reg = current_scope_->FindRegister(node->getIdName());
  auto val_reg = current_func_->CreateRegister(var_addr_reg->GetType()->DecreaseDimension());
  std::shared_ptr<Stmt> load_stmt = std::static_pointer_cast<Stmt>(
            std::make_shared<LoadStmt>(val_reg, var_addr_reg));
  current_basic_block_->AddStmt(load_stmt);
  return ;
}

void IRGenerator::visit(std::shared_ptr<TernaryExprNode> node) {
  auto pred = node->getPredicateNode();
  auto if_node = node->getThenExprNode();
  auto else_node = node->getElseExprNode();
  pred->accept(this);
  auto pred_reg = current_func_->GetLastReg();
  auto br_then = current_func_->CreateBlock("a_then", false);
  auto br_else = current_func_->CreateBlock("a_else", false);
  auto br_end = current_func_->CreateBlock("end", false);
  auto to_end = std::make_shared<BrUnconditionalStmt>(br_end->getBlockName());
  auto curr_block_tmp = current_basic_block_;
  current_basic_block_ = br_then;
  if_node->accept(this);
  current_basic_block_->AddStmt(to_end);
  //last reg is the last reg in br_then
  current_basic_block_ = br_else;
  else_node->accept(this);
  current_basic_block_->AddStmt(to_end);
  current_basic_block_ = curr_block_tmp;
  return ;
}

void IRGenerator::visit(std::shared_ptr<ForStatNode> node) {

  std::shared_ptr<StatNode> init_stmt;
  std::shared_ptr<StatNode> update_stmt;
  if (node->getInitialExprNode() != nullptr) {
    init_stmt = node->getInitialExprNode();
  } else if (node->getInitialVarDefNode() != nullptr) {
    init_stmt = std::dynamic_pointer_cast<StatNode>(node->getInitialVarDefNode());
  } else if (node->getInitialAssignStatNode() != nullptr) {
    init_stmt = std::dynamic_pointer_cast<StatNode>(node->getInitialAssignStatNode());
  }
  if (node->getUpdateAssignStatNode() != nullptr) {
    update_stmt = node->getUpdateAssignStatNode();
  } else if (node->getUpdateExprNode() != nullptr) {
    update_stmt = std::dynamic_pointer_cast<StatNode>(node->getUpdateExprNode());
  }
  auto cond_stmt = node->getForCondExprNode();
  auto body_stmt = node->getBlockNode();
  auto loop_block = current_func_->CreateBlock("loop", false);
  auto loop_body_block = current_func_->CreateBlock("body", false);
  auto update_block = current_func_->CreateBlock("update", false);
  auto end_block = current_func_->CreateBlock("end_loop", false);
  auto new_scope = IRScope::CreateScope(current_scope_, update_block, end_block);
  current_scope_ = new_scope;
  init_stmt->accept(this);
  auto j_loop = std::static_pointer_cast<Stmt>(
    std::make_shared<BrUnconditionalStmt>(loop_block->getBlockName()));
  current_basic_block_->AddStmt(j_loop);
  auto curr_block_tmp = current_basic_block_;
  //loop:
  current_basic_block_ = loop_block;
  cond_stmt->accept(this);
  auto cond_reg = current_func_->GetLastReg();
  //if reg = 0 end
  auto cond_br = std::make_shared<BrConditionalStmt>(cond_reg, loop_body_block->getBlockName(), end_block->getBlockName());
  current_basic_block_->AddStmt(cond_br);
  //loop_body:
  current_basic_block_ = loop_body_block;
  body_stmt->accept(this);
  auto br_update_stmt = std::static_pointer_cast<Stmt>(
    std::make_shared<BrUnconditionalStmt>(update_block->getBlockName()));
  current_basic_block_->AddStmt(br_update_stmt);
  //update:
  current_basic_block_ = update_block;
  update_stmt->accept(this);
  auto loop_back = std::make_shared<BrUnconditionalStmt>(loop_block->getBlockName());
  current_basic_block_->AddStmt(loop_back);
  current_scope_ = current_scope_->GetParent();// back to previous scope
  // auto br_end_stmt = std::static_pointer_cast<Stmt>(
  //   std::make_shared<BrUnconditionalStmt>(end_block->getBlockName()));
  // current_basic_block_->AddStmt(br_end_stmt);
  current_basic_block_ = end_block;

}

void IRGenerator::visit(std::shared_ptr<WhileStatNode> node) {
  auto cond_stmt = node->getWhileCondExprNode();
  auto body_stmt = node->getBlockNode();
  auto loop_block = current_func_->CreateBlock("loop", false);
  auto loop_body_block = current_func_->CreateBlock("body", false);
  auto end_block = current_func_->CreateBlock("end_loop", false);
  auto new_scope = IRScope::CreateScope(current_scope_, loop_block, end_block);
  current_scope_ = new_scope;
  auto curr_block_tmp = current_basic_block_;
  //loop:
  current_basic_block_ = loop_block;;
  // cond_stmt->accept(this);
  // auto cond_reg = current_func_->GetLastReg();
  auto cond_rep = LiteralResolver(cond_stmt);
  //if reg = 0 end
  auto cond_br = std::make_shared<BrConditionalStmt>(cond_rep, loop_body_block->getBlockName(), end_block->getBlockName());
  current_basic_block_->AddStmt(cond_br);
  //loop_body:
  current_basic_block_ = loop_body_block;
  body_stmt->accept(this);
  auto loop_back = std::make_shared<BrUnconditionalStmt>(loop_block->getBlockName());
  current_basic_block_->AddStmt(loop_back);
  // current_basic_block_ = curr_block_tmp;
  // auto br_end_stmt = std::static_pointer_cast<Stmt>(
  // std::make_shared<BrUnconditionalStmt>(end_block->getBlockName()));
  // current_basic_block_->AddStmt(br_end_stmt);
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
    auto ret_reg = current_func_->GetLastReg();
    ret_stmt = std::make_shared<ReturnStmt>(ret_reg);
  } else {
    ret_stmt = std::make_shared<ReturnStmt>();
  }
  current_basic_block_->AddStmt(ret_stmt);
}

void IRGenerator::visit(std::shared_ptr<TerminalNode> node) {
  std::shared_ptr<Block> jump_block;
  if (node->GetType() == TerminalNode::TerminalType::kCONTINUE) {
    jump_block = current_scope_->GetLoopStart();
  } else {
    jump_block = current_scope_->GetLoopEnd();
  }
  auto jump_stmt = std::make_shared<BrUnconditionalStmt>(jump_block->getBlockName());
  current_basic_block_->AddStmt(jump_stmt);
}

void IRGenerator::visit(std::shared_ptr<ThisExprNode> node) {
  auto this_reg = current_scope_->FindRegister("this");
}

void IRGenerator::visit(std::shared_ptr<ArrayConstNode> node) {
  //don't want to implement, it will be processed in the def
}

void IRGenerator::visit(std::shared_ptr<DotExprNode> node) {
  auto lhs = node->getLhs();
  auto rhs = node->getRhs();
  lhs->accept(this);
  auto lhs_rep = FetchExprReg(lhs);
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
    auto dest_reg = current_func_->CreateRegister(func->GetReturnType());
    auto args = func_call->getArgs();
    std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> arg_reps;
    arg_reps.push_back(lhs_rep); // pass lhs as 'this' param
    for (const auto& arg : args) {
      arg->accept(this);
      auto arg_rep = FetchExprReg(arg);
      arg_reps.push_back(arg_rep);
    }
    std::shared_ptr<Stmt> call_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<CallStmt>(func, dest_reg, arg_reps));
    current_basic_block_->AddStmt(call_stmt);
  } else if (auto field = std::dynamic_pointer_cast<IdNode>(rhs)) {
    /* store address of the class in a reg(Type**)
     * load on use
     */
    std::string var_name = field->getIdName();
    std::pair<std::shared_ptr<IRType>, int> element = GetElementInStruct(lhs_type->GetTypeName(), var_name);
    auto dest_reg = current_func_->CreateRegister(element.first);

    auto base_reg = current_scope_->FindRegister(var_name);
    std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> offsets;
    offsets.push_back(0);
    offsets.push_back(element.second);
    std::shared_ptr<Stmt> gep_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<GEPStmt>(dest_reg, base_reg, offsets));
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
      //todo
      //find func to call
      auto add_string_func = FindFunction("builtin_strcat");
      auto call_add_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(add_string_func, result_string_reg, params));
      current_basic_block_->AddStmt(call_add_stmt);
    } else {
      auto expr = std::get<std::shared_ptr<ExprNode>>(child_node);
      expr->accept(this);
      auto expr_result = current_func_->GetLastReg(); // by doing this, we need to ensure that the result of expr is stored at the last reg it creates.
      if (result_string_reg == nullptr) {
        result_string_reg = expr_result;
        continue;
      }
      auto last_result = result_string_reg;
      result_string_reg = current_func_->CreateRegister(k_ir_string);
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
      params.push_back(expr_result);
      params.push_back(last_result);
      auto add_string_func = FindFunction("builtin_strcat");
      auto call_add_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(add_string_func, result_string_reg, params));
      current_basic_block_->AddStmt(call_add_stmt);
    }
  }
}

void IRGenerator::visit(std::shared_ptr<FuncCallNode> node) {
  auto func_name = node->getName();
  auto func = FindFunction(func_name);
  auto args = node->getArgs();
  std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
  // if (func->IsInClass()) {
  //   auto this_type = std::make_shared<IRType>(func->GetBelong(), 1);
  //
  // }
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
  }
}

void IRGenerator::visit(std::shared_ptr<IndexExprNode> node) {
  // auto base = node->getBase();
  // auto index = node->getIndex();
  // base->accept(this);
  // auto base_reg = current_func_->GetLastReg();
  // auto result_reg = current_func_->CreateRegister(base_reg->GetType()->DecreaseDimension());
  // std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
  // if (std::shared_ptr<LiteralNode> literal = std::dynamic_pointer_cast<LiteralNode>(index)) {
  //   params.push_back(literal);
  //   auto gep_stmt = std::static_pointer_cast<Stmt>(std::make_shared<GEPStmt>(result_reg, base_reg, params));
  //   current_basic_block_->AddStmt(gep_stmt);
  // } else {
  //   auto index_rep = LiteralResolver(index);
  //   // index->accept(this);
  //   // auto index_reg = current_func_->GetLastReg();
  //   params.push_back(index_rep);
  //   auto gep_stmt = std::static_pointer_cast<Stmt>(std::make_shared<GEPStmt>(result_reg, base_reg, params));
  //   current_basic_block_->AddStmt(gep_stmt);
  // }
  IndexExprGEP(node);
}

void IRGenerator::visit(std::shared_ptr<UnaryExprNode> node) {
  auto expr = node->getExpr();
  auto op = node->getOp();
  expr->accept(this);
  auto operand = current_func_->GetLastReg();
  switch (op) {
    case UnaryExprNode::UnaryOp::kSUB: {
      auto dest_reg = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSUB, 0, operand, dest_reg));
      break;
    }
    case UnaryExprNode::UnaryOp::kWAVE: {
      auto dest_reg = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kXOR, -1, operand, dest_reg));
      break;
    }
    case UnaryExprNode::UnaryOp::kEXCLAIMER: {
      auto dest_reg = current_func_->CreateRegister(k_ir_bool);
      auto binary_stmt = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kXOR, false, operand, dest_reg));
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

      auto id_node = std::dynamic_pointer_cast<IdNode>(expr);
      auto id_reg = FindRegister(id_node->getIdName());
      // auto load_dest = current_func_->CreateRegister(k_ir_int);
      // auto load_stmt = std::static_pointer_cast<Stmt>(std::make_shared<LoadStmt>(load_dest, id_reg));
      auto reg1 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt1 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand, 1, reg1));
      auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(reg1, id_reg));
      auto reg2 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt2 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand, 0, reg2));
      // current_basic_block_->AddStmt(load_stmt);
      current_basic_block_->AddStmt(binary_stmt1);
      current_basic_block_->AddStmt(store_stmt);
      current_basic_block_->AddStmt(binary_stmt2);
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
      auto id_node = std::dynamic_pointer_cast<IdNode>(expr);
      auto id_reg = FindRegister(id_node->getIdName());
      // auto load_dest = current_func_->CreateRegister(k_ir_int);
      // auto load_stmt = std::static_pointer_cast<Stmt>(std::make_shared<LoadStmt>(load_dest, id_reg));
      auto reg1 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt1 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand, 1, reg1));
      auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(reg1, id_reg));
      // current_basic_block_->AddStmt(load_stmt);
      current_basic_block_->AddStmt(binary_stmt1);
      current_basic_block_->AddStmt(store_stmt);
      break;
    }
    case UnaryExprNode::UnaryOp::kPOST_MM: {
      auto id_node = std::dynamic_pointer_cast<IdNode>(expr);
      auto id_reg = FindRegister(id_node->getIdName());
      // auto load_dest = current_func_->CreateRegister(k_ir_int);
      // auto load_stmt = std::static_pointer_cast<Stmt>(std::make_shared<LoadStmt>(load_dest, id_reg));
      auto reg1 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt1 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSUB, operand, 1, reg1));
      auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(reg1, id_reg));
      auto reg2 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt2 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand, 0, reg2));
      // current_basic_block_->AddStmt(load_stmt);
      current_basic_block_->AddStmt(binary_stmt1);
      current_basic_block_->AddStmt(store_stmt);
      current_basic_block_->AddStmt(binary_stmt2);
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
      auto id_node = std::dynamic_pointer_cast<IdNode>(expr);
      auto id_reg = FindRegister(id_node->getIdName());
      // auto load_dest = current_func_->CreateRegister(k_ir_int);
      // auto load_stmt = std::static_pointer_cast<Stmt>(std::make_shared<LoadStmt>(load_dest, id_reg));
      auto reg1 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt1 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSUB, operand, 1, reg1));
      auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(reg1, id_reg));
      // current_basic_block_->AddStmt(load_stmt);
      current_basic_block_->AddStmt(binary_stmt1);
      current_basic_block_->AddStmt(store_stmt);
      break;
    }
    case UnaryExprNode::UnaryOp::kADD:
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
      if (auto init_array = std::dynamic_pointer_cast<InitArrayNode>(expr)) {
        // an array def
        auto array_const = init_array->getDefaultArray();
        if (array_const != nullptr) {
          InitializeArray(id_reg, array_const);
        } else {
          init_array->accept(this);
          auto array_obj_reg = current_func_->GetReturnReg();
          auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(array_obj_reg, id_reg)); // there is a problem here
          current_basic_block_->AddStmt(store_stmt);
        }
        return ;
      } else if (auto init_object = std::dynamic_pointer_cast<InitObjectNode>(expr)) {
        //malloc, save the pointer to a reg
        //call ClassFuncDefNode with the reg
        std::string type_name = node_type->GetTypeName();
        auto malloc_func = FindFunction("builtin.malloc");
        auto pointer_reg = current_func_->CreateRegister(std::make_shared<IRType>(type_name, 1));
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> malloc_params;
        auto type_size = GetClassType(type_name)->GetClassSize();
        malloc_params.push_back(type_size);
        std::shared_ptr<Stmt> malloc_call = std::static_pointer_cast<Stmt>(std::make_shared<CallStmt>(malloc_func, pointer_reg, malloc_params));

        std::string class_func_name = type_name + "_" + type_name;
        auto class_func = FindFunction(class_func_name);
        auto return_reg = current_func_->CreateRegister(std::make_shared<IRType>(IRType::BasicType::kVOID));
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> class_func_params;
        std::shared_ptr<Stmt> class_func_call = std::static_pointer_cast<Stmt>(std::make_shared<CallStmt>(class_func, return_reg, class_func_params));
        current_basic_block_->AddStmt(malloc_call);
        current_basic_block_->AddStmt(class_func_call);
        std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<StoreStmt>(return_reg, id_reg)); // store the array address into the alloca address
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
  }
  //lhs is not necessarily an idnode, can also be array node or object.x
  else if (auto lhs_index_expr = std::dynamic_pointer_cast<IndexExprNode>(node->getLhs())) {
    // gep
    // store
    IndexExprGEP(lhs_index_expr, true);
    //compute rhs, store
    auto addr_reg = current_func_->GetLastReg();
    auto rhs_expr = node->getRhs();
    // rhs_expr->accept(this);
    // auto rhs_reg = current_func_->GetLastReg();
    auto rhs_rep = LiteralResolver(rhs_expr);
    std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(rhs_rep, addr_reg));
    current_basic_block_->AddStmt(store_stmt);

  } else if (auto lhs_dot_expr = std::dynamic_pointer_cast<DotExprNode>(node->getLhs())) {
    // find offset
    // gep
    // store
    DotExprGEP(lhs_dot_expr);
    auto addr_reg = current_func_->GetLastReg();
    auto rhs_expr = node->getRhs();
    rhs_expr->accept(this);
    auto rhs_reg = current_func_->GetLastReg();
    std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(rhs_reg, addr_reg));
    current_basic_block_->AddStmt(store_stmt);

  }
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
  expr->accept(this);
}

void IRGenerator::visit(std::shared_ptr<IfStatNode> node) {
  auto pred = node->getPredicate();
  pred->accept(this);
  auto pred_reg = current_func_->GetReturnReg();

  auto then_ast_block = node->getThenBlock();
  auto else_ast_block = node->getElseBlock();
  auto then_block = current_func_->CreateBlock("then_block", false);
  auto end_block = current_func_->CreateBlock("end_block", false);
  // auto to_then = std::make_shared<BrUnconditionalStmt>(then_block->getBlockName());
  // current_basic_block_->AddStmt(to_then);
  auto to_end = std::make_shared<BrUnconditionalStmt>(end_block->getBlockName());
  //predicate evaluation
  auto curr_block_tmp = current_basic_block_;
  if (else_ast_block == nullptr) {
    auto if_stmt = std::static_pointer_cast<Stmt>(
    std::make_shared<BrConditionalStmt>(pred_reg, then_block->getBlockName(), end_block->getBlockName()));
    current_basic_block_->AddStmt(if_stmt);
    current_basic_block_ = then_block;
    then_ast_block->accept(this);
    current_basic_block_->AddStmt(to_end);
    current_basic_block_ = end_block;
  } else {
    auto else_block = current_func_->CreateBlock("else_block", false);

    auto if_stmt = std::static_pointer_cast<Stmt>(
    std::make_shared<BrConditionalStmt>(pred_reg, then_block->getBlockName(), else_block->getBlockName()));
    current_basic_block_->AddStmt(if_stmt);
    current_basic_block_ = then_block;
    then_ast_block->accept(this);
    current_basic_block_->AddStmt(to_end);
    current_basic_block_ = curr_block_tmp;
    current_basic_block_ = else_block;
    else_ast_block->accept(this);
    current_basic_block_->AddStmt(to_end);
    current_basic_block_ = end_block;
    //jump end block
  }
}

void IRGenerator::InitFuncParam(std::shared_ptr<FuncDefNode> func_def_node) {
  //store all params to corresponding address
  if (current_func_->IsInClass()) { // store "this" reg
    std::shared_ptr<IRType> param_type = std::make_shared<IRType>(current_func_->GetBelong(), 1); //'this' is passed as a param
    std::shared_ptr<IRType> reg_type = std::make_shared<IRType>(current_func_->GetBelong(), 1); // 'this' is stored as a reg
    std::shared_ptr<Register> reg = current_func_->CreateRegister(reg_type);
    std::shared_ptr<Register> param_reg = current_func_->CreateRegister(param_type);
    std::shared_ptr<Stmt> alloca_stmt = static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(reg));
    std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(param_reg, reg));
    current_basic_block_->AddStmt(alloca_stmt);
    current_basic_block_->AddStmt(store_stmt);
    current_scope_->declare("this", reg); //name the self pointer "this"
  }
  for (auto param : func_def_node->getVarDefs()) {
    std::shared_ptr<IRType> reg_type = std::make_shared<IRType>(param->getIdNode()->getType(), 1);
    std::shared_ptr<IRType> param_type = std::make_shared<IRType>(param->getIdNode()->getType(), 0);
    std::shared_ptr<Register> reg = current_func_->CreateRegister(reg_type);
    std::shared_ptr<Register> param_reg = current_func_->CreateRegister(param_type);
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
    str_reg_counter[hashed_val] = 0;
  } else {
    for (int i = 0; i <= str_reg_counter[hashed_val]; i++) {
      auto reg = global_scope_->FindRegister(".str." + std::to_string(str_reg_counter[hashed_val]) + std::to_string(i));
      if (global_scope_->FindStringReg(string_val) != nullptr) {
        //load
        return global_scope_->FindStringReg(string_val);
      }
    }
    str_reg_counter[hashed_val]++;
  }
  auto reg_name = ".str." + std::to_string(hashed_val) + "." + std::to_string(str_reg_counter[hashed_val]);
  auto string_reg = std::make_shared<Register>(reg_name, k_ir_string, true);
  global_scope_->declare(".str." + string_val, string_reg);
  auto str_declare_stmt = std::make_shared<GlobalStmt>(reg_name, string_val);
  global_scope_->AddGlobalStmt(str_declare_stmt->commit());
  return string_reg;
}

std::shared_ptr<Register> IRGenerator::ToRightVal(std::shared_ptr<Register> reg) {
  auto rval_reg = current_func_->CreateRegister(reg->GetType()->DecreaseDimension());
  auto stmt = std::make_shared<LoadStmt>(rval_reg, reg);
  return rval_reg;
}

std::shared_ptr<Register> IRGenerator::FindRegister(const std::string& var_name) {
  auto result_reg = current_scope_->FindRegister(var_name);
  if (result_reg == nullptr) {
    return global_scope_->FindRegister(var_name);
  } else {
    return result_reg;
  }
}

std::shared_ptr<IRFunction> IRGenerator::FindFunction(const std::string& func_name) {
  return funcs_[func_name];
}

std::pair<std::shared_ptr<IRType>, int> IRGenerator::GetElementInStruct(std::string type_name, std::string field_name) {
  //get the index in a struct
  return types_[type_name]->GetElement(field_name);

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
  if (pos == static_cast<int>(range_vec.size() - 1)) {
    if (auto range_literal = std::dynamic_pointer_cast<LiteralNode>(range_vec[pos])) {
      int range_val = std::get<int>(std::dynamic_pointer_cast<LiteralNode>(range_vec[pos])->GetValue());
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> alloc_params;
      alloc_params.emplace_back(range_val * 4);
      auto base_type = std::make_shared<IRType>(node->getType(), 1);
      auto dest_reg = current_func_->CreateRegister(base_type);
      auto array_alloc_call_stmt = std::make_shared<CallStmt>(array_alloc_func, dest_reg, alloc_params);
      current_basic_block_->AddStmt(array_alloc_call_stmt);
    } else {
      const auto& curr_range = range_vec[pos];
      curr_range->accept(this);
      auto range_reg = current_func_->GetLastReg();
      auto size_reg = current_func_->CreateRegister(range_reg->GetType());
      auto mul_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kMUL, size_reg, 4, size_reg));
      current_basic_block_->AddStmt(mul_stmt);
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
      params.emplace_back(range_reg);
      auto malloc_dest_type = std::make_shared<IRType>(k_ir_void, range_vec.size() - pos);
      auto malloc_dest_reg = current_func_->CreateRegister(malloc_dest_type);
      auto malloc_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(array_alloc_func, malloc_dest_reg, params));
      current_basic_block_->AddStmt(malloc_stmt);
    }

  } else {
    if (auto range_literal = std::dynamic_pointer_cast<LiteralNode>(range_vec[pos])) {
      //call, store (here we only consider cases where ranges are all constants)
      int range_val = std::get<int>(std::dynamic_pointer_cast<LiteralNode>(range_vec[pos])->GetValue());
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> alloc_params;
      alloc_params.emplace_back(range_val * 8);

      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> addr_regs;
      for (int i = 0; i < range_val; i++) {
        DeclareArray(node, range_vec, pos + 1);
        addr_regs.emplace_back(current_func_->GetLastReg());
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
      auto range_loop_block = current_func_->CreateBlock("init_array" + std::to_string(pos), false);
      auto end_block = current_func_->CreateBlock("end_init_array" + std::to_string(pos), false);
      auto counter_reg_type = std::make_shared<IRType>(k_ir_int, 1);
      auto counter_reg = current_func_->CreateRegister(counter_reg_type);
      auto alloca_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<AllocaStmt>(counter_reg));
      auto store_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<StoreStmt>(0, counter_reg));
      current_basic_block_->AddStmt(alloca_stmt);
      current_basic_block_->AddStmt(store_stmt);
      const auto& curr_range = range_vec[pos];
      curr_range->accept(this);
      auto range_reg = current_func_->GetLastReg();
      auto size_reg = current_func_->CreateRegister(range_reg->GetType());
      auto mul_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kMUL, range_reg, 4, size_reg));
      current_basic_block_->AddStmt(mul_stmt);
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
      params.emplace_back(size_reg);
      auto malloc_dest_type = std::make_shared<IRType>(k_ir_void, range_vec.size() - pos);
      auto malloc_dest_reg = current_func_->CreateRegister(malloc_dest_type);
      auto malloc_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(array_alloc_func, malloc_dest_reg, params));
      current_basic_block_->AddStmt(malloc_stmt);
      //loop layer a:
      auto tmp_block = current_basic_block_;
      current_basic_block_ = range_loop_block;

      auto cmp_reg = current_func_->CreateRegister(k_ir_bool);
      auto cmp_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<IcmpStmt>(IcmpStmt::IcmpOp::kLT, counter_reg, range_reg, cmp_reg));
      current_basic_block_->AddStmt(cmp_stmt);
      auto br_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BrConditionalStmt>(cmp_reg, range_loop_block->getBlockName(), end_block->getBlockName()));
      current_basic_block_->AddStmt(br_stmt);


      current_basic_block_->AddStmt(malloc_stmt);
      DeclareArray(node, range_vec, pos + 1);
      auto next_layer_reg = current_func_->GetLastReg();
      auto gep_dest_reg = current_func_->CreateRegister(malloc_dest_type);
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> gep_params;
      gep_params.emplace_back(counter_reg);
      auto gep_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<GEPStmt>(gep_dest_reg, malloc_dest_reg, gep_params));
      current_basic_block_->AddStmt(gep_stmt);

      auto store_array_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<StoreStmt>(next_layer_reg, gep_dest_reg));
      current_basic_block_->AddStmt(store_array_stmt);
      auto add_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, counter_reg, 1, counter_reg));
      current_basic_block_->AddStmt(add_stmt);
      auto br_end_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BrUnconditionalStmt>(end_block->getBlockName()));
      current_basic_block_->AddStmt(br_stmt);
      current_basic_block_ = end_block;
    }
  }
}


std::shared_ptr<ClassType> IRGenerator::GetClassType(const std::string& type_name) {
  return types_[type_name];
}

void IRGenerator::IndexExprGEP(std::shared_ptr<IndexExprNode> expr, bool is_lval) {
  //solves recursion better than visit
  //a: int*
  //a[i]:
  std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices;
  while (1) {
    if (auto id_node = std::dynamic_pointer_cast<IdNode>(expr->getBase())) {
      auto base_reg_star = current_scope_->FindRegister(id_node->getIdName());
      auto base_reg = current_func_->CreateRegister(std::make_shared<IRType>(base_reg_star->GetType(), -1));
      auto load_id_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<LoadStmt>(base_reg, base_reg_star));
      current_basic_block_->AddStmt(load_id_stmt);
      auto index_expr_node = expr->getIndex();
      auto index_rep = LiteralResolver(index_expr_node);
      // index_expr_node->accept(this);
      // auto index_reg = current_func_->GetLastReg();
      indices.emplace_back(index_rep);
      //gep
      reverse(indices.begin(), indices.end());
      // std::shared_ptr<Stmt> gep_stmt = std::static_pointer_cast<Stmt>(
      //       std::make_shared<GEPStmt>(dest_reg, base_reg, indices));
      // current_basic_block_->AddStmt(gep_stmt);
      for (int i = 0; i < indices.size(); i++) {
        const auto& idx = indices[i];
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
        params.emplace_back(idx);
        const auto& gep_dest_reg = current_func_->CreateRegister(base_reg->GetType());
        auto gep_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<GEPStmt>(gep_dest_reg, base_reg, params));
        current_basic_block_->AddStmt(gep_stmt);
        if (i != indices.size() - 1 || !is_lval) {
          auto dest_reg = current_func_->CreateRegister(std::make_shared<IRType>(base_reg->GetType(), -1));
          auto load_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<LoadStmt>(dest_reg, gep_dest_reg));
          current_basic_block_->AddStmt(load_stmt);
          base_reg = dest_reg;
        }

      }
      break;
    } else {
      auto index_expr_node = expr->getIndex();
      // index_expr_node->accept(this);
      // auto index_reg = current_func_->GetLastReg();
      auto index_rep = LiteralResolver(index_expr_node);
      indices.emplace_back(index_rep);
      expr = std::dynamic_pointer_cast<IndexExprNode>(expr->getBase());
    }
  }
}

void IRGenerator::DotExprGEP(std::shared_ptr<DotExprNode> expr) {
  //a: int*
  //a[i]:
  std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices;
  while (1) {
    if (auto id_node = std::dynamic_pointer_cast<IdNode>(expr->getLhs())) {
      auto base_reg = current_scope_->FindRegister(id_node->getIdName());
      auto dot_id_node = std::dynamic_pointer_cast<IdNode>(expr->getRhs());
      //find dot id
      auto dot_index = types_[id_node->getIdName()]->GetElementIndex(dot_id_node->getIdName());
      indices.emplace_back(dot_index);
      auto dest_reg = current_func_->CreateRegister(base_reg->GetType());
      //gep
      reverse(indices.begin(), indices.end());
      std::shared_ptr<Stmt> gep_stmt = std::static_pointer_cast<Stmt>(
            std::make_shared<GEPStmt>(dest_reg, base_reg, indices));
      current_basic_block_->AddStmt(gep_stmt);
      break;
    } else {
      auto base_type = std::make_shared<IRType>(expr->getLhs()->getExprType());
      auto dot_id_node = std::dynamic_pointer_cast<IdNode>(expr->getRhs());
      auto dot_index = types_[base_type->GetTypeName()]->GetElementIndex(dot_id_node->getIdName());
      indices.emplace_back(dot_index);
      expr = std::dynamic_pointer_cast<DotExprNode>(expr->getLhs());
    }
  }
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
    return current_func_->GetLastReg();
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
