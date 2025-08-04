#pragma once
#include "ir_type.h"

class IRIntType : public IRType {
public:
  static IRIntType& Instance() {
    static IRIntType instance;
    return instance;
  }

  std::string toString() {
    return "i32";
  }

  std::string GetAlign() {
    return "4";
  }

  std::string DefaultValue() {
    return "0";
  }

private:
  IRIntType() : IRType(){
  }

  //Singleton
  IRIntType(const IRIntType&) = delete;             //delete copy construction
  IRIntType& operator=(const IRIntType&) = delete;  //delete copy assignment
  IRIntType(IRIntType&&) = delete;                  //delete move construction
  IRIntType& operator=(IRIntType&&) = delete;       //delete move assignment
};
