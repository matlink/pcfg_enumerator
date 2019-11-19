INC=include
SRC=src
CFLAGS := -Wall -Wextra -pedantic -I$(INC) -O3
LDFLAGS :=
SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(subst $(SRC)/,, $(subst .cpp,.o, $(SRCS)))
BIN = pcfg

all: $(BIN)

-include $(OBJS:.o=.d)

%.o: $(SRC)/%.cpp
	$(CXX) -c $(CFLAGS) $< -o $@
	$(CXX) -MM $(CFLAGS) $< -o $(@:.o=.d)

$(BIN): $(OBJS)
	$(CXX) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(BIN) *.o *.d
