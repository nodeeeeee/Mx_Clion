#pragma once
#include "ir_type.h"

class IRStringType : public IRType {
public:
  static IRStringType& Instance() {
    static IRStringType instance;
    return instance;
  }

  std::string toString() {
    return "ptr";
  }

  std::string GetAlign() {
    return "4";
  }

  std::string DefaultValue() {
    return "null";
  }


private:
  IRStringType() : IRType(){
  }

  //Singleton
  IRStringType(const IRStringType&) = delete;             //delete copy construction
  IRStringType& operator=(const IRStringType&) = delete;  //delete copy assignment
  IRStringType(IRStringType&&) = delete;                  //delete move construction
  IRStringType& operator=(IRStringType&&) = delete;       //delete move assignment
};
