//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "frontend/ast/ASTNode.h"

class TerminalNode : public ASTNode {
public:
  enum class TerminalType {
    kCONTINUE, kBREAK
  };

  TerminalNode(TerminalType node_type, Position position) : node_type(std::move(node_type)), ASTNode(position) {
  }

  void accept(VisitControl* visitor) { visitor->visit(this); }

private:
  TerminalType node_type;
};
