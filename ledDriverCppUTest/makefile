CXX := g++
CPPFLAGS := -Iinclude -Imocks
#CPPFLAGS := -I../cpputest/include -Iinclude -Imocks
CXXFLAGS := -Wall -Werror -g

SRC:= src/LedDriver.c

TEST_SRC := \
	test/LedDriverTest.cpp\
	mocks/RuntimeErrorStub.c\
	test/AllTests.cpp

TARGET := runTests
LIBS := /usr/local/lib/libCppUTest.a

all: $(TARGET)

$(TARGET): 
	$(CXX) $(TEST_SRC) $(SRC) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
	./$(TARGET)

clean:
	rm -f $(TARGET)

