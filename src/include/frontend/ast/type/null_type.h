//
// Created by zhang-kai on 6/17/25.
//

#pragma once
#include "type_type.h"


class NullType : public TypeType{
public:
  static NullType& Instance() {
    static NullType instance;
    return instance;
  }



private:
  NullType() : TypeType() {
  }

  //Singleton
  NullType(const NullType&) = delete;             //delete copy construction
  NullType& operator=(const NullType&) = delete;  //delete copy assignment
  NullType(NullType&&) = delete;                  //delete move construction
  NullType& operator=(NullType&&) = delete;       //delete move assignment
};
