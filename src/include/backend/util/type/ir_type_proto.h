#pragma once
#include <memory>
#include <utility>

#include "frontend/ast/type/type_type.h"
#include "frontend/ast/type/type_type.h"

class IRTypeProto {
public:
  virtual ~IRTypeProto() = default;
  virtual std::string toString_() = 0;
  virtual std::string GetAlign_() = 0;
  virtual std::string DefaultValue_() = 0;
};
