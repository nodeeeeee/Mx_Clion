//
// Created by zhang-kai on 6/9/25.
//

#pragma once
#include "def_node.h"
#include "var_def_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/id_node.h"

class TypeType;

class FuncDefNode : public DefNode, public std::enable_shared_from_this<FuncDefNode> {
public:
  FuncDefNode() = delete;

  FuncDefNode(std::shared_ptr<IdNode> ID, std::vector<std::shared_ptr<VarDefNode>> var_defs,
              std::shared_ptr<BlockNode> func_block, Position position) : DefNode(ID, DefType::kFunc, position),
                                                                          var_defs(std::move(var_defs)),
                                                                          func_block(std::move(func_block)) {
  }

  const std::vector<std::shared_ptr<VarDefNode>>& getVarDefs() { return var_defs; }
  const std::shared_ptr<BlockNode>& getFuncBlock() { return func_block; }
  std::shared_ptr<TypeType> getReturnType() {
    return this->getIdNode()->getType();
  }
  void accept(VisitControl* visitor) { visitor->visit(shared_from_this()); }

  // void AddInBlockVarDef(std::shared_ptr<VarDefNode> var_def) {
  //   in_block_var_defs.push_back(var_def);
  // }
  //
  // std::vector<std::shared_ptr<VarDefNode>>& getInBlockVarDef() { return in_block_var_defs; }

  void AddInBlockAllocas(std::shared_ptr<ASTNode> node, int num) {
    in_block_allocas.emplace_back(num, node);
  }

  std::vector<std::pair<int, std::shared_ptr<ASTNode>>> GetInBlockAllocas() {
    return in_block_allocas;
  }

private:
  std::vector<std::shared_ptr<VarDefNode>> var_defs; // for params
  std::shared_ptr<BlockNode> func_block;
  // std::vector<std::shared_ptr<VarDefNode>> in_block_var_defs;

  std::vector<std::pair<int, std::shared_ptr<ASTNode>>> in_block_allocas;
};
