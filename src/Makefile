
CXX = g++
CXXFLAGS = -g -Wall -Werror -Wextra -std=c++17 #-fsanitize=address
TEST_FLAGS = -lgtest
MODEL = $(wildcard model/*.cc)
TESTS = $(wildcard tests/*.cc)
MODEL_OBJS = $(MODEL:.cc=.o)
TESTS_OBJS = $(TESTS:.cc=.o)

all: install tests

install: uninstall clean
	mkdir SmartCalc
	cd ./view/ && cmake .
	cmake --build ./view/
	mv view/SmartCalc.app SmartCalc/SmartCalc.app
	chmod -R 755 ./SmartCalc/SmartCalc.app
	open SmartCalc/SmartCalc.app  

open_app:
	open SmartCalc/SmartCalc.app  

uninstall: 
	@-rm -rf SmartCalc


tests: clean test

test:  $(MODEL_OBJS) $(TESTS_OBJS)
	@echo "================================================================================"
	@echo "Starting testing program.."
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -o $@ $^
	./test
	@echo "================================================================================"


dvi: clean
	doxygen dvi/Doxyfile 
	-texmaker latex/index.tex &
	open html/index.html

dist: clean_all
	mkdir CPP_SmartCalc
	mkdir CPP_SmartCalc/view CPP_SmartCalc/model CPP_SmartCalc/controller
	mkdir CPP_SmartCalc/tests CPP_SmartCalc/lib
	cp model/*  CPP_SmartCalc/model
	cp tests/* CPP_SmartCalc/tests
	cp controller/* CPP_SmartCalc/controller
	cp lib/* CPP_SmartCalc/lib
	-cp view/*  CPP_SmartCalc/view
	cp Makefile CPP_SmartCalc
	tar czf CPP_SmartCalc.tar.gz CPP_SmartCalc/
	rm -rf CPP_SmartCalc


gcov_report: clean add_coverage test
	mkdir report
	lcov --no-external -t "test" -o test.info -c -d . 
	genhtml -o report test.info
	open report/index.html
	rm -rf *.gcda *.gcno 

add_coverage:
	$(eval CXXFLAGS += --coverage)

leak: tests
	leaks -atExit -- ./test

clean:
	@-rm simple_test
	@-rm test test.info
	@-rm -rf report latex
	@-rm  $(MODEL_OBJS) $(TESTS_OBJS)
	@-rm -rf  build*
	@-rm -rf model/*.gcda model/*.gcno tests/*.gcda tests/*.gcno 
	@-rm -rf ./html
	@-rm -rf view/CMakeFiles view/CMakeCache.txt view/cmake_install.cmake view/SmartCalc_autogen
	

clean_all: clean
	@-rm CPP_SmartCalc.tar.gz 
	
