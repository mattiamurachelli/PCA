CXX      ?= g++
CXXFLAGS ?= -std=c++20 -O3 -Wall -Wno-conversion-null -Wno-deprecated-declarations -MMD -MP
CPPFLAGS ?= -Iheaders

EXEC     = main_pca
SRC_DIR  = src
OBJ_DIR  = obj

# List all source files
SRCS     := main.cpp $(wildcard $(SRC_DIR)/*.cpp)

# Generate object file paths in obj/
OBJS     := $(OBJ_DIR)/main.o $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))

# Dependency files
DEPS     := $(OBJS:.o=.d)

LDFLAGS  ?=
LDLIBS   ?=

all: $(EXEC)

$(EXEC): $(OBJS)
		$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

# Compile main.cpp separately
$(OBJ_DIR)/main.o: main.cpp | $(OBJ_DIR)
		$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Compile other .cpp files inside src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
		$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Ensure obj directory exists
$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

# Include dependency files if they exist
-include $(DEPS)

clean:
		$(RM) -r $(OBJ_DIR)

distclean: clean