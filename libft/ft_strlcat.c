/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:05:42 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/27 14:43:45 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	i2;
	size_t	ls;
	size_t	ld;

	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	i = 0;
	if (ld < dstsize)
		i = ls + ld;
	else
		i = ls + dstsize;
	i2 = 0;
	while (ld + i2 + 1 < dstsize && src[i2] != '\0')
	{
		dst[ld + i2] = src[i2];
		i2++;
	}
	dst[ld + i2] = '\0';
	return (i);
}

// int	main(void)
// {
// 	// char dst[100] = {"hey"};
// 	// char d[100] = {"hey"};
// 	ft_strlcat("hey", "remove", 0);
// 	printf("%s MINE\n", "hey");
// 	printf("%zu MINE\n", ft_strlcat("hey", "remove", 0));
// 	printf("%lu \n", strlcat("hey", "remove", 0));
// 	printf("%zu \n", strlcat("hey", "remove", 0));
// 	return (0);
// }
