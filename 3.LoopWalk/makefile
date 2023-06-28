OPTIMIZER := libLoopWalk.so
OBJs := $(subst .cpp,.o,$(wildcard lib/*.cpp))

LLVM_VERSION ?= 15

CXXFLAGS := $(shell llvm-config-$(LLVM_VERSION) --cxxflags) -fPIC

all: $(OPTIMIZER) 

$(OPTIMIZER): $(OBJs)
	$(CXX) -dylib -shared $^ -o $@

run: $(OPTIMIZER)
	opt -enable-new-pm=0 -load ./libLoopWalk.so -loop-walk test/loop.ll -disable-output

hello-world: $(OPTIMIZER)
	clang++ -O0 -emit-llvm -S -c test/hello-world.c -o test/hello-world.ll
	opt -enable-new-pm=0 -load ./libLoopWalk.so -loop-walk test/hello-world.ll -disable-output


.PHONY: clean
clean:
	$(RM) $(OPTIMIZER) $(OBJs)