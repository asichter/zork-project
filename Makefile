EXECUTABLE=zork-project
SRC_C=main.cpp tinyxml/tinystr.cpp tinyxml/tinyxml.cpp tinyxml/tinyxmlerror.cpp tinyxml/tinyxmlparser.cpp XMLParser.cpp
TEST_C=main.cpp
SRC_H=tinyxml/tinyxml.h XMLParser.h
TARGET=main.cpp
CC=g++
CFLAGS=-std=c++11 -Wall -Wvla -pedantic #-Wshadow
SHELL=/bin/bash
RUN=run
TESTER=tester
CODE=code
GDB=gdb
VALGRIND=valgrind
ASG_TEST=test
ASG_DEBUG=debug
TEST_EXPECTED=expected.txt
ASG_TEST_COVERAGE=coverage
COVERAGE_FLAGS=-std=c++17 -lm -fprofile-arcs -ftest-coverage -DNDEBUG
CLEAN_FILES=*.gcno *.c.gcov *.gcda *.gcda $(EXECUTABLE)

$(EXECUTABLE): $(SRC_C) $(SRC_H)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(CFLAGS) ; ./$(EXECUTABLE)

$(RUN): $(EXECUTABLE)
	./$(EXECUTABLE)

$(TESTER):
	vim $(TEST_C)

$(CODE):
	vim $(TARGET)

$(GDB): $(EXECUTABLE)
	gdb $(EXECUTABLE)

$(VALGRIND): $(EXECUTABLE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose $(EXECUTABLE)

expected: $(EXECUTABLE)
	./$(EXECUTABLE) > $(TEST_EXPECTED)

$(ASG_DEBUG): $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS) -DDEBUG

$(ASG_TEST): $(ASG_DEBUG) $(TEST_EXPECTED)
	@if diff -a -B <("./$(EXECUTABLE)") $(TEST_EXPECTED) &> /dev/null ; then \
		echo -e '\x1b[32mTest passed: output of $(EXECUTABLE) matches $(TEST_EXPECTED)\x1b[0m' ; \
	else \
		echo -e '\x1b[31mTest failed: output of $(EXECUTABLE) does NOT match $(TEST_EXPECTED)\x1b[0m' ; \
	fi

$(ASG_TEST_COVERAGE):
	@$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(COVERAGE_FLAGS) -DDEBUG
	@./$(EXECUTABLE)
	@gcov -f $(SRC_C)

clean: 
	rm -f  $(CLEAN_FILES)

make:
	vim Makefile

zip:
	zip $(EXECUTABLE).zip $(SRC_C) $(SRC_H) $(TEST_C) Makefile

.PHONY: submit test pretest coverage debug clean run tester code make zip

