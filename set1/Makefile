
CXXFLAGS += -I../


targets := 	sol11 \
			sol12 \
			sol13 \
			sol14
			
all: $(targets)

%.o: %.cpp
	$(COMPILE.cc) $< -o $@

../lib.o: ../lib.cpp
	$(COMPILE.cc) ../lib.cpp -o $@

sol11: ../lib.o c1.o
	$(LINK.cc) -o $@ $^ $(LDLIBS)

sol12: ../lib.o c2.o
	$(LINK.cc) -o $@ $^ $(LDLIBS)

sol13: ../lib.o c3.o
	$(LINK.cc) -o $@ $^ $(LDLIBS)

sol14: ../lib.o c4.o
	$(LINK.cc) -o $@ $^ $(LDLIBS)


.PHONY: all, clean


clean:
	-rm $(targets) ../lib.o
