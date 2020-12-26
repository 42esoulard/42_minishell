/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esoulard <esoulard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:20:51 by user42            #+#    #+#             */
/*   Updated: 2020/10/26 10:12:20 by esoulard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt(t_env *env)
{
	char	*path;
	char	*user;
	char	*host;
	char	*home;
	int		fd;

	if (!(path = get_pwd(env)))
		exit(EXIT_FAILURE);
	home = find_env_val("HOME", env);
	user = find_env_val("USER", env);
	if ((!home[0] || !user[0]) && free_two_str(home, user))
		find_home_user(path, &home, &user, env);
	remove_home_path(&path, home);
	fd = open("/etc/hostname", O_RDONLY);
	get_next_line(fd, &host);
	ft_dprintf(2, "%s%s@%s%s:%s%s%s %s►%s ", YELLOW, user, host, END, \
	CYAN, path, END, YELLOW, END);
	free_two_str(user, home);
	free_two_str(path, host);
	close(fd);
}

void		sighandler(int num)
{
	if (num == SIGINT)
	{
		g_sigint = 1;
		if (g_forked == IS_MS)
		{
			ft_dprintf(2, "\n");
			prompt(g_lstenv);
		}
		else if (g_forked != IS_F_MS)
			ft_dprintf(2, "\n");
		if (g_forked != IS_PIPE)
			g_err = 130;
		kill_pipe(SIGINT);
	}
	else if (num == SIGQUIT)
	{
		if (g_forked == IS_EXEC)
		{
			ft_dprintf(2, "Quit: Core dumped\n");
			g_err = 131;
		}
		else if (g_forked == IS_MS)
			ft_dprintf(2, "\b\b \b  \b\b");
		kill_pipe(SIGQUIT);
	}
}

static int	read_err(int err)
{
	g_err = 2;
	ft_dprintf(2, ft_sprintf("bash: error reading input file:"));
	ft_dprintf(2, ft_sprintf(" %s\n", strerror(err)));
	return (-1);
}

static int	routine(t_sh *sh, char **line)
{
	int ret;

	if (read(0, NULL, 0) < 0)
		return (read_err(errno));
	prompt(sh->env);
	g_forked = IS_MS;
	g_lstenv = sh->env;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	*line = NULL;
	if ((ret = gnl_ms(0, line)) == 0)
	{
		if (*line)
			free(*line);
		*line = ft_strdup("exit\n");
	}
	else if (ret < 0)
		return (read_err(errno));
	if (sh->in)
		free(sh->in);
	sh->in = ft_strdup(*line);
	return (0);
}

int			main(int argc, char **argv, char **env)
{
	char		*line;
	int			ret;
	t_sh		*sh;

	(void)argc;
	(void)argv;
	g_lstenv = NULL;
	g_err = 0;
	g_forked = IS_MS;
	if (init_main(&sh, env) == -1)
		return (-1);
	while (1)
	{
		if (routine(sh, &line) < 0)
			break ;
		if (sh->in)
			ret = general_parser(sh);
		if (line)
			free(line);
		if (ret != 0)
			break ;
	}
	ret = g_err;
	clear_sh(sh);
	return (ret);
}
