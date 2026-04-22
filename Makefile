NAME = gnl.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = get_next_line.c get_next_line_utils.c
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs $@ $^

%.o: %.c get_next_line.h
	${CC} ${CFLAGS} -c $< -o $@
clean: ${OBJS}
	rm -rf ${OBJS}
fclean: clean
	rm -rf ${NAME}
re: all

.PHONY: all clean fclean re
