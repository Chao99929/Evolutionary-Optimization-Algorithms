CXX ?= c++
CXXFLAGS ?= -O2 -std=c++11 -Wall -Wextra -Wpedantic

.PHONY: all clean
all: pso

pso: main.cpp PSO.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) main.cpp $(LDFLAGS) $(LDLIBS) -o pso

clean:
	$(RM) pso
