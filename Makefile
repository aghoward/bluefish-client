GCC ?=g++
AR ?=ar

OBJ_DIR =./obj
LIB_DIR =./lib

LIBS =${LIB_DIR}/libserial.a ${LIB_DIR}/libcommands.a ${LIB_DIR}/libsupport.a ${LIB_DIR}/libapi.a ${LIB_DIR}/libencryption.a
EXE =bluefish

CXX_FLAGS +=--std=c++17 -Wall -Wextra -pedantic -Werror -I./cdif -I./ -O0
LD_FLAGS +=-L${LIB_DIR} -lpthread -lcryptopp
AR_FLAGS +=rcs

all: ${EXE}

clean:
	rm -Rf ${EXE} ${OBJ_DIR} ${LIB_DIR}
	make -C serial clean
	make -C api clean
	make -C support clean
	make -C commands clean

${EXE}: ${EXE}.cc ${LIBS}
	$(GCC) ${CXX_FLAGS} ${LD_FLAGS} -o $@ $< ${LIBS}

${LIB_DIR}:
	mkdir ${LIB_DIR}

${LIB_DIR}/lib%.a: % ${LIB_DIR}
	make -C $<
