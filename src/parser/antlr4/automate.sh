# Usage:
# for java actions only
# go into src/parser/antlr4 directory
# type   source automate.sh


source "$HOME/.bashrc"
#echo "当前用户： $(whoami)"
#echo "HOME 目录： $HOME"
#echo $SHELL
#which antlr4
antlr4 -Dlanguage=Cpp Mx.g4
#javac *.java
cmake
for filename in ../../../testcases/codegen; do
  echo "$filename"

  grun Mx prog -diagnostics "$filename"
done
#grun Mx prog -gui -diagnostics -tokens -tree -trace ../../../testcases/sema/array-package/array-5.mx
