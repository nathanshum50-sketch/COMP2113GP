# Compiler and flags
CXX = g++
CXXFLAGS = -std=gnu++11 -Wall -Wextra -pedantic

# Source files
SRCS = main.cpp game.cpp enemy.cpp interface.cpp scoring.cpp card_drawing.cpp card.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Dependency files
DEPS = $(SRCS:.cpp=.d)

# Executable name
TARGET = game

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files with dependency generation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include generated dependency files
-include $(DEPS)

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET) $(DEPS)

# Phony targets
.PHONY: all clean