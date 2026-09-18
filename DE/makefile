CXX ?= c++
CXXFLAGS ?= -O2 -std=c++11 -Wall -Wextra -Wpedantic

.PHONY: all clean
all: de

de: main.cpp Alg.cpp Alg.h ../tool.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) main.cpp Alg.cpp $(LDFLAGS) $(LDLIBS) -o de

clean:
	$(RM) de
