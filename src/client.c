/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:19:07 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/11/27 13:22:15 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	send_byte(unsigned char c)
{
	unsigned char	mask;
	int				shift;
	t_cnx_state		*cnx;
	int				server_ack;

	cnx = get_cnx_state();
	shift = 7;
	while (shift >= 0)
	{
		mask = (0b01 << shift);
		server_ack = check_server_bit_ack();
		if (server_ack < 0)
			return (server_ack);
		cnx->line_busy = 1;
		if (mask & c)
			kill(cnx->server_pid, SIGUSR2);
		else
			kill(cnx->server_pid, SIGUSR1);
		shift--;
	}
	return (server_ack);
}

static int	send_len(unsigned int len)
{
	int	i;
	int	server_ack;

	i = 3;
	while (i >= 0)
	{
		server_ack = send_byte(len >> 8 * i);
		if (server_ack < 0)
			return (server_ack);
		i--;
	}
	return (server_ack);
}

static int	send_msg(char *msg)
{
	int	i;
	int	server_ack;

	i = 0;
	while (msg[i])
	{
		server_ack = send_byte(msg[i]);
		if (server_ack < 0)
			return (server_ack);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cnx_state			*cnx;
	struct sigaction	act;

	if (argc != 3)
		return (ft_printf("Usage: ./client <PID> <MESSAGE>\n"), EXIT_FAILURE);
	cnx = get_cnx_state();
	cnx->server_pid = ft_atoi(argv[1]);
	if (cnx->server_pid <= 0)
		return (ft_printf("[%s] is not a valid PID\n", argv[1]), EXIT_FAILURE);
	sigemptyset(&act.sa_mask);
	act.sa_handler = rx_handler;
	sigaction(SIGUSR1, &act, NULL);
	act.sa_handler = ack_msg_handler;
	sigaction(SIGUSR2, &act, NULL);
	if (send_len(ft_strlen(argv[2])) < 0)
		return (ft_printf("Server is not responding\n"), EXIT_FAILURE);
	if (send_msg(argv[2]) < 0)
		return (ft_printf("Server is not responding\n"), EXIT_FAILURE);
	if (check_server_msg_ack() < 0)
		return (ft_printf("Server timeout sending ack_msg\n"), EXIT_FAILURE);
	ft_printf("Message received by server\n");
	return (EXIT_SUCCESS);
}
