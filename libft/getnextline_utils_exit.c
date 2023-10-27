/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline_utils_exit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:49:56 by dmaessen          #+#    #+#             */
/*   Updated: 2023/05/30 17:49:32 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_gnl_exit(char **memory, char *line)
{
	free(*memory);
	*memory = NULL;
	free(line);
}

char	*ft_strjoin_gnl_ex(char *memory, char *buf)
{
	size_t	i;
	size_t	len1;
	char	*join;

	if (!*memory && !*buf)
		return (free(memory), NULL);
	len1 = (ft_strlen(memory));
	join = ft_calloc((len1 + ft_strlen(buf) + 1), sizeof(char));
	if (!join)
		exit(EXIT_FAILURE);
	i = 0;
	while (memory[i])
	{
		join[i] = memory[i];
		i++;
	}
	i = 0;
	while (buf[i])
	{
		join[len1 + i] = buf[i];
		i++;
	}
	join[len1 + ft_strlen(buf)] = '\0';
	return (free(memory), join);
}

char	*ft_strchr_gnl_ex(const char *s, int c)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = 0;
	while (s[i] && s[i + 1] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (&str[i + 1]);
	return (NULL);
}

char	*ft_substr_gnl_ex(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		sub = malloc(1 * sizeof(char));
		if (!sub)
			exit(EXIT_FAILURE);
		sub[0] = '\0';
		return (sub);
	}
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
