GCC ?=g++
AR ?=ar

OBJ_DIR =./obj
LIB_DIR =./lib

LIBS =${LIB_DIR}/libserial.a \
	  ${LIB_DIR}/libui.a \
	  ${LIB_DIR}/libcommands.a \
	  ${LIB_DIR}/libcommandscommon.a \
	  ${LIB_DIR}/libsupport.a \
	  ${LIB_DIR}/libapi.a \
	  ${LIB_DIR}/libencryption.a
EXE =bluefish

CXX_FLAGS +=--std=c++17 -Wall -Wextra -pedantic -Werror -I./cdif -I./ -O3
LD_FLAGS +=-L${LIB_DIR} -lpthread -lcryptopp
AR_FLAGS +=rcs

all: ${EXE}

clean:
	rm -Rf ${EXE} ${OBJ_DIR} ${LIB_DIR}
	$(MAKE) -C serial clean
	$(MAKE) -C encryption clean
	$(MAKE) -C api clean
	$(MAKE) -C support clean
	$(MAKE) -C commands clean
	$(MAKE) -C ui clean

install: ${EXE}
	cp ${EXE} /usr/bin/${EXE}

${EXE}: ${EXE}.cc ${LIB_DIR} libs
	$(GCC) ${CXX_FLAGS} ${LD_FLAGS} -o $@ $< ${LIBS}

${LIB_DIR}:
	mkdir ${LIB_DIR}

${LIB_DIR}/lib%.a: %
	$(MAKE) -C $<

libs:
	$(MAKE) -C serial
	$(MAKE) -C ui
	$(MAKE) -C commands
	$(MAKE) -C support
	$(MAKE) -C api
	$(MAKE) -C encryption

.PRECIOUS: ${LIBS}
.PHONY: libs
