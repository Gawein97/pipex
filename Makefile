#SETUP
NAME		=	pipex
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

#FILES AND PATH
HEADER_SRCS		=	pipex.h
HEADER_DIR	=	includes/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

FUNC_SCRS	=	ft_strjoin.c ft_strstr.c ft_strlen.c ft_split.c ft_paths.c
OBJ_F		=	$(FUNC_SCRS:.c=.o)

MPATH_SRCS	=	pipex.c ft_utils.c
OBJ_M		=	$(MPATH_SRCS:.c=.o)

.PHONY:		all clean fclean bonus re
#COMMANDS
%.o: %.c $(HEADER) Makefile
				${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJ_F) $(OBJ_M)
				$(CC) $(OBJ_F) $(OBJ_M) -o $(NAME)
				@echo -e "--- $(NAME) created ---"

all:			$(NAME)

bonus:			
				@make -f MakefileBonus

clean:
				$(RM) $(OBJ_M)
				$(RM) $(OBJ_F)
				@make -f MakefileBonus clean
				@echo -e "--- object files deleted ---"

fclean:			clean
				$(RM) $(NAME)
				@echo -e "--- all files deleted ---"

re:				fclean all
