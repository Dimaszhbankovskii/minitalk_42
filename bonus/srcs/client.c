#include "../includes/minitalk.h"

int	g_flag;

static int	input_validation(char *pid)
{
	while (*pid)
	{
		if (!(ft_isdigit(*pid)))
			return (0);
		pid++;
	}
	return (1);
}

static void	change_flag(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	g_flag = 0;
}

static void	wait_send(void)
{
	struct sigaction	send;

	g_flag = 1;
	send.sa_flags = SA_SIGINFO;
	send.sa_sigaction = &change_flag;
	if (sigaction(SIGUSR1, &send, NULL) < 0)
		ft_putstr_fd("Error sigaction SIGUSR1\n", 1);
	while (g_flag)
		sleep(1);
}

static void	send_message(int pid, char chr)
{
	int	size;

	size = 0;
	while (size < 8)
	{
		if ((chr >> size) & 1)
		{
			printf("1");
			if (kill(pid, SIGUSR1) < 0)
				ft_putstr_fd("Error kill SIGUSR1\n", 1);
		}
		if (!((chr >> size) & 1))
		{
			printf("0");
			if (kill(pid, SIGUSR2) < 0)
				ft_putstr_fd("Error kill SIGUSR2\n", 1);
		}
		wait_send();
		size++;
	}
	printf("\ncheck client\n");

}

int main(int argc, char **argv)
{
	int		pid;
	char	*mess;
	int		i;

	if (argc != 3 || !input_validation(argv[1]))
		ft_putstr_fd("error: uninvalid pid or no message to send\n", 1);
	else
	{
		pid = ft_atoi(argv[1]);
		mess = argv[2];
		i = 0;
		while (mess[i])
		{
			send_message(pid, mess[i]);
			i++;
		}
		send_message(pid, mess[i]);
	}
	return (0);
}
