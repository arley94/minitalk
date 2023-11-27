/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:29:48 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/09/25 14:51:24 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	n_bytes;	

	s_len = ft_strlen(s);
	if (start < s_len)
	{
		if (s_len - start >= len)
			n_bytes = len;
		else
			n_bytes = s_len - start;
	}
	else
	{
		n_bytes = 0;
		start = 0;
	}
	substr = (char *)malloc(sizeof(char) * (n_bytes + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, n_bytes + 1);
	return (substr);
}
