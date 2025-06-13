//
// Created by zhang-kai on 6/13/25.
//
#pragma once
#include "parser/MxParser.h"

class IntType;
class BoolType;
class StringType;
class VoidType;

class TypeType {
public:
  enum Primitive_Type {
    kINT, kBOOL, kSTRING, kVOID
  };
  enum SpecialCode : int{
    IntType, NoType
  };
  TypeType () = default;
  TypeType (int special_code) ;
  TypeType (MxParser::TypeContext *ctx);
  bool operator==(TypeType const &other) const {
    if (this->type_ref != nullptr) {
      return this->type_ref == other.type_ref && this->dimension == other.dimension;
    } else {
      return this->customized_type == other.customized_type && this->dimension == other.dimension;
    }
  }



private:
  TypeType* type_ref = nullptr;
  std::string customized_type;
  int dimension = 0;
  bool has_type = true;
  int countBracket(MxParser::TypeContext *ctx, TypeType** type_ref_ptr, std::string *customized_ptr);
};
