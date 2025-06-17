//
// Created by zhang-kai on 6/9/25.
//
#pragma once
#include "frontend/ast/ASTNode.h"
class IdNode;

class DefNode : public ASTNode {
public:
  enum class DefType : int {
    kVar, kFunc, kClass, kMain, kClassFunc
  };

  virtual ~DefNode() = default;
  DefNode() = delete;
  void accept() ;
  explicit DefNode(std::shared_ptr<IdNode> id_node, DefType def_type, Position pos) : ASTNode(pos), def_type(def_type),
    id_node(std::move(id_node)) {
  }

  const std::shared_ptr<IdNode> &getIdNode() {
    return id_node;
  }
  const DefType &getDefType() {return def_type;}
  void accept(VisitControl *visitor) {visitor->visit(this);}

private:
  std::shared_ptr<IdNode> id_node;
  DefType def_type;
};
