/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 08:19:48 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 08:28:51 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <unistd.h>
#include <ft_stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <ft_string.h>
#include <mini_assert.h>
#include <ft_stdlib.h>

static char	*g_message;

t_bool
	send_bit(t_bool bit, pid_t pid)
{
	if (bit)
		return (kill(pid, SIGUSR2) == 0);
	return (kill(pid, SIGUSR1) == 0);
}

int
	get_next_bit(void)
{
	static int	bit_pos = 0;
	t_bool		bit;

	if (bit_pos < 0)
		return (-1);
	bit = *g_message & (1 << bit_pos);
	if (bit_pos == 7 && *g_message == '\0')
		bit_pos = -2;
	bit_pos++;
	bit_pos = bit_pos % 8;
	if (bit_pos == 0)
		g_message++;
	return (bit);
}

void
	handler(int sig, siginfo_t *info, void *context)
{
	t_bool	bit;

	(void)sig;
	(void)context;
	bit = get_next_bit();
	if (bit < 0)
		exit(EXIT_SUCCESS);
	mini_assert(send_bit(bit, info->si_pid));
}

static t_bool
	init(void)
{
	struct sigaction	ac;

	ft_memset(&ac, 0, sizeof(struct sigaction));
	if (sigemptyset(&ac.sa_mask) != 0)
		return (FALSE);
	ac.sa_sigaction = handler;
	ac.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &ac, NULL) != 0)
		return (FALSE);
	if (sigaction(SIGUSR2, &ac, NULL) != 0)
		return (FALSE);
	return (TRUE);
}

int
	main(int argc, char **argv)
{
	pid_t	pid;

	mini_assert(argc == 3);
	mini_assert(ft_checked_atoi(argv[1], &pid));
	g_message = argv[2];
	mini_assert(init());
	send_bit(get_next_bit(), pid);
	while (1)
		;
	return (0);
}
