//
// Created by zhang-kai on 6/17/25.
//

#pragma once
#include "type_type.h"


class NoType : public TypeType{
public:
  static NoType& Instance() {
    static NoType instance;
    return instance;
  }



private:
  NoType() : TypeType() {
  }

  //Singleton
  NoType(const NoType&) = delete;             //delete copy construction
  NoType& operator=(const NoType&) = delete;  //delete copy assignment
  NoType(NoType&&) = delete;                  //delete move construction
  NoType& operator=(NoType&&) = delete;       //delete move assignment
};
