/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:19:07 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/12/05 11:00:10 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	set_sigaction(struct sigaction *act,
	void (*handler)(int))
{
	sigemptyset(&(act->sa_mask));
	act->sa_handler = handler;
	sigaction(SIGUSR1, act, NULL);
	sigaction(SIGUSR2, act, NULL);
}

void	handler(int signum)
{
	t_tx_state	*tx;
	int			end;

	tx = get_tx_state();
	if (signum == SIGUSR1)
		end = send_bits(tx);
	else if (signum == SIGUSR2)
	{
		ft_printf("client: server ended unexpectdly.\n");
		exit(EXIT_FAILURE);
	}
	if (end)
	{
		ft_printf("client: message received by server\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	t_tx_state			*tx;
	struct sigaction	act;

	if (argc != 3 || !ft_str_is_numeric(argv[1]))
		return (ft_printf("Usage: ./client <PID> <MESSAGE>\n"), EXIT_FAILURE);
	tx = get_tx_state();
	tx->server_pid = ft_atoi(argv[1]);
	if (tx->server_pid <= 0)
		return (ft_printf("[%s] is not a valid PID\n", argv[1]), EXIT_FAILURE);
	tx->msg = argv[2];
	tx->msg_len = ft_strlen(argv[2]);
	set_sigaction(&act, handler);
	send_bits(tx);
	while (1)
	{
		pause();
	}
	return (EXIT_SUCCESS);
}
