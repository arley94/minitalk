/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 08:56:35 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/10/01 11:01:49 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

/* ************************************************************************** */
/*                          FUNCTIONS PROTOTYPES                              */
/* ************************************************************************** */

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_printf(const char *str, ...);
int		ft_print_char(char c);
int		ft_print_str(char *s);
int		ft_putnbr_base(int nbr, char *base);
int		ft_putnbr_base_u(unsigned long int nb, char *base);
int		ft_print_decimal(int nb);
int		ft_print_u(unsigned int nb);
int		ft_print_hex_l(unsigned int nb);
int		ft_print_hex_u(unsigned int nb);
int		ft_print_p(void *p);
int		ft_print_format(char c, va_list *ap);

#endif