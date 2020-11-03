
SRCS = ${shell find ./srcs/ -type f -name "*.c"}
LIBMLX = ./minilibx-linux/libmlx.a
CC = gcc
CFLAG = -lXext -lX11 -lm

all:
	$(CC) $(SRCS) $(LIBMLX) $(CFLAG)

run:
	./a.out