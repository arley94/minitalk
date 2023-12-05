/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:51:50 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/12/05 11:13:17 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_tx_state	*get_tx_state(void)
{
	static t_tx_state	tx_state;

	return (&tx_state);
}

t_rx_state	*get_rx_state(void)
{
	static t_rx_state	rx;

	return (&rx);
}

void	error_client(void)
{
	ft_printf("client: unexpected error.\n");
	exit(EXIT_FAILURE);
}

void	send_len(t_tx_state *tx)
{
	if (tx->msg_len & (0x80000000 >> (tx->bits_count % 32)))
	{
		if (kill(tx->server_pid, SIGUSR2) == -1)
			error_client();
	}
	else if (kill(tx->server_pid, SIGUSR1) == -1)
		error_client();
	tx->bits_count++;
}

int	send_bits(t_tx_state *tx)
{
	int	msg_bits;

	msg_bits = tx->bits_count - 32;
	if (tx->bits_count < 32)
	{
		send_len(tx);
		return (0);
	}
	else if (tx->msg[msg_bits / 8])
	{
		if (tx->msg[msg_bits / 8] & (0x80 >> (msg_bits % 8)))
		{
			if (kill(tx->server_pid, SIGUSR2) == -1)
				error_client();
		}
		else if (kill(tx->server_pid, SIGUSR1) == -1)
			error_client();
		tx->bits_count++;
		return (0);
	}
	return (1);
}
