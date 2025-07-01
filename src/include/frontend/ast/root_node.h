//
// Created by zhang-kai on 6/6/25.
//
#pragma once
#include "ASTNode.h"
#include "visit_control.h"
#include "stat_node/def_node/def_node.h"

class VisitControl;
class MainFuncNode;

class RootNode : public ASTNode, public std::enable_shared_from_this<RootNode> {
public:
    RootNode() = delete;
    RootNode(std::vector<std::shared_ptr<DefNode>> def_nodes, const Position& position) : def_nodes(std::move(def_nodes)), ASTNode(position) {
    };
    const std::vector<std::shared_ptr<DefNode>> &getDefNodes() const { return def_nodes; }
    const std::shared_ptr<MainFuncNode> &getMainNode() { return main_node; }
    void accept(VisitControl *visitor) override {visitor->visit(shared_from_this());}

private:
    std::vector<std::shared_ptr<DefNode>> def_nodes;
    std::shared_ptr<MainFuncNode> main_node;


};
