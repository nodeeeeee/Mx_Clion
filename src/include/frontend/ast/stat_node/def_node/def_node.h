//
// Created by zhang-kai on 6/9/25.
//
#pragma once
#include "frontend/ast/stat_node/stat_node.h"
class IdNode;

class DefNode : public StatNode {
public:
  enum class DefType : int {
    kVar, kFunc, kClass, kMain, kClassFunc
  };

  virtual ~DefNode() = default;
  DefNode() = delete;
  explicit DefNode(std::shared_ptr<IdNode> id_node, DefType def_type, Position pos) : StatNode(pos), def_type(def_type),
    id_node(std::move(id_node)) {
  }

  const std::shared_ptr<IdNode> &getIdNode() {
    return id_node;
  }
  const DefType &getDefType() {return def_type;}

private:
  std::shared_ptr<IdNode> id_node;
  DefType def_type;
};
