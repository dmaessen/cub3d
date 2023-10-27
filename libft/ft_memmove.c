/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:58:45 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/27 16:36:01 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst2;
	char	*src2;

	dst2 = (char *)dst;
	src2 = (char *)src;
	if (dst2 == NULL && src2 == NULL)
		return (0);
	i = 0;
	if (dst2 > src2)
	{
		while (len-- > 0)
			dst2[len] = src2[len];
	}
	else
	{
		while (i < len)
		{
			dst2[i] = src2[i];
			i++;
		}
	}
	return (dst);
}

// int	main(void)
// {
// 	char	src[100] = {"4lsok"};
// 	char	dst[100] = {"adsfgsss"};
// 	char	s[100] = {"4lsok"};
// 	char	d[100] = {"adsfgsss"};

// 	ft_memmove(dst, src, 0);
// 	printf("%s \n", dst);
// 	printf("%s", d, memmove(d, s, 0));
// 	return (0);
// }
