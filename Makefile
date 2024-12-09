SRC = mandatory/pipex.c mandatory/utils.c

SRC_BONUS = bonus/pipex_bonus.c bonus/utils_bonus.c bonus/get_next_line/get_next_line.c bonus/get_next_line/get_next_line_utils.c

OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

CC = clang
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
NAME = pipex

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME} :${OBJ}
	make -C libft
	${CC} ${CFLAGS} ${OBJ} -o pipex -L libft -lft

clean:
	make clean -C libft
	${RM} mandatory/*.o libft/*.o bonus/*.o bonus/get_next_line/*.o

fclean: clean
	make fclean -C libft
	${RM} ${NAME}

bonus: ${OBJ_BONUS}
	make -C libft
	${CC} ${CFLAGS} ${OBJ_BONUS} -g -o pipex -L libft -lft

re : fclean all clean

.PHONY: all clean fclean re