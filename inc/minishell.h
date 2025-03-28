/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:48:58 by sal-kawa          #+#    #+#             */
/*   Updated: 2025/03/22 09:01:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

extern int		g_shell_signal;

typedef struct s_shell
{
	char		*input;
	char		**input_splitted;
	char		***split_the_split;
	char		***command;
	char		***dir;
	char		***operate;
	char		**env;
	char		**exp;
	char		*old_pwd;
	char		*name_program;
	int			command_count;
	int			exit_status;
	int			operate_count;
	int			dir_count;
	int			count_pipe;
	int			flag_here;
}				t_shell;

typedef struct s_here_doc_data
{
	int			pipe_fd[2];
	int			saved_stdin;
	char		*accumulator;
}				t_here_doc_data;

typedef struct s_pipe_vars
{
	int			in_fd;
	int			out_fd;
	int			saved_stdin;
	int			saved_stdout;
	int			a;
	int			b;
	int			prev_fd;
	int			pipe_fd[2];
	int			pid;
	int			redir_success;
	int			pipe_created;
	int			i;
}				t_pipe_vars;

typedef struct s_range
{
	int	start;
	int	end;
}	t_range;

// struct for expander
typedef struct s_exp
{
	char		*res;
	char		*out;
}				t_exp;

//structs for Tokenizer :
typedef struct s_tok_state
{
	int			token_count;
	int			last_cmd_index;
	int			has_command;
	int			prev_redir;
}				t_tok_state;

typedef struct s_tok_data
{
	char		**tokens;
	int			*cmd_flags;
	int			max_tokens;
	t_tok_state	state;
}				t_tok_data;

typedef struct s_word
{
	char		*ts;
	char		*te;
	int			len;
}				t_word;

typedef struct s_rvars
{
	int			i;
	char		*space;
	int			word_len;
	int			extra_len;
	size_t		old_len;
	char		*merged;
	char		*operand;
}				t_rvars;

// struct for split_ft_echo
typedef struct s_token_info
{
	char		**tokens;
	int			*groups;
	int			*index;
}				t_token_info;

//dir.c
void			dir(t_shell *test);
void			process_dir_input(t_shell *test, int *j, int y);
void			store_redirect(t_shell *test, int *j, int y, int *x);
int				count_max_dir(t_shell *test, int y);

//operator.c
void			operate(t_shell *test);
void			process_input(t_shell *test, int *j, int y);
void			allocate_operate_array(t_shell *test);
void			count_pipe(t_shell *shell);
int				count_max_operate(t_shell *test, int y);

//command.c && command_two.c
void			command_count(t_shell *test);
void			store_command(t_shell *test, int *j, int i);
void			process_commands(t_shell *test);
void			command_malloc(t_shell *test, int *i, int *j, int *pipe);
void			command_initial_pipes(t_shell *test, int *i, int *j);
void			command_initial_pipes(t_shell *test, int *i, int *j);
void			process_temp_array(t_shell *test, int *i, int *j, char **t);
int				count_max_commands(t_shell *test);
int				handle_pipes(t_shell *test, int *i, int *j);
void			update_commands(t_shell *test, int *j, int *i, int flagg);
int				check_flagg(char **t);
char			**create_temp_array(t_shell *test, int index);
void			find_first_pipe(t_shell *test, int *i);
void			process_commands_loop(t_shell *test, int *i, int *j);
int				ch(char **t, int h);
int				check_if(t_shell *test, int i);

// ft_export folder
void			ft_export(t_shell *test, char **args);
void			print_array(char **arr);
void			sort_array(char **arr, int total);
void			print_export_list(t_shell *shell);
void			add_new_env_var(t_shell *shell, char *new_var);
void			update_env_var(t_shell *shell, char *var_name, char *new_var);
void			remove_from_export(t_shell *shell, char *var_name);
void			add_to_export(t_shell *shell, char *var);
void			process_arg_with_equal(t_shell *shell, char *local_arg,
					int *error_flag);
void			process_arg(t_shell *shell, char *arg, int *valid_args,
					int *error_flag);
char			*get_name_from_env(const char *str);
char			*get_invalid_identifier(const char *str);
char			**merge_lists(t_shell *shell);
char			*expand_arg_no_equal(t_shell *shell, char *arg);
char			*expand_arg(t_shell *shell, char *arg, int *error_flag);
char			*process_dollar_assignment(t_shell *shell, char *local_arg,
					int *error_flag);
char			*expand_arg_with_equal(t_shell *shell, char *arg,
					int *error_flag);
int				count_array(char **arr);
int				is_valid_identifier(const char *str);
int				copy_array(char **src, char **dest, int j);
int				export_exists(t_shell *shell, char *var);
int				update_existing_env(t_shell *shell, char *var_name,
					char *new_var);

//./bulitin folder
void			run_builtin_function(t_shell *shell, int i, int out_fd);
void			ft_cd(t_shell *path, int i);
void			get_directory(t_shell *shell, int i, char **target);
void			ft_echo(t_shell *string, int i);
void			handle_echo_flag(t_shell *string, int i, int *x, int *f);
void			print_echo_arguments(t_shell *string, int i, int x);
void			ft_env(t_shell *test, int i);
void			ft_env_init(t_shell *test);
void			ft_env_copy(t_shell *test, char **environ, int i);
void			re_shlvl(t_shell *shell);
void			create_shlvl_entry(t_shell *shell, int level);
void			ft_pwd(t_shell *shell);
void			ft_unset(t_shell *test, char **args);
void			get_old_pwd(t_shell *shell);
void			check_echo_flags(t_shell *str, int i, int *idx, int *flag);
void			update_pwd(t_shell *shell);
char			*get_env_value(t_shell *shell, char *var);
int				is_numeric(const char *str);
int				check_argc_in_exit(char *argv);
int				ft_exit(t_shell *shell, int i);
int				_exit_arguments(t_shell *shell, int i);
int				is_builtin_funcion(t_shell *test, int i);
int				check_char_newline(char *flag);
void			check_runer(t_shell *shell, int i);
void			handle_env_error_slash(t_shell *test, char **argv);

//split_command.c
int				tokenize_input(t_shell *g_shell, const char *input,
					t_tok_data *data);
const char		*process_operator(const char *p, t_tok_data *d);
const char		*collect_part(const char *p, char **part_out);
const char		*process_word(const char *p, t_shell *g, t_tok_data *d);
char			*alloc_t(const char *p, int len);
void			process_redir_word(t_word *w, t_shell *g, t_tok_data *d);
void			process_redir_quoted(t_word *w, t_shell *g, t_tok_data *d);
void			process_redir_unquoted(t_word *w, t_shell *g, t_tok_data *d);
void			process_redir_extra(t_rvars *r, t_word *w, t_shell *g,
					t_tok_data *d);
void			process_normal_word(t_word *w, t_shell *g, t_tok_data *d);
void			find_space(t_rvars *r, t_word *w);
void			process_redir_unquoted_branch(t_rvars *r, t_word *w, t_shell *g,
					t_tok_data *d);
void			process_redir_unquoted_else(t_word *w, t_shell *g,
					t_tok_data *d);
void			process_redir_extra_if(t_rvars *r, t_word *w, t_shell *g,
					t_tok_data *d);
void			process_redir_extra_else(t_rvars *r, t_word *w, t_shell *g,
					t_tok_data *d);
const char		*handle_quote(const char *p, int *in_quote, char *qc);

//split_utils1.c
size_t			ft_count_subwords(char *s);
char			*alloc_token(size_t len);
char			*handle_special_case(const char *start, size_t token_len,
					char **s, char *p);
void			skip_spaces(char **s);

//split_utils2.c
size_t			calculate_token_length(const char *str);
void			skip_quote_if_needed(const char **p, int *in_quote,
					char *quote);
void			fill_token_chars(char *token, const char *start,
					size_t token_len);
char			*copy_token_content(const char *start, size_t token_len);
char			*extract_token_with_quotes(char **s);

//split_utils3.c
size_t			count_tokens_with_quotes(char *s);
char			**allocate_token_array(size_t count);
char			**ft_split_whitespace(char *s);
void			fill_tokens(char **tokens, char *s);
void			skip_token_with_quotes(char **s);

//split_ft_export.c
char			*extract_command(char **s_ptr);
char			**build_tokens_with_arguments(char *cmd, char **args);
char			**build_tokens_with_no_argumnets(char *cmd);
char			**build_tokens(char *cmd, char *s);
char			**ft_split_export(char *s);

//split_ft_echo_utils1.c
void			handle_malloc_error(void);
void			init_malloc(char ***tokens, int **groups);
void			store_token(t_token_info *token_info, int group, char *start,
					size_t len);
void			quote_token(char **s, const char **start);
void			unquoted_token(char **s, const char **start);

//split_ft_echo_utils2.c
void			pr_token(char **s, t_token_info *token_info,
					int *current_group);
void			tokenize_loop(char *s, char **tokens, int *groups,
					int *token_index);
void			tok_input(char *s, char **tokens, int *groups,
					int *token_index);
size_t			calculate_total_length(char **tokens, int start, int count);
char			*merge_group_t(char **tokens, int start, int count);

//split_ft_echo.c
void			group_loop(char **tokens, int *groups, int token_count,
					char **final_tokens);
char			**group_tokens(char **tokens, int *groups, int token_count);
char			**ft_split_echo(char *s);

//split_input.c
char			***split_commands(char **s);
char			***allocate_split(char **s, size_t *count);
char			**ft_split(const char *input, t_shell *shell);
void			skip_quoted_input(char **s);

//check_operator.c
int				type_of_ope(const char *op);
int				is_operator(const char *s, int *op_len);
void			ft_trim(char *str, char **start, char **end);

//get_path.c
char			*getpath(t_shell *shell, char **test);
char			*find_executable(char *path, char *new_path, char *test);

//handel_signals
void			handle_signals(int sig);
void			change_sigint(int sig);

//pipe.c
void			free_for_args(t_shell *shell);
void			execute_pipes_redir(t_shell *shell);
void			child_handle_builtin(t_shell *shell, int i, t_pipe_vars *vars);
void			child_check_directory_errors_two_if(t_shell *shell, char *path);
void			child_check_directory_errors_two(t_shell *shell, char **argv);
void			execute_command(t_shell *shell, char **argv, char *cmd_path);
void			child_exec_command(t_shell *shell, char **argv);
void			close_after_fork(t_pipe_vars *vars);
void			wait_for_children(t_shell *shell, int pid);
void			child_setup_redirfds(t_shell *shell, t_pipe_vars *vars);
void			child_check_directory_errors_one(t_shell *shell, int i,
					char **argv);
void			child_check_directory_errors_one(t_shell *shell, int i,
					char **argv);
void			child_close_fds(t_pipe_vars *vars);
void			child_process(t_shell *shell, int i, t_pipe_vars *vars,
					char **argv);
void			command_pipeline_redirections(t_shell *shell, int i,
					t_pipe_vars *vars);
void			pipeline_with_command(t_shell *shell);
void			process_pipeline_redirections(t_shell *shell, int i,
					t_pipe_vars *vars);
void			execute_builtin_cleanup(t_pipe_vars *vars);
void			create_pipess(t_shell *shell, int i, t_pipe_vars *vars);
void			pipeline_no_command_inner(t_shell *shell, t_pipe_vars *vars);
void			pipeline_no_command_pipe_valid(t_shell *shell,
					t_pipe_vars *vars);
void			pipeline_no_command_dispatch(t_shell *shell, t_pipe_vars *vars);
void			pipeline_no_command(t_shell *shell);
int				bulitin_run_command_execute(t_shell *shell, int i,
					t_pipe_vars *vars);
int				create_fork(t_shell *shell, t_pipe_vars *vars);
void			setup_pipeline_iteration(t_shell *shell, int i,
					t_pipe_vars *vars);

// check_dir.c
int				check_dir(char *dir);
int				msg_operate_error(t_shell *msg);

//redirection.c
int				handle_input_redirection(char *filename, t_pipe_vars *vars);
int				handle_output_redirection(const char *filename,
					t_pipe_vars *vars, int append);
int				handle_here_doc(char *here_doc_world, int *in_fd,
					t_shell *test);
int				check_operator(char *filename, char *operator,
					t_pipe_vars *vars, t_shell *test);
int				get_redirections(char *filename, char *operator,
					t_pipe_vars *vars, t_shell *test);
int				handle_here_doc_util(char **accumulator, char *line,
					t_shell *test);
int				here_doc_finalize(t_here_doc_data *data, int *in_fd);
int				here_doc_setup(t_here_doc_data *data);
int				here_doc_read_loop(char *delimiter, t_here_doc_data *data,
					t_shell *test);
int				process_here_doc_line(char *delimiter, t_here_doc_data *data,
					t_shell *test, char *line);
void			restore_stdin(int saved_stdin);

//expander
char			*expander(char *token, t_shell *shell);
char			*delete_spaces(char *s);
char			*deal_with_dollar(char *s, t_shell *shell, t_exp *exp);
char			*deal_with_signal_quote(char *s, t_exp *exp);
char			*deal_with_double_quote(char *s, t_shell *shell, t_exp *exp);
char			*deal_with_un_quotetd(char *s, t_shell *shell, t_exp *exp);
char			*remove_extra_spaces(char *s, char *new);
char			*deal_with_char(char **s, t_shell *shell, t_exp *exp);
char			*check_type_of_token(char *s, t_shell *shell, t_exp *exp);
int				should_delete_sp(char *token);
int				expander_init(char *token, t_shell *shell,
					t_exp *exp, char **s);
char			*expander_finalize(char *token, t_exp *exp);

//free_and_exit
void			free_shell(t_shell *shell, int f, int child);
void			free_child_resources(t_shell *shell);
void			e_exit(t_shell *shell, int i);
void			free_3d(char ***ar);
void			free_2d(char **ar);
void			print_error(char *program, char *arg, char *msg);
void			null_and_zero(t_shell *shell);
void			free_dir_operate(t_shell *shell);

//main_utils
int				is_only_whitespace(char *s);
int				check_pipe_syntax(t_shell *test);
void			check_command_count(t_shell *test);
void			run_command(t_shell *test);
void			init_shell(t_shell *test, int argc, char **argv);
int				split_input(t_shell *test);
int				handle_input(t_shell *test);
void			expand_all_tokens(t_shell *test);
int				check_same_operator_case(t_shell *test, int i);
int				is_redirection_operatora(char op);
int				check_mixed_operator_case(t_shell *test, int i);
int				check_redirection_operator(t_shell *test, int i);
int				check_redirections(t_shell *test);
int				check_quotes(t_shell *test);
int				check_pipe_operate(t_shell *test);
void			execute_and_cleanup(t_shell *test);
void			expand_tokens_in_row(char ***tokens_ptr, t_shell *test);
int				check_redirection_error_sames(t_shell *test, int i);
int				check_redirection_error_diffs(t_shell *test, int i);
int				process_redirectionss(t_shell *test);
int				input_phase(t_shell *test);
int				process_redirectionss(t_shell *test);
int				command_phase(t_shell *test);
char			**merge_tokens_core(char **old_tokens, char **split, int j,
					char **new_tokens);
char			**allocate_new_tokens(char **old_tokens, char **split);
void			copy_tokens(char **dest, int *dest_index, char **src,
					t_range range);
void			shift_tokens_left(char **tokens, int index);
int				count_tokens(char **arr);
char			**merge_tokens(char **old_tokens, char **split, int j);
void			merge_expanded_token(char ***tokens_ptr, t_shell *shell,
					int *j_ptr, char **input_splitted_x);
void			process_token_with_dollar(char ***tokens_ptr,
					t_shell *shell, int *j_ptr);
void			process_token_without_dollar(char **tokens, t_shell *shell,
					int j);
void			expand_tokens_in_row(char ***tokens_ptr, t_shell *shell);
int				check_quotes_utils(t_shell *test);

#endif
