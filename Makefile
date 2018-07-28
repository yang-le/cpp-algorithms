OBJS = $(patsubst %.cc, %.o,$(wildcard test/*.cc))

.cc.o:
	$(CXX) $(CXXFLAGS) -Iinc -I. -c $< -o $@

test.bin : $(OBJS) gtest-all.o gtest_main.o
	$(CXX) $^ -pthread -o $@

gtest-all.o : gtest/gtest-all.cpp
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

gtest_main.o : gtest/gtest_main.cc
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

clean :
	$(RM) $(OBJS) gtest-all.o gtest_main.o test.bin

test : test.bin
	./test.bin