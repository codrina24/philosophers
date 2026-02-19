NAME        = philo
INC         = philosophers.h

OBJ_DIR     = obj/
SRC         = 	check_arg.c\
				code.c\
				ft_steps.c\
				ft_memory_alloc.c\
				init.c\
				start_simulate.c\
				threads_process.c\
				tprw_mutexes.c\
				utils_time.c\
				end_simulate.c\
                main.c\

OBJ         = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

CC          = cc
CFLAGS      = -Wall -Werror -Wextra -g3 -pthread
RM          = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) > /dev/null 
	@echo "\033[1;35m--------------------------\033[0m"
	@echo "\033[1;35m√ Compilation successful √\033[0m"
	@echo "\033[1;35m--------------------------\033[0m"

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)  
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null 

clean:
	@rm -rf $(OBJ_DIR) 
	@echo "\033[1;35m--------------------------\033[0m"
	@echo "\033[1;35m√ Clean done √\033[0m"
	@echo "\033[1;35m--------------------------\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;35m√ ${NAME} deleted √\033[0m"
	@echo "\033[1;35m--------------------------\033[0m"

re: fclean all

.PHONY: all clean fclean re
