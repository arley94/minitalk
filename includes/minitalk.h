/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:08:02 by acoto-gu          #+#    #+#             */
/*   Updated: 2023/11/27 13:24:20 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../libs/libft/libft.h"
#include "../libs/libftprintf/ft_printf.h"

struct s_cnx_state
{
	int		line_busy;
	int		msg_ack;
	pid_t	server_pid;
};

typedef struct s_cnx_state	t_cnx_state;

struct s_rx_state
{
	unsigned char	byte;
	int				bit_count;
	char			*msg;
	pid_t			pid_client;
	unsigned int	msg_len;
	int				ready;
	unsigned int	byte_count;
};

typedef struct s_rx_state	t_rx_state;

#define MSG_ACK_TIMEOUT_SECONDS 25
#define BIT_ACK_TIMEOUT_USECONDS 100

t_cnx_state	*get_cnx_state(void);
int			check_server_bit_ack(void);
int			check_server_msg_ack(void);
void		rx_handler(int signum);
void		ack_msg_handler(int signum);
