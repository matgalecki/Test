NAME = fdf
LIBFT = libs/Libft/libft.a
MLX42 = libs/MLX42/build/libmlx42.a
MLX42_FLAGS = -ldl -lglfw -pthread -lm
CFLAGS = -Wall -Werror -Wextra -g3 -O0 -ffast-math -fno-stack-protector
LIBS_HEADERS = -I libs/Libft/ -I libs/MLX42/include/

OBJECTS_FOLDER = ./obj/

MANDATORY_FOLDER = ./mandatory/
MANDATORY_SOURCES = $(addprefix $(MANDATORY_FOLDER), main.c parse_map.c \
	parse_map_utils.c draw_line.c draw_line_utils.c render.c render_utils.c \
	error_handler.c others_utils.c news.c)
MANDATORY_OBJECTS = $(subst $(MANDATORY_FOLDER),$(OBJECTS_FOLDER),$(MANDATORY_SOURCES:.c=.o))

all: $(OBJECTS_FOLDER) $(NAME)

$(OBJECTS_FOLDER):
	mkdir $(OBJECTS_FOLDER)

$(NAME): libs $(MANDATORY_OBJECTS)
	cc $(CFLAGS) $(MANDATORY_OBJECTS) $(LIBFT) $(MLX42) $(MLX42_FLAGS) $(LIBS_HEADERS) -o $(NAME)

libs: $(LIBFT) $(MLX42)

$(LIBFT):
	make -C libs/Libft/

$(MLX42):
	cd libs/MLX42/ && cmake -B build -DDEBUG=1
	cd libs/MLX42/ && cmake --build build -j4

$(OBJECTS_FOLDER)%.o: $(MANDATORY_FOLDER)%.c $(MANDATORY_FOLDER)fdf.h
	cc $(CFLAGS) $(LIBS_HEADERS) -c $< -o $@

$(OBJECTS_FOLDER)%.o: $(BONUS_FOLDER)%.c $(BONUS_FOLDER)fdf_bonus.h
	cc $(CFLAGS) $(LIBS_HEADERS) -c $< -o $@

val:
	valgrind --leak-check=full --suppressions=./sup.sup ./fdf_bonus ./maps/others/MGDS_WHOLE_WORLD_OCEAN0_L.fdf

clean:
	rm -rf $(OBJECTS_FOLDER)*

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

clean_libs:
	make -C libs/Libft/ fclean
	rm -rf libs/MLX42/build

re: fclean all

.PHONY: bonus clean fclean clean_libs