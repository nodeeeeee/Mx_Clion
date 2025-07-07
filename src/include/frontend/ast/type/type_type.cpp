//
// Created by zhang-kai on 6/13/25.
//
#include "type_type.h"

#include "bool_type.h"
#include "int_type.h"
#include "no_type.h"
#include "string_type.h"
#include "void_type.h"

TypeType::TypeType (MxParser::TypeContext *ctx) {

  if (ctx->INT()) {
    type_ref = &IntType::Instance();
    primitive_type_ = PrimitiveType::kINT;
  } else if (ctx -> BOOLEAN()) {
    type_ref = &BoolType::Instance();
    primitive_type_ = PrimitiveType::kBOOL;
  } else if (ctx -> STR()) {
    type_ref = &StringType::Instance();
    primitive_type_ = PrimitiveType::kSTRING;
  } else if (ctx -> VOID()) {
    type_ref = &VoidType::Instance();
    primitive_type_ = PrimitiveType::kVOID;
  } else if (auto id_terminal = ctx-> ID()) {
    customized_type = id_terminal ->getSymbol()->getText();
  } else if (auto array_type = ctx->type()) {
    dimension = countBracket(ctx, &type_ref, &customized_type);
  }
}
TypeType::TypeType(PrimitiveType primitive_type, int dimension) : dimension(dimension), primitive_type_(primitive_type) {
  if (primitive_type == PrimitiveType::kBOOL) {
    type_ref = &BoolType::Instance();
  } else if (primitive_type == PrimitiveType::kINT) {
    type_ref = &IntType::Instance();
  } else if (primitive_type == PrimitiveType::kVOID) {
    type_ref = &VoidType::Instance();
  } else if (primitive_type == PrimitiveType::kSTRING) {
    type_ref = &StringType::Instance();
  }
}


TypeType::TypeType(SpecialCode special_code) {
  if (special_code == IntType) { // for 'int main'
    type_ref = &IntType::Instance();
  } else if (special_code == NoType) {
    type_ref = &NoType::Instance();
  }
}

TypeType::TypeType(std::shared_ptr<TypeType> base, int increment) {
  type_ref = base->type_ref;
  customized_type = base->customized_type;
  dimension = base->dimension + increment;
}

TypeType::TypeType (std::string customized_type) : customized_type(std::move(customized_type)) {
  type_ref = nullptr;
  dimension = 0;
}

// std::shared_ptr<TypeType> TypeType::assignType(PrimitiveType primitive_type) {
//   if (primitive_type == PrimitiveType::kBOOL) {
//     return
//   }
// }
//
// std::shared_ptr<TypeType> TypeType::assignType(SpecialType special_type) {
//
// }
//
int TypeType::countBracket(MxParser::TypeContext *ctx, TypeType** type_ref_ptr, std::string *customized_ptr) {
  if (ctx->LEFT_SQUARE_BRACKET()) {
    return countBracket(ctx->type(), type_ref_ptr, customized_ptr);
  } else {
    if (ctx->INT()) {
      *type_ref_ptr = &IntType::Instance();
    } else if (ctx -> BOOLEAN()) {
      *type_ref_ptr = &BoolType::Instance();
    } else if (ctx -> STR()) {
      *type_ref_ptr = &StringType::Instance();
    } else if (ctx -> VOID()) {
      *type_ref_ptr = &VoidType::Instance();
    } else if (auto id_terminal = ctx-> ID()) {
      *customized_ptr = id_terminal ->getSymbol()->getText();
    }
    return 0;
  }
}

std::string TypeType::getTypeName() {
  if (type_ref != nullptr) {
    if (type_ref == &StringType::Instance()) {
      return "String";
    } else {
      throw std::runtime_error("getTypeName should only be used in dot Expr");
    }
  } else {
    return customized_type;
  }
}
