CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
INCLUDES = -I. -Inucleo

CORE = nucleo/User.cpp nucleo/MessageStatus.cpp nucleo/TextMessage.cpp nucleo/Chat.cpp
SOURCES = ColaEnvios.cpp ChatCola.cpp
HEADERS = ColaEnvios.hpp ChatCola.hpp nucleo/User.hpp nucleo/MessageStatus.hpp nucleo/TextMessage.hpp nucleo/Chat.hpp nucleo/CSV.hpp
TEST = tests/test_modelo.cpp

all: main

main: $(SOURCES) $(CORE) main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) $(CORE) main.cpp -o main
	./main

test: $(SOURCES) $(CORE) $(TEST) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) $(CORE) $(TEST) -o test_modelo
	./test_modelo

clean:
	rm -f main test_modelo test_cola.csv demo_cola.csv *.o

.PHONY: all main test clean
