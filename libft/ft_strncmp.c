/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 19:47:29 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/11 15:10:42 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char const *str1, char const *str2, long n)
{
	size_t	len1;
	long	i;

	if (n == 0 || (str1 == NULL && str2 == NULL))
		return (1);
	if (str1 == NULL || str2 == NULL)
		return (0);
	if (n < 0)
	{
		len1 = ft_strlen(str1);
		if (len1 != ft_strlen(str2))
			return (0);
		n = (int)len1;
	}
	i = 0;
	while (i < n && str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		++i;
	}
	return (1);
}
