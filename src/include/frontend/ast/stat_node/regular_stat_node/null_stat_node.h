//
// Created by zhang-kai on 7/2/25.
//

#pragma once
#include "regular_stat_node.h"
#include "frontend/ast/stat_node/stat_node.h"

class NullStatNode : public RegularStatNode {
  NullStatNode(Position position) : RegularStatNode(position) {}
};
