#pragma once
#include "ir_type.h"

class IRNullType : public IRTypeProto {
public:
  static IRNullType& Instance() {
    static IRNullType instance;
    return instance;
  }

  std::string toString_() override {
    return "ptr";
  }

  std::string GetAlign_() override {
    throw std::runtime_error("no align for null");
  }

  std::string DefaultValue_() override {
    return "null";
  }

private:
  IRNullType() : IRTypeProto(){
  }

  //Singleton
  IRNullType(const IRNullType&) = delete;             //delete copy construction
  IRNullType& operator=(const IRNullType&) = delete;  //delete copy assignment
  IRNullType(IRNullType&&) = delete;                  //delete move construction
  IRNullType& operator=(IRNullType&&) = delete;       //delete move assignment
};
