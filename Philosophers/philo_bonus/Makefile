COMPILER = cc

CFLAGS = -Wall -Wextra -Werror

YELLOW = \033[0;33m
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

BONUS =	routine_bonus.c simulation_bonus.c main_bonus.c utils_bonus.c events_bonus.c

OBJB = $(BONUS:.c=.o)

NAME = philo_bonus

all: $(NAME)

$(NAME) : $(OBJB)
	@echo "${YELLOW}🚀 Launching compilation...${RESET}"
	$(COMPILER) $(CFLAGS) $(OBJB) -o $(NAME)
	@echo "${GREEN}✅ ${NAME} successfully compiled!${RESET}"


%.o: %.c mindcore_bonus.h
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJB)
	@echo "${RED}🗑 Object files removed!${RESET}"

fclean: clean
	$(RM) $(NAME)
	@echo "${RED}🔥 Executable removed!${RESET}"

re: fclean all

.PHONY: clean