//
// Created by zhang-kai on 6/13/25.
//

#pragma once
#include <memory>

class ExprNode;
class RegularStatNode;
class StatNode;
class IdNode;
class AssignStatNode;
class Scope;
class RootNode;
class ClassFuncDefNode;
class ClassDefNode;
class FuncDefNode;
class MainFuncNode;
class VarDeclNode;
class VarDefNode;
class ArrayConstNode;
class BinaryExprNode;
class DotExprNode;
class FormatStringNode;
class FuncCallNode;
class IndexExprNode;
class InitArrayNode;
class InitObjectNode;
class NullExprNode;
class UnaryExprNode;
class AssignExprNode;
class BlockNode;
class ForStatNode;
class IfStatNode;
class ReturnStatNode;
class WhileStatNode;
class LiteralNode;
class TerminalNode;
class ASTNode;
class DefNode;
class TernaryExprNode;
class ThisExprNode;
class ParenExprNode;

class VisitControl {
public:
  virtual ~VisitControl();

  //get to other nodes from current node.
  virtual void visit (std::shared_ptr<ClassFuncDefNode> node) = 0;
  virtual void visit (std::shared_ptr<ClassDefNode> node) = 0;
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
  virtual void visit (std::shared_ptr<TernaryExprNode> node) = 0;
  virtual void visit (std::shared_ptr<AssignStatNode> node) = 0;
  virtual void visit (std::shared_ptr<BlockNode> node) = 0;
  virtual void visit (std::shared_ptr<ForStatNode> node) = 0;
  virtual void visit (std::shared_ptr<IfStatNode> node) = 0;
  virtual void visit (std::shared_ptr<ReturnStatNode> node) = 0;
  virtual void visit (std::shared_ptr<WhileStatNode> node) = 0;
  virtual void visit (std::shared_ptr<LiteralNode> node) = 0;
  virtual void visit (std::shared_ptr<TerminalNode> node) = 0;
  virtual void visit (std::shared_ptr<RootNode> node) = 0;
  // virtual void visit (std::shared_ptr<DefNode> node) = 0;
  virtual void visit(std::shared_ptr<IdNode> node) = 0;
  virtual void visit(std::shared_ptr<StatNode> node) = 0;
  virtual void visit(std::shared_ptr<RegularStatNode> node) = 0;
  virtual void visit(std::shared_ptr<ExprNode> node) = 0;
  virtual void visit(std::shared_ptr<ParenExprNode> node) = 0;
};
