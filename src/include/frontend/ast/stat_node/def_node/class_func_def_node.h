//
// Created by zhang-kai on 6/11/25.
//

#pragma once
#include "def_node.h"

class BlockNode;

class ClassFuncDefNode : public DefNode, public std::enable_shared_from_this<ClassFuncDefNode> {
public:
  const std::shared_ptr<BlockNode>& getBlockNode() const { return block_node; }
  ClassFuncDefNode() = delete;

  ClassFuncDefNode(std::shared_ptr<IdNode> ID, std::shared_ptr<BlockNode> block_node, Position position) :
    block_node(std::move(block_node)), DefNode(std::move(ID), DefType::kClassFunc, position) {
  };
  void accept(VisitControl* visitor) { visitor->visit(shared_from_this()); }

private:
  std::shared_ptr<BlockNode> block_node;


};
