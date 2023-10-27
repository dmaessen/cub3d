/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:54:16 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/19 11:52:18 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		c = (c -32);
	}
	return (c);
}

// int	main(void)
// {
// 	int	c;

// 	c = 'i';
// 	ft_toupper(c);
// 	printf("%d \n", ft_toupper(c));
// 	printf("%d", toupper(c));
// 	return (0);
// }
