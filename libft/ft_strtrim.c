/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:30:55 by dmaessen          #+#    #+#             */
/*   Updated: 2022/11/02 13:35:56 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*trim;

	i = 0;
	len = ft_strlen(s1);
	if (s1 == NULL || set == NULL)
		return (0);
	while (s1[i] && ft_strchr(set, s1[i]) != 0)
		i++;
	while (ft_strrchr(set, s1[len]) != 0 && len > i)
		len--;
	trim = (char *)malloc((len - i + 2) * sizeof(char));
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, &s1[i], len - i + 2);
	return (trim);
}

// int	main(void)
// {
// 	char const	s1[100] = "adfft 25tgfdfdfffad";

// 	printf("%s", ft_strtrim(s1, "ad"));
// 	return (0);
// }
