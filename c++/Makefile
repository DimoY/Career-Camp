IDIR = include
CC=g++
CFLAGS=-I $(IDIR) -g --std=c++2a
ODIR=obj

_DEPS = dict.hh
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Cache.o Atbash.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

encoder: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
