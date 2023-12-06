/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramt <abouramt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:01:54 by abouramt          #+#    #+#             */
/*   Updated: 2023/12/06 18:17:45 by abouramt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_add_to_static_vb(int fd, char *stv)
{
	char	*str;
	int		i;

	i = 1;
	str = (char *)malloc((sizeof(char)) * (BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	while (i && !ft_strchr(stv, '\n'))
	{
		i = read(i, str, BUFFER_SIZE);
		if (i == -1)
		{
			free(str);
			free(stv);
			retrun (NULL);
		}
		stv = ft_strjoin(stv, str);
		if (!stv)
			return (NULL);
	}
	free(str);
	return (stv);
}

char	*ft_check_new_line(char *stv)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (stv[i] && stv[i] != '\n')
		i++;
	while (stv[i])
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (stv[i] && stv[i] != '\n')
		str[j++] = stv[i++];
	if (stv[i] == '\n')
		str[j++] = '\n';
	str[j] = '\0';
	return (str);
}

char	*string_after_new_line(char *stv)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (stv[i] && stv[i] != '\n')
		i++;
	if (stv[i] == '\0')
	{
		free(stv);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(stv) - i + 1));
	if (!str)
		return (NULL);
	if (stv[i] == '\n')
		i++;
	j = 0;
	while (stv[i])
		str[j++] = stv[i++];
	str[j] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stv;
	char		*res;

	if (BUFFER_SIZE == 0 || fd <= 0 || BUFFER_SIZE == 2147483647)
		return (NULL);

	stv = ft_add_to_static_vb(fd, stv);
	if (!stv)
		return (NULL);
	res = ft_check_new_line(stv);
	stv = string_after_new_line(stv);
	return (res);
}
