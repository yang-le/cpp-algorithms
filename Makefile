OBJS = $(patsubst %.cc, %.o,$(wildcard test/*.cc))
DEPS = $(patsubst %.cc, %.d,$(wildcard test/*.cc))

CXXFLAGS = -Wall -Wno-sign-compare -Os -std=c++11

.cc.o:
	$(CXX) $(CXXFLAGS) -Iinc -I. -MM -MT"$*.d" -MT"$(<:.cc=.o)" $< > $*.d
	$(CXX) $(CXXFLAGS) -Iinc -I. -c $< -o $@

test.bin : $(OBJS) gtest-all.o gtest_main.o
	$(CXX) $^ -pthread -o $@

gtest-all.o : gtest/gtest-all.cpp
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

gtest_main.o : gtest/gtest_main.cc
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

sinclude $(DEPS)

clean :
	$(RM) $(OBJS) $(DEPS) gtest-all.o gtest_main.o test.bin

test : test.bin
	./test.bin

lint:
	./cpplint.py --filter=-build/header_guard --headers=hpp inc/** test/**
