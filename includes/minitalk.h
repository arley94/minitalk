/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:08:02 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/12/05 11:08:56 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "../libs/libft/libft.h"
# include "../libs/libftprintf/ft_printf.h"

struct s_tx_state
{
	char	*msg;
	int		msg_len;
	int		bits_count;
	pid_t	server_pid;
};

typedef struct s_tx_state	t_tx_state;

struct s_rx_state
{
	int		bit_count;
	char	*msg;
	pid_t	pid_client;
	int		msg_len;
};

typedef struct s_rx_state	t_rx_state;

t_tx_state	*get_tx_state(void);
void		send_len(t_tx_state *tx);
int			send_bits(t_tx_state *tx);
t_rx_state	*get_rx_state(void);
void		error_client(void);

#endif