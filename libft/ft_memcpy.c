/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:40:45 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/27 16:34:31 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if (dst2 == NULL && src2 == NULL)
		return (0);
	i = 0;
	while (n > 0)
	{
		dst2[i] = src2[i];
		i++;
		n--;
	}
	return (dst);
}

// int	main(void)
// {
// 	// char	src[100] = {""};
// 	char	dst[100] = {""};

// 	ft_memcpy(((void *)0), ((void *)0), 3);
// 	printf("%s \n", dst);
// 	printf("%s", dst, memcpy(((void *)0), ((void *)0), 3));
// 	return (0);
// }
