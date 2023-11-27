/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:30:49 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/09/25 20:52:46 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_char(unsigned long number)
{
	size_t	count;

	count = 1;
	while (number >= 10)
	{
		number = number / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t			n_chars;
	char			*ptr;
	long int		number;
	unsigned int	sign;

	sign = 0;
	number = (long)n;
	if (number < 0)
	{
		sign = 1;
		number = number * -1;
	}
	n_chars = count_char((unsigned long)number);
	ptr = malloc(sizeof(char) * (n_chars + sign + 1));
	if (!ptr)
		return (NULL);
	if (sign)
		ptr[0] = '-';
	ptr[n_chars + sign] = '\0';
	while (n_chars > 0)
	{
		ptr[n_chars-- + sign - 1] = number % 10 + '0';
		number = number / 10;
	}
	return (ptr);
}
