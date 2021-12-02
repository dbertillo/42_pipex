/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbertill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:26:17 by dbertill          #+#    #+#             */
/*   Updated: 2021/12/01 17:26:20 by dbertill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

#include <stdio.h>

int	openfile(char *filename, int mode)
{
	if (mode == 0)
	{
		if (access(filename, F_OK))
		{
			write(STDERR, "pipex: no suh file or directory: ", 33);
			write(STDERR, filename, ft_pchr(filename, 0));
			exit(1);
		}
		return (open(filename, O_RDONLY));
	}
	else
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
}

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_str_split(cmd, ' ');
	if (ft_pchr(args[0], '/') > -1)
		path = args[0];
	else
		path = ft_get_path(args[0], env);
	execve(path, args, env);
	write(STDERR, "pipex: ", 7);
	write(STDERR, "command not found: ", 20);
	write(STDERR, cmd, ft_pchr(cmd, 0));
	exit(127);
}

void	redir(char *cmd, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		exec(cmd, env);
	}
}

void	ft_here_doc(int ac, char **av, char **env)
{
	char	*buff;
	char	ch[2];
	int		i;
	int		fdout;

	// if (ac <= 5)
	// {
	// 	write(STDERR, "Here_doc. Invalid number  of arguments.\n", 29);
	// 	exit(1);
	// }
	buff = NULL;
	ft_print_here_doc(ac);
	while (read(STDIN, ch, 1))
	{
		buff = ft_str_rall(buff, ch[0]);
		if (ft_is_delimiter(buff, av[2]))
			break ;
		if (ch[0] == '\n')
			ft_print_here_doc(ac);
	}
	buff = ft_extract_env_vars(buff, env);
	buff = ft_remove_delimiter(buff, av[2]);
	redir_heredoc(buff);
	fdout = openfile(av[ac - 1], OUTFILE);
	dup2(fdout, STDOUT);
	i = 3;
	while (i < ac - 2)
		redir(av[i++], env);
	exec(av[i], env);
}

int	main(int ac, char **av, char **env)
{
	int	fdin;
	int	fdout;
	int	i;

	i = 2;
	if (av[1] && ft_str_cmp(av[1], "here_doc"))
		ft_here_doc(ac, av, env);
	else if (ac >= 5)
	{
		fdin = openfile(av[1], INFILE);
		fdout = openfile(av[ac - 1], OUTFILE);
		dup2(fdin, STDIN);
		dup2(fdout, STDOUT);
		while (i < ac - 2)
			redir(av[i++], env);
		exec(av[i], env);
	}
	else
		write(STDERR, "Invalid number  of arguments.\n", 29);
	return (1);
}
