#ifndef BIGERRNO_H
# define BIGERRNO_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include "../libft/libft.h"

# define SHELL "bigerrno"
# define SEP     28
# define SEP_STR "\034"
# define LOGOP_COLON 0
# define LOGOP_OR    1
# define LOGOP_AND   2

extern char	**environ;
extern int	g_signum;

typedef enum e_color
{
	E_COLOR_GNOME,
	E_COLOR_PEACH,
	E_COLOR_POWDER,
	E_COLOR_AZUR,
	E_COLOR_PURPLE,
	E_COLOR_PINK,
	E_COLOR_LIMIT
}	t_color;

/* `pl` stands for "pipeline" */
typedef struct s_file
{
	char	*filename;
	int		flags;
	int		io;
}	t_file;

typedef struct s_pl
{
	size_t	len;
	size_t	index;
	int		circular;
	int		exit_code;
	char	*err_msg;
	char	**path;
	char	***cmdl;
	t_file	**file;
	int		fd_std[2];
	int		fd_src[2];
	int		fd_circ[2];
}	t_pl;

/* `ex` stands for `execution` */
typedef struct s_ex
{
	int			logop;
	t_pl		pl;
	struct s_ex	*next;
}	t_ex;

/* `rl` stands for "readline" */
typedef struct s_rl_arr
{
	char	*value;
	int		is_heredoc;
	int		backslashes;
	char	**delimiters;
}	t_rl_arr;

typedef struct s_rl
{
	char		*user;
	char		*prompt;
	char		**buf;
	t_rl_arr	**arr;
	char		**tokens;
	char		**hd;
}	t_rl;

/* `env` stands for "environment" */
typedef struct s_env
{
	char			*key;
	char			*value;
	int				withvalue;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

/* `sh` stands for "shell" */
typedef struct s_sh
{
	char		*first_arg;
	int			valid_term;
	char		*pid;
	char		*user;
	char		*host;
	char		*home;
	char		*shells;
	int			subshell;
	int			keep_running;
	int			exit_code;
	char		*pwd;
	t_env		*env;
	t_env		*hidden;
	t_env		*local;
	t_rl		rl;
	t_ex		*ex;
	t_color		color;
	const char	*prompt_color1;
	const char	*prompt_color2;
	int			pid_disco;
}	t_sh;

/* Parser ------------------------------------------------------------------- */

void	run_shell(t_sh *sh);
void	free_shell(t_sh *sh);
void	interpret_and_process_cmd(t_sh *sh);

void	handle_no_tty(void);
void	handle_default_background_color(int set);
void	reset_title_and_background_color(void);
void	set_prompt_color(t_sh *sh, t_color color);
void	set_background_color(t_color color);
int		is_term_var_valid(t_sh *sh);
char	*circular_pipeline(t_sh *sh, const char *cmdl);
int		get_pid(t_sh *sh, const char *first_arg);
char	*get_home_path(t_sh *sh, const char *username);
char	*get_shells(t_sh *sh);
int		is_shell(const char *shells, const char *cmd);
char	*get_clean_token(const char *s);
int		is_unicode_format(const char *s);
void	process_unicode_value(int is_echo_e, char **s, size_t *i);

/* Signals ------------------------------------------------------------------ */

int		set_signals(int reset);
int		set_signal_handling(int signum, void (*handler)(int));
void	signal_handler(int signum);
char	*get_sig_flavor_text(int signum);

/* Executor ----------------------------------------------------------------- */

int		execute_pipeline(t_sh *sh);
void	execute_subprocess(t_sh *sh, int fd_pipe[2], int fd_input, int *pid);
int		pop_head_ex(t_sh *sh);
void	destroy_all_ex(t_sh *sh);

int		redirect_io(t_pl *pl);
int		restore_io(t_pl *pl);
int		resolve_command(t_pl *pl, char *cmd_path, char **cmd_fullpath);
void	wait_for_subprocesses(t_sh *sh, int *pid, int options);

/* Builtins ----------------------------------------------------------------- */

int		is_builtin(char **cmd);
int		execute_builtin(t_sh *sh);

int		bigerrno_cd(t_sh *sh, char **arg);
int		bigerrno_echo(char **arg);
int		bigerrno_exit(t_sh *sh, char **arg);
int		bigerrno_export(t_env **env, t_env **hidden, t_env **local, char **arg);
int		bigerrno_pwd(t_sh *sh);
int		bigerrno_set(t_env *hidden, char **arg);
int		bigerrno_unset(t_sh *sh, char **arg);

int		bigerrno_disco(t_sh *sh);
int		bigerrno_lulu(t_sh *sh);
int		bigerrno_matrix(t_sh *sh, char **arg);
int		bigerrno_shoot(t_sh *sh, char **arg);

/* Utils -------------------------------------------------------------------- */

char	*compose_err_msg(const char *shell, const char *cmd, const char *arg,
			const char *msg);
int		output_error(int code, char *msg);

char	*insert_str_before_char(const char *s, size_t i, const char *to_insert);
char	*remove_str(const char *s, size_t i, size_t len_to_remove);
char	*concatenate_strings(char **arr, const char *separator);
char	**duplicate_strings(char **arr);
void	sort_strings_alpha(char **arr, int (*cmp)(const char *, const char *));

size_t	get_array_length(void **array);
size_t	find_array_index(void **array, int (*condition)(void *element));
void	**insert_array_element(void ***array, void *to_insert, size_t index);
void	**insert_array_elements(void ***array, void **to_insert, size_t index);
void	*extract_array_element(void **array, size_t index);
void	**extract_array_elements(void **array, size_t from, size_t to);
void	remove_array_elements(void **array, size_t from, size_t to,
			void (*free_element)(void *));
void	free_entire_array(void **array, void (*free_element)(void *));

int		only_var(char **arg);
int		update_hidden(t_env **hidden, char **token);
void	update_shlvl(t_env **env, int inpipe);
t_env	*convert_to_lst(char **env, const char *sh_first_arg);
t_env	*lstadd_back(t_env **lst, t_env *new);
t_env	*lst_new(const char *key, const char *value);
void	lst_clear(t_env **lst);
int		lst_size(t_env **lst);
t_env	*add_node(t_env **lst, char *key, char *value);
t_env	*find_key(t_env **lst, char *key);
char	*get_var_value(t_sh *sh, char *key);
int		update_pwd(t_sh *sh, const char *arg, int code_err);
int		valid_keyvalue(char *key_value);
char	*get_literal_token(const char *s);
char	*get_echo_escaped_token(const char *s, int *is_c_found);
void	swap_node_content(t_env *s1, t_env *s2);
t_env	*find_smallest_p(t_env **p_order);
t_env	*find_biggest_p(t_env **p_order);
t_env	*next_smallest(t_env **p_order, t_env *smallest);
void	clear_node(t_env *node);
t_env	*alpha_order_lst(t_env **env);
void	update_env(t_env **env, t_env **hidden);
void	extract_local_update(char ***cmd, t_env **local);
int		firstocc(char *s, char c);
int		continued_occurence(char *s, char c);
char	**convert_to_arr(t_env *env);
void	update_prompt(t_sh *sh);
char	*extract_key(int separator, char *key_value);

#endif
