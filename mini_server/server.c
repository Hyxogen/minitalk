#define _POSIC_C_SOURCE 199309L
#define _XOPEN_SOURCE 500
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <ft_string.h>
#include <ft_stdbool.h>
#include <ft_sstream.h>

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
	stream_write(&g_stream, &byte, 1);
	return (byte == '\0');
}

void handler(int sig, siginfo_t *info, void *context)
{
	char val;
	ft_bool done;
	ft_bool print;

	(void)context;
	usleep(1);
	print = FALSE;
	if (sig == SIGUSR1)
		done = push_back_bit(FALSE, &val);
	else
		done = push_back_bit(TRUE, &val);
	if (done)
		print = push_back_byte(val);
	if (print)
		stream_flush(&g_stream, 1);
	kill(info->si_pid, SIGUSR2);
}

void init(void)
{
	struct sigaction ac;

	ft_memset(&ac, 0, sizeof(struct sigaction));
	sigemptyset(&ac.sa_mask);
	ac.sa_sigaction = handler;
	ac.sa_flags = SA_SIGINFO;/*Bitwise or equals mag niet?*/
	sigaction(SIGUSR1, &ac, NULL);
	sigaction(SIGUSR2, &ac, NULL);

	stream_init(&g_stream, SERVER_BUFFER_SIZE);
}

int main(void)
{
	pid_t pid = getpid();

	init();
	printf("pid:%d\n", pid);
	
	while (1)
	{

	}
}
