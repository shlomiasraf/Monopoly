CXX=clang++
CXXFLAGS=-std=c++11 -Werror
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99

# Source files for different targets
SOURCESDemo = Board.cpp Button.cpp Catan.cpp Edge.cpp Hexagon.cpp Player.cpp Square.cpp Demo.cpp
SOURCESCounterTests = Board.cpp Button.cpp Catan.cpp Edge.cpp Hexagon.cpp Player.cpp Square.cpp testCounter.cpp tests.cpp

# Object files for different targets
OBJECTSDemo = $(SOURCESDemo:.cpp=.o) 
OBJECTSCounterTests = $(SOURCESCounterTests:.cpp=.o) 

# Main targets
fullGame: demo
	./demo

tests: testCounter
	./testCounter

# Build rules for executable targets
demo: $(OBJECTSDemo)
	$(CXX) $(CXXFLAGS) $^ -o $@

testCounter: $(OBJECTSCounterTests)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Tidy target for code quality checks
tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

# Valgrind targets for memory checking
testvalgrind: testCounter
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./testCounter 2>&1 | { egrep "lost| at " || true; }

demovalgrind: demo
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1

# Pattern rule for building object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -f *.o demo testCounter

