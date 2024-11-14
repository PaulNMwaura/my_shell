TARGET = my_shell.exe
SRCS = src/main.c src/read_input.c src/parse_input.c src/handle_args.c src/builtin.c src/binary_exe.c
OBJS = $(SRCS:.c=.o)
CC = gcc
#CFLAGS = -g3 -fsanitize=address --pedantic-errors 
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address --pedantic-errors

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(TARGET)

re: fclean all