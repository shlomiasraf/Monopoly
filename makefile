CXX = clang++
CXXFLAGS = -std=c++17 -Werror
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=99

# Define the sources for the demo executable (excluding test files)
SOURCES = Board.cpp Button.cpp kindSquare.cpp Monopoly.cpp Player.cpp Square.cpp surpriseCard.cpp

# Define the headers
HEADERS = Board.hpp Button.hpp kindSquare.hpp Monopoly.hpp Player.hpp Square.hpp surpriseCard.hpp

# Define the DEMO sources (including Demo.cpp)
DEMO_SOURCES = $(SOURCES) Demo.cpp

# Define the test sources (including test files)
TEST_SOURCES = $(SOURCES) tests.cpp testCounter.cpp

# Define the object files for the DEMO and test executables
DEMO_OBJECTS = $(DEMO_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Define the executables
DEMO_EXECUTABLE = monopoly
TEST_EXECUTABLE = runTests

# SFML Libraries to link
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Default rule
all: $(DEMO_EXECUTABLE) $(TEST_EXECUTABLE)

# Run demo rule
demo: $(DEMO_EXECUTABLE)
	./$(DEMO_EXECUTABLE)

# Run tests rule
test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

# Rule for linking the DEMO executable
$(DEMO_EXECUTABLE): $(DEMO_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

# Rule for linking the test executable
$(TEST_EXECUTABLE): $(filter-out Demo.o,$(TEST_OBJECTS))
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

# Rule for compiling object files with corresponding headers
%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for compiling object files without corresponding headers
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind_test: $(TEST_EXECUTABLE)
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$(TEST_EXECUTABLE)

valgrind_monopoly: $(DEMO_EXECUTABLE)
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$(DEMO_EXECUTABLE)

#2>&1 | { egrep "lost| at " || true; }

# Clean rule
clean:
	rm -f $(DEMO_OBJECTS) $(TEST_OBJECTS) $(DEMO_EXECUTABLE) $(TEST_EXECUTABLE)
