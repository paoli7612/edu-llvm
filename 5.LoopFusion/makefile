OPTIMIZER := LoFu.so

LLVM_VERSION ?= 15

CXXFLAGS := $(shell llvm-config-$(LLVM_VERSION) --cxxflags) -fPIC

all: $(OPTIMIZER)

LoFu.o: lib/LoFu.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OPTIMIZER): LoFu.o
	$(CXX) -shared $^ -o $@

run: $(OPTIMIZER)
	clang -O0 -emit-llvm -S -c test/LF.c -o test/LF.ll
	opt -enable-new-pm=0 -load ./LoFu.so -lofu test/LF.ll -o test/LF.bc
	llvm-dis test/LF.bc -o test/LoFu.ll

.PHONY: clean
clean:
	$(RM) $(OPTIMIZER) LoFu.o LoFu.o test/LF.bc test/LF.bc