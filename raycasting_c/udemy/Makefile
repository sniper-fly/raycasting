
SRCS = ${shell find ./srcs/ -type f -name "*.c"}
OBJS = ${SRCS:%.c=%.o}
LIBMLX = ./minilibx-linux/libmlx.a
CC = gcc
CFLAGS = -g -fsanitize=address,undefined -lm -lXext -lX11
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJS) $(LIBMLX)
	${CC} -o ${NAME} ${OBJS} ${LIBMLX} ${CFLAGS}

run:
	./${NAME}

clean:
	rm -f ${OBJS}

.PHONY: all clean run