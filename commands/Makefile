GCC ?=g++
AR ?=ar

OBJ_DIR =./obj
LIB_DIR =../lib

OBJS =${OBJ_DIR}/add_file_command.o ${OBJ_DIR}/format_command.o \
	  ${OBJ_DIR}/list_files_command.o ${OBJ_DIR}/read_file_command.o \
	  ${OBJ_DIR}/remove_file_command.o ${OBJ_DIR}/command_composite.o \
	  ${OBJ_DIR}/rename_file_command.o ${OBJ_DIR}/challenge_verifier.o \
	  ${OBJ_DIR}/create_backup_command.o ${OBJ_DIR}/restore_backup_command.o \
	  ${OBJ_DIR}/print_usage_command.o ${OBJ_DIR}/verify_backup_command.o \
	  ${OBJ_DIR}/commands_module.o

LIB =${LIB_DIR}/libcommands.a

CXX_FLAGS +=--std=c++17 -Wall -Wextra -pedantic -Werror -I../ -I../cdif -O3
AR_FLAGS +=rcs

all: ${LIB}
	make -C common

clean:
	make -C common clean
	rm -Rf ${OBJ_DIR} ${LIB}

${OBJ_DIR}:
	[ -f ${OBJ_DIR} ] || mkdir ${OBJ_DIR}

${OBJ_DIR}/%.o: %.cpp %.h ${OBJ_DIR}
	$(GCC) -o $@ ${CXX_FLAGS} -c $<

${LIB_DIR}/lib%.a: ${OBJS}
	$(AR) ${AR_FLAGS} $@ ${OBJS}

.PRECIOUS: ${OBJS} ${LIB}
