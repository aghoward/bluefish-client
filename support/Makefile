GCC ?=g++
AR ?=ar

OBJ_DIR =./obj
LIB_DIR =../lib

OBJS =${OBJ_DIR}/argument_parsing.o ${OBJ_DIR}/failure_reason_translator.o ${OBJ_DIR}/support_module.o ${OBJ_DIR}/askpass.o
LIB =${LIB_DIR}/libsupport.a

CXX_FLAGS +=--std=c++17 -Wall -Wextra -pedantic -Werror -I../ -I../cdif -O3
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

.PRECIOUS: ${OBJS} ${LIB}
