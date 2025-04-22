C_COMPILER :=gcc
UNITY_ROOT=../../Unity
INC_DIRS=-Iinclude -Isrc -I$(UNITY_ROOT)/src -I$(UNITY_ROOT)/extras/fixture/src
SYMBOLS=-DUNITY_FIXTURE_NO_EXTRAS
TARGET=run_tests

SRC_FILES=\
	  $(UNITY_ROOT)/src/unity.c\
	  $(UNITY_ROOT)/extras/fixture/src/unity_fixture.c\
	  src/LedDriver.c\
	  test/LedDriverTest.c\
	  test/all_tests.c\
	  test/LedDriverTestRunner.c
default:
	$(C_COMPILER) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES) -o $(TARGET)
	./$(TARGET)
clean:
	rm -f $(TARGET)
show: 
	@echo "Current compiler is $(C_COMPILER)"
	@echo "Include diriectories are $(INC_DIRS)"
