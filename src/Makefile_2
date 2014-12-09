#
# $Id: src/Makefile,v 0.2 2005-05-08 21:10:00 sigterm Exp $
#
#	all:		compile sources
#	clean:		remove .o files
#	dclean:		debug clean

PROGRAM = herbivore
OBJS = 	$(PROGRAM).o help.o std_encode.o string.o key.o user.o hcore.o std_decode.o math.o io.o 
LIBS = -lgd -lm
CC = gcc

all: $(PROGRAM)
$(PROGRAM): $(OBJS) $(LIBS)

clean:
	@rm *.o
	@rm $(PROGRAM)

dclean:
	@rm *.o
	@rm $(PROGRAM)