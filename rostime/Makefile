test: bin main

bin:
	mkdir -p bin

main: bin/test_main.o bin/time.o bin/duration.o bin/autotest.o bin/rostime_test.o
	g++ bin/test_main.o bin/time.o bin/duration.o bin/autotest.o bin/rostime_test.o -o test_main -lrt -lboost_system

bin/test_main.o: test_exceptions/test_main.cpp
	g++ -c -Iinclude test_exceptions/test_main.cpp -o bin/test_main.o

bin/time.o: src/time.cpp include/ros/time.h include/ros/impl/time.h
	g++ -c -Iinclude src/time.cpp -o bin/time.o

bin/autotest.o: test_exceptions/autotest.cpp test_exceptions/autotest.h
	g++ -c -Iinclude test_exceptions/autotest.cpp -o bin/autotest.o 

bin/rostime_test.o: test_exceptions/rostime_test.cpp test_exceptions/rostime_test.h
	g++ -c -Iinclude test_exceptions/rostime_test.cpp -o bin/rostime_test.o

bin/duration.o: src/duration.cpp include/ros/duration.h include/ros/impl/duration.h
	g++ -c -Iinclude src/duration.cpp -o bin/duration.o

clean:
	rm -rf bin test_main
