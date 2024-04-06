/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:27:43 by tsaari            #+#    #+#             */
/*   Updated: 2024/04/06 14:21:47 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	string_length(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

static size_t	count_strings(const char *so, char c)
{
	size_t	strings;
	char	*s;

	s = (char *)so;
	strings = 0;
	while (*s != '\0')
	{
		if (*s == '\'')
		{
			strings++;
			s++;
			while (*s != '\'')
				s++;
		}
		else if (*s == c)
		{
			strings++;
			while (*s == c && *s == '\0')
				s++;
		}
		s++;
	}
	return (strings);
}

static char	*split_word(char *s, char **return_array, char c, int i)
{
	int	len;

	len = string_length(s, c);
	return_array[i] = ft_substr(s, 0, len);
	if (return_array[i] == NULL)
		ft_free(return_array);
	s += len;
	while (*s == c)
		s++;
	return (s);
}

static char	*split_single_quotes(char *s, char **return_array, char x, int i)
{
	int	len;

	s++;
	len = string_length(s, x);
	return_array[i] = ft_substr(s, 0, len);
	if (return_array[i] == NULL)
		free(return_array);
	s += len;
	return (s);
}

char	**ft_split_pipex(const char *so, char c)
{
	size_t	strings;
	size_t	i;
	char	**return_array;
	char	*s;
	char	x;

	s = (char *)so;
	i = 0;
	x = '\'';
	strings = count_strings(s, c);
	return_array = (char **)malloc((strings + 1) * sizeof(char *));
	if (!return_array)
		return (NULL);
	while (i < strings)
	{
		if (*s != c)
			s = split_word(s, return_array, c, i++);
		if (*s == x)
			s = split_single_quotes(s, return_array, x, i++);
		s++;
	}
	return_array[i] = 0;
	return (return_array);
}
