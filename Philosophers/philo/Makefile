COMPILER = cc

CFLAGS = -Wall -Wextra -Werror

YELLOW = \033[0;33m
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

MANDATORY =	main.c utils.c simulation.c events.c routine.c

OBJM = $(MANDATORY:.c=.o)

NAME = philo

all: $(NAME)

$(NAME) : $(OBJM)
	@echo "${YELLOW}🚀 Launching compilation...${RESET}"
	$(COMPILER) $(CFLAGS) $(OBJM) -o $(NAME)
	@echo "${GREEN}✅ ${NAME} successfully compiled!${RESET}"


%.o: %.c mindcore.h
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJM)
	@echo "${RED}🗑 Object files removed!${RESET}"

fclean: clean
	$(RM) $(NAME)
	@echo "${RED}🔥 Executable removed!${RESET}"

re: fclean all

.PHONY: clean