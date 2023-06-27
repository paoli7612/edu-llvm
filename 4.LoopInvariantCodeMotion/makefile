OPTIMIZER := LICoMo.so

LLVM_VERSION ?= 15

CXXFLAGS := $(shell llvm-config-$(LLVM_VERSION) --cxxflags) -fPIC

all: $(OPTIMIZER)

LICoMo.o: lib/LICoMo.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OPTIMIZER): LICoMo.o
	$(CXX) -shared $^ -o $@

run: $(OPTIMIZER)
	clang -O0 -emit-llvm -S -c test/LICM.c -o test/LICM.ll
	opt -enable-new-pm=0 -load ./LICoMo.so -licomo test/LICM.ll -o test/LICM.bc
	llvm-dis test/LICM.bc -o test/LICMout.ll

.PHONY: clean
clean:
	$(RM) $(OPTIMIZER) LICoMo.o test/LICM.bc test/LICMout.ll test/LICM.ll