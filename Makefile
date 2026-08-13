NAME        = cub3d

SRCDIR      = srcs
OBJDIR      = obj
SRCS        = main.c utils.c validator.c init_cube3d.c free_memory.c
                
OBJS        = ${SRCS:%.c=$(OBJDIR)/%.o}

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

GNL_DIR     = GNL
GNL         = $(GNL_DIR)/gnl.a

MLX_DIR     = mlx
MLX         = $(MLX_DIR)/libmlx.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

CC          = cc
RM          = rm -f

CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -Iincludes -I$(LIBFT_DIR)/includes -I$(GNL_DIR) -I$(MLX_DIR)

# Colori
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
RED     = \033[0;31m
CYAN    = \033[0;36m
BOLD    = \033[1m
RESET   = \033[0m

all: libft gnl mlx $(NAME)

libft:
	@printf "$(CYAN)$(BOLD)Compilando libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@printf "$(GREEN)✔ libft pronta!$(RESET)\n"

gnl:
	@printf "$(CYAN)$(BOLD)Compilando gnl...$(RESET)\n"
	@$(MAKE) -C $(GNL_DIR) --no-print-directory
	@printf "$(GREEN)✔ gnl pronto!$(RESET)\n"

mlx:
	@printf "$(CYAN)$(BOLD)Compilando mlx...$(RESET)\n"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory
	@printf "$(GREEN)✔ mlx pronta!$(RESET)\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@printf "$(YELLOW)Compilando: $<$(RESET)\n"
	@${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

$(NAME): ${OBJS}
	@printf "$(CYAN)$(BOLD)Creazione dell'eseguibile $(NAME)...$(RESET)\n"
	@${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${GNL} ${MLX_FLAGS} -o ${NAME}
	@printf "$(GREEN)$(BOLD)✔ $(NAME) compilato con successo!$(RESET)\n"

clean:
	@printf "$(RED)Cancellando i file oggetto...$(RESET)\n"
	@${RM} -r $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(GNL_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory # NUOVO
	@printf "$(GREEN)✔ Oggetti cancellati!$(RESET)\n"

fclean: clean
	@printf "$(RED)Cancellando $(NAME)...$(RESET)\n"
	@${RM} ${NAME}
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(GNL_DIR) fclean --no-print-directory	
	@printf "$(GREEN)✔ Tutto pulito!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re libft gnl mlx