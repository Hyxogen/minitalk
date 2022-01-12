#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static char *g_message;
static size_t g_bits_left;

void send_bit(bool bit, pid_t pid)
{
	int success;

	write(1, "Send bit...", 12);
	if (bit)
		success = kill(pid, SIGUSR2);
	else
		success = kill(pid, SIGUSR1);
	if (success == 0)
		write(1, "Success\n", 9);
	else
		write(1, "Failed\n", 8);
}

bool get_next_bit()
{
	static int bit_pos = 0;
	bool bit;
	bit = *g_message & (1 << bit_pos);
	bit_pos = ++bit_pos % 8;
	if (bit_pos == 0)
		g_message++;
	g_bits_left--;
	return (bit);
}

void handler(int sig, siginfo_t *info, void *context)
{
	static int bit_pos = 0;
	bool bit;

	if (g_bits_left == 0)
		exit(EXIT_SUCCESS);
	bit = get_next_bit();
	send_bit(bit, info->si_pid);
}

int main(int argc, char **argv)
{
	pid_t pid = atoi(argv[1]);

	struct sigaction ac;
	memset(&ac, 0, sizeof(sigaction));
	sigemptyset(&ac.sa_mask);
	ac.sa_sigaction = handler;
	ac.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &ac, NULL);
	sigaction(SIGUSR2, &ac, NULL);
	g_message = argv[2];
	g_bits_left = (strlen(argv[2]) + 1) * 8;

	send_bit(get_next_bit(), pid);

	while (1)
	{

	}
	return (0);
}
