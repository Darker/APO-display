CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS=-lrt -lpthread
#CC_FLAGS := ...
CC_FLAGS := -fpermissive -std=c++0x -pedantic -Wall

display: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o $@ $^

obj/%.o: %.cpp
	g++ $(CC_FLAGS) -c -o $@ $<



