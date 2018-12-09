# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/07 18:45:57 by rnaumenk          #+#    #+#              #
#    Updated: 2018/05/07 18:46:00 by rnaumenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lem-in
LIBFT_DIR	=	./libft/
LIBFT		=	libft.a
LIB			=	libftlemin.a
INC_DIR		=	./include/
INC			=	lemin.h
SRC_DIR		=	./src/
SRC			= 	./calculate_the_best_output.c \
				./cpy_and_cmp_functs.c \
				./create_the_link.c \
				./create_the_room.c \
				./decision_finder.c \
				./errors.c \
				./free_and_color_stuff.c \
				./main.c \
				./movement.c \
				./path_finder.c \
				./show_the_result.c \
				./solution.c \
				./sort_stuff.c \
				./unsortable.c \
				./validation.c 
OBJ_DIR		=	./obj/
OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT_DIR)$(LIBFT) $(LIB)
	@gcc -Wall -Wextra -Werror -o $@ $^
	@echo "\033[4;32mlem-in is ready\033[0m"

$(LIB): $(OBJ)
	@ar rc $@ $^
	@ranlib $@
	@echo "\033[3;36mlibftlemin.a has been made\033[0m"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(INC_DIR)$(INC)
	@mkdir -p $(OBJ_DIR)
	@gcc -Wall -Wextra -Werror -o $@ -c $<

$(LIBFT_DIR)$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "\033[3;36mlibft.a has been made\033[0m"

clean:
	@rm -rf $(LIB) $(OBJ_DIR)
	@cd $(LIBFT_DIR) && make fclean
	@echo "\033[3;33mlibft.a and libftlemin.a have been deleted\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[3;31mlem-in has been deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re
