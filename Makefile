EXECUTABLE=zork-project
SRC_C=tinyxml/*.cpp source/*.cpp source/map/*.cpp
TEST_C=source/main.cpp
SRC_H=tinyxml/*.h header/*.h header/map/*.h
TARGET=source/main.cpp
CC=g++
CFLAGS=-g -std=c++11 -Wall -Wvla -pedantic -DTIXML_USE_STL #-Wshadow
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
COVERAGE_FLAGS=-std=c++11 -lm -fprofile-arcs -ftest-coverage -DNDEBUG
CLEAN_FILES=*.gcno *.c.gcov *.gcda *.gcda $(EXECUTABLE) zork-project.zip
ARGS=samples/triggersample.xml

$(EXECUTABLE): $(SRC_C) $(SRC_H)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(CFLAGS)

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
	zip $(EXECUTABLE).zip header/* header/map/* source/* source/map/* tinyxml/* samples/* Makefile sample.xml

demo: $(EXECUTABLE)
	printf "\n\n\x1b[32mOutput from samples/containersample.xml\x1b[0m\n" ;\
	./$(EXECUTABLE) samples/containersample.xml ;\
	printf "\n\n\x1b[32mOutput from samples/creaturesample.xml\x1b[0m\n" ;\
	./$(EXECUTABLE) samples/creaturesample.xml ;\
	printf "\n\n\x1b[32mOutput from samples/itemsample.xml\x1b[0m\n" ;\
	./$(EXECUTABLE) samples/itemsample.xml ;\
	printf "\n\n\x1b[32mOutput from samples/roomsample.xml\x1b[0m\n" ;\
	./$(EXECUTABLE) samples/roomsample.xml ;\
	printf "\n\n\x1b[32mOutput from samples/triggersample.xml\x1b[0m\n" ;\
	./$(EXECUTABLE) samples/triggersample.xml ;\
	printf "\n\n\x1b[32mOutput from samples/sample.xml\x1b[0m\n" ;\
	./$(EXECUTABLE) sample.xml

.PHONY: submit test pretest coverage debug clean run tester code make zip demo

