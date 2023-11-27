/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:09:23 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/09/25 12:00:54 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (n == 0 || dest == src)
		return (dest);
	d = (char *) dest;
	s = (char *) src;
	if (s > d)
		while (n-- > 0)
			*d++ = *s++;
	else
		while (n-- > 0)
			*(d + n) = *(s + n);
	return (dest);
}
