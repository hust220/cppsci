ifeq (,${CPPSCI_CC})
	CPPSCI_CC := mpiicpc
endif

ifneq (,$(findstring mpi,${CPPSCI_CC}))
	MACROS  := -DUSEMPI
else
	MACROS  :=
endif

#the complier and build option
CC := $(CPPSCI_CC)
LD := $(CPPSCI_CC)

FLAGS := -mkl -fopenmp -parallel-source-info=2 -xHost $(TBB) -std=c++11 -static-intel $(FLOAT_FLAGS)

ifeq (true,${INFO})
	FLAGS        := $(FLAGS) -DJN_SHOW_INFO
endif

# build on KNL
ifeq (true,${CPPSCI_FLOAT})
	FLOAT_FLAGS := -DFLOAT_PRECISION
else
	FLOAT_FLAGS := 
endif

#debug for vtune and some vectorization report
ifeq (true,${CPPSCI_DEBUG})
	BUILD_PREFIX := build/debug
	FLAGS        := $(FLAGS) -g
else
	BUILD_PREFIX := build/release
	FLAGS        := $(FLAGS) -DNDEBUG -O3
endif

#The following line disables offload.  By default we not offload, no flags needed
ifneq (true,${CPPSCI_OFFLOAD})
	OFFLOAD      := -qno-offload
endif

#This line allows offload debugging
SRC_DIR   := src
TEST_DIR  := test
BIN_DIR   := bin

BUILD_DIR := $(addprefix $(BUILD_PREFIX)/, $(SRC_DIR) $(TEST_DIR))

SRC_CPP   := $(foreach sdir,$(SRC_DIR),  $(wildcard $(sdir)/*.cpp))
TEST_CPP  := $(foreach sdir,$(TEST_DIR), $(wildcard $(sdir)/*.cpp))

SRC_OBJ   := $(patsubst %.cpp, $(BUILD_PREFIX)/%.o, $(SRC_CPP))
TEST_OBJ  := $(patsubst %.cpp, $(BUILD_PREFIX)/%.o, $(TEST_CPP))

vpath %.cpp $(SRC_DIR) $(TEST_DIR)

define make-goal

$1/%.o: %.cpp
	$(CC) $(FLAGS) $(MACROS) $(OFFLOAD) -c $$< -o $$@

$1/%.o: %.cc
	$(CC) $(FLAGS) $(MACROS) $(OFFLOAD) -c $$< -o $$@

endef

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))

.PHONY: all checkdirs clean

all: test

test: checkdirs $(TEST_OBJ) $(SRC_OBJ)
	$(LD) $(FLAGS) $(MACROS) $(OFFLOAD) $(TEST_OBJ) $(SRC_OBJ) -o bin/$@

checkdirs: $(BUILD_DIR) $(BIN_DIR)

$(BUILD_DIR):
	@mkdir -p $@

$(BIN_DIR):
	@mkdir bin

clean:
	@rm -rf bin build


