//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include <optional>

#include "terminal_node.h"
#include "ast/type/type_type.h"
#include "terminal_node.h"
#include "frontend/ast/type/type_type.h"
#include "parser/MxParser.h"

class LiteralNode : public TerminalNode {
public:
    LiteralNode() = delete;
    explicit LiteralNode(antlr4::Token* token) : TerminalNode(TerminalType::kLITERAL, Position(token)) {
        if (token->getType() == MxParser::INTEGER) {
            literal_type = TypeType::PrimitiveType::kINT;
            int_value = std::stoi(token->getText());
        } else if (token->getType() == MxParser::BOOL) {
            literal_type = TypeType::PrimitiveType::kBOOL;
            bool_value = token->getText() == "true" ? true : false;
        } else if (token->getType() == MxParser::STRING) {
            literal_type = TypeType::PrimitiveType::kSTRING;
            string_value = token->getText();
        } else if (token->getType() == MxParser::NULL_) {
            is_null = true;
        }
    }

    TypeType::PrimitiveType getLiteralType() {return literal_type;}
    bool isNull() {return is_null;}
    void accept(VisitControl *visitor) {visitor->visit(this);}

private:
    TypeType::PrimitiveType literal_type;
    bool is_null;
    std::optional<std::string> string_value;
    std::optional<size_t> int_value;
    std::optional<bool> bool_value;
};
