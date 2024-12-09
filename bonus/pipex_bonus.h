/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:12:48 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/04 13:12:48 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H	

# include "get_next_line/get_next_line.h"
# include <errno.h>	
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include "../libft/libft.h"

char	*find_all_path(char **envp);
char	*precis_path(char *path_all, char *argm);
void	free_split(char **str);
void	print_error_message(char *str, int cod_err, int err_exit);
int		read_fd(int *pipefd, char *limiter);

#endif