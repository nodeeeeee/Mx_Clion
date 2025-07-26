#pragma once
#include "frontend/ast/stat_node/stat_node.h"

class BlockStatNode : public StatNode, public std::enable_shared_from_this<BlockStatNode> {

public:
  BlockStatNode() = delete;
  BlockStatNode(std::shared_ptr<BlockNode> block_node, Position position) : block_node(std::move(block_node)), StatNode(position) {};


  const std::shared_ptr<BlockNode>& getBlockNode() const { return block_node; }
  void accept(VisitControl *visitor) override {visitor->visit(shared_from_this());}

private:
  std::shared_ptr<BlockNode> block_node;
};