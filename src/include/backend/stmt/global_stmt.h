#pragma once
#include "stmt.h"
#include "../util/block.h"
#include "backend/util/constant.h"
#include "backend/util/register.h"
#include "backend/util/type/ir_int_type.h"
#include "backend/util/type/ir_type.h"
#include "frontend/ast/stat_node/def_node/var_def_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/id_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/literal_node.h"
#include "frontend/ast/type/bool_type.h"
#include "frontend/ast/type/int_type.h"
#include "frontend/ast/type/null_type.h"
#include "frontend/ast/type/string_type.h"


class Constant;

class GlobalStmt : Stmt {
public:
  explicit GlobalStmt(std::shared_ptr<VarDefNode> node): Stmt() {
    name_ = node->getIdNode()->getIdName();
    if (*node->getIdNode()->getType() == IntType::Instance()) {
      register_ = std::make_shared<Register>(name_, k_int, true);
    } else if (*node->getIdNode()->getType() == BoolType::Instance()) {
      register_ = std::make_shared<Register>(name_, k_bool, true);
    } else if (*node->getIdNode()->getType() == StringType::Instance()) {
      register_ = std::make_shared<Register>(name_, k_string, true);
    } else {
      std::shared_ptr<IRType> customized_type = std::make_shared<IRType>(node->getIdNode()->getType()->getTypeName());
      register_ = std::make_shared<Register>(name_, customized_type, true);
    }
    if (node->getExpr() != nullptr) {
      if (auto literal = std::dynamic_pointer_cast<LiteralNode>(node->getExpr())) {
        if (*literal->getLiteralType() == IntType::Instance() || *literal->getLiteralType() == BoolType::Instance() || *
          literal->getLiteralType() == NullType::Instance()) {
          constant_value_ = std::make_shared<Constant>(literal);
        }
      }
    }
  }

  explicit GlobalStmt(std::string str) {
    constant_value_ = std::make_shared<Constant>(str);
    name_ = ".str." + str;
  }

  [[nodiscard]] std::string commit() const{
    //to-do: initialize the value if rhs is literal, and type is int/bool
    if (constant_value_.has_value()) {
      if (*constant_value_.value()->GetConstType() == *k_string) {
        auto string_size = name_.size();
        return "@" + name_ + " = private unnamed_addr constant [" + string_size + "x i8] c\"" + name_ + "\\00, align 1";
      }
      auto value_tmp = constant_value_.value();
      return "@" + name_ + " global " + register_->GetType()->toString() + register_->GetType()->DefaultValue() + value_tmp->ToString() + ", align" + register_->GetType()->GetAlign();
    } else {
      return "@" + name_ + " global " + register_->GetType()->toString() + register_->GetType()->DefaultValue() + "0, align" + register_->GetType()->GetAlign();
    }
  }


private:
  std::string name_;
  std::shared_ptr<Register> register_;
  std::optional<std::shared_ptr<Constant>> constant_value_;
  const std::shared_ptr<IRType> k_int = std::make_shared<IRType>(IRType::BasicType::kINT);
  const std::shared_ptr<IRType> k_bool = std::make_shared<IRType>(IRType::BasicType::kBOOL);
  const std::shared_ptr<IRType> k_string = std::make_shared<IRType>(IRType::BasicType::kSTRING);
};
