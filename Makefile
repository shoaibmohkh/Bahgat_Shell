NAME = minishell

SRCS = src/main.c \
       src/main_utils/utils_one.c \
       src/main_utils/utils_two.c \
       src/main_utils/utils_three.c \
       src/main_utils/utils_four.c \
       src/main_utils/utils_five.c \
       src/main_utils/utils_six.c \
       src/main_utils/utils_seven.c \
       src/allocate/dir.c \
       src/allocate/operator.c \
       src/allocate/command.c \
       src/allocate/command_two.c \
       src/allocate/command_three.c \
       src/free/ft_free.c \
       src/free/error_exit.c \
       src/signals/handle_signals.c \
       src/split/check_operator.c \
       src/split/tokenizer/split_command_one.c \
       src/split/tokenizer/split_command_two.c \
       src/split/tokenizer/split_command_three.c \
       src/split/tokenizer/split_command_four.c \
       src/split/split_ft_echo_utils1.c \
       src/split/split_ft_echo_utils2.c \
       src/split/split_ft_echo.c \
       src/split/split_ft_export.c \
       src/split/split_input.c \
       src/split/split_utils1.c \
       src/split/split_utils2.c \
       src/split/split_utils3.c \
       src/builtin/ft_exit.c \
       src/builtin/ft_cd.c \
       src/builtin/ft_echo.c \
       src/builtin/env/pwd_and_shlvl.c \
       src/builtin/env/ft_env.c \
       src/builtin/ft_export/ft_export_utils_three.c \
       src/builtin/ft_export/ft_export_utils_one.c \
       src/builtin/ft_export/ft_export_utils_two.c \
       src/builtin/ft_export/ft_export_utils_four.c \
       src/builtin/ft_export/ft_export.c \
       src/builtin/ft_unset.c \
       src/builtin/ft_pwd.c \
       src/builtin/is_builtin_function.c \
       src/execute/pipe_one.c \
       src/execute/pipe_two.c \
       src/execute/pipe_three.c \
       src/execute/pipe_four.c \
       src/execute/pipe_five.c \
       src/execute/here_doc.c \
       src/execute/here_doc_two.c \
       src/execute/get_path.c \
       src/execute/check_dir.c \
       src/execute/redirection.c \
       src/expander/expand_tokens.c \
       src/expander/expand_tokens_two.c \
       src/expander/expand_tokens_three.c \
       src/expander/process_dollar_sign.c

OBJ_DIR = obj
OBJ = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
LIBFT_PATH = libft
CC = cc 
CFLAGS = -Wall -Wextra -Werror
LINKER = -L./libft -lft -lreadline
INC = -I./inc -I./libft/inc

all: LIB $(NAME)

LIB:
	make -C $(LIBFT_PATH)

$(NAME): $(OBJ)
	$(CC) $^ $(LINKER) -o $@

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_PATH) clean 

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re LIB
