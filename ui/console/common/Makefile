GCC ?=g++

OBJ_DIR =../../obj

OBJS =${OBJ_DIR}/input.o \
	  ${OBJ_DIR}/output.o

CXX_FLAGS +=--std=c++17 -Wall -Wextra -pedantic -Werror -I../../../ -I../../../cdif -O3

all: ${OBJS}

clean:
	rm -Rf ${OBJ_DIR} ${LIB}

${OBJ_DIR}/%.o: %.cpp %.h
	$(GCC) -o $@ ${CXX_FLAGS} -c $<

.PRECIOUS: ${OBJS}
