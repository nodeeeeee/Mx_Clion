source "$HOME/.bashrc"
#echo "当前用户： $(whoami)"
#echo "HOME 目录： $HOME"
#echo $SHELL
#which antlr4
antlr4 -Dlanguage=Java Mx.g4
javac *.java
#for filename in ../../../testcases/codegen/*.mx; do
#  echo "$filename"
#  grun Mx prog -diagnostics "$filename"
#done
grun Mx prog -gui -diagnostics ../../../testcases/codegen/t76.mx