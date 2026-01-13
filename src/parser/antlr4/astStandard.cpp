#include <memory>

#include "ast/ast.h"                  // 引入AST节点定义
#include "frontend/ast_builder.h"     // 引入ASTBuilder类声明
#include "utils/error/semantic_error.hpp"  // 引入语义错误处理类

// ASTBuilder 类负责遍历由 ANTLR4 生成的解析树（Parse Tree），并构建对应的抽象语法树（AST）节点。
// 以下各个 visit* 方法对应不同的语法规则，将 Parse Tree 中的节点转为 AST 节点。

std::any ASTBuilder::visitProgram(MxParser::ProgramContext *ctx) {
  // 定义一个结构体，用于临时存储 DefNode 节点和它在源码中的位置（pos），
  // 后续按 pos 排序以保持与源代码中定义顺序一致。
  struct DefType {
    std::shared_ptr<DefNode> node;  // AST 中的定义节点（函数、变量、类等）
    ssize_t pos;                    // 在源码中的开始位置，用于排序
  };
  std::vector<DefType> defs;                        // 存储所有定义及其位置
  std::vector<std::shared_ptr<DefNode>> definitions; // 最终按顺序的定义列表

  // 1. 处理所有顶层的函数定义
  auto func_def = ctx->funcDef();
  for (const auto &item : func_def) {
    // 递归访问子节点，构建对应的 DefNode 节点
    auto ret = std::any_cast<std::shared_ptr<DefNode>>(item->accept(this));
    // 将节点及其起始位置加入 defs
    defs.emplace_back(std::move(ret), item->getSourceInterval().a);
  }

  // 2. 处理所有顶层的变量定义
  auto var_def = ctx->varDef();
  for (const auto &item : var_def) {
    auto ret = std::any_cast<std::shared_ptr<DefNode>>(item->accept(this));
    defs.emplace_back(std::move(ret), item->getSourceInterval().a);
  }

  // 3. 处理所有顶层的类定义
  auto class_def = ctx->classDef();
  for (const auto &item : class_def) {
    auto ret = std::any_cast<std::shared_ptr<DefNode>>(item->accept(this));
    defs.emplace_back(std::move(ret), item->getSourceInterval().a);
  }

  // 4. 处理 main 函数（特殊处理，因为在语法中 mainFunc 会单独出现）
  auto main_func = ctx->mainFunc();
  // 通过 visitMainFunc 返回的是一个 StmtNode（函数体），因为 main 函数没有单独的 DefNode 结构
  auto main_func_body = std::any_cast<std::shared_ptr<StmtNode>>(main_func->accept(this));
  // 手动构造一个 FunctionDefNode，name 固定为 "main"，返回类型固定为 int
  auto main = std::shared_ptr<DefNode>(
      new FunctionDefNode({main_func}, "main", {"int", 0}, {}, main_func_body));
  defs.emplace_back(std::move(main), main_func->getSourceInterval().a);

  // 对 defs 按照 pos 进行排序，以保证 AST 中定义的顺序与源代码一致
  std::sort(defs.begin(), defs.end(), [](const DefType &lhs, const DefType &rhs) {
    return lhs.pos < rhs.pos;
  });
  // 将排序后的节点提取到 definitions 数组中
  for (const auto &item : defs) {
    definitions.push_back(item.node);
  }

  // 最后构造一个 RootNode，包含整个程序的函数体（main 函数体）和所有顶层定义
  return std::make_shared<RootNode>(Position{ctx}, std::move(main_func_body),
                                    std::move(definitions));
}

// 访问 MainFunc 语法规则：只需要返回函数体部分（Suite），因为 main 函数在 visitProgram 中被包装为 FunctionDefNode
std::any ASTBuilder::visitMainFunc(MxParser::MainFuncContext *ctx) {
  auto function = ctx->suite();  // 拿到 main 函数体的语句块
  // 递归访问 suite，将其转为一个 StmtNode（SuiteStmtNode）
  auto func_body = std::any_cast<std::shared_ptr<StmtNode>>(function->accept(this));
  // 直接返回函数体节点本身（后续会在 visitProgram 中包装成 FunctionDefNode）
  return std::shared_ptr(std::move(func_body));
}

// 访问 ClassDef 语法规则：构建 ClassDefNode，将类名和所有成员（ClassStmtNode）传入
std::any ASTBuilder::visitClassDef(MxParser::ClassDefContext *ctx) {
  auto name = ctx->classIdentifier->getText();  // 类名
  auto stmts = ctx->classStmt();                // 类体中所有的成员定义
  std::vector<std::shared_ptr<ClassStmtNode>> return_stmts;
  // 依次访问每个 classStmt，将其转为 ClassStmtNode
  for (const auto &item : stmts) {
    auto ret = std::any_cast<std::shared_ptr<ClassStmtNode>>(item->accept(this));
    return_stmts.push_back(std::move(ret));
  }
  // 返回一个新的 ClassDefNode，包含类名和所有成员节点
  return std::shared_ptr<DefNode>(
      new ClassDefNode({ctx}, std::move(name), std::move(return_stmts)));
}

// 访问 MemberDefStmt 语法规则：类成员变量定义
std::any ASTBuilder::visitMemberDefStmt(MxParser::MemberDefStmtContext *ctx) {
  auto type_name = std::any_cast<TypeType>(ctx->memberType->accept(this));  // 成员变量类型
  auto name = ctx->Identifier();  // 成员变量名列表
  std::vector<std::string> ret_name;
  // 将每个 Identifier 文本提取为字符串
  for (const auto &item : name) {
    ret_name.push_back(item->getText());
  }
  // 返回一个 VarDefClassStmtNode，用于表示类成员变量定义
  return std::shared_ptr<ClassStmtNode>(
      new VarDefClassStmtNode({ctx}, std::move(type_name), std::move(ret_name)));
}

// 访问 ConstructorDefStmt 语法规则：类构造函数定义
std::any ASTBuilder::visitConstructorDefStmt(MxParser::ConstructorDefStmtContext *ctx) {
  auto class_name = ctx->classIdentifier->getText();  // 构造函数对应的类名
  // 递归访问构造函数体（suite），转为 StmtNode
  auto func_body = std::any_cast<std::shared_ptr<StmtNode>>(ctx->suite()->accept(this));
  // 返回一个 ConstructorClassStmtNode，包含类名和构造函数体
  return std::shared_ptr<ClassStmtNode>(
      new ConstructorClassStmtNode({ctx}, std::move(class_name), std::move(func_body)));
}

// 访问 FuncDefStmt 语法规则：类成员函数定义
std::any ASTBuilder::visitFuncDefStmt(MxParser::FuncDefStmtContext *ctx) {
  auto return_type = std::any_cast<TypeType>(ctx->returnType->accept(this));  // 返回类型
  auto func_name = ctx->funcName->getText();  // 方法名
  auto arg_type = ctx->type();               // 参数类型列表
  auto arg_name = ctx->Identifier();         // 参数名列表
  std::vector<std::pair<TypeType, std::string>> arguments;
  // 检查参数类型和名称数量是否一致
  if (arg_type.size() != arg_name.size()) {
    throw std::runtime_error("Arg type number does not match arg name number in Method definition");
  }
  // 从 i=1 开始，跳过第一个参数（因为在 ANTLR 生成的树中，第一个子节点可能是 returnType 或 funcName）
  for (int i = 1; i < arg_name.size(); ++i) {
    arguments.emplace_back(
        std::any_cast<TypeType>(arg_type[i]->accept(this)), arg_name[i]->getText());
  }
  // 递归访问方法体（suite），转为 StmtNode
  auto func_body = std::any_cast<std::shared_ptr<StmtNode>>(ctx->suite()->accept(this));
  // 返回一个 FunctionDefClassStmtNode，表示类的成员函数定义
  return std::shared_ptr<ClassStmtNode>(new FunctionDefClassStmtNode(
      {ctx}, std::move(func_name), std::move(return_type), std::move(arguments),
      std::move(func_body)));
}

// 访问 FuncDef 语法规则：顶层函数定义（不在类中）
std::any ASTBuilder::visitFuncDef(MxParser::FuncDefContext *ctx) {
  auto return_type = std::any_cast<TypeType>(ctx->returnType->accept(this));  // 返回类型
  auto func_name = ctx->funcName->getText();  // 函数名
  auto arg_type = ctx->type();               // 参数类型列表
  auto arg_name = ctx->Identifier();         // 参数名列表
  std::vector<std::pair<TypeType, std::string>> arguments;
  if (arg_type.size() != arg_name.size()) {
    throw std::runtime_error("Arg type number does not match arg name number in Method definition");
  }
  // 提取参数类型和名称
  for (int i = 1; i < arg_name.size(); ++i) {
    arguments.emplace_back(
        std::any_cast<TypeType>(arg_type[i]->accept(this)), arg_name[i]->getText());
  }
  // 递归访问函数体（suite），转为 StmtNode
  auto func_body = std::any_cast<std::shared_ptr<StmtNode>>(ctx->suite()->accept(this));
  // 返回一个 FunctionDefNode，表示顶层函数定义
  return std::shared_ptr<DefNode>(new FunctionDefNode({ctx}, std::move(func_name),
                                                      std::move(return_type), std::move(arguments),
                                                      std::move(func_body)));
}

// 访问 VarDef 语法规则：顶层变量定义
std::any ASTBuilder::visitVarDef(MxParser::VarDefContext *ctx) {
  auto type_name = std::any_cast<TypeType>(ctx->type()->accept(this));  // 变量类型
  auto var_name = ctx->Identifier();  // 变量名列表
  auto var_value = ctx->expression(); // 初始值表达式列表
  int pos = 0;
  std::vector<std::string> ret_name;
  std::vector<std::shared_ptr<ExprNode>> ret_val;
  // 对于每个变量名，判断其后是否跟有对应的初始化表达式
  for (const auto &item : var_name) {
    ret_name.push_back(item->getText());
    // 如果当前位置有初始化表达式且位置匹配，则递归访问表达式
    if (pos < var_value.size() &&
        item->getSourceInterval().b + 2 == var_value[pos]->getSourceInterval().a) {
      auto ret = std::any_cast<std::shared_ptr<ExprNode>>(var_value[pos]->accept(this));
      ret_val.push_back(std::move(ret));
      ++pos;
    } else {
      ret_val.push_back(nullptr);  // 没有初始化，使用 nullptr
    }
  }
  assert(ret_name.size() == ret_val.size());
  // 返回一个 VarDefNode，包含类型、变量名列表和初始化表达式列表
  return std::shared_ptr<DefNode>(
      new VarDefNode({ctx}, std::move(type_name), std::move(ret_name), std::move(ret_val)));
}

// 访问 VarDefStmt 语法规则：作为语句出现的变量定义（在代码块内部）
std::any ASTBuilder::visitVarDefStmt(MxParser::VarDefStmtContext *ctx) {
  auto type_name = std::any_cast<TypeType>(ctx->type()->accept(this));  // 变量类型
  auto var_name = ctx->Identifier();  // 变量名列表
  auto var_value = ctx->expression(); // 初始化表达式列表
  int pos = 0;
  std::vector<std::string> ret_name;
  std::vector<std::shared_ptr<ExprNode>> ret_val;
  for (const auto &item : var_name) {
    ret_name.push_back(item->getText());
    if (pos < var_value.size() &&
        item->getSourceInterval().b + 2 == var_value[pos]->getSourceInterval().a) {
      auto ret = std::any_cast<std::shared_ptr<ExprNode>>(var_value[pos]->accept(this));
      ret_val.push_back(std::move(ret));
      ++pos;
    } else {
      ret_val.push_back(nullptr);
    }
  }
  assert(ret_name.size() == ret_val.size());
  // 返回一个 VarDefStmtNode，表示局部变量定义语句
  return std::shared_ptr<StmtNode>(
      new VarDefStmtNode({ctx}, std::move(type_name), std::move(ret_name), std::move(ret_val)));
}

// 访问 EmptyStmt 语法规则：空语句（仅分号）
std::any ASTBuilder::visitEmptyStmt(MxParser::EmptyStmtContext *ctx) {
  return std::shared_ptr<StmtNode>(new EmptyStmtNode(Position{ctx}));
}

// 访问 SuiteStmt：代表只有一层的语句（不带额外包装）
std::any ASTBuilder::visitSuiteStmt(MxParser::SuiteStmtContext *ctx) {
  return ctx->suite()->accept(this);
}

// 访问 Suite：将一组语句打包成 SuiteStmtNode
std::any ASTBuilder::visitSuite(MxParser::SuiteContext *ctx) {
  auto stmts = ctx->statement();  // 套件内所有语句
  std::vector<std::shared_ptr<StmtNode>> ret_stmts;
  for (const auto &item : stmts) {
    auto ret = std::any_cast<std::shared_ptr<StmtNode>>(item->accept(this));
    ret_stmts.push_back(std::move(ret));
  }
  // 返回一个 SuiteStmtNode，包含一系列子语句
  return std::shared_ptr<StmtNode>(
      new SuiteStmtNode({ctx}, std::move(ret_stmts)));
}

// 访问 ExprStmt：表达式语句，将表达式转为 ExprNode 后包装在 ExprStmtNode 中
std::any ASTBuilder::visitExprStmt(MxParser::ExprStmtContext *ctx) {
  auto expr_node = ctx->expression();  // 取到表达式节点
  auto ret = std::any_cast<std::shared_ptr<ExprNode>>(expr_node->accept(this));
  return std::shared_ptr<StmtNode>(new ExprStmtNode({ctx}, std::move(ret)));
}

// 访问 IfStmt：if 语句，包含条件、真分支和可选的假分支
std::any ASTBuilder::visitIfStmt(MxParser::IfStmtContext *ctx) {
  auto condition = ctx->expression();  // if 条件表达式
  auto condition_ret = std::any_cast<std::shared_ptr<ExprNode>>(condition->accept(this));
  auto true_stmt = ctx->trueStmt;  // 真分支
  auto true_stmt_ret = std::any_cast<std::shared_ptr<StmtNode>>(true_stmt->accept(this));
  auto false_stmt = ctx->falseStmt;  // 假分支（可能为空）
  std::shared_ptr<StmtNode> false_stmt_ret = nullptr;
  if (false_stmt) {
    false_stmt_ret = std::any_cast<std::shared_ptr<StmtNode>>(false_stmt->accept(this));
  }
  // 返回一个 IfStmtNode，包含条件、真分支、假分支（可能为 nullptr）
  return std::shared_ptr<StmtNode>(
      new IfStmtNode({ctx}, std::move(condition_ret), std::move(true_stmt_ret),
                     std::move(false_stmt_ret)));
}

// 访问 WhileStmt：while 语句，包含条件和循环体
std::any ASTBuilder::visitWhileStmt(MxParser::WhileStmtContext *ctx) {
  auto condition = ctx->expression();  // 循环条件
  auto condition_ret = std::any_cast<std::shared_ptr<ExprNode>>(condition->accept(this));
  auto suite = ctx->statement();  // 循环体
  auto suite_ret = std::any_cast<std::shared_ptr<StmtNode>>(suite->accept(this));
  // 返回一个 WhileStmtNode，包含条件和循环体
  return std::shared_ptr<StmtNode>(
      new WhileStmtNode({ctx}, std::move(condition_ret), std::move(suite_ret)));
}

// 访问 ForStmt：for 语句，包含初始化语句、条件表达式、步进表达式和循环体
std::any ASTBuilder::visitForStmt(MxParser::ForStmtContext *ctx) {
  auto initialize_stmt = ctx->initializeStmt;  // 初始化语句（可能是 VarDefStmt 或 ExprStmt 等）
  auto initialize_ret = std::any_cast<std::shared_ptr<StmtNode>>(initialize_stmt->accept(this));
  auto condition_expr = ctx->conditionExpr;  // 条件表达式（可能为 nullptr 表示永真）
  auto condition_ret =
      condition_expr == nullptr
          ? nullptr
          : std::any_cast<std::shared_ptr<ExprNode>>(condition_expr->accept(this));
  auto step_expr = ctx->stepExpr;  // 步进表达式（可能为 nullptr）
  auto step_ret = step_expr == nullptr
                     ? nullptr
                     : std::any_cast<std::shared_ptr<ExprNode>>(step_expr->accept(this));
  auto loop_stmt = ctx->statement().back();  // 循环体语句
  auto loop_ret = std::any_cast<std::shared_ptr<StmtNode>>(loop_stmt->accept(this));
  // 返回一个 ForStmtNode，包含所有部分
  return std::shared_ptr<StmtNode>(
      new ForStmtNode({ctx}, std::move(initialize_ret), std::move(condition_ret),
                      std::move(step_ret), std::move(loop_ret)));
}

// 访问 ReturnStmt：return 语句，可能带表达式或不带
std::any ASTBuilder::visitReturnStmt(MxParser::ReturnStmtContext *ctx) {
  auto expr = ctx->expression();  // 返回值表达式（可能为空）
  std::shared_ptr<ExprNode> ret = nullptr;
  if (expr != nullptr) {
    ret = std::any_cast<std::shared_ptr<ExprNode>>(expr->accept(this));
  }
  // 返回一个 ControlStmtNode，类型为 kReturn，并携带可能的返回表达式
  return std::shared_ptr<StmtNode>(
      new ControlStmtNode({ctx}, ControlStmtNode::StmtType::kReturn, ret));
}

// 访问 BreakStmt：break 语句
std::any ASTBuilder::visitBreakStmt(MxParser::BreakStmtContext *ctx) {
  return std::shared_ptr<StmtNode>(
      new ControlStmtNode({ctx}, ControlStmtNode::StmtType::kBreak));
}

// 访问 ContinueStmt：continue 语句
std::any ASTBuilder::visitContinueStmt(MxParser::ContinueStmtContext *ctx) {
  return std::shared_ptr<StmtNode>(
      new ControlStmtNode({ctx}, ControlStmtNode::StmtType::kContinue));
}

// 访问 AtomicExpr：原子表达式，将 primary 节点包装成 AtomExprNode
std::any ASTBuilder::visitAtomicExpr(MxParser::AtomicExprContext *ctx) {
  auto primary = ctx->primary();  // primary 节点
  auto ret = std::any_cast<std::shared_ptr<PrimaryNode>>(primary->accept(this));
  return std::shared_ptr<ExprNode>(new AtomExprNode({ctx}, std::move(ret)));
}

// 访问 UnaryExpr：一元表达式，根据符号类型创建对应的 UnaryExprNode
std::any ASTBuilder::visitUnaryExpr(MxParser::UnaryExprContext *ctx) {
  auto expr = ctx->expression();  // 子表达式
  auto expr_ret = std::any_cast<std::shared_ptr<ExprNode>>(expr->accept(this));
  UnaryExprNode::OpType op_type;
  // 判断是一元加法、减法、逻辑非、按位非，还是前/后++/-- 运算
  if (ctx->Add()) {
    op_type = UnaryExprNode::OpType::kPlus;
  } else if (ctx->Sub()) {
    op_type = UnaryExprNode::OpType::kMinus;
  } else if (ctx->Not()) {
    op_type = UnaryExprNode::OpType::kNot;
  } else if (ctx->NotLogic()) {
    op_type = UnaryExprNode::OpType::kNotLogic;
  } else if (auto increment = ctx->Increment()) {
    // 根据 Increment 出现的位置判断是前置递增还是后置递增
    op_type = expr->getSourceInterval().a > increment->getSourceInterval().a
                  ? UnaryExprNode::OpType::kPreIncrement
                  : UnaryExprNode::OpType::kSufIncrement;
  } else if (auto decrement = ctx->Decrement()) {
    // 根据 Decrement 出现的位置判断是前置递减还是后置递减
    op_type = expr->getSourceInterval().a > decrement->getSourceInterval().a
                  ? UnaryExprNode::OpType::kPreDecrement
                  : UnaryExprNode::OpType::kSufDecrement;
  } else {
    throw std::runtime_error("No valid operator for unary expr");
  }
  // 返回一个新的 UnaryExprNode
  return std::shared_ptr<ExprNode>(
      new UnaryExprNode({ctx}, op_type, std::move(expr_ret)));
}

// 访问 BinaryExpr：二元表达式，根据运算符类型创建对应的 BinaryExprNode
std::any ASTBuilder::visitBinaryExpr(MxParser::BinaryExprContext *ctx) {
  auto expr = ctx->expression();  // 子表达式列表，expr[0] 为左操作数，expr[1] 为右操作数
  auto lhs = std::any_cast<std::shared_ptr<ExprNode>>(expr[0]->accept(this));
  auto rhs = std::any_cast<std::shared_ptr<ExprNode>>(expr[1]->accept(this));
  BinaryExprNode::OpType op_type;
  // 根据具体的运算符标识符设置 op_type
  if (ctx->Add()) {
    op_type = BinaryExprNode::OpType::kAdd;
  } else if (ctx->Sub()) {
    op_type = BinaryExprNode::OpType::kSub;
  } else if (ctx->Mul()) {
    op_type = BinaryExprNode::OpType::kMul;
  } else if (ctx->Div()) {
    op_type = BinaryExprNode::OpType::kDiv;
  } else if (ctx->Mod()) {
    op_type = BinaryExprNode::OpType::kMod;
  } else if (ctx->And()) {
    op_type = BinaryExprNode::OpType::kAnd;
  } else if (ctx->Or()) {
    op_type = BinaryExprNode::OpType::kOr;
  } else if (ctx->Xor()) {
    op_type = BinaryExprNode::OpType::kXor;
  } else if (ctx->AndLogic()) {
    op_type = BinaryExprNode::OpType::kAndLogic;
  } else if (ctx->OrLogic()) {
    op_type = BinaryExprNode::OpType::kOrLogic;
  } else if (ctx->ShiftLeft()) {
    op_type = BinaryExprNode::OpType::kShiftL;
  } else if (ctx->ShiftRight()) {
    op_type = BinaryExprNode::OpType::kShiftR;
  } else if (ctx->Equal()) {
    op_type = BinaryExprNode::OpType::kEqual;
  } else if (ctx->UnEqual()) {
    op_type = BinaryExprNode::OpType::kNotEqual;
  } else if (ctx->Less()) {
    op_type = BinaryExprNode::OpType::kLess;
  } else if (ctx->Greater()) {
    op_type = BinaryExprNode::OpType::kGreater;
  } else if (ctx->LessEqual()) {
    op_type = BinaryExprNode::OpType::kLessEqual;
  } else if (ctx->GreaterEqual()) {
    op_type = BinaryExprNode::OpType::kGreaterEqual;
  } else {
    throw std::runtime_error("Invalid binary operator");
  }
  // 返回一个新的 BinaryExprNode，包含左右操作数及运算类型
  return std::shared_ptr<ExprNode>(
      new BinaryExprNode({ctx}, op_type, std::move(lhs), std::move(rhs)));
}

// 访问 TenaryExpr：三元表达式，形如 cond ? trueExpr : falseExpr
std::any ASTBuilder::visitTenaryExpr(MxParser::TenaryExprContext *ctx) {
  auto expr = ctx->expression();  // expr[0] = 条件, expr[1] = 真分支, expr[2] = 假分支
  auto condition = std::any_cast<std::shared_ptr<ExprNode>>(expr[0]->accept(this));
  auto true_expr = std::any_cast<std::shared_ptr<ExprNode>>(expr[1]->accept(this));
  auto false_expr = std::any_cast<std::shared_ptr<ExprNode>>(expr[2]->accept(this));
  // 返回一个 TenaryExprNode，包含条件节点、真分支节点、假分支节点
  return std::shared_ptr<ExprNode>(
      new TenaryExprNode({ctx}, std::move(condition), std::move(true_expr),
                         std::move(false_expr)));
}

// 访问 AssignExpr：赋值表达式，形如 lhs = rhs
std::any ASTBuilder::visitAssignExpr(MxParser::AssignExprContext *ctx) {
  auto expr = ctx->expression();
  auto lhs = std::any_cast<std::shared_ptr<ExprNode>>(expr[0]->accept(this));
  auto rhs = std::any_cast<std::shared_ptr<ExprNode>>(expr[1]->accept(this));
  // 返回一个 AssignExprNode，包含左值节点和右值节点
  return std::shared_ptr<ExprNode>(
      new AssignExprNode({ctx}, std::move(lhs), std::move(rhs)));
}

// 访问 MemberExpr：成员访问表达式，如 obj.member
std::any ASTBuilder::visitMemberExpr(MxParser::MemberExprContext *ctx) {
  auto expr = ctx->expression();  // 对象表达式
  auto ret = std::any_cast<std::shared_ptr<ExprNode>>(expr->accept(this));
  std::string member = ctx->Identifier()->getText();  // 成员名
  return std::shared_ptr<ExprNode>(
      new MemberExprNode({ctx}, std::move(ret), std::move(member)));
}

// 访问 SubscriptExpr：下标表达式，如 arr[index1][index2]...
std::any ASTBuilder::visitSubscriptExpr(MxParser::SubscriptExprContext *ctx) {
  auto expr = ctx->expression();
  auto base = std::any_cast<std::shared_ptr<ExprNode>>(expr[0]->accept(this));  // 基础数组表达式
  std::vector<std::shared_ptr<ExprNode>> index;
  // 依次访问后续的所有下标表达式
  for (int i = 1; i < expr.size(); ++i) {
    auto ret = std::any_cast<std::shared_ptr<ExprNode>>(expr[i]->accept(this));
    index.push_back(std::move(ret));
  }
  // 返回一个 SubscriptExprNode，包含 base 节点和所有下标表达式节点
  return std::shared_ptr<ExprNode>(
      new SubscriptExprNode({ctx}, std::move(base), std::move(index)));
}

// 访问 FormatExpr：格式化字符串表达式，将字符串字面量和嵌入的表达式按位置交替存储
std::any ASTBuilder::visitFormatExpr(MxParser::FormatExprContext *ctx) {
  auto literal = ctx->FormatStringLiteral();  // 字符串字面量列表
  auto expr = ctx->expression();              // 嵌入的表达式列表
  auto pos1 = 0, pos2 = 0;
  // 格式化内容可以包含纯文本（字符串字面量）和动态表达式（ExprNode）
  std::vector<std::variant<std::string, std::shared_ptr<ExprNode>>> format;
  // 按照源码中出现顺序合并 literal 和 expr 两个列表
  while (pos1 < literal.size() && pos2 < expr.size()) {
    // 比较字面量和表达式的起始位置，位置更小的先加入 format
    if (literal[pos1]->getSourceInterval().a < expr[pos2]->getSourceInterval().a) {
      format.emplace_back(literal[pos1]->getText());
      ++pos1;
    } else {
      auto ret = std::any_cast<std::shared_ptr<ExprNode>>(expr[pos2]->accept(this));
      format.emplace_back(std::move(ret));
      ++pos2;
    }
  }
  // 剩余的纯文本部分
  while (pos1 < literal.size()) {
    format.emplace_back(literal[pos1]->getText());
    ++pos1;
  }
  // 剩余的表达式部分
  while (pos2 < expr.size()) {
    auto ret = std::any_cast<std::shared_ptr<ExprNode>>(expr[pos2]->accept(this));
    format.emplace_back(std::move(ret));
    ++pos2;
  }
  // 返回 FormatExprNode，包含交替的文本和表达式
  return std::shared_ptr<ExprNode>(
      new FormatExprNode({ctx}, std::move(format)));
}

// 访问 ParenExpr：圆括号表达式，直接返回子表达式的 AST 节点
std::any ASTBuilder::visitParenExpr(MxParser::ParenExprContext *ctx) {
  auto expr = ctx->expression();
  return expr->accept(this);
}

// 访问 FuncCallExpr：函数调用表达式，可能带有类成员调用（对象.方法）
std::any ASTBuilder::visitFuncCallExpr(MxParser::FuncCallExprContext *ctx) {
  auto func_name = ctx->funcName->getText();  // 函数名
  auto arguments = ctx->arguments();          // 参数列表节点
  std::vector<std::shared_ptr<ExprNode>> ret_arg;
  if (arguments) {
    // 递归访问参数，得到所有 ExprNode
    ret_arg = std::any_cast<std::vector<std::shared_ptr<ExprNode>>>(arguments->accept(this));
  }
  auto class_var = ctx->classVar;  // 如果是成员调用，则 classVar 非空
  std::shared_ptr<ExprNode> ret_val = nullptr;
  if (class_var) {
    ret_val = std::any_cast<std::shared_ptr<ExprNode>>(class_var->accept(this));
  }
  // 返回一个 FunctionCallExprNode，包含可选的对象表达式、函数名和参数列表
  return std::shared_ptr<ExprNode>(
      new FunctionCallExprNode({ctx}, std::move(ret_val), std::move(func_name),
                               std::move(ret_arg)));
}

// 访问 Arguments：参数列表，将多个表达式依次转为 ExprNode 并存入向量
std::any ASTBuilder::visitArguments(MxParser::ArgumentsContext *ctx) {
  auto expr = ctx->expression();
  std::vector<std::shared_ptr<ExprNode>> ret_args;
  for (const auto &item : expr) {
    auto ret = std::any_cast<std::shared_ptr<ExprNode>>(item->accept(this));
    ret_args.push_back(std::move(ret));
  }
  return std::move(ret_args);
}

// 访问 VarPrimary：变量原子节点，直接构造 VarPrimaryNode
std::any ASTBuilder::visitVarPrimary(MxParser::VarPrimaryContext *ctx) {
  auto name = ctx->Identifier()->getText();
  return std::shared_ptr<PrimaryNode>(new VarPrimaryNode({ctx}, std::move(name)));
}

// 访问 LiteralPrimary：字面量原子节点，根据实际字面量类型转发给对应的 visit 函数
std::any ASTBuilder::visitLiteralPrimary(MxParser::LiteralPrimaryContext *ctx) {
  auto literal = ctx->literal();
  return literal->accept(this);
}

// 访问 ThisPrimary：this 关键字，表示当前对象
std::any ASTBuilder::visitThisPrimary(MxParser::ThisPrimaryContext *ctx) {
  return std::shared_ptr<PrimaryNode>(new ThisPrimaryNode(Position{ctx}));
}

// 访问 NewPrimary：new 表达式，用于对象或数组的创建
std::any ASTBuilder::visitNewPrimary(MxParser::NewPrimaryContext *ctx) {
  auto type_name = ctx->type()->getText();    // 要创建的类型
  auto l_bracket = ctx->LeftBracket().size(); // [ 的个数
  auto array = ctx->array();                  // 如果有 array 嵌套，则表示多维数组字面量
  if (l_bracket == 0) {
    // 普通 new 类型() 不带数组
    return std::shared_ptr<PrimaryNode>(
        new NewPrimaryNode({ctx}, std::move(type_name)));
  }
  if (array) {
    // 带数组字面量的情况，递归访问 array 得到 ArrayNode
    auto array_ret = std::any_cast<std::shared_ptr<ArrayNode>>(array->accept(this));
    return std::shared_ptr<PrimaryNode>(
        new NewPrimaryNode({ctx}, std::move(type_name), l_bracket, std::move(array_ret)));
  }
  // 带动态维度（表达式）的数组创建，如 new int[expr1][expr2]...
  auto expr = ctx->expression();
  std::vector<std::shared_ptr<ExprNode>> index;
  for (const auto &item : expr) {
    auto ret = std::any_cast<std::shared_ptr<ExprNode>>(item->accept(this));
    index.push_back(std::move(ret));
  }
  // 检测非法类型错误，例如 new Type [ 未闭合
  if (ctx->getStart()->getInputStream()
          ->getText(misc::Interval{ctx->stop->getStopIndex() + 1,
                                   ctx->stop->getStopIndex() + 1}) == "[") {
    throw InvalidType(Position{ctx});
  }
  // 返回一个 NewPrimaryNode，包含类型名、维度个数和下标表达式列表
  return std::shared_ptr<PrimaryNode>(
      new NewPrimaryNode({ctx}, std::move(type_name), l_bracket, std::move(index)));
}

// 访问 BoolLiteral：布尔字面量，True 或 False
std::any ASTBuilder::visitBoolLiteral(MxParser::BoolLiteralContext *ctx) {
  auto res = ctx->True() != nullptr;
  return std::shared_ptr<PrimaryNode>(new LiteralPrimaryNode({ctx}, res));
}

// 访问 DecimalLiteral：十进制整数字面量
std::any ASTBuilder::visitDecimalLiteral(MxParser::DecimalLiteralContext *ctx) {
  // stoll 将字符串转为 long long，再转换为 int
  auto res = std::stoll(ctx->DecimalNumber()->getText());
  return std::shared_ptr<PrimaryNode>(new LiteralPrimaryNode({ctx}, static_cast<int>(res)));
}

// 访问 NullLiteral：null 字面量
std::any ASTBuilder::visitNullLiteral(MxParser::NullLiteralContext *ctx) {
  return std::shared_ptr<PrimaryNode>(new LiteralPrimaryNode(Position{ctx}));
}

// 访问 StringLiteral：字符串字面量，去除前后双引号后保存
std::any ASTBuilder::visitStringLiteral(MxParser::StringLiteralContext *ctx) {
  auto str = ctx->StringLiteral()->getText();
  // 去除开头和结尾的双引号
  str = str.substr(1, str.size() - 2);
  return std::shared_ptr<PrimaryNode>(new LiteralPrimaryNode({ctx}, std::move(str)));
}

// 访问 ArrayLiteral：数组字面量，将 array 子节点转为 ArrayNode 后包装为 LiteralPrimaryNode
std::any ASTBuilder::visitArrayLiteral(MxParser::ArrayLiteralContext *ctx) {
  auto array = ctx->array();
  auto res = std::any_cast<std::shared_ptr<ArrayNode>>(array->accept(this));
  return std::shared_ptr<PrimaryNode>(new LiteralPrimaryNode({ctx}, std::move(res)));
}

// 访问 Array：处理嵌套数组字面量或简单数组字面量
std::any ASTBuilder::visitArray(MxParser::ArrayContext *ctx) {
  auto literal = ctx->literal(); // 如果有再次嵌套，则 literal 长度为子元素个数
  auto array = ctx->array();     // 嵌套的 array 节点
  if (!array.empty()) {
    // 有嵌套 array，递归构建多个 ArrayNode 形成 JaggedArray
    std::vector<std::shared_ptr<ArrayNode>> array_ret;
    for (const auto &item : array) {
      auto ret = std::any_cast<std::shared_ptr<ArrayNode>>(item->accept(this));
      array_ret.push_back(std::move(ret));
    }
    return std::shared_ptr<ArrayNode>(
        new JaggedArrayNode({ctx}, std::move(array_ret)));
  }
  // 否则是简单数组，逐个将 literal 中的 Primary 构建为 PrimaryNode
  std::vector<std::shared_ptr<PrimaryNode>> literal_ret;
  for (const auto &item : literal) {
    auto ret = std::any_cast<std::shared_ptr<PrimaryNode>>(item->accept(this));
    literal_ret.push_back(std::move(ret));
  }
  // 返回一个 SimpleArrayNode，包含所有字面量元素
  return std::shared_ptr<ArrayNode>(
      new SimpleArrayNode({ctx}, std::move(literal_ret)));
}

// 访问 Type：类型节点，可以是用户定义类型（Identifier）或关键字类型（bool/int/string/void），并记录数组维度
std::any ASTBuilder::visitType(MxParser::TypeContext *ctx) {
  std::string identifier;
  if (auto id = ctx->Identifier()) {
    identifier = id->getText();
  } else if (ctx->Bool()) {
    identifier = "bool";
  } else if (ctx->Int()) {
    identifier = "int";
  } else if (ctx->String()) {
    identifier = "string";
  } else if (ctx->Void()) {
    identifier = "void";
  } else {
    throw std::runtime_error("Invalid type");
  }
  // LeftBracket().size() 表示类型后面方括号的深度（数组维度）
  return TypeType{std::move(identifier), ctx->LeftBracket().size()};
}
