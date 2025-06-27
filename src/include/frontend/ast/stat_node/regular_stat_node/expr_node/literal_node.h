//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include <optional>

#include "ast/type/type_type.h"
#include "frontend/ast/def_node/class_def_node.h"
#include "parser/MxParser.h"

class LiteralNode : public ExprNode {
public:
    LiteralNode() = delete;
    explicit LiteralNode(antlr4::Token* token) : ExprNode(Position(token)) {
        if (token->getType() == MxParser::INTEGER) {
            literal_type = std::make_shared<TypeType>(TypeType::PrimitiveType::kINT);
            int_value = std::stoi(token->getText());
        } else if (token->getType() == MxParser::BOOL) {
            literal_type = std::make_shared<TypeType>(TypeType::PrimitiveType::kBOOL);
            bool_value = token->getText() == "true" ? true : false;
        } else if (token->getType() == MxParser::STRING) {
            literal_type = std::make_shared<TypeType>(TypeType::PrimitiveType::kSTRING);
            string_value = token->getText();
        } else if (token->getType() == MxParser::NULL_) {
            is_null = true;
        }
    }

    std::shared_ptr<TypeType> getLiteralType() {return literal_type;}
    bool isNull() {return is_null;}
    void accept(VisitControl *visitor) {visitor->visit(this);}

private:
    std::shared_ptr<TypeType> literal_type;
    bool is_null;
    std::optional<std::string> string_value;
    std::optional<size_t> int_value;
    std::optional<bool> bool_value;
};
