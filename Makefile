INCLDIR	:= include
SRCDIR	:= src
CC      := g++
CFLAGS  := -Wall -I$(INCLDIR) -O3

#Source and object files (automatic)
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(subst $(SRCDIR)/,, $(subst .cpp,.o, $(SRCS)))

# Define here your main source files separated by spaces (without suffix!)
EXEC = pcfg

# For multiple binaries
$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: $(SRCDIR)/%.cpp $(INCLDIR)/%.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *.o $(EXEC)