#include "backend/ir_generator.h"

#include "backend/stmt/global_stmt.h"
#include "frontend/ast/stat_node/def_node/func_def_node.h"
#include "frontend/ast/stat_node/def_node/var_def_node.h"


void IRGenerator::visit(std::shared_ptr<RootNode> root_node) {
  auto def_nodes = root_node->getDefNodes();
  std::vector<GlobalStmt> global_stmts;
  for (const auto def_node : def_nodes) {
    if (auto var_def = std::dynamic_pointer_cast<VarDefNode>(def_node)) {
      global_stmts.push_back(GlobalStmt(var_def));
    } else if (auto func_def = std::dynamic_pointer_cast<FuncDefNode>(def_node)) {
      std::shared_ptr<IRFunction> func = std::make_shared<IRFunction>(func_def);
      func_def->accept(this);
    }
  }
}
