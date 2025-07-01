//
// Created by zhang-kai on 6/13/25.
//

#pragma once
#include "type_type.h"


class BoolType : public TypeType{
public:
  static BoolType& Instance() {
    static BoolType instance;
    return instance;
  }

private:
  BoolType() : TypeType(){}
  //Singleton
  BoolType(const BoolType&) = delete;             //delete copy construction
  BoolType& operator=(const BoolType&) = delete;  //delete copy assignment
  BoolType(BoolType&&) = delete;                  //delete move construction
  BoolType& operator=(BoolType&&) = delete;       //delete move assignment
};
