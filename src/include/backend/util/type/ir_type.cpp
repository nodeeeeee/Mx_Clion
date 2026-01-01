#include "ir_type.h"

#include <backend/util/type/ir_type.h>
#include <bits/regex_constants.h>

#include "ir_bool_type.h"
#include "ir_int_type.h"
#include "ir_ptr_type.h"
#include "ir_void_type.h"
#include "ir_string_type.h"
#include "ir_null_type.h"

IRType::IRType(BasicType basic_type, int dim) : basic_type_(basic_type), dim_(dim) {
  if (basic_type == BasicType::kINT) {
    type_ref_ = &IRIntType::Instance();
  } else if (basic_type == BasicType::kBOOL) {
    type_ref_ = &IRBoolType::Instance();
  } else if (basic_type == BasicType::kSTRING) {
    type_ref_ = &IRStringType::Instance();
    // dim_ = 1;
  } else if (basic_type == BasicType::kVOID) {
    type_ref_ = &IRVoidType::Instance();
  } else if (basic_type == BasicType::kNULL) {
    type_ref_ = &IRNullType::Instance();
  } else {
    throw std::runtime_error("invalid TypeType");
  }
}

IRType::IRType(const std::shared_ptr<TypeType>& type_type){
  dim_ = type_type->getDimension();
  if (type_type->compareBase(*k_int)) {
    type_ref_ = &IRIntType::Instance();
    basic_type_ = BasicType::kINT;
  } else if (type_type->compareBase(*k_bool)) {
    type_ref_ = &IRBoolType::Instance();
    basic_type_ = BasicType::kBOOL;
  } else if (type_type->compareBase(*k_string)) {
    type_ref_ = &IRStringType::Instance();
    basic_type_ = BasicType::kSTRING;
    // dim_ = 1;
  } else if (type_type->compareBase(*k_void)) {
    type_ref_ = &IRVoidType::Instance();
    basic_type_ = BasicType::kVOID;
  } else if (type_type->compareBase(*k_null)) {
    type_ref_ = &IRNullType::Instance();
    basic_type_ = BasicType::kNULL; // kNULL can be any pointer type
  }
  else {
    throw std::runtime_error("invalid TypeType");
  }
}
IRType::IRType(const std::shared_ptr<TypeType>& type_type, int dim) : dim_(dim){
  if (type_type->compareBase(*k_int)) {
    type_ref_ = &IRIntType::Instance();
    basic_type_ = BasicType::kINT;
  } else if (type_type->compareBase(*k_bool)) {
    type_ref_ = &IRBoolType::Instance();
    basic_type_ = BasicType::kBOOL;
  } else if (type_type->compareBase(*k_string)) {
    type_ref_ = &IRStringType::Instance();
    basic_type_ = BasicType::kSTRING;
    // dim_ = 1;
  } else if (type_type->compareBase(*k_void)) {
    type_ref_ = &IRVoidType::Instance();
    basic_type_ = BasicType::kVOID;
  } else if (type_type->compareBase(*k_null)) {
    type_ref_ = &IRNullType::Instance();
    basic_type_ = BasicType::kNULL;
  }
  else if (type_type->is_customized()) {
    customized_type_ = type_type->getTypeName();
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






