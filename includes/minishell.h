/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 16:59:02 by rturcey           #+#    #+#             */
/*   Updated: 2020/10/25 09:49:18 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"

# define YELLOW 	"\033[1;93m"
# define CYAN 		"\033[1;96m"
# define END  		"\033[0m"
# define IS_MS		0
# define IS_PIPE	1
# define IS_EXEC	2
# define IS_F_MS	3

typedef struct stat	t_stat;

typedef struct		s_env
{
	char			*key;
	char			*val;
	char			*val_sp;
	int				in;
	int				sp;
	struct s_env	*next;
	int				pluseq;
}					t_env;

typedef struct		s_redir
{
	int				cmd_in;
	int				cmd_output;
	int				err_output;
}					t_redir;

typedef struct		s_obj
{
	char			*obj;
	int				type;
	int				option;
	t_redir			*redir;
	char			*result;
	char			*error;
	int				pip;
	char			**args;
	char			**charenv;
	int				tube[2];
	int				qts;
	int				fk;
	struct s_obj	*next;
	struct s_obj	*prev;
}					t_obj;

typedef struct		s_sh
{
	t_obj			*obj;
	t_env			*env;
	char			*in;
	int				lev;
	int				**running;
	int				running_nb;
	int				wait;
	int				*tmp;
	int				*temp;
}					t_sh;

t_env				*g_lstenv;
int					g_forked;
int					g_err;
pid_t				g_pid;
int					g_sigint;

typedef int			(*t_parse_cmd)(t_sh *, int *);

int					init_main(t_sh **sh, char **env);
void				sighandler(int num);
void				kill_pipe(int sig);
void				clear_sh(t_sh *sh);

t_obj				*obj_new(t_obj *prev);
t_redir				*redir_new(void);
char				*init_obj(t_obj *obj, char *sample, int type);
int					free_obj(t_obj **obj);
void				*free_redir(t_redir *redir);

int					gnl_ms(int fd, char **line);
int					general_parser(t_sh *sh);
int					general_loop(t_sh *sh, int *i, int lev);
int					pass_spaces(char *str, int i);
int					check_single(char *str, int i);
int					is_quote	(char *str, int i, char quote);
int					is_quote_mod(char *str, int i);
int					in_quotes(char *str, int i);
int					one_quote(char *s, char *s1);
int					lonely_quote(char *str);
int					last_backslash(char *str);
int					find_string_end(char *src, int i);
int					find_end(char *in, int i);
int					find_redir(t_sh *sh, int *i);
int					find_redir_err(t_sh *sh, int *i);
int					is_redir(char *str, int i);
int					redir_loop(t_sh *sh, int *i);
char				*sample_str(t_sh *sh, int *i, char *sample);
int					skim_str(char *sample, int k, int *i);
int					is_separator(char *str, int i);
int					is_end(char *str, int i);
int					get_next_quote(char *str, int i, t_sh *sh, int l);
int					count_strings(char *in, int i);
int					parse_syntax(t_sh *sh, int i);
int					normed_char(char c);
void				alt_skim(char **s, int *j, int *i);

t_env				*init_env(char **env, int in, int lev);
int					env_clear(t_env *env);
void				print_env(t_env *env, int fd);
t_env				*env_new(int in);
char				*find_env_val(char *key, t_env *env);
t_env				*find_env_entry(char *key, t_env *env);
t_env				*env_cpy(t_env *elt);
char				**env_to_array(t_env *env);
int					export_var(t_env *elt, t_env *env, int in);
void				export_solo(t_sh *sh);
int					sample_export(char *sample, t_env *env, int ret);
void				del_var(t_env *var);
void				del_from_key(t_env **begin, char *key);
int					unset_var(char **elt, t_sh *sh);
int					add_var(t_env *elt, t_env *env);
int					parse_var(t_sh *sh, int *i, int len);
void				parse_all_var(t_sh *sh, char **s, int i);
void				pass_quotes(t_sh *sh, int *i);
char				**ft_split_var(char *s, char c, t_sh *sh, int *i);
int					split_val(char *s, int i);
void				split_pass_quotes(char const *s, int *i);
int					split_env(char *line, t_env *elt);
int					check_var(char *sample);
int					check_var_loop(t_env *tmp, t_env *env, t_env *w);
int					replace_var_check(t_env *w, char *key, t_env *tru);
int					parse_sample_var(char **sample, int *j, t_env *env, int *i);
int					pluseq(char *sample, int i);
int					repluseq(char *sample, int i, t_env *env, int in);
char				**empty_env(void);
void				*check_empty(int lever, char **env);
t_env				*old_empty(t_env **env, int lev);
int					find_path(t_env *lst);
void				find_home_user(char *path, char **home, char **user, \
						t_env *env);

void				pipe_checks(t_sh *sh, int *i);
void				set_gfork(t_sh *sh, char *tmp);
int					dup_exec(t_sh *sh);
int					try_exec(char *tmp, t_sh *sh, int *i);
int					check_empty_var(t_sh *sh, int *i);
int					is_cmd(char *sample);
int					parse_cmds(t_sh *sh, int *i);
int					parse_echo(t_sh *sh, int *i);
int					parse_cd(t_sh *sh, int *i);
int					only_n(char *str, int i);
int					parse_pwd(t_sh *sh, int *i);
int					replace_pwd(t_env *env, char **path);
int					old_pwd(t_env *env);
char				*get_pwd(void *env);
int					parse_export(t_sh *sh, int *i);
int					parse_unset(t_sh *sh, int *i);
int					parse_env(t_sh *sh, int *i);
int					parse_exit(t_sh *sh, int *i);
int					parse_exec(t_sh *sh, int *i);
int					check_path(t_sh *sh, char **path);
void				remove_home_path(char **path, char *home);
int					is_ms(char *exec);
int					start_exec(char *tmp, t_sh *sh, int *i);
void				pass_option(t_sh *sh, int *i);
void				handle_parent(pid_t pid, t_sh *sh);
int					free_shrun_arr(t_sh *sh, int ret);

int					print_result(t_sh *sh, int ret, char *to_free);
void				maj_err(t_sh *sh, char *str, int err);
int					set_g_err(t_sh *sh);
int					parse_g_err(char **sample, int *l, int *i);

#endif
