#pragma once
#include "ir_type.h"

class IRVoidType : public IRType {
public:
  static IRVoidType& Instance() {
    static IRVoidType instance;
    return instance;
  }

  std::string toString_() override {
    throw std::runtime_error("no toString for void");
  }

  std::string GetAlign_() override {
    throw std::runtime_error("no align for void");
  }

  std::string DefaultValue_() override {
    throw std::runtime_error("no default value for void");
  }

private:
  IRVoidType() : IRType(){
  }

  //Singleton
  IRVoidType(const IRVoidType&) = delete;             //delete copy construction
  IRVoidType& operator=(const IRVoidType&) = delete;  //delete copy assignment
  IRVoidType(IRVoidType&&) = delete;                  //delete move construction
  IRVoidType& operator=(IRVoidType&&) = delete;       //delete move assignment
};
