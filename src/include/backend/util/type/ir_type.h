#pragma once
#include <memory>

#include "frontend/ast/type/type_type.h"
#include "frontend/ast/type/type_type.h"

class IRType {
public:
  enum BasicType {
    kINT, kBOOL, kPTR, kSTRING
  };
  IRType() = default;
  explicit IRType(BasicType basic_type);
  explicit IRType(std::string type_name) : customized_type_(type_name) {}
  explicit IRType(const std::shared_ptr<TypeType>& type_type);
  virtual std::string toString() = 0;
  virtual std::string GetAlign() = 0;
  virtual std::string DefaultValue() = 0;

  bool operator==(IRType const &other) const {
    if (this->type_ref_ != nullptr) {
      return this->type_ref_ == other.type_ref_;
    } else {
      return this->customized_type_ == other.customized_type_;
    }
  }

private:
  // need singleton to boost up assignment
  BasicType basic_type_;
  IRType *type_ref_;
  std::string customized_type_;
  std::shared_ptr<TypeType> k_int = std::make_shared<TypeType>(TypeType::PrimitiveType::kINT);
  std::shared_ptr<TypeType> k_bool = std::make_shared<TypeType>(TypeType::PrimitiveType::kBOOL);
  std::shared_ptr<TypeType> k_string = std::make_shared<TypeType>(TypeType::PrimitiveType::kSTRING);

};
