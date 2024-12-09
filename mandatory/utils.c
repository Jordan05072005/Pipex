/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:49:54 by jguaglio          #+#    #+#             */
/*   Updated: 2024/11/05 15:49:54 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_all_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i] && !path)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = ft_strdup(envp[i] + 5);
		i++;
	}
	return (path);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

//looking for a path like this: /usr/local/bin
char	*precis_path(char *path_all, char *argm)
{
	char	**str;
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	str = ft_split(path_all, ':');
	while (str[i])
	{
		temp = ft_strjoin(str[i], "/");
		path = ft_strjoin(temp, argm);
		if (access(path, F_OK | X_OK) == 0)
			return (free(temp), free_split(str), free(path_all), path);
		free(temp);
		free(path);
		i++;
	}
	return (free_split(str), free(path_all), NULL);
}

void	print_error_message(char *str, int cod_err, int err_exit)
{
	char	*error_message;

	if (err_exit > 128)
		err_exit = err_exit - 128;
	if (cod_err > 0 && cod_err <= 84)
	{
		error_message = strerror(cod_err);
		perror(error_message);
		exit(err_exit);
		return ;
	}
	else
	{
		ft_putstr_fd(str, 2);
		exit(err_exit);
		return ;
	}
}
