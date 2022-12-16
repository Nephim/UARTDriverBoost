SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(SOURCES:.cpp=.d)
EXE=prog.out
CXXFLAGS=-I.
LIBS=-lpthread

ARCH?=x86-64

# Making for x86-64 e.g. x86-64 (the architecture employed )
# > make ARCH=x86-64
ifeq (${ARCH},x86-64)
CXX=g++
BUILD_DIR=build/x86-64
BIN_DIR=bin/x86-64
endif

# Making for architecture
# > make ARCH=arm
ifeq (${ARCH},arm)
CXX=arm-rpizw-g++
BUILD_DIR=build/arm
BIN_DIR=bin/arm
endif


$(BIN_DIR)/$(EXE): $(addprefix $(BUILD_DIR)/,$(DEPS) $(OBJECTS))  # << Check the $(DEPS) new dependency
	mkdir -p $(BIN_DIR) 
	$(CXX) $(CXXFLAGS) -o $@ $(addprefix $(BUILD_DIR)/,$(OBJECTS)) $(LIBS)

# %.cpp -> %.o needs to be added ! Target is NOT just %.o...

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(BUILD_DIR) 
	$(CXX) -c $< $(CXXFLAGS) -o $@


# Rule that describes how a .d ( dependency ) file is created from a .cpp
# Similar to the assigment that you just completed %. cpp -> %.o
$(BUILD_DIR)/%.d: %.cpp
	mkdir -p $(BUILD_DIR) 
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@



.PHONY: clean
clean:
	@rm -rf build/*/*.o build/*/*.d bin/*/$(EXE)
	@rm -rd bin build

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif