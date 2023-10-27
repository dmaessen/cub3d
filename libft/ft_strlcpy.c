/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:02:31 by dmaessen          #+#    #+#             */
/*   Updated: 2022/11/01 10:28:54 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srcsize;

	srcsize = 0;
	while (src[srcsize] != '\0')
		srcsize++;
	if (dstsize == 0)
		return (srcsize);
	i = 0;
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srcsize);
}

// int main(void)
// {
// 	char	dst[15] = {""};
// 	printf("%zu mine\n", ft_strlcpy(dst, "", 15));
// 	printf("%p mine\n", dst);
// 	printf("%zu THEIRS\n", strlcpy(dst, "", 15));
// 	printf("%p THEIRS", dst);
// 	return (0);
// }
