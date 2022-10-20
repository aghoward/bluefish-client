AR ?=ar
OUTPUT_LIB_DIR =../lib
LIB_DIR =./lib
OBJ_DIR =./obj

AR_FLAGS +=rcs

LIB =${OUTPUT_LIB_DIR}/libui.a

all: ${OBJ_DIR} ${LIB_DIR} ${LIB}

clean:
	$(MAKE) -C console clean
	rm -Rf ${LIB_DIR} ${OBJ_DIR}

${LIB}:
	$(MAKE) -C console
	$(AR) ${AR_FLAGS} $@ ${OBJ_DIR}/*.o

${LIB_DIR}:
	mkdir ${LIB_DIR}

${OBJ_DIR}:
	mkdir ${OBJ_DIR}

.PRECIOUS: ${LIB} ${OBJ_DIR}/*.o
