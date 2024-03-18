.PHONY: all clean fclean re log bonus libft builtin_test

CC = clang
NAME = cub3D
# NAME_BONUS = .minishell_bonus.txt
LIBFT = libft/libft.a
LIBFT_DIR = libft
MANDATORY_DIR := mandatory
# BONUS_DIR := bonus
OBJS_DIR := objects
BONUS_OBJS_DIR := bonus_objects
INC_DIR := include 
CFLAGS = -Wall -Wextra -Werror -g3
UNAME := $(shell uname)
LIBS := -lft -lmlx -lm -lX11 -lXext
LIB_DIRS := $(LIBFT_DIR)

# ifeq ($(UNAME), Darwin)
#  	# CFLAGS += -arch x86_64
# 	INC_DIR += -I /opt/homebrew/opt/readlinde/include
# 	LIB_DIRS += -L /opt/homebrew/opt/readline/lib
# endif

SRCS = $(addprefix $(MANDATORY_DIR)/, cub3d.c\
					mlx.c\
					render.c\
					movement.c\
					key_events.c\
					rotate_view.c\
					img_pixel_put.c\
					init_textures.c\
					dda_algorithm.c\
					init_player_data.c\
					calculate_strafe.c\
					vector_arithmetic.c\
					texture_calculations.c\
					move_forward_backward.c\
					utils.c\
					calculate_rays_position.c)

# BONUS = $(addprefix $(BONUS_DIR)/, minishell_bonus.c\
			
# 		)

OBJS = $(patsubst $(MANDATORY_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))
# BONUS_OBJS = $(patsubst $(BONUS_DIR)%.c, $(BONUS_OBJS_DIR)%.o, $(BONUS))
# All Src subdirectories
SRC_SUBDIR := $(dir $(OBJS))
# BONUS_SUBDIR := $(dir $(BONUS_OBJS))
# Objects Subdirectories
OBJS_SUBDIR := $(subst $(MANDATORY_DIR), $(OBJS_DIR), $(SRC_SUBDIR))
# BONUS_OBJS_SUBDIR := $(subst $(BONUS_DIR), $(BONUS_OBJS_DIR), $(BONUS_SUBDIR))

$(NAME): $(OBJS) | libft
	@if [ -d "$(BONUS_OBJS_DIR)" ]; then \
      		rm -rf $(BONUS_OBJS_DIR); \
      		rm -f $(NAME); \
    fi
	@$(CC) $(CFLAGS) $(OBJS) -o $@ -L$(LIB_DIRS) $(LIBS) 
	@echo ________________________
	@echo cub3d binary created
	@echo ________________________

# $(NAME_BONUS): $(BONUS_OBJS) | libft
# 	@if [ -d "$(OBJS_DIR)" ]; then \
#       		rm -rf $(OBJS_DIR); \
#       		rm -f $(NAME); \
#     fi
# 	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o minishell -L$(LIB_DIRS) $(LIBS)
# 	@touch $@
# 	@echo ______________________________
# 	@echo Minishell bonus binary created
# 	@echo ______________________________

$(OBJS_DIR)/%.o: $(MANDATORY_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR)/include -I$(INC_DIR) -c $< -o $@

# $(BONUS_OBJS_DIR)/%.o: $(BONUS_DIR)/%.c
# 	@mkdir -p $(@D)
# 	@$(CC) $(CFLAGS) -I$(LIBFT_DIR)/include -I$(INC_DIR) -c $< -o $@

all: $(NAME)

# bonus: $(NAME_BONUS)

libft:
	@make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS_DIR)
	rm -rf $(BONUS_OBJS_DIR)
	rm -f  $(BUILTIN_TEST_OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS) $(LIBFT)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

git_libft:
	git clone https://github.com/taandreo/42-libft.git libft
