# ══════════════════════════════════════════════════════════════════════════ #
#                                                                              #
#   ░█▀▀░█░█░█▀▄░█▀▀░█▀▄     Wolfenstein-style RayCaster                     #
#   ░█░░░█░█░█▀▄░▀▀█░█░█     42 School Project                               #
#   ░▀▀▀░▀▀▀░▀▀░░▀▀▀░▀▀      Press START to compile...                      #
#                                                                              #
# ══════════════════════════════════════════════════════════════════════════ #

NAME		= cub3D
BONUS_NAME	= cub3D_bonus

# ── Colors ─────────────────────────────────────────────────────────────── #
RESET		= \033[0m
BOLD		= \033[1m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
MAGENTA		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m

# ── Compiler ───────────────────────────────────────────────────────────── #
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -O2
DEPFLAGS	= -MMD -MP

# ── Directories ────────────────────────────────────────────────────────── #
SRCS_DIR	= srcs
OBJS_DIR	= objs
INC_DIR		= includes

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= minilibx
MLX_LIB		= $(MLX_DIR)/libmlx.a

# ── Includes / Libs ────────────────────────────────────────────────────── #
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

# ── Source files (mandatory) ───────────────────────────────────────────── #
SRC_FILES	= main.c \
			  parsing/parse_file.c \
			  parsing/parse_textures.c \
			  parsing/parse_colors.c \
			  parsing/parse_map.c \
			  validation/validate_map.c \
			  validation/validate_scene.c \
			  graphics/mlx_init.c \
			  graphics/render.c \
			  graphics/textures.c \
			  raycasting/dda.c \
			  raycasting/raycast.c \
			  raycasting/wall_calc.c \
			  player/movement.c \
			  player/rotation.c \
			  events/hooks.c \
			  utils/errors.c \
			  utils/free_utils.c

# ── Source files (bonus, only compiled with `make bonus`) ─────────────── #
BONUS_FILES	= bonus/minimap_bonus.c \
			  bonus/doors_bonus.c \
			  bonus/sprites_bonus.c \
			  bonus/mouse_bonus.c

SRCS		= $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))
DEPS		= $(OBJS:.o=.d)

BONUS_SRCS	= $(addprefix $(SRCS_DIR)/, $(BONUS_FILES))
BONUS_OBJS	= $(addprefix $(OBJS_DIR)/, $(BONUS_FILES:.c=.o))
DEPS		+= $(BONUS_OBJS:.o=.d)

# ── Retro loading bar helper ───────────────────────────────────────────── #
define LOADING_BAR
	@echo "$(CYAN)$(BOLD)[■■■■■■■■■■■■■■■■■■■■] LOADING $(1)... DONE$(RESET)"
endef

# ══════════════════════════════════════════════════════════════════════════ #
#  MAIN RULES                                                                 #
# ══════════════════════════════════════════════════════════════════════════ #

all: banner $(LIBFT) $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	$(call LOADING_BAR,ENGINE)
	@echo ""
	@echo "$(GREEN)$(BOLD)  ██████╗ ██████╗ ██████╗ ██████╗ ██████╗ "
	@echo "  ██╔══██╗██╔════╝██╔══██╗██╔══██╗╚════██╗"
	@echo "  ██████╔╝█████╗  ███████║██║  ██║ █████╔╝"
	@echo "  ██╔══██╗██╔══╝  ██╔══██║██║  ██║ ╚═══██╗"
	@echo "  ██║  ██║███████╗██║  ██║██████╔╝██████╔╝"
	@echo "  ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚═════╝ $(RESET)"
	@echo "$(YELLOW)$(BOLD)        >> PRESS ANY KEY TO ./$(NAME) <<$(RESET)"
	@echo ""

# ── Object compilation ─────────────────────────────────────────────────── #
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(BLUE)  [BUILD]$(RESET) $<"

-include $(DEPS)

# ── Libft ───────────────────────────────────────────────────────────────── #
$(LIBFT):
	@echo "$(MAGENTA)$(BOLD)[LEVEL 1]$(RESET) Building libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)
	$(call LOADING_BAR,LIBFT)

# ── MinilibX ────────────────────────────────────────────────────────────── #
$(MLX_LIB):
	@echo "$(MAGENTA)$(BOLD)[LEVEL 2]$(RESET) Building minilibx..."
	@$(MAKE) -s -C $(MLX_DIR)
	$(call LOADING_BAR,MINILIBX)

# ══════════════════════════════════════════════════════════════════════════ #
#  BONUS                                                                      #
# ══════════════════════════════════════════════════════════════════════════ #

bonus: CFLAGS += -DBONUS=1
bonus: banner $(LIBFT) $(MLX_LIB) $(BONUS_NAME)

$(BONUS_NAME): $(OBJS) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(BONUS_OBJS) $(LIBS) -o $(BONUS_NAME)
	$(call LOADING_BAR,BONUS CONTENT)
	@echo "$(RED)$(BOLD)  >> SECRET LEVEL UNLOCKED: ./$(BONUS_NAME) <<$(RESET)"
	@echo ""

# ══════════════════════════════════════════════════════════════════════════ #
#  CLEAN                                                                      #
# ══════════════════════════════════════════════════════════════════════════ #

clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean 2>/dev/null || true
	@$(MAKE) -s -C $(MLX_DIR) clean 2>/dev/null || true
	@rm -rf $(OBJS_DIR)
	@echo "$(YELLOW)$(BOLD)[RESPAWN]$(RESET) Object files wiped."

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean 2>/dev/null || true
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "$(RED)$(BOLD)[GAME OVER]$(RESET) $(NAME) and $(BONUS_NAME) removed."

re: fclean all

# ══════════════════════════════════════════════════════════════════════════ #
#  BANNER                                                                     #
# ══════════════════════════════════════════════════════════════════════════ #

banner:
	@echo "$(CYAN)$(BOLD)"
	@echo "  ╔══════════════════════════════════════════════╗"
	@echo "  ║   c u b 3 D   —   R A Y C A S T   E N G I N E ║"
	@echo "  ║   id Software vibes // 42 School // v1.0      ║"
	@echo "  ╚══════════════════════════════════════════════╝$(RESET)"

.PHONY: all bonus clean fclean re banner