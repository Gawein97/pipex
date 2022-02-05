#SETUP
NAME		=	pipex
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

#FILES AND PATH
HEADER_SRCS	=	pipex.h pipex_bonus.h
HEADER_DIR	=	includes/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))


MPATH_SRCS	=	pipex.c ft_strjoin.c ft_strstr.c ft_strlen.c ft_split.c \
				ft_paths.c ft_utils.c
OBJ_M		=	$(MPATH_SRCS:.c=.o)

BPATH_SRCS	=	pipex_bonus.c ft_strjoin_bonus.c ft_strstr_bonus.c ft_strlen_bonus.c ft_split_bonus.c \
				ft_paths_bonus.c ft_utils_bonus.c ft_errors.c

B_PATH_DIR	=	bonus/
B_PATH		=	$(addprefix $(B_PATH_DIR), $(BPATH_SRCS))
OBJ_B		=	$(B_PATH:.c=.o)

.PHONY:		all clean fclean bonus re
#COMMANDS
%.o: %.c $(HEADER) Makefile
				${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJ_M)
				$(CC) $(OBJ_M) -o $(NAME)
				@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

all:			$(NAME)

bonus:			$(OBJ_B)
				$(CC) $(OBJ_B) -o $(NAME)
				@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
				$(RM) $(OBJ_M)
				$(RM) $(OBJ_B)
				@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:			clean
				$(RM) $(NAME)
				@echo -e "$(RED)all deleted!$(DEFAULT)"

re:				fclean all

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m