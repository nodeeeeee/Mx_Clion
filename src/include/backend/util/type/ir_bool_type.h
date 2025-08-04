#pragma once
#include "ir_type.h"

class IRBoolType : public IRType {
public:
  static IRBoolType& Instance() {
    static IRBoolType instance;
    return instance;
  }

  std::string toString() {
    return "i8";
  }
  std::string GetAlign() {
    return "1";
  }

  std::string DefaultValue() {
    return "0";
  }

private:
  IRBoolType() : IRType(){
  }


  //Singleton
  IRBoolType(const IRBoolType&) = delete;             //delete copy construction
  IRBoolType& operator=(const IRBoolType&) = delete;  //delete copy assignment
  IRBoolType(IRBoolType&&) = delete;                  //delete move construction
  IRBoolType& operator=(IRBoolType&&) = delete;       //delete move assignment
};
