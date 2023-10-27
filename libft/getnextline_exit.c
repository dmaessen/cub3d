/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:40:25 by dmaessen          #+#    #+#             */
/*   Updated: 2023/05/30 17:49:13 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*current_line(char *memory)
{
	size_t	i;
	char	*line;

	i = 0;
	while (memory[i] != '\0' && memory[i] != '\n')
		i++;
	if (memory[i] == '\n')
		i++;
	line = ft_substr_gnl_ex(memory, 0, i);
	if (!line)
		return (free(line), NULL);
	return (line);
}

static char	*sub_mem(char *memory)
{
	size_t	i;
	size_t	len;
	char	*sub;

	i = 0;
	len = ft_strlen(memory);
	while (memory[i] != '\0' && memory[i] != '\n')
		i++;
	if (memory[i] == '\n')
		i++;
	if (!memory[i])
		return (free(memory), NULL);
	sub = ft_substr_gnl_ex(memory, i, len - i);
	if (!sub)
		return (ft_free_gnl_exit(&memory, NULL), NULL);
	free(memory);
	return (sub);
}

static char	*reading(int fd, char *memory)
{
	int		nbyte;
	char	*buf;

	buf = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		exit(EXIT_FAILURE);
	nbyte = 1;
	while (nbyte != 0 && !ft_strchr_gnl_ex(memory, '\n'))
	{
		nbyte = read(fd, buf, BUFFER_SIZE);
		if (nbyte < 0)
			return (ft_free_gnl_exit(&memory, buf), NULL);
		buf[nbyte] = '\0';
		memory = ft_strjoin_gnl_ex(memory, buf);
		if (!memory)
			return (ft_free_gnl_exit(&memory, buf), NULL);
	}
	free (buf);
	return (memory);
}

char	*get_next_line_exit(int fd)
{
	static char	*memory;
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		exit(EXIT_FAILURE);
	if (!memory)
	{
		memory = ft_calloc(1, 1);
		if (!memory)
			exit(EXIT_FAILURE);
	}
	memory = reading(fd, memory);
	if (!memory)
		return (free(memory), NULL);
	newline = current_line(memory);
	if (!newline)
		return (ft_free_gnl_exit(&memory, NULL), NULL);
	memory = sub_mem(memory);
	return (newline);
}
