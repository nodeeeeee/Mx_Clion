//
// Created by zhang-kai on 6/7/25.
//

#pragma once
#include <utility>

#include "frontend/ast/ASTNode.h"
#include "frontend/ast/stat_node/def_node/def_node.h"

class DefNode;
class IdNode;
class ExprNode;
class Register;

class VarDefNode : public DefNode, public std::enable_shared_from_this<VarDefNode> {
public:
    VarDefNode() = delete;
    VarDefNode(std::shared_ptr<IdNode> ID, const Position& position, std::shared_ptr<ExprNode> expr_node) : DefNode(std::move(ID), DefType::kVar, position), expr_node(std::move(expr_node)){
    }
    VarDefNode(std::shared_ptr<IdNode> ID, const Position& position) : DefNode(std::move(ID),DefType::kVar, position){
    }
    [[nodiscard]] const std::shared_ptr<ExprNode>& getExpr() const { return expr_node; }
    void accept(VisitControl *visitor) {visitor->visit(shared_from_this());}

    void AddPreAllocatedReg(std::shared_ptr<Register> reg) {
        pre_allocated_reg.emplace_back(reg);
    }

    std::vector<std::shared_ptr<Register>> GetPreAllocatedRegs() {
        return pre_allocated_reg;
    }

private:
    std::shared_ptr<ExprNode> expr_node;
    std::vector<std::shared_ptr<Register>> pre_allocated_reg;
};
