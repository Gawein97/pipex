#SETUP
NAME		=	pipex
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

#FILES AND PATH
HEADER_SRCS	=	pipex.h pipex_bonus.h
HEADER_DIR	=	includes/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

FUNC_SCRS	=	ft_strjoin.c ft_strstr.c ft_strlen.c ft_split.c ft_paths.c
OBJ_F		=	$(FUNC_SCRS:.c=.o)

MPATH_SRCS	=	pipex.c ft_utils.c
OBJ_M		=	$(MPATH_SRCS:.c=.o)

BPATH_SRCS	=	pipex_bonus.c ft_utils_bonus.c ft_errors.c here_doc.c get_next_line.c \
				get_next_line_utils.c ft_strncmp.c

B_PATH_DIR	=	bonus/
B_PATH		=	$(addprefix $(B_PATH_DIR), $(BPATH_SRCS))
OBJ_B		=	$(B_PATH:.c=.o)

.PHONY:		all clean fclean bonus re
#COMMANDS
%.o: %.c $(HEADER) Makefile
				${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJ_F) $(OBJ_M)
				$(CC) $(OBJ_F) $(OBJ_M) -o $(NAME)
				@echo -e "--- bonus $(NAME) created ---"

all:			$(NAME)

bonus:			$(OBJ_F) $(OBJ_B)
				$(CC) $(OBJ_F) $(OBJ_B) -o $(NAME)
				@echo -e "--- $(NAME) created ---"

clean:
				$(RM) $(OBJ_M)
				$(RM) $(OBJ_B)
				$(RM) $(OBJ_F)
				@echo -e "--- object files deleted ---"

fclean:			clean
				$(RM) $(NAME)
				@echo -e "--- all files deleted ---"

re:				fclean all
