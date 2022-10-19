GCC ?=g++

OBJ_DIR =../../obj

OBJS =${OBJ_DIR}/add_file_command.o \
	  ${OBJ_DIR}/change_password_command.o \
	  ${OBJ_DIR}/change_username_command.o \
	  ${OBJ_DIR}/command_composite.o \
	  ${OBJ_DIR}/create_backup_command.o \
	  ${OBJ_DIR}/list_files_command.o \
	  ${OBJ_DIR}/format_command.o \
	  ${OBJ_DIR}/print_usage_command.o \
	  ${OBJ_DIR}/read_file_command.o \
	  ${OBJ_DIR}/remove_file_command.o \
	  ${OBJ_DIR}/rename_file_command.o \
	  ${OBJ_DIR}/restore_backup_command.o \
	  ${OBJ_DIR}/verify_backup_command.o \
	  ${OBJ_DIR}/commands_module.o

CXX_FLAGS +=--std=c++17 -Wall -Wextra -pedantic -Werror -I../../../ -I../../../cdif -O3

all: ${OBJ_DIR} ${OBJS}

clean:
	rm -f ${OBJS}

${OBJ_DIR}/%.o: %.cpp %.h
	$(GCC) -o $@ ${CXX_FLAGS} -c $<

.PRECIOUS: ${OBJS}
