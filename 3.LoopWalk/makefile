OPTIMIZER := libLoopWalk.so
OBJs := $(subst .cpp,.o,$(wildcard lib/*.cpp))

LLVM_VERSION ?= 15

CXXFLAGS := $(shell llvm-config-$(LLVM_VERSION) --cxxflags) -fPIC

all: $(OPTIMIZER) 

run:
	opt -load ./libLoopWalk.so -loop-walk < test/loop.ll > /dev/null


$(OPTIMIZER): $(OBJs)
	$(CXX) -dylib -shared $^ -o $@

.PHONY: clean
clean:
	$(RM) $(OPTIMIZER) $(OBJs)