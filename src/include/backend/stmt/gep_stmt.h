//
// Created by zhang-kai on 8/24/25.
//

#pragma once
#include <memory>
#include <utility>
#include <variant>

#include "stmt.h"
#include "backend/util/register.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/literal_node.h"
//%res = getelementptr <pointee-type>, ptr <base>, <index>...
class GEPStmt : public Stmt {
public:
  GEPStmt(std::shared_ptr<Register> dest_ptr, std::shared_ptr<Register> base_ptr, std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices) : dest_ptr_(std::move(dest_ptr)), base_ptr_(std::move(base_ptr)), indices_(std::move(indices)) {
  }



  std::string commit() {
    std::string ret =dest_ptr_->GetIndex() + " = getelementptr inbounds " + base_ptr_->GetType()->GetTypeName();
    for (const auto& index : indices_) {
      if (std::holds_alternative<std::shared_ptr<LiteralNode>>(index)) {
        auto literal = std::get<std::shared_ptr<LiteralNode>>(index);
        ret += ", " + std::make_shared<IRType>(literal->getLiteralType())->toString() + literal->ToString();
      } else if (std::holds_alternative<std::shared_ptr<Register>>(index)) {
        auto reg = std::get<std::shared_ptr<Register>>(index);
        assert(reg->GetType()->toString() == "i32");
        ret += ", " + reg->GetType()->toString() + reg->GetIndex();
      } else {
        auto val = std::get<int>(index);
        ret += "i32 " + std::to_string(val);
      }
    }
    return ret;
  }
private:
  std::shared_ptr<Register> dest_ptr_;
  std::shared_ptr<Register> base_ptr_;  // pointee-type can be retrieved from base_ptr
  std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices_;
};
