/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:51:14 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/09/25 13:19:14 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	my_c;
	int		s_len;

	s_len = ft_strlen(s);
	my_c = (char) c;
	if (my_c == '\0')
		return ((char *) s + s_len);
	while (s_len-- > 0)
		if (s[s_len] == my_c)
			return ((char *) s + s_len);
	return (NULL);
}
