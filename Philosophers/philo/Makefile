NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread 

SCR = main.c check.c display.c end_simulation.c error.c free.c init.c protect.c simulation.c timing.c check_parsing.c

OBJ = $(SCR:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "--------------------------------------------------"
	@echo "Project compiled successfully!!!"
	@echo "--------------------------------------------------"

all: $(NAME)

clean:
	@echo "Cleaning up object files..."
	rm -rf $(OBJ)
	@echo "finished cleaning"
	@echo "--------------------------------------------------"

fclean: clean
	@echo "Cleaning up all..."
	rm -rf $(NAME)
	@echo "finished cleaning"
	@echo "--------------------------------------------------"

re: fclean all

.PHONY: all clean fclean re
