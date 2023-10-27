/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:17:16 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/27 10:37:50 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_put(int n1, char *s, size_t len)
{
	while (n1 != 0)
	{
		s[len] = ((n1 % 10) + '0');
		n1 = (n1 / 10);
		len--;
	}
}

char	*ft_itoa(int n)
{
	size_t		len;
	long long	n1;
	char		*s;

	len = ft_len(n);
	n1 = n;
	if (n1 == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n1 == 0)
		return (ft_strdup("0"));
	s = malloc((len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	s[len--] = '\0';
	if (n1 < 0)
	{
		s[0] = '-';
		n1 *= -1;
	}
	ft_put(n1, s, len);
	return (s);
}

// int	main(void)
// {
// 	printf("%s", ft_itoa(21448));
// 	return (0);
// }
