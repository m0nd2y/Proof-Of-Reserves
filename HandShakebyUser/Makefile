CC = gcc
CFLAGS = -Wall -pthread
MAIN_SRC = MAIN.c
MAIN_EXE = main

.PHONY: all clean fclean re

all: $(MAIN_EXE) $(CLIENT_EXE)

$(MAIN_EXE): $(MAIN_SRC)
	$(CC) $(CFLAGS) -o $(MAIN_EXE) $(MAIN_SRC)
clean:
	rm -f $(MAIN_EXE)

fclean: clean

re: fclean all