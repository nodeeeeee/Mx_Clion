//
// Created by zhang-kai on 6/13/25.
//
#pragma once
#include "parser/MxParser.h"

// stores the type attribute, and has compare method.
class Function;
class IntType;
class BoolType;
class StringType;
class VoidType;

class TypeType {
public:
  enum class PrimitiveType : int {
    kINT, kBOOL, kSTRING, kVOID
  };
  enum SpecialCode : int{
    IntType, NoType
  };
  TypeType () = default;
  TypeType (SpecialCode special_code) ;
  TypeType (PrimitiveType primitive_type, int dimension = 0);
  TypeType (MxParser::TypeContext *ctx);
  // std::shared_ptr<TypeType> assignType(PrimitiveType primitive_type);
  // std::shared_ptr<TypeType> assignType(SpecialCode special_code);
  bool operator==(TypeType const &other) const {

    if (this->type_ref != nullptr) {
      return this->type_ref == other.type_ref && this->dimension == other.dimension;
    } else {
      return this->customized_type == other.customized_type && this->dimension == other.dimension;
    }
  }
  // bool hasType() {
  //   return has_type;
  // }
  // std::pair<std::string, int> getType() {
  //   if (!has_type) {
  //     throw std::runtime_error("Cannot get type of non-type");
  //   }
  //   if (customized_type.empty()) {
  //     switch (primitive_type) {
  //       case PrimitiveType::kINT: return std::make_pair("int",dimension);
  //       case PrimitiveType::kBOOL: return std::make_pair("bool", dimension);
  //       case PrimitiveType::kSTRING: return std::make_pair("string", dimension);
  //       case PrimitiveType::kVOID: return std::make_pair("void", dimension);
  //     }
  //   } else {
  //     return std::make_pair(customized_type, dimension);
  //   }
  // }

private:
  TypeType* type_ref = nullptr;

  std::string customized_type;
  std::vector<TypeType> param_type;
  std::vector<std::shared_ptr<Function>> string_functions;
  int dimension = 0;
  int countBracket(MxParser::TypeContext *ctx, TypeType** type_ref_ptr, std::string *customized_ptr);
};
