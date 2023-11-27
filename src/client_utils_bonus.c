/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:51:50 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/11/27 13:45:09 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_cnx_state	*get_cnx_state(void)
{
	static t_cnx_state	cnx_state;

	return (&cnx_state);
}

int	check_server_bit_ack(void)
{
	t_cnx_state	*cnx;
	int			useconds;

	cnx = get_cnx_state();
	useconds = 0;
	while (cnx->line_busy == 1 && useconds < BIT_ACK_TIMEOUT_USECONDS)
	{
		usleep(1);
		useconds++;
	}
	if (cnx->line_busy == 1)
		return (-1);
	return (0);
}

int	check_server_msg_ack(void)
{
	t_cnx_state	*cnx;
	int			seconds;

	cnx = get_cnx_state();
	seconds = 0;
	while (cnx->msg_ack == 0 && seconds < MSG_ACK_TIMEOUT_SECONDS)
	{
		sleep(1);
		seconds++;
	}
	if (cnx->msg_ack == 0)
		return (-1);
	return (0);
}

void	rx_handler(int signum)
{
	t_cnx_state	*cnx;

	if (signum == SIGUSR1)
	{
		cnx = get_cnx_state();
		cnx->line_busy = 0;
	}
}

void	ack_msg_handler(int signum)
{
	t_cnx_state			*cnx;

	if (signum == SIGUSR2)
	{
		cnx = get_cnx_state();
		cnx->msg_ack = 1;
	}
}
