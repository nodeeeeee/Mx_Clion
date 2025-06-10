//
// Created by zhang-kai on 6/9/25.
//

#pragma once
#include "def_node.h"
#include "var_def_node.h"

class FuncDefNode : public DefNode {
private:
    std::vector<std::shared_ptr<VarDefNode>> var_defs;
    std::string return_type;
    std::shared_ptr<BlockNode> func_block;
public:
    FuncDefNode() = delete;
    FuncDefNode(std::string return_type, std::string ID, std::vector<std::shared_ptr<VarDefNode>> var_defs, std::shared_ptr<BlockNode> func_block, Position position) : DefNode(ID, position), return_type(std::move(return_type)), var_defs(std::move(var_defs)), func_block(std::move(func_block)) {}
};
