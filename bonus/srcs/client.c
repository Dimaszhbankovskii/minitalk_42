#include "../includes/minitalk.h"

t_send	g_mess;

static void	error_mess(void)
{
	ft_putstr_fd("error: invalid pid or date\n", 1);
	ft_putstr_fd("try again\n", 1);
	exit (0);
}

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

static void	send(int signum, siginfo_t *info, void *context)
{
	char	c;

	(void)signum;
	(void)context;
	c = *g_mess.mess;
	if (c >> g_mess.size & 1)
		if (kill(info->si_pid, SIGUSR1) < 0)
			ft_putstr_fd("error kill SIGUSR1\n", 1);
	if (!(c >> g_mess.size & 1))
		if (kill(info->si_pid, SIGUSR2) < 0)
			ft_putstr_fd("error kill SIGUSR2\n", 1);
	if (!g_mess.size)
	{
		if (!c)
			exit(0);
		g_mess.size = 7;
		g_mess.mess++;
	}
	else
		g_mess.size--;
}

int	main(int argc, char **argv)
{
	struct sigaction	action;

	if (argc != 3 || !input_validation(argv[1]))
		error_mess();
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &send;
	if (sigaction(SIGUSR1, &action, NULL) < 0)
		ft_putstr_fd("error sigaction SIGUSR1\n", 1);
	g_mess.pid = ft_atoi(argv[1]);
	g_mess.mess = argv[2];
	g_mess.size = 7;
	if (kill(g_mess.pid, SIGUSR1) < 0)
	{
		ft_putstr_fd("error: connect with server\n", 1);
		return (-1);
	}
	while (1)
		pause();
	return (0);
}
