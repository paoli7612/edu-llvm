OPTIMIZER := ExploreIR.so
OBJs := $(subst .cpp,.o,$(wildcard lib/*.cpp))

LLVM_VERSION ?= 15

CXXFLAGS := $(shell llvm-config-$(LLVM_VERSION) --cxxflags) -fPIC

all: $(OPTIMIZER) 

$(OPTIMIZER): $(OBJs)
	$(CXX) -dylib -shared $^ -o $@

.PHONY: clean
clean:
	$(RM) $(OPTIMIZER) $(OBJs) ll -rf

alfa: ll $(OPTIMIZER) 
	clang -O0 -emit-llvm -S -c test/alfa.c -o ll/alfa.ll
	opt -load-pass-plugin=./$(OPTIMIZER) -passes=explore-ir ll/alfa.ll -disable-output

beta: ll $(OPTIMIZER)
	clang -O0 -emit-llvm -S -c test/beta.c -o ll/beta.ll
	opt -load-pass-plugin=./$(OPTIMIZER) -passes=explore-ir ll/beta.ll -disable-output

gamma: ll $(OPTIMIZER)
	clang -O0 -emit-llvm -S -c test/gamma.c -o ll/gamma.ll
	opt -load-pass-plugin=./$(OPTIMIZER) -passes=explore-ir ll/gamma.ll -disable-output

delta: $(OPTIMIZER)
	opt -load-pass-plugin=./$(OPTIMIZER) -passes=explore-ir test/delta.ll -disable-output
ll:
	mkdir ll