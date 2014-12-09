PROGRAM = herbivore
USRLIB = /usr/lib
INCLUDES = include
COMMAND = make
SRCDIR = src
CP = cp

all:
	@cd $(SRCDIR); $(COMMAND)
	@cd $(SRCDIR); $(CP) $(PROGRAM) ../herbivore

clean:
	@rm -f $(PROGRAM) *.log config.status config.h
	@cd $(SRCDIR); make clean
	
