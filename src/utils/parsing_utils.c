/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:41 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/13 14:55:15 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"
#include <string.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if ((s1[i] < s2[i]) || (s1[i] > s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}

void	*calloc_exit(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		err_msg("Calloc failed.\n");
	i = 0;
	while (i < count * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*rm_spaces(char *line)
{
	char	*newline;
	int		i;
	int		spaces;
	int		j;

	i = -1;
	spaces = 0;
	while (line[++i])
	{
		if (line[i] == ' ')
			spaces++;
	}
	newline = calloc_exit((ft_strlen(line) - spaces + 1), sizeof(char));
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] != ' ')
		{
			newline[j] = line[i];
			j++;
		}
	}
	newline[j] = '\0';
	return (newline);
}

char	*ft_strdup_check(const char *s1)
{
	int		i;
	int		size;
	char	*ptr;

	size = ft_strlen(s1);
	ptr = (char *)malloc((size + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		if (s1[i] == '\n')
			break;
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strarrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}