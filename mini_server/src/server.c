#define _POSIC_C_SOURCE 199309L
#define _XOPEN_SOURCE 500
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <ft_string.h>
#include <ft_stdbool.h>
#include <ft_sstream.h>
#include <mini_assert.h>

#ifndef SERVER_BUFFER_SIZE
#define SERVER_BUFFER_SIZE 10
#endif

static t_sstream g_stream;

ft_bool push_back_bit(ft_bool bit, char *val)
{
	static char byte = 0;
	static int bit_pos = 0;

	byte &= ~(1 << bit_pos);
	byte |= (bit == 1) << bit_pos;
	*val = byte & 0xFF;
	bit_pos++;
	return (!(bit_pos %= 8));
}

ft_bool push_back_byte(char byte)
{
	mini_assert(stream_write(&g_stream, &byte, 1));
	return (byte == '\0');
}

void handler(int sig, siginfo_t *info, void *context)
{
	char val;
	ft_bool done;
	ft_bool print;

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

ft_bool init(void)
{
	struct sigaction ac;

	ft_memset(&ac, 0, sizeof(struct sigaction));
	if (sigemptyset(&ac.sa_mask) == -1)
		return (FALSE);
	ac.sa_sigaction = handler;
	ac.sa_flags = SA_SIGINFO;/*Bitwise or equals mag niet?*/
	if (sigaction(SIGUSR1, &ac, NULL) == -1)
		return (FALSE);
	if (sigaction(SIGUSR2, &ac, NULL) == -1)
		return (FALSE);
	if (stream_init(&g_stream, SERVER_BUFFER_SIZE) == FALSE)
		return (FALSE);
	return (TRUE);
}

int main(void)
{
	pid_t pid = getpid();

	mini_assert(init());
	printf("pid:%d\n", pid);
	
	while (1)
	{

	}
}
