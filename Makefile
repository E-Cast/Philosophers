SRC				=	main.c \
					params.c \
					table.c \

SRC_DIR			:=	sources/
OBJ_DIR			:=	objects/
SRC				:=	$(addprefix $(SRC_DIR), $(SRC))
OBJ				:=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))
NAME			:=	philo

# DEBUG			:=	-g 
CC				:=	gcc -Wall -Werror -Wextra -pthread $(DEBUG)
INC_DIR			:= 	includes
INCLUDES		:=	-I $(INC_DIR)

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
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: clean all

fclean: clean
	@rm -rf $(OBJ_DIR)

norm:
	@norminette $(SRC) $(INC_DIR) || true

.PHONY: all clean re bonus fclean norm