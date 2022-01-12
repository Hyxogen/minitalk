#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stream.h"

#ifndef SERVER_BUFFER_SIZE
#define SERVER_BUFFER_SIZE 10
#endif

static t_io_stream g_stream;

bool push_back_bit(bool bit, char *val)
{
	static char byte = 0;
	static int bit_pos = 0;

	byte &= ~(1 << bit_pos);
	byte |= (bit == 1) << bit_pos;
	*val = byte & 0xFF;
	bit_pos++;
	return (!(bit_pos %= 8));
}

bool push_back_byte(char byte)
{
	stream_write(&g_stream, &byte, 1);
	return (byte == '\0');
}

void handler(int sig, siginfo_t *info, void *context)
{
	char val;
	char *str;
	bool done;
	bool print;

	usleep(1);
	print = false;
	if (sig == SIGUSR1)
		done = push_back_bit(false, &val);
	else
		done = push_back_bit(true, &val);
	if (done)
		print = push_back_byte(val);
	if (print)
		stream_flush(&g_stream, 1);
	kill(info->si_pid, SIGUSR2);
}

void init(void)
{
	struct sigaction ac;

	memset(&ac, 0, sizeof(sigaction));
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