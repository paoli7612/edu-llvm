OPTIMIZER := optimizer.so
OBJs := $(subst .cpp,.o,$(wildcard src/*.cpp))

LLVM_VERSION ?= 15

CXXFLAGS := $(shell llvm-config-$(LLVM_VERSION) --cxxflags) -fPIC

all: $(OPTIMIZER) 

$(OPTIMIZER): $(OBJs)
	$(CXX) -dylib -shared $^ -o $@

.PHONY: clean
clean:
	$(RM) $(OPTIMIZER) $(OBJs) out/*.ll bc/*.bc test/*.ll

dead: $(OPTIMIZER)
	clang++ -S -emit-llvm test/dead-code-elimination-example.c -o test/dead-code-elimination-example.ll 
	opt -load-pass-plugin=./$(OPTIMIZER) -passes='dead-code-elimination' test/dead-code-elimination-example.ll -o bc/dead-code-elimination-example.bc
	llvm-dis bc/dead-code-elimination-example.bc -o out/dead-code-elimination-example.ll

algebraic: $(OPTIMIZER)
	clang++ -S -emit-llvm test/algebraic-identity-example.c -o test/algebraic-identity-example.ll 
	opt -load-pass-plugin=./$(OPTIMIZER) -passes='algebraic-identity' test/algebraic-identity-example.ll -o bc/algebraic-identity-example.bc
	llvm-dis bc/algebraic-identity-example.bc -o out/algebraic-identity-example.ll

constant: $(OPTIMIZER)
	opt -load-pass-plugin=./$(OPTIMIZER) -passes='constant-propagation' test/constant-propagation-example.ll -o bc/constant-propagation-example.bc
	llvm-dis bc/constant-propagation-example.bc -o out/constant-propagation-example.ll

strenght: $(OPTIMIZER)
	clang++ -S -emit-llvm test/strenght-elimination-example.c -o test/strenght-elimination-example.ll 
	opt -load-pass-plugin=./$(OPTIMIZER) -passes='strenght-elimination,dce' test/strenght-elimination-example.ll -o bc/strenght-elimination-example.bc
	llvm-dis bc/strenght-elimination-example.bc -o out/strenght-elimination-example.ll