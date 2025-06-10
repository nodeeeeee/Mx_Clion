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

   