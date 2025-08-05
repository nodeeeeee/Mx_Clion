#include "backend/ir_generator.h"

#include "backend/stmt/alloca_stmt.h"
#include "backend/stmt/global_stmt.h"
#include "backend/stmt/store_stmt.h"
#include "frontend/ast/stat_node/def_node/func_def_node.h"
#include "frontend/ast/stat_node/def_node/main_func_node.h"
#include "frontend/ast/stat_node/def_node/var_def_node.h"


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
  current_func_->SetIndex(node->getVarDefs().size());
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

void IRGenerator::InitFuncParam(std::shared_ptr<FuncDefNode> entry_block) {
  int cnt = 0;
  //store all params to corresponding address
  for (auto param : entry_block->getVarDefs()) {
    cnt++;
    std::shared_ptr<IRType> reg_type = std::make_shared<IRType>(param->getIdNode()->getType(), 1);
    std::shared_ptr<IRType> param_type = std::make_shared<IRType>(param->getIdNode()->getType(), 0);
    std::shared_ptr<Register> reg = current_func_->CreateRegister(reg_type);
    std::shared_ptr<Register> param_reg = current_func_->CreateRegister(param_type);
    std::shared_ptr<Stmt> alloca_stmt = static_pointer_cast<Stmt>(std::make_shared<AllocaStmt>(reg));
    std::shared_ptr<Stmt> store_stmt = std::static_pointer_cast<Stmt>(std::make_shared<StoreStmt>(param_reg, reg));
    current_basic_block_->AddStmt(alloca_stmt);
    current_basic_block_->AddStmt(store_stmt);
    current_scope_->declare(param->getIdNode()->getIdName() ,reg);
    //whenever there is an alloca, we need to add it to scope
  }
}


