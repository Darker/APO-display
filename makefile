CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS :=

ifeq ($(OS),Windows_NT)

    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)

    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)

        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)

        endif
    endif
else
    LD_FLAGS += -lrt -lpthread
endif

#CC_FLAGS := ...
CC_FLAGS := -fpermissive -std=c++0x -w

display: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^

obj/%.o: %.cpp
	mkdir -p obj
	g++ $(CC_FLAGS) -c -o $@ $<
