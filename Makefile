NAME = cub3D

SRC = cube.c matrix.c check_map.c movement.c utils.c raycasting.c raycasting2.c texture.c fence.c

SRC_DIR = ./Src/

OBJ_DIR = ./Src/.obj/

LINK = ./minilibx-linux/libmlx_Linux.a -lX11 -lXext -lm

SRCP = $(addprefix $(SRC_DIR),$(SRC))

OBJP = $(addprefix $(OBJ_DIR),$(notdir $(SRCP:.c=.o)))

CFLAGS = -Wall -Wextra -Werror -fPIE -g 

LIB = ./Src/MyLib/mylib.a

all: lib $(NAME)

lib:
	@echo "\033[32mCompiling $(NAME) 🚀"
	make -s -C Src/MyLib

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJP)
	@make -sC minilibx-linux
	@gcc $(CFLAGS) $(OBJP) $(LIB) $(LINK) -o $(NAME)
	@echo "\033[32mCompiled ✅\033[0;37m"

clean:
	@echo "\033[0;31mCleaning objects 🧹"
	@rm -rf $(OBJ_DIR)
	@rm -rf minilibx-linux/*.o
	@make clean -s -C Src/MyLib

fclean: clean
	@echo "\033[0;31mRemoving $(NAME) 🗑\033[0;37m"
	@rm -rf $(NAME)
	@rm -rf minilibx-linux/*.a
	@make fclean -s -C Src/MyLib

re: fclean all

.SILENT: $(OBJ) lib

.PHONY: all lib clean fclean re
