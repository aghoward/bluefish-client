GCC ?=g++
AR ?=ar

OBJ_DIR =./obj
LIB_DIR =../lib

OBJS =${OBJ_DIR}/serial_device.o ${OBJ_DIR}/serial_module.o
LIB =${LIB_DIR}/libserial.a

CXX_FLAGS +=--std=c++17 -Wall -Wextra -pedantic -Werror -I../cdif -I../ -O0
AR_FLAGS +=rcs

all: ${LIB}

clean:
	rm -Rf ${OBJ_DIR} ${LIB}

${OBJ_DIR}:
	[ -f ${OBJ_DIR} ] || mkdir ${OBJ_DIR}

${OBJ_DIR}/%.o: %.cpp %.h ${OBJ_DIR}
	$(GCC) -o $@ ${CXX_FLAGS} -c $<

${LIB_DIR}/lib%.a: ${OBJS}
	$(AR) ${AR_FLAGS} $@ ${OBJS}
