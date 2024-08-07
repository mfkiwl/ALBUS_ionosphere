#
# JMA_code.rules
#
# Example Makefile for JMA coding
# 2004 Feb 13  James M Anderson  --NRAO  reorganize from various places
# 2008 Feb 15  JMA  --MPIfR updates for generalizing build





INCLUDES += -Ivex2005 -Ivexplus -I../mim/test/PIMrunner -I$(INSTALLDIR)/include
CFLAGS += -Ivex2005 -Ivexplus -I../mim/test/PIMrunner -I$(INSTALLDIR)/include

HEADERS = \
	ellipsoidal_coord.h \
	ut1_interp.h \
	vex_source.h \
	vex_time.h \
	vex_ut1_interp.h \

SRCS = \
	ellipsoidal_coord.cxx \
	ut1_interp.f \
	vex_iono_processor.cxx \
	vex_time.cxx \
	vex_ut1_interp.cxx

OBJS = \
	ellipsoidal_coord.o \
	ut1_interp.o \
	vex_iono_processor.o \
	vex_time.o \
	vex_ut1_interp.o


SUBDIRS = \
	vex2005 \
	vexplus






# As far as I can see we never make any use of ell_coord_converter. Coordinate conversions stuff
# is handled by python code these days
PROG = \
	ell_coord_converter


LIBS = \
	libjmavex.$(EXT)

#EXTERN_LIBS = -L$(INSTALLDIR)/lib -lvexplus -lvex -lfl -L../mim/test/PIMrunner -lmim -lsofa -l$(F77_COMPILER_LIB)
EXTERN_LIBS = -L$(INSTALLDIR)/lib -lvexplus -lvex -lfl -L../mim/test/PIMrunner  -lsofa -l$(F77_COMPILER_LIB)



all: subdirs $(LIBS) $(PROG) 
.PHONY : all subdirs $(SUBDIRS)









subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ install







libjmavex.so: $(SUBDIRS) $(OBJS)
	$(RM) $@.$(VER_MAJOR).$(VER_MINOR).$(VER_SUBSUB) $@.$(VER_MAJOR) $@ 
	gcc -shared -Wl,-soname,$@.$(VER_MAJOR) -o $@.$(VER_MAJOR).$(VER_MINOR).$(VER_SUBSUB) $(OBJS)
	ln -s $@.$(VER_MAJOR).$(VER_MINOR).$(VER_SUBSUB) $@.$(VER_MAJOR)
	ln -s $@.$(VER_MAJOR) $@ 


libjmavex.a: $(SUBDIRS) $(OBJS)
	$(RM) $@
	ar rcs $@ $(OBJS)

install: subdirs libjmavex.so $(PROG)
	$(CP) libjmavex.* $(INSTALLDIR)/lib
	$(CP) $(HEADERS) $(INSTALLDIR)/include
	$(MKDIR) $(INSTALLDIR)/bin
#       $(CP) $(PROG) $(INSTALLDIR)/bin
# we no longer install the compiled program


test: $(OBJS) test.o
	$(C++) $(CFLAGS) -o $@ test.o $(OBJS) $(EXTERN_LIBS) -lm

ell_coord_converter: ellipsoidal_coord.o ell_coord_converter.o
	$(C++) $(CFLAGS) -o $@ ell_coord_converter.o ellipsoidal_coord.o -lm
#$(INCLUDES) $(EXTERN_LIBS) -lm





# This will probably work best with C and C++ code.  Modify
# If you want to do this for FORTRAN too.
.PHONY : depend clean distclean install
depend:
	$(RM) $(MAKEDEPENDREAL)
	$(foreach i,$(SRCS), $(MAKEDEPEND) $(CFLAGS) $i;cat $(MAKEDEPENDTEMP) >> $(MAKEDEPENDREAL);)
	$(RM) $(MAKEDEPENDTEMP)
	$(foreach i,$(SUBDIRS), $(MAKE) -C $i $@;)


clean:
	$(RM) $(OBJS) $(PROG)
	$(foreach i,$(SUBDIRS), $(MAKE) -C $i $@;)
	$(RM) *.o libjmavex.*

distclean: clean
	$(RM) *~
	$(foreach i,$(SUBDIRS), $(MAKE) -C $i $@;)




# make sure we can compile C++ stuff
.SUFFIXES:
.SUFFIXES: .cxx $(SUFFIXES)









# declare our own default compilation rules
.cxx.o:
	$(CC) $(CFLAGS) -c $<

.cc.o:
	$(CC) $(CFLAGS) -c $<

.F.o:
	$(F77) $(FFLAGS) -c $<

.f.o:
	$(F77) $(FFLAGS) -c $<












# If you are going to use MAKEDEPEND with GCC, uncomment the following
#include .dependencies.mk



# The following stuff is for automatic generation of dependencies
# Some MAKEDEPEND programs need it.  I tend to use gcc to make
# it's own dependencies file.
# DO NOT DELETE THIS LINE -- make depend depends on it.
