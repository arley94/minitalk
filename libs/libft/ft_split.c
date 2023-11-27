/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 09:35:09 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/09/25 18:03:53 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	word_count;
	int	i;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word_count++;
		i++;
	}
	return (word_count);
}

static char	**free_arr(char **str_arr, int n_words)
{
	int	i;

	i = 0;
	while (i < n_words)
		free (str_arr[i++]);
	free(str_arr);
	return (0);
}

static char	**split(char **str_arr, char const *s, char c, int n_words)
{
	int	i;
	int	num_words;
	int	w_len;

	i = 0;
	num_words = 0;
	w_len = 0;
	while (num_words < n_words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			w_len++;
		}
		str_arr[num_words] = ft_substr(s, i - w_len, w_len);
		if (!str_arr[num_words])
			return (free_arr(str_arr, num_words));
		w_len = 0;
		num_words++;
	}
	str_arr[num_words] = NULL;
	return (str_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		n_words;

	if (!s)
		return (NULL);
	n_words = count_words(s, c);
	ptr = malloc(sizeof(char *) * (n_words + 1));
	if (!ptr)
		return (NULL);
	ptr = split(ptr, s, c, n_words);
	return (ptr);
}
