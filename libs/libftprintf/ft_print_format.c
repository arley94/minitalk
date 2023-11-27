/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:36:39 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/10/01 11:01:23 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format(char c, va_list *ap)
{
	int		char_count;

	char_count = 0;
	if (c == 'c')
		char_count = ft_print_char((char) va_arg(*ap, int));
	else if (c == 's')
		char_count = ft_print_str(va_arg(*ap, char *));
	else if (c == 'p')
		char_count = ft_print_p(va_arg(*ap, void *));
	else if (c == 'd' || c == 'i')
		char_count = ft_print_decimal(va_arg(*ap, int));
	else if (c == 'u')
		char_count = ft_print_u(va_arg(*ap, unsigned int));
	else if (c == 'x')
		char_count = ft_print_hex_l(va_arg(*ap, unsigned int));
	else if (c == 'X')
		char_count = ft_print_hex_u(va_arg(*ap, unsigned int));
	else if (c == '%')
		char_count = (ft_print_char('%'));
	return (char_count);
}
