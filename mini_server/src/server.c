/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 08:19:02 by dmeijer       #+#    #+#                 */
/*   Updated: 2022/01/17 08:28:51 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <ft_string.h>
#include <ft_stdbool.h>
#include <ft_sstream.h>
#include <mini_assert.h>
#include <ft_stdio.h>

#ifndef SERVER_BUFFER_SIZE
# define SERVER_BUFFER_SIZE 1024
#endif

static t_sstream	g_stream;

t_bool
	push_back_bit(t_bool bit, char *val)
{
	static char	byte = 0;
	static int	bit_pos = 0;

	byte &= ~(1 << bit_pos);
	byte |= (bit == 1) << bit_pos;
	*val = byte & 0xFF;
	bit_pos++;
	return (!(bit_pos %= 8));
}

t_bool
	push_back_byte(char byte)
{
	mini_assert(stream_write(&g_stream, &byte, 1));
	return (byte == '\0');
}

void
	handler(int sig, siginfo_t *info, void *context)
{
	char	val;
	t_bool	done;
	t_bool	print;

	(void)context;
	mini_assert(usleep(1) == 0);
	print = FALSE;
	if (sig == SIGUSR1)
		done = push_back_bit(FALSE, &val);
	else
		done = push_back_bit(TRUE, &val);
	if (done)
		print = push_back_byte(val);
	if (print)
		mini_assert(stream_flush(&g_stream, 1));
	mini_assert(kill(info->si_pid, SIGUSR2) == 0);
}

t_bool
	init(void)
{
	struct sigaction	ac;

	ft_memset(&ac, 0, sizeof(struct sigaction));
	if (sigemptyset(&ac.sa_mask) == -1)
		return (FALSE);
	ac.sa_sigaction = handler;
	ac.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &ac, NULL) == -1)
		return (FALSE);
	if (sigaction(SIGUSR2, &ac, NULL) == -1)
		return (FALSE);
	if (stream_init(&g_stream, SERVER_BUFFER_SIZE) == FALSE)
		return (FALSE);
	return (TRUE);
}

int
	main(void)
{
	pid_t	pid;

	pid = getpid();
	mini_assert(init());
	ft_putstr_fd(STDIN_FILENO, "pid:");
	ft_putnbr_fd(STDOUT_FILENO, pid);
	ft_putchar_fd(STDOUT_FILENO, '\n');
	while (1)
		;
	return (0);
}
