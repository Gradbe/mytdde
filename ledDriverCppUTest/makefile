C_COMPILER = gcc
CPP_COMPILER = g++

CPPFLAGS += -Iinclude -Imocks -I/usr/local/include
CFLAGS += -std=c99 -Wall -Werror
LDFLAGS += -L/usr/local/lib -lCppUTest -lCppUTestExt

SRC_DIR = src
INC_DIR = include
MOCK_DIR = mocks
TEST_DIR = test

C_SOURCES = $(SRC_DIR)/LedDriver.c $(MOCK_DIR)/RuntimeErrorStub.c
CPP_SOURCES = $(TEST_DIR)/LedDriverTest.cpp $(TEST_DIR)/AllTests.cpp

OBJECTS = $(C_SOURCES:.c=.o) $(CPP_SOURCES:.cpp=.o)
TARGET = runTests

.PHONY: all clean test

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CPP_COMPILER) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(C_COMPILER) -c $< -o $@ $(CPPFLAGS) $(CFLAGS)

%.o: %.cpp
	$(CPP_COMPILER) -c $< -o $@ $(CPPFLAGS)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(SRC_DIR)/*.o $(MOCK_DIR)/*.o $(TEST_DIR)/*.o $(TARGET)
