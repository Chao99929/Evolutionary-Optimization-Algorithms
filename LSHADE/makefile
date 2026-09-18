CXX ?= c++
CXXFLAGS ?= -O2 -std=c++11 -Wall -Wextra -Wpedantic

.PHONY: all clean
all: lshade

lshade: main.cpp test2lshade.h ../Problem.h ../tool.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) main.cpp $(LDFLAGS) $(LDLIBS) -o lshade

clean:
	$(RM) lshade
