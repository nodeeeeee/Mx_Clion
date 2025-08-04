#pragma once
#include<backend/util/type/ir_type.h>

class TypeGetter {
public:
  static std::shared_ptr<IRType> get_type(IRType::BasicType basic_type) {
    if (basic_type == IRType::BasicType::kINT) {
      return k_int;
    } else if (basic_type == IRType::BasicType::kBOOL) {
      return k_bool;
    } else if (basic_type == IRType::BasicType::kSTRING) {
      return k_string;
    } else if (basic_type == IRType::BasicType::kPTR) {
      return k_ptr;
    } else {
      throw std::runtime_error("not valid literal type");
    }
  }
private:
  inline static const std::shared_ptr<IRType> k_int = std::make_shared<IRType>(IRType::BasicType::kINT);
  inline static const std::shared_ptr<IRType> k_bool = std::make_shared<IRType>(IRType::BasicType::kBOOL);
  inline static const std::shared_ptr<IRType> k_string = std::make_shared<IRType>(IRType::BasicType::kSTRING);
  inline static const std::shared_ptr<IRType> k_ptr = std::make_shared<IRType>(IRType::BasicType::kPTR);

};
