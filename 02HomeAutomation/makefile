C_COMPILER = gcc
CPP_COMPILER = g++

INCLUDES = -Iinclude -Imocks -I/usr/local/include
CFLAGS += -std=c99 -Wall -Werror -g3
LDFLAGS += -L/usr/local/lib -lCppUTest -lCppUTestExt

SRC_DIR = src
MOCK_DIR = mocks
TEST_DIR = test

# Explicitly include only the needed .c files (excluding real_hardware.c)
C_SOURCES = $(SRC_DIR)/LightScheduler.c\
	    $(SRC_DIR)/RandomMinute.c\
	    $(MOCK_DIR)/LightControllerSpy.c \
	    $(MOCK_DIR)/FakeTimeService.c\
	    $(MOCK_DIR)/FakeRandomMinute.c
CPP_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)

OBJECTS = $(C_SOURCES:.c=.o) $(CPP_SOURCES:.cpp=.o)
TARGET = runTests

.PHONY: all clean test

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CPP_COMPILER) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(C_COMPILER) -c $< -o $@ $(INCLUDES) $(CFLAGS)

%.o: %.cpp
	$(CPP_COMPILER) -c $< -o $@ $(INCLUDES)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(SRC_DIR)/*.o $(MOCK_DIR)/*.o $(TEST_DIR)/*.o $(TARGET)
