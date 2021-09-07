NAME = philo
CC = @gcc
INC = -I ./
SRCS = 	./main.c \
		./philo_utils.c
FLAGS = -Wall -Wextra -Werror -pthread -fsanitize=address
OBJS = $(SRCS:.c=.o)
all: $(NAME)
	
$(NAME): $(OBJS) 
	$(CC) $(FLAGS) $(INC) $(SRCS) -o $(NAME)
clean:
	@rm -rf $(OBJS) *.dSYM
fclean: clean
	@rm -f $(NAME) 

re : fclean $(NAME)