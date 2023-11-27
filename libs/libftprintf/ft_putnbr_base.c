/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:24:52 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/09/30 23:32:40 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(int nbr, char *base)
{
	long int	base_len;
	long int	nb;
	int			char_count;

	char_count = 0;
	nb = (long int) nbr;
	base_len = (long int) ft_strlen(base);
	if (base_len >= 2)
	{
		if (nb < 0)
		{
			write(1, "-", 1);
			nb = nb * -1;
			char_count++;
		}
		if (nb >= base_len)
			char_count += ft_putnbr_base(nb / base_len, base);
		write(1, base + (nb % base_len), 1);
		return (1 + char_count);
	}
	return (0);
}

int	ft_putnbr_base_u(unsigned long int nb, char *base)
{
	unsigned long int	base_len;
	int					char_count;

	char_count = 0;
	base_len = (long int) ft_strlen(base);
	if (base_len >= 2)
	{
		if (nb >= base_len)
			char_count += ft_putnbr_base_u(nb / base_len, base);
		write(1, base + (nb % base_len), 1);
		return (1 + char_count);
	}
	return (0);
}
