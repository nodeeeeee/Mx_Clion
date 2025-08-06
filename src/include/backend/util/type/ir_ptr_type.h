#pragma once
#include "ir_type.h"

class IRPtrType : public IRType {
public:
  static IRPtrType& Instance() {
    static IRPtrType instance;
    return instance;
  }

  std::string toString_() override {
    return "ptr";
  }

  std::string GetAlign_() override {
    return "4";
  }

  std::string DefaultValue_() override {
    return "0";
  }

private:
  IRPtrType() : IRType(){
  }

  //Singleton
  IRPtrType(const IRPtrType&) = delete;             //delete copy construction
  IRPtrType& operator=(const IRPtrType&) = delete;  //delete copy assignment
  IRPtrType(IRPtrType&&) = delete;                  //delete move construction
  IRPtrType& operator=(IRPtrType&&) = delete;       //delete move assignment
};
