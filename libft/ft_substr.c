/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:49:56 by dmaessen          #+#    #+#             */
/*   Updated: 2022/11/02 15:42:43 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_final_len(char const *s, unsigned int start, size_t len)
{
	size_t	final_len;

	if (start > ft_strlen(s))
		final_len = 0;
	else
		final_len = ft_strlen(s) - start;
	if (final_len > len)
		final_len = len;
	return (final_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	i2;
	size_t	final_len;
	char	*sub;

	final_len = ft_final_len(s, start, len);
	sub = (char *)malloc((final_len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	i = 0;
	i2 = 0;
	while (s[i])
	{
		if (i >= start && i2 < len)
		{
			sub[i2] = s[i];
			i2++;
		}
		i++;
	}
	sub[i2] = '\0';
	return (sub);
}

// int	main(void)
// {
// 	// char const	s[] = "qwerty";

// 	ft_substr("hola", 0, -1);
// 	printf("%s", ft_substr("hola", 0, -1));
// 	return (0);
// }
