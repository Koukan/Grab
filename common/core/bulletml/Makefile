RANLIB=ranlib
INCLUDES += -I../std -I..
LIBS += ../tinyxml/tinyxml.o ../tinyxml/tinyxmlparser.o ../tinyxml/tinyxmlerror.o
CXX = g++ 
CXXFLAGS += -g3 -std=c++0x -W -fpermissive -Wall -ansi -pedantic
OBJS = bulletmlparser-tinyxml.o bulletmlparser.o bulletmltree.o calc.o formula-variables.o bulletmlrunner.o bulletmlrunnerimpl.o

all: libbulletml.a

libbulletml.a: $(OBJS)
	$(AR) -r ../../libbulletml.a $(OBJS) $(LIBS)
	$(RANLIB) ../../libbulletml.a

clean:
	rm -f *.o

fclean: clean
	rm -f *.a

re: fclean all

calc.cc: calc.yy
	bison -y   calc.yy && mv y.tab.c calc.cc

$(OBJS): %.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<
