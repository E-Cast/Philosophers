SRC				=	main.c #sources here

SRC_DIR			:=	sources/
OBJ_DIR			:=	objects/
SRC				:=	$(addprefix $(SRC_DIR), $(SRC))
OBJ				:=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))
NAME			:=	#output name here

# DEBUG			:=	-g 
CC				:=	gcc -Wall -Werror -Wextra $(DEBUG)
INC_DIR			:= 	includes
INCLUDES		:=	-I $(INC_DIR)
## INCLUDES		:=	-I $(INC_DIR) -I libft/includes
## LIBFT_DIR		:=	libft/
## LIBFT			:=	$(LIBFT_DIR)libft.a
## LIBFT_FLAGS		:=	-L $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC)$(INCLUDES) $(OBJ) -o $@
	@echo "$(CC)$(INCLUDES) -o $(NAME)"
## $(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
## 	@$(CC)$(INCLUDES) $(LIBFT_FLAGS) $(OBJ) -lft -o $@
## 	@echo "$(CC)$(INCLUDES) -lft -o $(NAME)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC)$(INCLUDES) -c $< -o $@
	@echo "$(CC)$< $@"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: clean all

## libft/Makefile:
## 	git submodule init
## 	git submodule update --remote

## libft:
## 	git submodule init
## 	git submodule update --remote
## 	@make --no-print-directory -C $(LIBFT_DIR) re

## $(LIBFT): libft/Makefile
## 	@make --no-print-directory -C $(LIBFT_DIR)

## clean_libft:
## 	@make --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(OBJ_DIR)
## fclean: clean
## 	@rm -rf $(OBJ_DIR) $(B_OBJ_DIR)
## 	@make --no-print-directory -C $(LIBFT_DIR) fclean

norm:
	@norminette $(SRC) $(INC_DIR) || true
## norm:
## 	@norminette $(SRC) $(INC_DIR) $(LIBFT_DIR) || true

.PHONY: all clean re bonus fclean norm
## .PHONY: all clean re bonus fclean norm libft