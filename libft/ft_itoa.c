/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:11:17 by tsaari            #+#    #+#             */
/*   Updated: 2023/11/28 10:38:42 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrofdigits(int n)
{
	int	x;

	x = 0;
	while (n != 0)
	{
		x++;
		n = n / 10;
	}
	return (x);
}

static char	*allocate(int len)
{
	char	*ret;

	ret = (char *)ft_calloc(len, sizeof(char));
	if (!ret)
	{
		free (ret);
		return (0);
	}
	return (ret);
}

static char	*makearray(int n, int neg)
{
	char	*ret;
	int		len;

	len = nbrofdigits(n);
	if (neg == -1)
	{
		ret = allocate(len + 2);
		if (!ret)
		{
			free(ret);
			return (0);
		}
		ret[0] = '-';
		len++;
	}
	else
		ret = allocate(len + 1);
	if (!ret)
	{
		free(ret);
		return (0);
	}
		
	ret[len] = '\0';
	len--;
	while (n > 0)
	{
		ret[len] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		neg;

	neg = 1;
	if (n == -2147483648)
	{
		ret = allocate(12);
		if (!ret)
		{
			free(ret);
			return (0);
		}
		ft_strlcpy (ret, "-2147483648", 12);
		return (ret);
	}
	if (n == 0)
	{
		ret = allocate(2);
		if (!ret)
		{
			free(ret);
			return (NULL);
		}
		ft_strlcpy (ret, "0", 2);
		return (ret);
	}
	if (n < 0)
		neg = -1;
	n *= neg;
	ret = makearray(n, neg);
	if (!ret)
	{
		free(ret);
		return (0);
	}
	return (ret);
}
