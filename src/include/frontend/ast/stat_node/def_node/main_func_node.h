//
// Created by zhang-kai on 6/9/25.
//

#pragma once
#include "frontend/ast/ASTNode.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/id_node.h"
#include "frontend/ast/type/type_type.h"
#include "frontend/ast/stat_node/regular_stat_node/block_node.h"

class MainFuncNode : public DefNode, public std::enable_shared_from_this<MainFuncNode> {
public:
    MainFuncNode() = delete;
    MainFuncNode(std::shared_ptr<BlockNode> body, Position position) : body(std::move(body)),
    DefNode(std::make_shared<IdNode>(std::make_shared<TypeType>(TypeType::PrimitiveType::kINT),"main", position),
        DefType::kFunc, position) {}
    const std::shared_ptr<BlockNode> getBody() const { return body; }
    void accept(VisitControl *visitor) override {visitor->visit(shared_from_this());}
private:
    std::shared_ptr<BlockNode> body;

};
