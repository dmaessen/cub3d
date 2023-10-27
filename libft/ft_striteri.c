/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:00:29 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/19 11:51:39 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, s + i);
		i++;
	}
}

// void	f(unsigned int i, char *a)
// {
// 	printf("%s \n", a);
// 	printf("%d \n", i);
// }

// int	main(void)
// {
// 	char s[100] = "654";
// 	ft_striteri(s, f);
// }
