CC=gcc
FLAGS= -Wall -Werror -Wextra -std=c++17
LIBS= -lgtest -lstdc++ -pthread
OPEN=xdg-open

OS:=$(shell uname -s)
ifeq ($(OS), Darwin)
	OPEN=open
else
	LIBS+=-lm
	OPEN=xdg-open
endif

all: clean test

s21_matrix_oop.a: s21_matrix_oop.cpp
	$(CC) $(FLAGS) -c s21_matrix_oop.cpp -o s21_matrix_oop.o
	ar rc s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a

test: tests.cpp s21_matrix_oop.a
	$(CC) $(FLAGS) -c tests.cpp -o tests.o
	$(CC) $(FLAGS) tests.o s21_matrix_oop.a $(LIBS) -o test
	./test

gcov_report: $(REPORT_DIR)
	$(CC) $(FLAGS) -c s21_matrix_oop.cpp --coverage -o s21_matrix_oop.o
	$(CC) $(FLAGS) -c tests.cpp -o tests.o
	$(CC) $(FLAGS) tests.o s21_matrix_oop.o --coverage $(LIBS) -o test
	./test
	gcovr --exclude-unreachable-branches --exclude-throw-branches -r . --html --html-details -o report.html
	$(OPEN) report.html

linter:
	clang-format -i --style=Google *.cpp *.h
	clang-format -n --style=Google *.cpp *.h

clean:
	rm -rf *.o *.a *.gcda *.gcno test *.html