OBJS = $(patsubst %.cc, %.o,$(wildcard test/*.cc))
DEPS = $(patsubst %.cc, %.d,$(wildcard test/*.cc))

CXXFLAGS = -Wall -Wno-sign-compare -g -O1 -std=c++11

ifeq ($(MAKECMDGOALS), coverage)
	CXX = clang++
	COVERAGE_FLAGS = -fprofile-instr-generate -fcoverage-mapping
endif

ifdef SANITIZER
	ifeq ($(SANITIZER), memory)
		CXX = clang++
	endif
	SANITIZER_FLAGS = -fsanitize=$(SANITIZER) -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

.cc.o:
	$(CXX) $(CXXFLAGS) -Iinc -I. -MM -MT"$*.d" -MT"$(<:.cc=.o)" $< > $*.d
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) $(SANITIZER_FLAGS) -Iinc -I. -c $< -o $@

test.bin : $(OBJS) gtest-all.o gtest_main.o
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) $(SANITIZER_FLAGS) $^ -pthread -o $@

gtest-all.o : gtest/gtest-all.cpp
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

gtest_main.o : gtest/gtest_main.cc
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

sinclude $(DEPS)

clean :
	@$(RM) $(OBJS) $(DEPS) gtest-all.o gtest_main.o test.bin *.prof*

test : test.bin
	@./$< --gtest_filter=\
	-BinarySearchTreeNodeTest.abandon_removed_node\
	:TrieNodeTest.add_child

coverage : test.bin
	@-./$<
	@llvm-profdata-3.9 merge -sparse default.profraw -o default.profdata
	@llvm-cov-3.9 show $< -instr-profile=default.profdata
	@llvm-cov-3.9 report $< -instr-profile=default.profdata
	@$(RM) *.prof*

lint:
	@./cpplint.py --filter=-build/header_guard --headers=hpp inc/** test/**

help:
	@echo "command:"
	@echo "	test		run all tests"
	@echo "	lint		run cpplint"
	@echo "	coverage	report code coverage"
	@echo "	clean		clean workspace"
	@echo "	SANITIZER=	build with google sanitizers"
	@echo "		address		fast memory error detector"
	@echo "		thread		detects data races"
	@echo "		memory		detector of uninitialized reads"
	@echo "		undefined	fast undefined behavior detector"
	@echo "		leak		run-time memory leak detector"
