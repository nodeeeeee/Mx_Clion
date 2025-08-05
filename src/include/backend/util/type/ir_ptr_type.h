// #pragma once
// #include "ir_type.h"
//
// class IRPtrType : public IRType {
// public:
//   static IRPtrType& Instance() {
//     static IRPtrType instance;
//     return instance;
//   }
//
//   std::string toString() {
//     return "ptr";
//   }
//
//   std::string GetAlign() {
//     return "4";
//   }
//
//   std::string DefaultValue() {
//     return "null";
//   }
//
// private:
//   IRPtrType() : IRType(){
//   }
//
//   //Singleton
//   IRPtrType(const IRPtrType&) = delete;             //delete copy construction
//   IRPtrType& operator=(const IRPtrType&) = delete;  //delete copy assignment
//   IRPtrType(IRPtrType&&) = delete;                  //delete move construction
//   IRPtrType& operator=(IRPtrType&&) = delete;       //delete move assignment
// };
