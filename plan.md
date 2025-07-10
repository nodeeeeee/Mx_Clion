对于global scope，由于class和function可以进行向后引用，所以进行提前提取

class需要提取ID和内部所有var declaration, function declaration（当作普通function进行collect），class constructor但是我们不会用嵌套类

function需要提取return type，param type，ID

在semantic_check的rootnode入口处先调用global_scope_extractor。

semantic_check中我需要追踪current scope，其实可以作为全局变量进行keep track。在global_scope_extractor的时候要进行传入。

我将为所有的scope加入return type，为了进行return statement判断。只有function会有valid return type，其他都是nullptr

为了将return, continue, break定位，我为所有block加入了其父节点信息。

在global_scope_extractor中我已经将所有global中的classdef, funcdef拉取出来了。同时也拉取了class中的funcdef。所以在所有semantic check的 funcdef 和 classdef 中我不需要再加入scope了

idNode和LiteralNode应该是ExprNode下面的

todo: arrayconstnode访问时要记录下arrayconst的dimension

idNode如果算作exprnode，那么definition中用的ID应该另存在一个地方
semantic check时我不对Idnode本身进行检查，只在exprnode中用到idnode时对其检查



问题：我该如何让这个程序跑起来，并debug？

问题：进行检查之后下一步是应该构筑中间语言程序了吗？





std::cerr

手动析构：1. 跑我定义的析构函数      2. 对每一个成员自动析构       3. 删除自己 free

把asttree的根传给semantic check



对于class来说，在extract时候直接开scope；semantic check的时候进入scope即可





我应该先查IdNode的Type，然后再进行方法调用。

String是一个特殊情况，需要特殊处理。（但是暂时不用考虑，等到前面调试正确再改）

很多问题是因为Id没有正确获得type导致的。当遇到普通id的时候我需要先findvar找到其type