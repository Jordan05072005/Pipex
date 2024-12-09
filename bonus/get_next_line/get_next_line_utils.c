/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:47:29 by jguaglio          #+#    #+#             */
/*   Updated: 2024/09/30 13:47:29 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;	

	i = -1;
	j = 0;
	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	dest = (char *)malloc((ft_strlen((const char *)s1)
				+ ft_strlen((const char *)s2) + 1) * sizeof(char));
	if (dest == NULL)
		return (free(s1), NULL);
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (free(s1), dest);
}

int	in_str(char *str, char find)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == find)
			return (i);
		i++;
	}
	if (str[i] == find)
		return (i);
	return (-1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (start >= (unsigned int)ft_strlen(s))
	{
		dest = malloc(sizeof(char));
		dest[i] = '\0';
		return (dest);
	}
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	dest[0] = '\0';
	while (s[i + start] && i < len)
	{
		dest[i] = s[i + start];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
