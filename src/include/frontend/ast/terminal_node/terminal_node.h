//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "frontend/ast/ASTNode.h"

class TerminalNode : public StatNode, public std::enable_shared_from_this<TerminalNode> {
public:
  enum class TerminalType {
    kCONTINUE, kBREAK
  };

  TerminalNode(TerminalType node_type, Position position) : node_type(std::move(node_type)), StatNode(position) {
  }

  void accept(VisitControl* visitor) override { visitor->visit(shared_from_this()); }

private:
  TerminalType node_type;
};
