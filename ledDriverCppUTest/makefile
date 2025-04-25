CXX := g++
CPPFLAGS := -I../cpputest/include
CXXFLAGS := -Wall -Werror -g

TEST_SRC := test/SprintfTest.cpp test/AllTests.cpp
TARGET := runTests
LIBS := /usr/local/lib/libCppUTest.a

all: $(TARGET)

$(TARGET): $(TEST_SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./$(TARGET)

clean:
	rm -f $(TARGET)

