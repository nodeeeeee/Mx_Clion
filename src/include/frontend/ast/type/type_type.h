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
    kINT, kBOOL, kSTRING, kVOID, kNULL, kOTHER
  };
  enum SpecialCode : int{
    IntType, NoType
  };
  TypeType () = default;
  explicit TypeType (SpecialCode special_code) ;
  explicit TypeType (PrimitiveType primitive_type, int dimension = 0);
  explicit TypeType (MxParser::TypeContext *ctx);
  TypeType (std::shared_ptr<TypeType> base, int increment);
  explicit TypeType (std::string customized_type);

  // std::shared_ptr<TypeType> assignType(PrimitiveType primitive_type);
  // std::shared_ptr<TypeType> assignType(SpecialCode special_code);
  bool operator==(TypeType const &other) const {

    if (this->type_ref != nullptr) {
      return this->type_ref == other.type_ref && this->dimension == other.dimension;
    } else {
      return this->customized_type == other.customized_type && this->dimension == other.dimension;
    }
  }

  size_t getDimension() {return dimension;}

  std::string getTypeName();

private:
  TypeType *type_ref = nullptr;
  PrimitiveType primitive_type_ = PrimitiveType::kOTHER;
  std::string customized_type;
  std::vector<TypeType> param_type;
  std::vector<std::shared_ptr<Function>> string_functions;
  int dimension = 0;
  int countBracket(MxParser::TypeContext *ctx, TypeType** type_ref_ptr, std::string *customized_ptr);
};
