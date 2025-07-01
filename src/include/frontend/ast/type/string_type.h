//
// Created by zhang-kai on 6/13/25.
//

#pragma once
#include "type_type.h"

class StringType : public TypeType {
public:
  static StringType& Instance() {
    static StringType instance;
    return instance;
  }
private:
  StringType() : TypeType() {}
  //Singleton
  StringType(const StringType&) = delete;             //delete copy construction
  StringType& operator=(const StringType&) = delete;  //delete copy assignment
  StringType(StringType&&) = delete;                  //delete move construction
  StringType& operator=(StringType&&) = delete;       //delete move assignment
};
