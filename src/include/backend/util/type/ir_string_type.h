#pragma once
#include "ir_type.h"

class IRStringType : public IRTypeProto {
public:
  static IRStringType& Instance() {
    static IRStringType instance;
    return instance;
  }

  std::string toString_() override {
    return "ptr";
  }

  std::string GetAlign_() override {
    return "4";
  }

  std::string DefaultValue_() override {
    return "null";
  }


private:
  IRStringType() : IRTypeProto(){

  }

  //Singleton
  IRStringType(const IRStringType&) = delete;             //delete copy construction
  IRStringType& operator=(const IRStringType&) = delete;  //delete copy assignment
  IRStringType(IRStringType&&) = delete;                  //delete move construction
  IRStringType& operator=(IRStringType&&) = delete;       //delete move assignment
};
