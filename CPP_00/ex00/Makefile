GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
RED 	= \033[1;31m
RESET 	= \033[0m

CXX 		= c++

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

NAME 		= megaphone

SRCS 		= megaphone.cpp

OBJS 		= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "$(YELLOW)Object files cleaned$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) cleaned successfully!$(RESET)"

re: fclean all