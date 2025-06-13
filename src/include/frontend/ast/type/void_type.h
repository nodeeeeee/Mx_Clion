//
// Created by zhang-kai on 6/13/25.
//

#pragma once
#include "type_type.h"

class VoidType : public TypeType{
public:
  static VoidType& Instance() {
    static VoidType instance;
    return instance;
  }
private:
  VoidType() {}
  //Singleton
  VoidType(const VoidType&) = delete;             //delete copy construction
  VoidType& operator=(const VoidType&) = delete;  //delete copy assignment
  VoidType(VoidType&&) = delete;                  //delete move construction
  VoidType& operator=(VoidType&&) = delete;       //delete move assignment
};
