
CXXFLAGS += -I../


targets := 	set11 \
			set12 \
			set13 \
			set14
			
all: $(targets)

%.o: %.cpp
	$(COMPILE.cc) $< -o $@

../lib.o:
	$(COMPILE.cc) ../lib.cpp -o $@

set11: ../lib.o c1.o
	$(LINK.cc) -o $@ $^ $(LDLIBS)

set12: ../lib.o c2.o
	$(LINK.cc) -o $@ $^ $(LDLIBS)

set13: ../lib.o c3.o
	$(LINK.cc) -o $@ $^ $(LDLIBS)

set14: ../lib.o c4.o
	$(LINK.cc) -o $@ $^ $(LDLIBS)


.PHONY: all, clean


clean:
	-rm $(targets) ../lib.o
