OPTIMIZER := libLocalOpts.so
OBJs := $(subst .cpp,.o,$(wildcard lib/*.cpp))

LLVM_VERSION ?= 15

CXXFLAGS := $(shell llvm-config-$(LLVM_VERSION) --cxxflags) -fPIC

all: $(OPTIMIZER) 

$(OPTIMIZER): $(OBJs)
	$(CXX) -dylib -shared $^ -o $@

.PHONY: clean
clean:
	$(RM) $(OPTIMIZER) $(OBJs) transformOUT.bc algebraicOUT.bc testOUT.ll a.out hello-worldOUT.ll test/hello-world.ll algebraicOUT.ll transformOUT.ll

transform: $(OPTIMIZER)
	opt -load-pass-plugin=./$(OPTIMIZER) -passes=transform test/test.ll -o transformOUT.bc
	llvm-dis transformOUT.bc -o transformOUT.ll

algebraic: $(OPTIMIZER)
	opt -load-pass-plugin=./$(OPTIMIZER) -passes=algebraic-identity test/test.ll -o algebraicOUT.bc
	llvm-dis algebraicOUT.bc -o test/algebraicOUT.ll

hello-world: $(OPTIMIZER)
	clang -O0 -emit-llvm -S -c test/hello-world.c -o test/hello-world.ll
	opt -load-pass-plugin=./$(OPTIMIZER) -passes=algebraic-identity test/hello-world.ll -o hello-worldOUT.bc
	llvm-dis hello-worldOUT.bc -o hello-worldOUT.ll
	clang++ hello-worldOUT.ll

