#pragma once
#include "ir_type.h"

class IRVoidType : public IRTypeProto {
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
  IRVoidType() : IRTypeProto(){
  }

  //Singleton
  IRVoidType(const IRVoidType&) = delete;             //delete copy construction
  IRVoidType& operator=(const IRVoidType&) = delete;  //delete copy assignment
  IRVoidType(IRVoidType&&) = delete;                  //delete move construction
  IRVoidType& operator=(IRVoidType&&) = delete;       //delete move assignment
};
