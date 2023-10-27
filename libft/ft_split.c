/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:58:11 by dmaessen          #+#    #+#             */
/*   Updated: 2023/03/09 17:16:51 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(char const *s, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (words);
}

static int	ft_words_length(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static char	**ft_free(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	**ft_write(char const *s, char c, char **split)
{
	int	i;
	int	j;
	int	words;
	int	len;

	words = ft_words(s, c);
	i = 0;
	j = 0;
	while (s[i] != '\0' && words > j)
	{
		if (s[i] != c)
		{
			len = ft_words_length(s, c, i);
			split[j] = ft_substr(s, i, len);
			if (split[j] == NULL)
				return (ft_free(split));
			i = i + len;
			j++;
		}
		else
			i++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**split;

	words = ft_words(s, c);
	if (s == NULL)
		return (NULL);
	split = malloc((words + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	ft_write(s, c, split);
	split[words] = NULL;
	return (split);
}

// int	main(void)
// {
// 	int i;
// 	char **split;

// 	i = 0;
// 	split = ft_split("awk '{count++} END {print count}'", ' ');
// 	while(split[i] != NULL)
// 	{
// 		printf("[%d]: %s\n", i, split[i]);
// 		i++;
// 	}
// 	return (0);
// }
