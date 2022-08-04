CXX = clang++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -pedantic
LD = clang++
LDLIBS = -L/usr/lib/cs70lib -listring -ltestinglogger -lstringhashtest
TARGETS = stringhash-test hashset-cow-test hashset-test

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
	rm -rf *.o

stringhash-test: stringhash.o
	$(LD) $(LDFLAGS) $^ -o $@ $(LDLIBS)

hashset-cow-test: hashset-cow-test.o 
	$(LD) $(LDFLAGS) $^ -o $@ -L/usr/lib/cs70lib -ltestinglogger

hashset-test: hashset-test.o
	$(LD) $(LDFLAGS) $^ -o $@ -L/usr/lib/cs70lib -ltestinglogger

hashset-cow-test.o: hashset-cow-test.cpp hashset.hpp hashset-private.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

hashset-test.o: hashset-test.cpp hashset.hpp hashset-private.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

stringhash.o: stringhash.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
