/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:00:03 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/12/06 13:35:20 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	error_server(t_rx_state *rx)
{
	ft_printf("server: unexpected error.\n");
	kill(rx->pid_client, SIGUSR2);
	if (rx->msg)
		free (rx->msg);
	exit(EXIT_FAILURE);
}

static int	rx_msg(t_rx_state *rx, int signum)
{
	if (rx->bit_count < 32)
	{
		if (signum == SIGUSR2)
			rx->msg_len |= (0x80000000 >> rx->bit_count);
		if (rx->bit_count == 31)
		{
			rx->msg = malloc(rx->msg_len + 1);
			if (!rx->msg)
				error_server(rx);
			ft_bzero(rx->msg, rx->msg_len);
			ft_printf("Rx %d bytes from id:%d\n", rx->msg_len, rx->pid_client);
		}
	}
	else
	{
		if (signum == SIGUSR2)
			rx->msg[(rx->bit_count - 32) / 8] |= 0x80
				>> ((rx->bit_count - 32) % 8);
		if (((rx->bit_count - 32) + 1) / 8 == rx->msg_len)
			return (1);
	}
	rx->bit_count++;
	return (0);
}

static void	handler(int signum, siginfo_t *siginfo, void *ucontext)
{
	t_rx_state	*rx;
	int			end;

	(void) ucontext;
	rx = get_rx_state();
	if (!rx->pid_client && siginfo->si_pid)
		rx->pid_client = siginfo->si_pid;
	if (siginfo->si_pid && rx->pid_client != siginfo->si_pid)
	{
		kill(siginfo->si_pid, SIGUSR2);
		return ;
	}
	end = 0;
	end = rx_msg(rx, signum);
	if (end)
	{
		rx->msg[rx->msg_len] = 0;
		ft_printf("%s\n", rx->msg);
		if (rx->msg)
			free (rx->msg);
		kill (rx->pid_client, SIGUSR1);
		ft_bzero(rx, sizeof(t_rx_state));
	}
	else if (kill(rx->pid_client, SIGUSR1) == -1)
		error_server(rx);
}

int	main(void)
{
	struct sigaction	act;
	sigset_t			block_mask;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	act.sa_flags = SA_RESTART | SA_SIGINFO;
	act.sa_mask = block_mask;
	act.sa_sigaction = handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
