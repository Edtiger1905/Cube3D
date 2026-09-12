NAME		=	cub3d

SRCDIR		=	srcs
OBJDIR		=	obj
SRCS		=	check_map.c \
				free_memory.c \
				init_cube3d.c \
				init_map.c \
				init_render.c \
				init_textures.c \
				main.c \
				movement.c \
				open_file.c \
				parser_rgb.c \
				parser_texture.c \
				raycasting.c \
				raycasting_draw.c \
				raycasting_utils.c \
				hooks.c \
				utils.c

OBJS		=	${SRCS:%.c=$(OBJDIR)/%.o}

TOTAL_FILES	:=	$(words $(SRCS))

LIBFT_DIR	=	$(SRCDIR)/libft
LIBFT		=	$(LIBFT_DIR)/libft.a

GNL_DIR		=	$(SRCDIR)/GNL
GNL			=	$(GNL_DIR)/gnl.a

MLX_DIR		=	$(SRCDIR)/mlx
MLX			=	$(MLX_DIR)/libmlx.a
MLX_FLAGS	=	-L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

CC			=	cc
RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-Iincludes -I$(LIBFT_DIR)/includes -I$(GNL_DIR) -I$(MLX_DIR)

# --- PALETTE RETRO ARCADE (ANSI) ---
GREEN		=	\033[0;32m
BRIGHT_GRN	=	\033[1;32m
YELLOW		=	\033[1;33m
RED			=	\033[0;31m
BRIGHT_RED	=	\033[1;31m
CYAN		=	\033[0;36m
MAGENTA		=	\033[1;35m
BOLD		=	\033[1m
RESET		=	\033[0m

# Suono "Beep" da PC Speaker vintage
BEEP		=	\a

all: intro libft gnl mlx $(NAME) victory

intro:
	@printf "\033[2J\033[H"
	@printf "$(MAGENTA)$(BOLD)"
	@printf "=================================================================\n"
	@printf "  ______  _    _  _____  ____   ____  _____  \n"
	@printf " / ____/ | |  | ||  _  ||___ \ |  _ \|  __ \ \n"
	@printf "| |      | |  | || |_| |  __) || | | | |  | |\n"
	@printf "| |____  | |__| ||  _  | / __/ | |_| | |__| |\n"
	@printf " \_____|  \____/ |_| |_||_____||____/|_____/  [ENGINE 1993]\n"
	@printf "=================================================================$(RESET)\n"
	@printf "$(YELLOW) [INSERT FLOPPY DISK A:\...]  -  3.5\" HD 1.44MB $(RESET)\n\n"

libft:
	@printf "$(CYAN)$(BOLD)[STAGE 1] LOADING LIBFT MODULE...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@printf "$(BRIGHT_GRN)[✔] LIBFT ENGINE READY (+500 XP)$(RESET)\n\n"

gnl:
	@printf "$(CYAN)$(BOLD)[STAGE 2] INITIALIZING GNL PROTOCOL...$(RESET)\n"
	@$(MAKE) -C $(GNL_DIR) --no-print-directory
	@printf "$(BRIGHT_GRN)[✔] GNL PARSER LOADED (+500 XP)$(RESET)\n\n"

mlx:
	@printf "$(CYAN)$(BOLD)[STAGE 3] BOOTING GRAPHICS DRIVER (MLX)...$(RESET)\n"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1
	@printf "$(BRIGHT_GRN)[✔] MLX DISPLAY RENDERING READY (+1000 XP)$(RESET)\n\n"
	@printf "$(CYAN)$(BOLD)[STAGE 4] READING SECTORS FROM FLOPPY...$(RESET)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@
	@$(eval COMPILED_FILES := $(shell find $(OBJDIR) -name "*.o" | wc -l))
	@$(eval PERCENT := $(shell expr $(COMPILED_FILES) \* 100 / $(TOTAL_FILES)))
	@$(eval FILLED := $(shell expr $(PERCENT) / 5))
	@$(eval UNFILLED := $(shell expr 20 - $(FILLED)))
	@printf "\r$(YELLOW)[FLOPPY A:\] Reading sector %2d/%2d [" $(COMPILED_FILES) $(TOTAL_FILES)
	@for i in $$(seq 1 $(FILLED)); do printf "$(BRIGHT_GRN)█$(YELLOW)"; done
	@for i in $$(seq 1 $(UNFILLED)); do printf "░"; done
	@printf "] %3d%%  =>  %-20s$(RESET)" $(PERCENT) "$<"

$(NAME): ${OBJS}
	@printf "\n\n$(MAGENTA)$(BOLD)[FINAL BOSS] LINKING ALL MODULES INTO $(NAME)...$(RESET)\n"
	@${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${GNL} ${MLX_FLAGS} -o ${NAME}

victory:
	@printf "\n$(BRIGHT_GRN)$(BOLD)=================================================================\n"
	@printf "   STAGE CLEAR! $(NAME) HAS BEEN SUCCESSFULLY LINKED!\n"
	@printf "   READY TO PLAY: ./$(NAME) maps/example.cub\n"
	@printf "=================================================================$(BEEP)$(RESET)\n"

clean:
	@printf "$(BRIGHT_RED)[CLEANUP] PURGING OBJECT FILES FROM MAZE...$(RESET)\n"
	@${RM} -r $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(GNL_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory > /dev/null 2>&1
	@printf "$(RED)[✔] ALL OBJECTS DEFEATED & REMOVED.$(RESET)\n"

fclean: clean
	@printf "$(BRIGHT_RED)[ANNIHILATION] DESTROYING EXE BINARY ($(NAME))...$(RESET)\n"
	@${RM} ${NAME}
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(GNL_DIR) fclean --no-print-directory
	@printf "$(RED)[✔] GAME OVER: ENTIRE BUILD WIPED OUT.$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re libft gnl mlx intro victory