#include "../includes/minitalk.h"

int	g_flag_wait;

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
	g_flag_wait = 0;
}

static void	end_program(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	printf("ens\n");
	exit (0);
}

static void	wait_send(void)
{
	struct sigaction	send;
	struct sigaction	end;

	g_flag_wait = 1;
	send.sa_flags = SA_SIGINFO;
	send.sa_sigaction = &change_flag;
	end.sa_flags = SA_SIGINFO;
	end.sa_sigaction = &end_program;
	if (sigaction(SIGUSR1, &send, NULL) < 0)
		ft_putstr_fd("Error sigaction SIGUSR1\n", 1);
	if (sigaction(SIGUSR2, &end, NULL) < 0)
		ft_putstr_fd("Error sigaction SIGUSR1\n", 1);
	while (g_flag_wait)
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
			if (kill(pid, SIGUSR1) < 0)
				ft_putstr_fd("Error kill SIGUSR1\n", 1);
		}
		if (!((chr >> size) & 1))
		{
			if (kill(pid, SIGUSR2) < 0)
				ft_putstr_fd("Error kill SIGUSR2\n", 1);
		}
		wait_send();
		size++;
	}
}

int main(int argc, char **argv)
{
	int		pid;
	char	*mess;
	int		i;

	if (argc == 3 && input_validation(argv[1]))
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
	else
		ft_putstr_fd("error input\n", 1);
	return (0);
}
