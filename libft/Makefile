# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apavlyuc <apavlyuc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/09 13:25:28 by apavlyuc          #+#    #+#              #
#    Updated: 2018/09/09 14:30:13 by apavlyuc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libft.a

SRC_DIR 	:= src
INC_DIR 	:= inc 
OBJ_DIR 	:= build

CC			:= gcc
FLAGS		:= -c -Wall -Wextra -Werror -I./$(INC_DIR)

NORM_CHECK	:= $(shell command -v norminette)

DIRS		:= $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(shell find $(SRC_DIR) -type d))
SRCS		:= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS		:= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

#		Block			#
#	creating $(NAME)	#
all:		$(NAME)

$(NAME):	$(OBJS)
	@ar rc $@ $^
	@ranlib $@

$(OBJ_DIR):
	@mkdir -p $(DIRS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(FLAGS) $< -o $@

#		Block			#
#	describing commands	#
clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

norm:
ifeq (,$(NORM_CHECK))
	@echo "DEUS VULT!!1"
else
	@find . -type f -name "*.[ch]" -exec norminette {} \+
endif
#		end block		#

n: norm
c: clean
f: fclean

.PHONY: all clean fclean re
