
RM 			= rm -rf
NAME		=	 philo
CC			=	 cc
CFLAGS		=	 -Wall -Wextra -Werror
OBJ_DIR		=	 obj
SOURCE		=	src/philosopher.c \
				src/monitoring.c \
				src/utils.c \
				src/getters.c \
				src/time_philo.c \
				src/validate_arg.c\
				src/routine.c \
				src/setters.c
				
OBJS		=	$(SOURCE:src/%.c=$(OBJ_DIR)/%.o)
src/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				@echo "Compiling of $(NAME) ..."
				@$(CC) -o $(NAME) $(OBJS)  -lpthread -g
				@echo "$(NAME) Compiled successfully. ✔️"


$(OBJ_DIR)/%.o:	src/%.c
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

clean:
				@$(RM) $(OBJ_DIR)
				@echo "Deleting objs ✔️"
fclean:			clean
				@$(RM) $(NAME)	
				@echo "Deleting $(NAME) binary ✔️"

re:				fclean all

.PHONY:			all clean fclean re
