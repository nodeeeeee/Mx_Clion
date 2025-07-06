//
// Created by zhang-kai on 6/13/25.
//

#pragma once
#include "type_type.h"


class IntType : public TypeType{
public:
  static IntType& Instance() {
    static IntType instance;
    return instance;
  }



private:
  IntType() : TypeType(){
  }

  //Singleton
  IntType(const IntType&) = delete;             //delete copy construction
  IntType& operator=(const IntType&) = delete;  //delete copy assignment
  IntType(IntType&&) = delete;                  //delete move construction
  IntType& operator=(IntType&&) = delete;       //delete move assignment
};
