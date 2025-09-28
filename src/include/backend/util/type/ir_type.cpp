#include "ir_type.h"

#include <backend/util/type/ir_type.h>
#include <bits/regex_constants.h>

#include "ir_bool_type.h"
#include "ir_int_type.h"
#include "ir_void_type.h"
#include "ir_string_type.h"

IRType::IRType(BasicType basic_type, int dim) : basic_type_(basic_type), dim_(dim) {
  if (basic_type == BasicType::kINT) {
    type_ref_ = &IRIntType::Instance();
  } else if (basic_type == BasicType::kBOOL) {
    type_ref_ = &IRBoolType::Instance();
  } else if (basic_type == BasicType::kSTRING) {
    type_ref_ = &IRStringType::Instance();
  }
}

IRType::IRType(const std::shared_ptr<TypeType>& type_type){
  dim_ = type_type->getDimension();
  if (*type_type == *k_int) {
    type_ref_ = &IRIntType::Instance();
    basic_type_ = BasicType::kINT;
  } else if (*type_type == *k_bool) {
    type_ref_ = &IRBoolType::Instance();
    basic_type_ = BasicType::kBOOL;
  } else if (*type_type == *k_string) {
    type_ref_ = &IRStringType::Instance();
    basic_type_ = BasicType::kSTRING;
  } else {
    throw std::runtime_error("invalid TypeType");
  }
}
IRType::IRType(const std::shared_ptr<TypeType>& type_type, int dim) : dim_(dim){
  dim_ = type_type->getDimension();
  if (*type_type == *k_int) {
    type_ref_ = &IRIntType::Instance();
    basic_type_ = BasicType::kINT;
  } else if (*type_type == *k_bool) {
    type_ref_ = &IRBoolType::Instance();
    basic_type_ = BasicType::kBOOL;
  } else if (*type_type == *k_string) {
    type_ref_ = &IRStringType::Instance();
    basic_type_ = BasicType::kSTRING;
  } else {
    throw std::runtime_error("invalid TypeType");
  }
}

IRType::IRType(const std::shared_ptr<IRType>& base_ir_type, int increment) {
  type_ref_ = base_ir_type->type_ref_;
  basic_type_ = base_ir_type->basic_type_;
  customized_type_ = base_ir_type->customized_type_;
  dim_ = base_ir_type->dim_ + increment;
}


std::shared_ptr<IRType> IRType::DecreaseDimension() {
  return std::make_shared<IRType>(basic_type_, dim_ - 1);
}






