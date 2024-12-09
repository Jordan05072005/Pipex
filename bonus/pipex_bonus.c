/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:10:34 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/04 13:10:34 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execution(char *path_all, char *av, char **envp)
{
	char	**argm;
	char	*path;

	argm = ft_split(av, ' ');
	path = precis_path(path_all, argm[0]);
	if (!path)
	{
		free_split(argm);
		print_error_message("error : path no found\n", 0, 0);
	}
	if (execve(path, argm, envp) == -1)
	{
		print_error_message("error : no execution\n", errno, errno);
		free(path);
		free_split(argm);
	}
	free(path);
	free_split(argm);
}

void	pipes(char **av, char **envp, int i)
{
	int		pipefd[2];
	pid_t	proc;
	char	*path;

	if (pipe(pipefd) == -1)
		print_error_message("errror : tunel not create\n", errno, errno);
	proc = fork();
	if (proc == -1)
		print_error_message("error : processus not create\n", errno, errno);
	if (proc == 0)
	{
		path = find_all_path(envp);
		if (!path)
			return ;
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		execution(path, av[i], envp);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
	}
}

void	last_pipe(char **av, int ac, int i, char **envp)
{
	int		fd;
	char	*path;

	fd = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
		print_error_message("error : folder not open\n", errno, errno);
	dup2(fd, 1);
	path = find_all_path(envp);
	if (!path)
		return ;
	execution(path, av[i], envp);
}

void	here_doc(char *limiter)
{
	int		pipefd[2];
	pid_t	proc;

	if (pipe(pipefd) == -1)
		print_error_message("errror : tunel not create\n", errno, errno);
	proc = fork();
	if (proc == -1)
		print_error_message("error : processus not create\n", errno, errno);
	if (proc == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		read_fd(pipefd, limiter);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
	}
}

//pipefd -> [0] : R , [1] : W
int	main(int ac, char **av, char **envp)
{
	int		fd;
	char	*path;
	int		i;

	i = 2 - 1 ;
	if (ac < 5)
		print_error_message("error : bad number of arguments\n", errno, 2);
	if (!ft_strncmp(av[1], "here_doc", 7))
	{
		here_doc(av[2]);
		i++;
	}
	else
	{
		fd = open(av[1], O_CREAT | O_RDONLY, 0777);
		if (fd == -1)
			print_error_message("error : folder not open\n", errno, errno);
		dup2(fd, 0);
	}
	while (++i < ac - 2)
		pipes(av, envp, i);
	close(fd);
	last_pipe(av, ac, i, envp);
	exit(0);
}
