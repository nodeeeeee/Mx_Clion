#pragma once
#include <memory>
#include <utility>

#include "frontend/ast/type/type_type.h"
#include "frontend/ast/type/type_type.h"

class IRType {
public:
  enum BasicType {
    kINT, kBOOL, kSTRING, kVOID, kPTR
  };
  IRType() = default;
  explicit IRType(BasicType basic_type, int dim = 0);
  explicit IRType(std::string type_name, int dim = 0) : customized_type_(std::move(type_name)), dim_(dim) {}
  explicit IRType(const std::shared_ptr<TypeType>& type_type, int dim = 0);
  virtual std::string toString_() = 0;
  virtual std::string GetAlign_() = 0;
  virtual std::string DefaultValue_() = 0;

  std::string toString() {
    if (dim_ == 0) return type_ref_->toString_();
    else return "ptr";
  }
  std::string ElementToString() {
    assert(dim_ > 0);
    return dim_ == 1 ? type_ref_->toString() : "ptr";
  }
  std::string GetAlign() {
    if (dim_ == 0) return type_ref_->GetAlign_();
    else return "4";
  }
  std::string DefaultValue() {
    if (dim_ == 0) return type_ref_->DefaultValue_();
    else return "0";
  }


  bool operator==(IRType const &other) const {
    if (this->type_ref_ != nullptr) {
      return this->type_ref_ == other.type_ref_;
    } else {
      return this->customized_type_ == other.customized_type_;
    }
  }

  [[nodiscard]] int GetDim() const {
    return dim_;
  }

private:
  // need singleton to boost up assignment
  BasicType basic_type_;
  IRType *type_ref_;
  std::string customized_type_;
  int dim_ = 0;
  std::shared_ptr<TypeType> k_int = std::make_shared<TypeType>(TypeType::PrimitiveType::kINT);
  std::shared_ptr<TypeType> k_bool = std::make_shared<TypeType>(TypeType::PrimitiveType::kBOOL);
  std::shared_ptr<TypeType> k_string = std::make_shared<TypeType>(TypeType::PrimitiveType::kSTRING);
};
