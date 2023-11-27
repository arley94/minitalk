/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server _bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:00:03 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/11/27 13:44:19 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static t_rx_state	*get_rx_state(void)
{
	static t_rx_state	rx;

	return (&rx);
}

static void	rx_len_hanlder(int signum, siginfo_t *siginfo, void *ucontext)
{
	t_rx_state			*rx;

	(void) ucontext;
	rx = get_rx_state();
	if (rx->pid_client == 0)
		rx->pid_client = siginfo->si_pid;
	else if (rx->pid_client != 0 && rx->pid_client != siginfo->si_pid)
		return ;
	if (signum == SIGUSR2)
		rx->msg_len = (0x80000000 >> rx->bit_count) | rx->msg_len;
	rx->bit_count++;
	if (rx->bit_count < 32)
		kill(siginfo->si_pid, SIGUSR1);
	else
	{
		rx->bit_count = 0;
		rx->ready = 1;
	}
}

static void	rx_msg_hanlder(int signum, siginfo_t *siginfo, void *ucontext)
{
	t_rx_state			*rx;

	(void) ucontext;
	rx = get_rx_state();
	if (rx->pid_client != siginfo->si_pid)
		return ;
	if (signum == SIGUSR2)
		rx->byte = (0x80 >> rx->bit_count) | rx->byte;
	rx->bit_count++;
	if (rx->bit_count == 8)
	{
		rx->msg[rx->byte_count] = rx->byte;
		rx->bit_count = 0;
		rx->byte = 0;
		rx->byte_count++;
	}
	kill(siginfo->si_pid, SIGUSR1);
}

void	set_sigaction(struct sigaction *act,
	void (*handler)(int, siginfo_t *, void *))
{
	sigemptyset(&(act->sa_mask));
	act->sa_sigaction = handler;
	act->sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, act, NULL);
	sigaction(SIGUSR2, act, NULL);
}

int	main(void)
{
	struct sigaction	act;
	t_rx_state			*rx;

	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		set_sigaction(&act, rx_len_hanlder);
		rx = get_rx_state();
		while (!rx->ready)
			sleep(1);
		rx->msg = malloc(sizeof(char) * (rx->msg_len + 1));
		if (!rx->msg)
			return (ft_printf("Fail allocating memory"), EXIT_FAILURE);
		ft_printf("Rx %d bytes from PID: %d\n", rx->msg_len, rx->pid_client);
		set_sigaction(&act, rx_msg_hanlder);
		kill(rx->pid_client, SIGUSR1);
		while (rx->byte_count < rx->msg_len)
			sleep(1);
		rx->msg[rx->byte_count] = 0;
		ft_printf("%s\n", rx->msg);
		kill(rx->pid_client, SIGUSR2);
		free(rx->msg);
		ft_bzero(rx, sizeof(t_rx_state));
	}
	return (0);
}
