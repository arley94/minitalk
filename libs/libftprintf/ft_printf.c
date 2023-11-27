/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:50:09 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/10/01 11:00:17 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		char_count;

	char_count = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			char_count += ft_print_format(*++str, &ap);
			str++;
		}
		else
			char_count += ft_print_char(*str++);
	}
	va_end(ap);
	return (char_count);
}
