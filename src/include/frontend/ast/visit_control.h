//
// Created by zhang-kai on 6/13/25.
//

#pragma once
#include "all_ast_nodes.h"

class VisitControl {
public:
  virtual ~VisitControl() = default;

  //get to other nodes from current node.
  virtual void visit (RootNode* node) = 0;
  virtual void visit (std::shared_ptr<ClassFuncDefNode> node) = 0;
  virtual void visit(std::shared_ptr<ClassDefNode> node);
  virtual void visit (std::shared_ptr<FuncDefNode> node) = 0;
  virtual void visit (std::shared_ptr<MainFuncNode> node) = 0;
  virtual void visit (std::shared_ptr<VarDefNode> node) = 0;
  virtual void visit (std::shared_ptr<ArrayConstNode> node) = 0;
  virtual void visit (std::shared_ptr<BinaryExprNode> node) = 0;
  virtual void visit (std::shared_ptr<DotExprNode> node) = 0;
  virtual void visit (std::shared_ptr<FormatStringNode> node) = 0;
  virtual void visit (std::shared_ptr<FuncCallNode> node) = 0;
  virtual void visit (std::shared_ptr<IndexExprNode> node) = 0;
  virtual void visit (std::shared_ptr<InitArrayNode> node) = 0;
  virtual void visit (std::shared_ptr<InitObjectNode> node) = 0;
  virtual void visit (std::shared_ptr<NullExprNode> node) = 0;
  virtual void visit (std::shared_ptr<UnaryExprNode> node) = 0;
  virtual void visit (std::shared_ptr<AssignStatNode> node) = 0;
  virtual void visit (std::shared_ptr<BlockNode> node) = 0;
  virtual void visit (std::shared_ptr<ForStatNode> node) = 0;
  virtual void visit (std::shared_ptr<IfStatNode> node) = 0;
  virtual void visit (std::shared_ptr<ReturnStatNode> node) = 0;
  virtual void visit (std::shared_ptr<WhileStatNode> node) = 0;
  virtual void visit (std::shared_ptr<IdNode> node) = 0;
  virtual void visit (std::shared_ptr<LiteralNode> node) = 0;
  virtual void visit (std::shared_ptr<TerminalNode> node) = 0;
  virtual void visit (std::shared_ptr<RootNode> node) = 0;
  virtual void createScope(const std::shared_ptr<ASTNode> &node);
  virtual void exitScope();
};