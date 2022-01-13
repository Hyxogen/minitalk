#define _POSIX_C_SOURCE 199309L
#include <sys/types.h>
#include <unistd.h>
#include <ft_stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <ft_string.h>

static char *g_message;
static size_t g_bits_left;

void send_bit(ft_bool bit, pid_t pid)
{
	int success;

	if (bit)
		success = kill(pid, SIGUSR2);
	else
		success = kill(pid, SIGUSR1);
	(void)success;
}

ft_bool get_next_bit()
{
	static int bit_pos = 0;
	ft_bool bit;
	bit = *g_message & (1 << bit_pos);
	bit_pos++;
	bit_pos = bit_pos % 8;
	if (bit_pos == 0)
		g_message++;
	g_bits_left--;
	return (bit);
}

void handler(int sig, siginfo_t *info, void *context)
{
	ft_bool bit;

	(void)sig;
	(void)context;
	if (g_bits_left == 0)
		exit(EXIT_SUCCESS);
	bit = get_next_bit();
	send_bit(bit, info->si_pid);
}

int main(int argc, char **argv)
{
	pid_t pid = atoi(argv[1]);
	struct sigaction ac;

	(void)argc;
	ft_memset(&ac, 0, sizeof(struct sigaction));
	sigemptyset(&ac.sa_mask);
	ac.sa_sigaction = handler;
	ac.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &ac, NULL);
	sigaction(SIGUSR2, &ac, NULL);
	g_message = argv[2];
	g_bits_left = (ft_strlen(argv[2]) + 1) * 8;

	send_bit(get_next_bit(), pid);

	while (1)
	{

	}
	return (0);
}
