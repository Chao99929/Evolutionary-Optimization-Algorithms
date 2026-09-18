CXX ?= c++
CXXFLAGS ?= -O2 -std=c++11 -Wall -Wextra -Wpedantic

.PHONY: all clean
all: shade

shade: main.cpp shade.h ../Problem.h ../tool.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) main.cpp $(LDFLAGS) $(LDLIBS) -o shade

clean:
	$(RM) shade
