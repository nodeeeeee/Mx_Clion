//
// Created by zhang-kai on 6/11/25.
//

#pragma once
class BlockNode : public StatNode, std::enable_shared_from_this<BlockNode> {
private:
    std::vector<std::shared_ptr<StatNode>> stat_nodes;
public:
    BlockNode() = delete;
    BlockNode(std::vector<std::shared_ptr<StatNode>> stat_nodes, Position position) : stat_nodes(std::move(stat_nodes)), StatNode(position) {};
    BlockNode(std::shared_ptr<StatNode> stat_node, Position position) : StatNode(position) {
        stat_nodes.push_back(stat_node);
    }

    const std::vector<std::shared_ptr<StatNode>>& getStatNodes() const { return stat_nodes; }
    void accept(VisitControl *visitor) {visitor->visit(shared_from_this());}

};