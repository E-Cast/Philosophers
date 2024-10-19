# files
SRC		=	main.c \
			get_params.c \
			utils.c \
			data.c \
			threads.c \
			routine.c \
			time.c \
			monitor.c

SRC_DIR		:= sources/
OBJ_DIR		:= objects/
SRC			:=	$(addprefix $(SRC_DIR), $(SRC))
OBJ			:=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))

# compilation
NAME		:=	philo
# DEBUG 		:=	-g
SANITIZE	:=	-fsanitize=threads
CC			:=	gcc -Wall -Werror -Wextra -pthread $(SANITIZE) $(DEBUG) 
INC_DIR		:= 	includes
INCLUDES	:=	-I $(INC_DIR)

all: $(NAME)
$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC)$(INCLUDES) $(OBJ) -o $@
	@echo "$(CC)$(INCLUDES) -o $(NAME)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC)$(INCLUDES) -c $< -o $@
	@echo "$(CC)$< $@"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

re: clean all

fclean: clean
	@rm -f $(NAME)

norm:
	@norminette $(SRC) $(INC_DIR) || true

.PHONY: all clean re bonus fclean norm