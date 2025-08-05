#include "ir_type.h"

#include <backend/util/type/ir_type.h>

#include "ir_bool_type.h"
#include "ir_int_type.h"
#include "ir_ptr_type.h"
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

IRType::IRType(const std::shared_ptr<TypeType>& type_type, int dim) : dim_(dim) {
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





