OPTIMIZER := libLoopFusion.so
OBJs := $(subst .cpp,.o,$(wildcard lib/*.cpp))

LLVM_VERSION ?= 15

CXXFLAGS := $(shell llvm-config-$(LLVM_VERSION) --cxxflags) -fPIC

all: $(OPTIMIZER) 

$(OPTIMIZER): $(OBJs)
	$(CXX) -dylib -shared $^ -o $@

run: $(OPTIMIZER)
	clang -O0 -emit-llvm -S -c test/LF.c -o test/LF.ll
	opt -load-pass-plugin=./$(OPTIMIZER) -passes=custom-loopfusion test/LF.ll -S -o test/LF.bc
	llvm-dis test/LF.bc -o test/LFout.ll

.PHONY: clean
clean:
	$(RM) $(OPTIMIZER) LICoMo.o test/LICM.bc test/LICMout.ll test/LICM.ll
