brew install raylib
clang main.c -o main -O2 -std=c11 -I"$(brew --prefix)/include" -L"$(brew --prefix)/lib" -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
./main
