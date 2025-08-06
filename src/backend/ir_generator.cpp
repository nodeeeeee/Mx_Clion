#include "backend/ir_generator.h"

#include "backend/stmt/alloca_stmt.h"
#include "backend/stmt/global_stmt.h"
#include "backend/stmt/store_stmt.h"
#include "frontend/ast/stat_node/def_node/func_def_node.h"
#include "frontend/ast/stat_node/def_node/main_func_node.h"
#include "frontend/ast/stat_node/def_node/var_def_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/binary_expr_node.h"


void IRGenerator::visit(std::shared_ptr<RootNode> root_node) {
  auto def_nodes = root_node->getDefNodes();
  std::vector<GlobalStmt> global_stmts;
  for (const auto def_node : def_nodes) {
    if (auto var_def = std::dynamic_pointer_cast<VarDefNode>(def_node)) {
      global_stmts.push_back(GlobalStmt(var_def));
    } else if (auto func_def = std::dynamic_pointer_cast<FuncDefNode>(def_node)) {
      std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(func_def);
      current_func_ = func;
      current_scope_ = func->GetScope();
      func_def->accept(this);
      funcs_.push_back(std::move(func));
    } else if (auto main_func_def = std::dynamic_pointer_cast<MainFuncNode>(def_node)) {
      std::shared_ptr<IRFunction> main_func = std::make_shared<IRFunction>(main_func_def);
      current_func_ = main_func;
      func_def->accept(this);
      funcs_.push_back(std::move(main_func));
    } else if (auto class_def = std::dynamic_pointer_cast<ClassDefNode>(def_node)) {
      std::shared_ptr<ClassType> class_type = std::make_shared<ClassType>(class_def->getIdNode()->getIdName());
      current_class_type_ = class_type;
      class_def->accept(this);
      types_.push_back(std::move(class_type));
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
      current_class_type_->AddElement(var_type);
    } else if (auto func_def = std::dynamic_pointer_cast<FuncDefNode>(stat)) {
      std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(func_def, node->getIdNode()->getIdName());
      current_func_ = func;
      current_scope_ = func->GetScope();
      func_def->accept(this);
      funcs_.push_back(std::move(func));
    } else if (auto class_func_def = std::dynamic_pointer_cast<ClassFuncDefNode>(stat)) {
      std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(class_func_def);
      current_func_ = func;
      current_scope_ = func->GetScope();
      class_func_def->accept(this);
      funcs_.push_back(std::move(func));
    }
  }
}

void IRGenerator::visit(std::shared_ptr<ClassFuncDefNode> node) { // "this" is the #1 reg in llvm ir
  auto func_block = node->getBlockNode();
  auto entry_block = current_func_->CreateBlock(node->getIdNode()->getIdName() + ".entry");
  current_basic_block_ = entry_block;
  std::shared_ptr<IRType> param_type = std::make_shared<IRType>(IRType::kPTR);;
  std::shared_ptr<IRType> reg_type = std::make_shared<IRType>(IRType::kPTR);
  std::shared_ptr<Register> reg = current_func_->CreateRegister(reg_type);
  std::shared_ptr<Register> param_reg = current_func_->CreateRegister(param_type);
  std::shared_ptr<Stmt> alloca_stmt = static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(reg));
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
    expr->accept(this);
    std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(current_func_->GetLastReg(), var_reg)); // last reg is where i store the result
    current_basic_block_->AddStmt(store_stmt);
  }
  //store back
}

void IRGenerator::visit(std::shared_ptr<BinaryExprNode> node) {
  auto lhs = node->getLhs();
  auto rhs = node->getRhs();

  lhs->accept(this);
  rhs->accept(this);
  auto lhs_type = lhs->getExprType();
  auto rhs_type = rhs->getExprType();
  switch (node->getOp()) {
    case BinaryExprNode::BinaryOp::kADD: {
      if (*lhs_type == *k_string) {
        // todo concatenate strings
      } else if (*lhs_type == *k_int) {

      }
      break;
    }
    case BinaryExprNode::BinaryOp::kMUL:
    case BinaryExprNode::BinaryOp::kDIV:
    case BinaryExprNode::BinaryOp::kMOD:
    case BinaryExprNode::BinaryOp::kSUB:
    case BinaryExprNode::BinaryOp::kSRL:
    case BinaryExprNode::BinaryOp::kSLL:
    case BinaryExprNode::BinaryOp::kAND:
    case BinaryExprNode::BinaryOp::kXOR:
    case BinaryExprNode::BinaryOp::kOR: {
      if (*lhs_type != *k_int) {

      }
      node->setExprType(lhs_type);
      break;
    }
    case BinaryExprNode::BinaryOp::kBT:
    case BinaryExprNode::BinaryOp::kLT:
    case BinaryExprNode::BinaryOp::kBEQ:
    case BinaryExprNode::BinaryOp::kLEQ:
    case BinaryExprNode::BinaryOp::kET:
    case BinaryExprNode::BinaryOp::kNET: {
      node->setExprType(k_bool);
      node->setAssignable(false);
      break;
    }
    case BinaryExprNode::BinaryOp::kAND_AND:
    case BinaryExprNode::BinaryOp::kOR_OR: {
      if (*lhs_type != *k_bool) {
        throw(std::runtime_error("the operator only applies to booleans"));
      }
      node->setExprType(lhs_type);
      node->setAssignable(false);
    }
  }
  }
}





void IRGenerator::InitFuncParam(std::shared_ptr<FuncDefNode>func_def_node) {
  //store all params to corresponding address
  if (current_func_->IsInClass()) {
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
    current_scope_->declare(param->getIdNode()->getIdName() ,reg);
    //whenever there is an alloca, we need to add it to scope
  }
}

std::shared_ptr<Register> IRGenerator::FetchExprReg(std::shared_ptr<ExprNode> expr) {
  if (auto id = std::dynamic_pointer_cast<IdNode>(expr)) {
    return current_scope_->FindRegister(id->getIdName());
  } else if (auto literal = std::dynamic_pointer_cast<LiteralNode>(expr)) {
    if (*literal->getLiteralType() != *k_string) {

    }
  }
}
