OPTIMIZER := libTestPass.so
OBJs := $(subst .cpp,.o,$(wildcard lib/*.cpp))

LLVM_VERSION ?= 15

CXXFLAGS := $(shell llvm-config-$(LLVM_VERSION) --cxxflags) -fPIC

all: $(OPTIMIZER) 

$(OPTIMIZER): $(OBJs)
	$(CXX) -dylib -shared $^ -o $@

.PHONY: clean
clean:
	$(RM) $(OPTIMIZER) $(OBJs) *.ll test/*.bc 

Loop: $(OPTIMIZER)
	clang -O0 -emit-llvm -S -c test/Loop.c -o loop.ll
	opt -load-pass-plugin=./$(OPTIMIZER) -passes=test-pass loop.ll -disable-output

Fibonacci: $(OPTIMIZER)
	clang -O0 -emit-llvm -S -c test/Fibonacci.c -o Fibonacci.ll
	opt -load-pass-plugin=./$(OPTIMIZER) -passes=test-pass Fibonacci.ll -disable-output