//
// Created by zhang-kai on 6/9/25.
//

#pragma once
#include "def_node.h"
#include "def_node.h"
#include "var_def_node.h"

class TypeType;

class FuncDefNode : public DefNode {

public:
    FuncDefNode() = delete;
    FuncDefNode(std::shared_ptr<IdNode> ID, std::vector<std::shared_ptr<VarDefNode>> var_defs, std::shared_ptr<BlockNode> func_block, Position position) : DefNode(ID, DefType::kFunc, position), return_type(std::move(return_type)), var_defs(std::move(var_defs)), func_block(std::move(func_block)) {}

    const std::vector<std::shared_ptr<VarDefNode>> &getVarDefs() {return var_defs;}
    const std::shared_ptr<BlockNode> &getFuncBlock() {return func_block;}
    const std::shared_ptr<TypeType> &getReturnType() {return return_type;}
    void accept(VisitControl *visitor) {visitor->visit(this);}

private:
    std::vector<std::shared_ptr<VarDefNode>> var_defs;
    std::shared_ptr<TypeType> return_type;
    std::shared_ptr<BlockNode> func_block;
};
