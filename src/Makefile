CC = g++
CFLAGS = -Wall -Werror -Wextra
TFLAGS = -lgtest --coverage

#ifeq ($(shell uname), Linux)
#	TFLAGS += -lm -lsubunit
#endif

ifeq ($(shell uname), Darwin)
	TFLAGS += -fprofile-arcs -ftest-coverage
endif

all: clean s21_matrix_oop.a test gcov_report

s21_matrix_oop.a:
	$(CC) $(CFLAGS) -c s21_matrix_oop.cc
	ar -rcs $@ s21_*.o

s21_matrix_oop_test.a:
	$(CC) $(CFLAGS) -c s21_matrix_oop.cc $(TFLAGS)
	ar -rcs $@ s21_*.o

test: s21_matrix_oop_test.a
	$(CC) unit_tests/s21_matrix_oop_test.cc s21_matrix_oop_test.a -o test.a $(TFLAGS)
	./test.a

gcov_report: test
	gcov -b s21_matrix_oop.cc
	lcov -d . -c -o coverage.info
	lcov --remove coverage.info '/usr/include/*' '/usr/lib/*' -o coverage.info
	genhtml coverage.info -o html_report
	open html_report/index.html

format:
	clang-format --style=Google -i s21_*.cc s21_*.h

format-check:
	clang-format --style=Google  -n s21_*.cc s21_*.h

clean:
	rm -rf *.o *.a *.gch *.gcno *.gcov *.gcda *.info html_report
