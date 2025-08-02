## Points worth noticing when coding compiler

1. Match the version of antlr4-runtime and antlr parse-generator, otherwise their will be unexpected errors

2. Antlr4 will automatically add lexers of top priority if you don't rename the string but used in your parser. This may cause override problems.

3. Antlr4's parse tree preview in its plug in works incorrectly if you inject some predicate code into it. You will need to use grun with Java to visualize and debug your .g4 file. Grun does not work with C++

4. after writing the non-interactive shell script, we need to execute it using `source script.sh` instead of `bash script.sh` because the former will execute the file in the current shell environment, but the latter will open another shell environment. In the new environment you cannot source ~/.bashrc, which will cause some aliasing errors.

5. move:
   **lvalue: ** turn the left value into rvalue. (and subsequently rebinding it to another lvalue. Without copy or deleting the original rvalue.)
   **rvalue reference: **`T&&` type is still a lvalue (variable with a name is always lvalue), though it is a reference to the rvalue. If you want to move the rvalue again to the new variable, 
   **prvalue: ** no effect, works just the same as using the original prvalue.

   **xvalue: **since an xvalue typically has nothing inside after assignment(`auto y = std::move(v);`), you can apply move to it but it has nothing to steal.

   **smart pointer: **rvalue of the pointer is its address and control block(for smart pointers). So by applying std::move, you transfer the rvalue to a new smart pointer and reset this pointer to null.

   **raw pointer: **nothing happens, just turns `T*` to `T*&&`, because it doesn't have the concept of move construction.

   **lvalue/rvalue of primitives: **is actually still copying the value.

   **const:** no effect. You cannot move the content away for const types.

   p.s. prvalue is just temporary, and does not have an address, need to be objectified to get its own address. While xvalue already has its address, its resources will be stolen and moved to another address. It is like prvalue is gold panning and store it somewhere, xvalue is a opened safe, its gold is prepared to be moved to other places.
   
6. forward:
   std::forward acts with T&&, the universal reference. 

   ```C++
   void takeByValue(std::string s) {
       std::cout << "[takeByValue] received \"" << s << "\"\n";
   }
   
   template <typename T>
   void withoutForward(T&& x) {
       // x is always treated as an lvalue here
       takeByValue(x);        // ✅ always invokes copy constructor
   }
   ```

   what std::forward does: Keep x as its original type, if it is a rvalue, it will be passed to takeByValue as a rvalue, vice versa. Otherwise, a x is still a lvalue even if it is actually a reference to rvalue, and it will call copy.
   what T&& does: Forward usually work when we don't know what kind of value a variable is referring at, otherwise we can just infer by ourselves and use move. T&& create the scenario where we don't know what value T&& is referring to.

7. Only binding to a const lvalue reference extends the lifetime of a xvalue. Binding it to a rvalue reference doesn't work.

8. You can bind lvalue, prvalue, xvalue to const &T, but can only bind lvalue to &T(non-const)

9. **how to call a function without copying to parameter**

   ```cpp
   // by-value + move
   // Use when you need a local copy inside foo anyway, and don't need it in the original scope
   // gives you strong exception-safety guarantees 
   void foo(std::string x);
   std::string y = /*…*/;
   foo(std::move(y));
   ```

   ```cpp
   // rvalue reference
   // less flexible than by-value + move because it can only take in rvalues.
   void foo(std::string&& s);
   std::string y = /*…*/;
   foo(std::move(y));
   ```

   ```cpp
   // const lvalue reference
   // First choice, simplest and fast, can take in both lvalue and rvalue
   void foo(const std::string& s);
   std::string y = /*…*/;
   foo(y);
   ```

   ```cpp
   // Raw Pointer 
   // hard to manage memory
   void foo(const std::string* ps);
   std::string y = /*…*/;
   foo(&y);
   ```

   ```cpp
   // Perfect forwarding
   // useful when don't know the type of y(lvalue or rvalue)
   template<class T>
   void foo(T&& x) {
     bar(std::forward<T>(x));  // preserves l- or r-value such that if it is rvalue it doesn't need to copy again.
   }
   ```

   ```cpp
   // unique ptr
   // cost almost the same as raw pointer, not using it very much because for each address, only one instance can own it.
   void foo(MyType* p);
   auto up = std::make_unique<MyType>(…);
   foo(up.get());
   ```

   ```cpp
   // shared ptr
   // it is a heavy time itself. Only used when you truly need shared ownership that outlives any single scope.
   void f(std::shared_ptr<Foo> p);
   f(ptr);
   ```

   In conclusion: 

   1. const lvalue reference: first choice
   2. by-value + move: Use when you need a local copy inside foo anyway, and don't need it in the original scope
   3. Perfect forwarding: useful when don't know the type of the argument(lvalue or rvalue), saves time for rvalues
   4. shared ptr: it is a heavy time itself. Only used when no other choices.
   5. by-value without move: for primitives

   Note that:

   ```cpp
   DefNode(const std::string& name) : name(std::move(name)) {}
   // doesn't work because move turns const T& to const T&&, which cannot be bound to T&&, and falls back copying.
   // In this case we recommend
   DefNode(std::string name) : name(std::move(name)) {}
   ```


9. **difference between returning the original variable and returning alias**

   Returning the original variable: requires copy, but exists after the original object is destructed. 

   Returning alias: doesn't require copy, but we need to guarantee that the original object is still available when visiting it through alias.

10. Do not do the following because even though we wrote `#pragma once`, the IDE and compiler will still find the definition of some classes missing, reporting unexpected warnings.

    ```cpp
    // B is a subclass of A, but we will need to use B in A.
    #define "b.h"   //in a.h
    #define "a.h"   //in b.h
    ```

    A better practice is to move the definition to `a.cpp` and `b.cpp`, only do declaration in `a.h` and `b.h`. And use forward declaration `Class B;` 

11. ```cpp
    virtual void visit(RootNode *node) = 0;
    // With '= 0': method pure virtual, containing class abstract and unable to instantiate, derived classes must override it
    // Without '= 0': method not pure virtual, containing class can instantiate if there is no other pure virtual methods, derived classes need not override it.
    ```

    When we want to use dynamic type casting, we must make the base class virtual, and must declare a virtual destructor `virtual ~Base() = default;`

12. Things to be aware of when using `T &` as return type:
    This is returning a reference of the original value, which means we must guarantee that the object is still alive when we use its value outside the method.
    If we don't want the object be modified outside the method, we can return `const T&`.
    We must avoid returning a local variable inside the method or a prvalue.

13. `if`,`while`,`for` has two types of writing, either adding curly bracket or not.
    So I manually added the brackets when there is not, making it a block. So I can easily judge which is a new scope by looking at the blocks.

14. ```cpp
    Scope current_scope = new GlobalScope();
    ```

    This is wrong for C++, because `new GlobalScope()` yields a GlobalScope* pointer. 

15. To support built-in methods, I will hard-code `string` as a class.

16. It seems quite important to design your code structure before you start coding. This includes drawing a diagram for the main methods and classes, assigning jobs to each file, and plot `.h` file.

17. Use visitor + accept to dfs the ast-tree. Because this can automatically give you dynamic binding. If you only use visit method, then you have to manually write massive dynamic bindings.

18. For class usage, we can either forward declare using `class Foo;`, or use `#include`. We need to notice the following points:

    1. `class Foo;` does not automatically help you find the definition of the class. This is typically used in `.h` files, we need to materialize it using `# include` in the corresponding `.cpp` files.
    2. When using `#include`, we need to beware that we cannot `include` recursively, namely, `#include b.h` in `a.h` and `#include a.h` in `b.h`.
    3. One common solution is to give `class` declaration in `.h` to guarantee no recursive declaration is involved. And then use `#include` in `.cpp` files. In these `include` sentences, they will find the declaration of `.h` file, and now we don't have recursive `#include` in `.h` files.

19. Singleton
    We use singleton mainly for category classes. Such as when we need to separate different types, we may define a virtual class `Type`, and define its subclasses `BoolType`, `IntType`, etc. We need to delete all the invisible move constructors and copy constructors to ensure safety. We need to add a factory method, and an existing instance.

    ```C++
    static BoolType& Instance() {
        static BoolType instance;
        return instance;
      }
    ```

    

    Then in `Type` class, we will define some basic methods:

    ```c++
    class Type{
        ...
        bool equal(Type& other) {
            return this == other;
        }
    }
    ```

    When we want to bind a type to a identifier, we can use 

    ```C++
    Type& tmp = BoolType::Instance();
    ```

20. virtual functions in the base class only requires the leaf derived classes implements those functions, and the whole thing works properly. For example, if `A->B->CDE`, A has a virtual function f(), if `CDE` correctly implements f(), and B doesn't implement, it will perform dynamic binding properly.

21. if we perform any_cast to std::any, we need to make sure the type we are casting to is precisely the compile time type of the object. So here in my compiler, I cannot `auto a = any_cast<std::shared_ptr<ExprNode>>(binary_expr->accept(this))`, if my accept returns a `BinaryExprNode`. What I can do is to make the return type of `visitBinaryExprNode` to `ExprNode`.

22. when we use auto, and the actual type is std::vector<...>, the static syntax analyzer cannot identify whether you have used `#include<vector>` or not. This may lead to runtime error.

23. ```
    ../../../testcases/sema/scripts/test_all.bash '../../../cmake-build-testall/Mx_Clion -fsyntax-only' ../../../testcases/sema
    ```

    This is how to call the run_all script. I can either change profile or change the application. When changing the profile, I am changing the compile options(program arguments). When changing the application, I can designate program arguments, environment variables and working directory.

24. We can define debugging mode and oj/test mode in Clion, by "Edit Cmake Profiles", and write your customized CMake options. For example, if I add `-DENABLE_OJ_MODE=ON`, and add

    ```cmake
    if(ENABLE_OJ_MODE)
        set(CMAKE_CXX_FLAGS "-Ofast -Dtestall")
        message(STATUS ">>> OJ_MODE is ON")
    else()
        set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -g -O0 ")
        message(STATUS ">>> OJ_MODE is OFF")
    endif()
    ```

    in CMakeLists.txt, and add corresponding `#ifdef`, `#ifndef`, `#endif` in `main.cpp`. We can conveniently switch b

    