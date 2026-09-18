CXX ?= c++
CXXFLAGS ?= -O2 -std=c++11 -Wall -Wextra -Wpedantic

.PHONY: all clean
all: jade

jade: main.cpp Alg.cpp Alg.h ../Problem.h ../tool.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) main.cpp Alg.cpp $(LDFLAGS) $(LDLIBS) -o jade

clean:
	$(RM) jade
