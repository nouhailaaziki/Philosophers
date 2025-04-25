# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 17:05:42 by noaziki           #+#    #+#              #
#    Updated: 2025/04/25 17:05:45 by noaziki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPILER = cc

CFLAGS = -Wall -Wextra -Werror

YELLOW = \033[0;33m
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

MANDATORY =	philosophers.c input_guard.c

OBJM = $(MANDATORY:.c=.o)

NAME = philo

all: $(NAME)

$(NAME) : $(OBJM)
	@echo "${YELLOW}🚀 Launching compilation...${RESET}"
	$(COMPILER) $(CFLAGS) $(OBJM) -o $(NAME)
	@echo "${GREEN}✅ ${NAME} successfully compiled!${RESET}"


%.o: %.c philosophers.h
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJM)
	@echo "${RED}🗑 Object files removed!${RESET}"

fclean: clean
	$(RM) $(NAME)
	@echo "${RED}🔥 Executable removed!${RESET}"

re: fclean all

.PHONY: clean