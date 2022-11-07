CC=gcc
SRCDIR=./src/
LIBDIR=./lib/
BINDIR=./bin/


DLLC=conv.c features.c standardwave.c tensor.c tool.c
DLLFILES=$(addprefix $(SRCDIR), $(DLLC))
DLLNAME=$(LIBDIR)libnilmue.so

all:dynamic
	$(CC) -o $(BINDIR)nilmue.out main.c $(DLLNAME) -lm
	LD_LIBRARY_PATH=. $(BINDIR)nilmue.out

dynamic:
	$(CC) -shared -fPIC -o $(DLLNAME) $(DLLFILES)


clean:
	$(RM) $(LIBDIR)*.so $(BINDIR)*

