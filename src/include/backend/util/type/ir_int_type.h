#pragma once
#include "ir_type.h"

class IRIntType : public IRType {
public:
  static IRIntType& Instance() {
    static IRIntType instance;
    return instance;
  }

  std::string toString_() override {
    return "i32";
  }

  std::string GetAlign_() override {
    return "4";
  }

  std::string DefaultValue_() override {
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
