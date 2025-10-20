#include "backend/ir_generator.h"

#include "backend/stmt/alloca_stmt.h"
#include "backend/stmt/binary_stmt.h"
#include "backend/stmt/call_stmt.h"
#include "backend/stmt/gep_stmt.h"
#include "backend/stmt/global_stmt.h"
#include "backend/stmt/load_stmt.h"
#include "backend/stmt/store_stmt.h"
#include "frontend/ast/stat_node/def_node/func_def_node.h"
#include "frontend/ast/stat_node/def_node/main_func_node.h"
#include "frontend/ast/stat_node/def_node/var_def_node.h"
#include "frontend/ast/stat_node/regular_stat_node/assign_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/block_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/array_const_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/binary_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/dot_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/format_string_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/func_call_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/index_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/init_object_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/unary_expr_node.h"


void IRGenerator::visit(std::shared_ptr<RootNode> root_node) {
  auto def_nodes = root_node->getDefNodes();
  for (const auto def_node : def_nodes) {
    if (auto var_def = std::dynamic_pointer_cast<VarDefNode>(def_node)) {
      auto reg_type = std::make_shared<IRType>(var_def->getIdNode()->getType());
      std::shared_ptr<Register> reg = std::make_shared<Register>(var_def->getIdNode()->getIdName(), reg_type, true);
      global_scope_->declare(reg->GetName(), reg);
      global_scope_->AddGlobalStmt(std::make_shared<GlobalStmt>(var_def)->commit());
    } else if (auto func_def = std::dynamic_pointer_cast<FuncDefNode>(def_node)) {
      std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(func_def);
      current_func_ = func;
      current_scope_ = func->GetScope();
      func_def->accept(this);
      funcs_[func->GetName()] = (std::move(func));
    } else if (auto main_func_def = std::dynamic_pointer_cast<MainFuncNode>(def_node)) {
      std::shared_ptr<IRFunction> main_func = std::make_shared<IRFunction>(main_func_def);
      current_func_ = main_func;
      func_def->accept(this);
      funcs_["main"] = (std::move(main_func));
    } else if (auto class_def = std::dynamic_pointer_cast<ClassDefNode>(def_node)) {
      std::shared_ptr<ClassType> class_type = std::make_shared<ClassType>(class_def->getIdNode()->getIdName());
      current_class_type_ = class_type;
      class_def->accept(this);
      types_[class_def->getIdNode()->getIdName()] = std::move(class_type);
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
}

void IRGenerator::visit(std::shared_ptr<ClassDefNode> node) {
  auto block_node = node->getBlockNode();
  auto stats = block_node->getStatNodes();
  for (const auto& stat : stats) {
    if (auto var_def = std::dynamic_pointer_cast<VarDefNode>(stat)) {
      //add to type
      std::shared_ptr<IRType> var_type = std::make_shared<IRType>(var_def->getIdNode()->getType());
      current_class_type_->AddElement(var_def->getIdNode()->getIdName(), var_type);
    } else if (auto func_def = std::dynamic_pointer_cast<FuncDefNode>(stat)) {
      std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(func_def, node->getIdNode()->getIdName());
      current_func_ = func;
      current_scope_ = func->GetScope();
      func_def->accept(this);
      funcs_[node->getIdNode()->getIdName() + "@" + func->GetName()] = (std::move(func));
    } else if (auto class_func_def = std::dynamic_pointer_cast<ClassFuncDefNode>(stat)) {
      std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(class_func_def);
      current_func_ = func;
      current_scope_ = func->GetScope();
      class_func_def->accept(this);
      funcs_[node->getIdNode()->getIdName() + "@" + func->GetName()] = (std::move(func));
    }
  }
}

void IRGenerator::visit(std::shared_ptr<ClassFuncDefNode> node) {
  // "this" is the #1 reg in llvm ir
  // ClassFuncDefNode has only one parameter, which is 'this' pointer
  auto func_block = node->getBlockNode();
  auto entry_block = current_func_->CreateBlock(node->getIdNode()->getIdName() + ".entry");
  current_basic_block_ = entry_block;
  std::shared_ptr<IRType> param_type = std::make_shared<IRType>(IRType::kPTR);;
  std::shared_ptr<IRType> reg_type = std::make_shared<IRType>(IRType::kPTR);
  std::shared_ptr<Register> reg = current_func_->CreateRegister(reg_type);
  std::shared_ptr<Register> param_reg = current_func_->CreateRegister(param_type);
  std::shared_ptr<Stmt> alloca_stmt = std::static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(reg));
  std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(param_reg, reg));
  current_basic_block_->AddStmt(alloca_stmt);
  current_basic_block_->AddStmt(store_stmt);
  current_scope_->declare("this", reg); //name the self pointer "this"
  func_block->accept(this);
}

void IRGenerator::visit(std::shared_ptr<VarDefNode> node) {
  std::shared_ptr<IRType> node_type = std::make_shared<IRType>(node->getIdNode()->getType(), 1);
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
        int a[100];
        InitializeArray(var_reg, array_const, 0, a);
      }
      return ;
    } else if (auto init_object = std::dynamic_pointer_cast<InitObjectNode>(expr)) {
      //malloc, save the pointer to a reg
      //call ClassFuncDefNode with the reg
      std::string type_name = node_type->GetTypeName();
      auto malloc_func = FindFunction("builtin.malloc");
      auto pointer_reg = current_func_->CreateRegister(std::make_shared<IRType>(IRType::BasicType::kPTR, 1));
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> malloc_params;
      auto type_size = GetClassType(type_name)->GetClassSize();
      malloc_params.push_back(type_size);
      std::shared_ptr<Stmt> malloc_call = std::static_pointer_cast<Stmt>(std::make_shared<CallStmt>(malloc_func, pointer_reg, malloc_params));

      std::string class_func_name = type_name + "@" + type_name;
      auto class_func = FindFunction(class_func_name);
      auto return_reg = current_func_->CreateRegister(std::make_shared<IRType>(IRType::BasicType::kVOID));
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> class_func_params;
      std::shared_ptr<Stmt> class_func_call = std::static_pointer_cast<Stmt>(std::make_shared<CallStmt>(class_func, return_reg, class_func_params));
      current_basic_block_->AddStmt(malloc_call);
      current_basic_block_->AddStmt(class_func_call);
      std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(return_reg, var_reg)); // store the array address into the alloca address
      current_basic_block_->AddStmt(store_stmt);
      return ;
    } else {
      //store back to id_reg
      auto expr_reg = current_func_->GetLastReg();
      std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
            std::make_shared<StoreStmt>(expr_reg, id_reg)); // store the array address into the alloca address
      current_basic_block_->AddStmt(store_stmt);
    }

    expr->accept(this);
    std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<StoreStmt>(current_func_->GetLastReg(), var_reg)); // last reg is where i store the result
    current_basic_block_->AddStmt(store_stmt);
  }
  //store back
}

void IRGenerator::visit(std::shared_ptr<BinaryExprNode> node) {
  auto lhs = node->getLhs();
  auto rhs = node->getRhs();
  lhs->accept(this);
  auto lhs_rep = FetchExprReg(lhs);
  rhs->accept(this);
  auto rhs_rep = FetchExprReg(rhs);
  auto lhs_type = lhs->getExprType();
  auto rhs_type = rhs->getExprType();
  switch (node->getOp()) {
    case BinaryExprNode::BinaryOp::kADD: {
      if (*lhs_type == *k_string) {
        auto concat_func = FindFunction("__concat");
        std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kPTR);
        std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
        std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
        params.push_back(lhs_rep);
        params.push_back(rhs_rep);
        std::shared_ptr<Stmt> call_stmt = std::static_pointer_cast<Stmt>(
          std::make_shared<CallStmt>(concat_func, dest_reg, params));
        current_basic_block_->AddStmt(call_stmt);
        // find function by name, call
        // todo concatenate strings
      } else if (*lhs_type == *k_int) {
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
      if (*lhs_type != *k_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> mul_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kMUL, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(mul_stmt);
    }
    case BinaryExprNode::BinaryOp::kDIV: {
      if (*lhs_type != *k_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> div_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kDIV, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(div_stmt);
    }
    case BinaryExprNode::BinaryOp::kMOD: {
      if (*lhs_type != *k_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> mod_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kMOD, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(mod_stmt);
    }
    case BinaryExprNode::BinaryOp::kSUB: {
      if (*lhs_type != *k_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> sub_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSUB, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(sub_stmt);
    }
    case BinaryExprNode::BinaryOp::kSRL: {
      if (*lhs_type != *k_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> srl_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSRL, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(srl_stmt);
    }
    case BinaryExprNode::BinaryOp::kSLL: {
      if (*lhs_type != *k_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kINT);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> sll_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSLL, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(sll_stmt);
    }
    case BinaryExprNode::BinaryOp::kAND: {
      if (*lhs_type != *k_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> and_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kAND, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(and_stmt);
    }
    case BinaryExprNode::BinaryOp::kXOR: {
      if (*lhs_type != *k_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> xor_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kXOR, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(xor_stmt);
    }
    case BinaryExprNode::BinaryOp::kOR: {
      if (*lhs_type != *k_int) {
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
      if (*lhs_type != *k_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> bt_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kBT, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(bt_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kLT: {
      if (*lhs_type != *k_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> lt_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kLT, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(lt_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kBEQ: {
      if (*lhs_type != *k_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> beq_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kBEQ, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(beq_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kLEQ: {
      if (*lhs_type != *k_int) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> leq_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kLEQ, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(leq_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kET: {
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> et_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kET, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(et_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kNET: {
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> net_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kNET, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(net_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kAND_AND: {
      if (*lhs_type != *k_bool) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> and_and_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kAND_AND, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(and_and_stmt);
      break;
    }
    case BinaryExprNode::BinaryOp::kOR_OR: {
      if (*lhs_type != *k_bool) {
        throw std::runtime_error("binary operation type mismatch");
      }
      std::shared_ptr<IRType> dest_reg_type = std::make_shared<IRType>(IRType::kBOOL);
      std::shared_ptr<Register> dest_reg = current_func_->CreateRegister(dest_reg_type);
      std::shared_ptr<Stmt> or_or_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kOR_OR, lhs_rep, rhs_rep, dest_reg));
      current_basic_block_->AddStmt(or_or_stmt);
      break;
    }
  }
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
  if (std::holds_alternative<LiteralNode>(lhs_rep)) {
    lhs_type = std::make_shared<IRType>(std::get<LiteralNode>(lhs_rep).getLiteralType());
  } else {
    lhs_type = std::get<std::shared_ptr<Register>>(lhs_rep)->GetType();
  }
  if (auto func_call = std::dynamic_pointer_cast<FuncCallNode>(rhs)) {
    std::string func_name = lhs_type->GetTypeName() + "@" + func_call->getName();
    std::shared_ptr<IRFunction> func = FindFunction(func_name);
    auto dest_reg = current_func_->CreateRegister(func->GetReturnType());
    auto args = func_call->getArgs();
    std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> arg_reps;
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
      auto add_string_func = FindFunction("String.add");
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
      auto add_string_func = FindFunction("String.add");
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
  for (const auto& arg : args) {
    arg->accept(this);
    auto arg_reg = current_func_->GetLastReg();
    params.push_back(arg_reg);
  }
  auto result_reg = current_func_->CreateRegister(func->GetReturnType());
  auto func_call_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<CallStmt>(func, result_reg, params));
  current_basic_block_->AddStmt(func_call_stmt);
}

void IRGenerator::visit(std::shared_ptr<IndexExprNode> node) {
  auto base = node->getBase();
  auto index = node->getIndex();
  base->accept(this);
  auto base_reg = current_func_->GetLastReg();
  auto result_reg = current_func_->CreateRegister(base_reg->GetType()->DecreaseDimension());
  std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params;
  if (std::shared_ptr<LiteralNode> literal = std::dynamic_pointer_cast<LiteralNode>(index)) {
    params.push_back(literal);
    auto gep_stmt = std::static_pointer_cast<Stmt>(std::make_shared<GEPStmt>(result_reg, base_reg, params));
    current_basic_block_->AddStmt(gep_stmt);
  } else {
    index->accept(this);
    auto index_reg = current_func_->GetLastReg();
    params.push_back(index_reg);
    auto gep_stmt = std::static_pointer_cast<Stmt>(std::make_shared<GEPStmt>(result_reg, base_reg, params));
    current_basic_block_->AddStmt(gep_stmt);
  }
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
      auto load_dest = current_func_->CreateRegister(k_ir_int);
      auto load_stmt = std::static_pointer_cast<Stmt>(std::make_shared<LoadStmt>(load_dest, id_reg));
      auto reg1 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt1 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand, 1, reg1));
      auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(reg1, id_reg));
      auto reg2 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt2 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand, 0, reg2));
      current_basic_block_->AddStmt(load_stmt);
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
      auto load_dest = current_func_->CreateRegister(k_ir_int);
      auto load_stmt = std::static_pointer_cast<Stmt>(std::make_shared<LoadStmt>(load_dest, id_reg));
      auto reg1 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt1 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand, 1, reg1));
      auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(reg1, id_reg));
      current_basic_block_->AddStmt(load_stmt);
      current_basic_block_->AddStmt(binary_stmt1);
      current_basic_block_->AddStmt(store_stmt);
      break;
    }
    case UnaryExprNode::UnaryOp::kPOST_MM: {
      auto id_node = std::dynamic_pointer_cast<IdNode>(expr);
      auto id_reg = FindRegister(id_node->getIdName());
      auto load_dest = current_func_->CreateRegister(k_ir_int);
      auto load_stmt = std::static_pointer_cast<Stmt>(std::make_shared<LoadStmt>(load_dest, id_reg));
      auto reg1 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt1 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSUB, operand, 1, reg1));
      auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(reg1, id_reg));
      auto reg2 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt2 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kADD, operand, 0, reg2));
      current_basic_block_->AddStmt(load_stmt);
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
      auto load_dest = current_func_->CreateRegister(k_ir_int);
      auto load_stmt = std::static_pointer_cast<Stmt>(std::make_shared<LoadStmt>(load_dest, id_reg));
      auto reg1 = current_func_->CreateRegister(k_ir_int);
      auto binary_stmt1 = std::static_pointer_cast<Stmt>(std::make_shared<BinaryStmt>(BinaryStmt::BinaryOp::kSUB, operand, 1, reg1));
      auto store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(reg1, id_reg));
      current_basic_block_->AddStmt(load_stmt);
      current_basic_block_->AddStmt(binary_stmt1);
      current_basic_block_->AddStmt(store_stmt);
      break;
    }
    case UnaryExprNode::UnaryOp::kADD:
    case default: {
      break;
    }

  }
}

void IRGenerator::visit(std::shared_ptr<AssignStatNode> node) {
  auto lhs_id = dynamic_pointer_cast<IdNode>(node->getLhs());
  auto id_reg = FindRegister(lhs_id->getIdName());
  auto node_type = id_reg->GetType();
  //visit expr
  auto expr = node->getRhs();
  if (expr != nullptr) {
    if (auto init_array = std::dynamic_pointer_cast<InitArrayNode>(expr)) {
      // an array def
      auto array_const = init_array->getDefaultArray();
      if (array_const != nullptr) {
        int a[100];
        InitializeArray(id_reg, array_const, 0, a);
      }
      return ;
    } else if (auto init_object = std::dynamic_pointer_cast<InitObjectNode>(expr)) {
      //malloc, save the pointer to a reg
      //call ClassFuncDefNode with the reg
      std::string type_name = node_type->GetTypeName();
      auto malloc_func = FindFunction("builtin.malloc");
      auto pointer_reg = current_func_->CreateRegister(std::make_shared<IRType>(IRType::BasicType::kPTR, 1));
      std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> malloc_params;
      auto type_size = GetClassType(type_name)->GetClassSize();
      malloc_params.push_back(type_size);
      std::shared_ptr<Stmt> malloc_call = std::static_pointer_cast<Stmt>(std::make_shared<CallStmt>(malloc_func, pointer_reg, malloc_params));

      std::string class_func_name = type_name + "@" + type_name;
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
      auto expr_reg = current_func_->GetLastReg();
      std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
            std::make_shared<StoreStmt>(expr_reg, id_reg)); // store the array address into the alloca address
      current_basic_block_->AddStmt(store_stmt);
    }
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

}

void IRGenerator::InitFuncParam(std::shared_ptr<FuncDefNode> func_def_node) {
  //store all params to corresponding address
  if (current_func_->IsInClass()) { // store "this" reg
    std::shared_ptr<IRType> param_type = std::make_shared<IRType>(IRType::kPTR);;
    std::shared_ptr<IRType> reg_type = std::make_shared<IRType>(IRType::kPTR);
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
  if (auto id = std::dynamic_pointer_cast<IdNode>(expr)) {
    return current_scope_->FindRegister(id->getIdName());
  } else if (auto literal = std::dynamic_pointer_cast<LiteralNode>(expr)) {
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
  auto string_type = std::make_shared<IRType>(IRType::kSTRING);
  auto string_reg = std::make_shared<Register>(string_literal->ToString(), string_type, true);
  auto stmt = std::make_shared<GlobalStmt>(string_literal->ToString());
  global_scope_->AddGlobalStmt(stmt->commit());
  global_scope_->declare(string_literal->ToString(), string_reg);
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
void IRGenerator::InitializeArray(std::shared_ptr<Register> base, std::shared_ptr<ArrayConstNode> array_const, int depth, int track[]) {
  if (!array_const->GetLiteralElements().empty()) {
    auto literal_elements = array_const->GetLiteralElements();
    std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices;
    for (int i = 0; i < depth; i++) {
      indices.push_back(track[i]);
    }
    for (int i = 0; i < literal_elements.size(); i++) {
      indices[depth] = i;
      std::shared_ptr<IRType> addr_type = std::make_shared<IRType>(literal_elements[0]->getLiteralIRType(), 1);
      std::shared_ptr<Register> tmp_addr = current_func_->CreateRegister(addr_type);
      std::shared_ptr<Stmt> gep_stmt = std::static_pointer_cast<Stmt>(
      std::make_shared<GEPStmt>(tmp_addr, base, indices)
      );
      std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(
        std::make_shared<StoreStmt>(literal_elements[i], current_func_->GetLastReg())); // last reg is where i store the result
      current_basic_block_->AddStmt(store_stmt);
      return ;
    }

  } else {
    for (int i = 0; i < array_const->GetArrayElements().size(); i++) {
      track[depth] = i;
      InitializeArray(base, array_const->GetArrayElements()[i], depth + 1, track);
    }
  }
}


std::shared_ptr<ClassType> IRGenerator::GetClassType(const std::string& type_name) {
  return types_[type_name];
}


