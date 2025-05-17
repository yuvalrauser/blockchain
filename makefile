CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -fPIC
INCLUDES = -I.

LIBNAME = blockchain

# הספרייה (קובץ utils)
LIB_SRC := blockchain_utils.cpp
LIB_OBJ := $(LIB_SRC:.cpp=.o)
LIB_SO := lib$(LIBNAME).so

# כל שאר קבצי ה־.cpp חוץ מהספרייה
SRCS := $(filter-out $(LIB_SRC), $(wildcard *.cpp))
BINARIES := $(SRCS:.cpp=.out)

LDFLAGS = -L. -l$(LIBNAME) -Wl,-rpath='$$ORIGIN'

all: $(LIB_SO) $(BINARIES)

$(LIB_SO): $(LIB_OBJ)
	$(CXX) -shared -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.out: %.cpp $(LIB_SO)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $< $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o *.out *.so blockchain_data.txt blocks.csv
