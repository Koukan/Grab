RANLIB=ranlib
INCLUDES += -I../std -I..
LIBS += tinyxml/tinyxml.o tinyxml/tinyxmlparser.o tinyxml/tinyxmlerror.o
CXXFLAGS += -O2 -W -fpermissive -Wall -ansi -pedantic
OBJS = bulletmlparser-tinyxml.o bulletmlparser.o bulletmltree.o calc.o formula-variables.o bulletmlrunner.o bulletmlrunnerimpl.o

USE_YGG = 0
ifeq ($(USE_YGG),1)
OBJS += bulletmlparser-ygg.o
endif

all: libbulletml.a

libbulletml.a: $(OBJS)
	$(MAKE) -C tinyxml
	$(AR) -r libbulletml.a $(OBJS) $(LIBS)
	$(RANLIB) libbulletml.a

clean:
	rm -f *.o
	rm -f ygg/ygg.o
	$(MAKE) -C tinyxml clean

fclean: clean
	rm -f *.a

re: fclean all

calc.cc: calc.yy
	bison -y   calc.yy && mv y.tab.c calc.cc

$(OBJS): %.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $<

doxy:
	doxygen

distdir:

