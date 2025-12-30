#pragma once
#include "ir_type.h"
#include "ir_type_proto.h"

class IRBoolType : public IRTypeProto {
public:
  static IRBoolType& Instance() {
    static IRBoolType instance;
    return instance;
  }

  std::string toString_() {
    return "i1";
  }
  std::string GetAlign_() {
    return "1";
  }

  std::string DefaultValue_() {
    return "0";
  }

private:
  IRBoolType() : IRTypeProto(){
  }


  //Singleton
  IRBoolType(const IRBoolType&) = delete;             //delete copy construction
  IRBoolType& operator=(const IRBoolType&) = delete;  //delete copy assignment
  IRBoolType(IRBoolType&&) = delete;                  //delete move construction
  IRBoolType& operator=(IRBoolType&&) = delete;       //delete move assignment
};
