//
// Created by zhang-kai on 6/7/25.
//

#pragma once
#include <utility>

#include "frontend/ast/ASTNode.h"
#include "frontend/ast/def_node/def_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/type_node.h"

class ExprNode;

class VarDefNode : public DefNode {
private:
    std::shared_ptr<ExprNode> expr_node;

public:
    VarDefNode() = delete;
    VarDefNode(std::shared_ptr<IdNode> ID, const Position& position, std::shared_ptr<ExprNode> expr_node) : DefNode(std::move(ID), DefType::kVar, position), expr_node(std::move(expr_node)){
    }
    VarDefNode(std::shared_ptr<IdNode> ID, const Position& position) : DefNode(std::move(ID),DefType::kVar, position){
    }
    const std::shared_ptr<ExprNode>& getExpr() const { return expr_node; }
    void accept(VisitControl *visitor) {visitor->visit(this);}

};
