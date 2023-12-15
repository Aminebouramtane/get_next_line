/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:01:54 by abouramt          #+#    #+#             */
/*   Updated: 2023/12/13 17:43:39 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_my_line(int fd, char *str)
{
	char	*tmp;
	int		boolean;

	boolean = 1;
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	while (boolean != 0 && !ft_strchr(str, '\n'))
	{
		boolean = read(fd, tmp, BUFFER_SIZE);
		if (boolean == -1)
		{
			free(tmp);
			free(str);
			return (NULL);
		}
		tmp[boolean] = '\0';
		str = ft_strjoin(str, tmp);
		if (!str)
			return (NULL);
	}
	free(tmp);
	return (str);
}

char	*return_my_line(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str[0])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i])
		i++;
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		res[j++] = str[i++];
	if (str[i] == '\n')
	{
		res[j] = '\n';
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*after_new_line(char *str)
{
	char	*res;
	int		j;
	size_t	i;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	res = malloc(ft_strlen(str) - i + 1);
	if (!res)
		return (NULL);
	if (str[i] == '\n')
		i++;
	while (str[i] != '\0')
		res[j++] = str[i++];
	res[j] = '\0';
	free(str);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*res;

	if (BUFFER_SIZE <= 0 || fd < 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	str = get_my_line(fd, str);
	if (!str)
		return (NULL);
	res = return_my_line(str);
	str = after_new_line(str);
	return (res);
}
