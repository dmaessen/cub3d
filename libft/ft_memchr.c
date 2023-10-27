/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:27:32 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/20 15:20:19 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (n > 0)
	{
		if (str[i] == (unsigned char)c)
		{
			return (&str[i]);
		}
		i++;
		n--;
	}
	return (0);
}

// int	main(void)
// {
// 	const char	s[40] = "Everyth1ing h25-else";
// 	int	c = '-';

// 	printf("%s \n", ft_memchr(s, c, 10));
// 	printf("%s", memchr(s, c, 10));
// }
