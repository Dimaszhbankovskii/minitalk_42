#include "../includes/minitalk.h"

t_get	g_mess;

static void	write_pid(void)
{
	ft_putstr_fd("Server pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
}

static char	*str_add_chr(char *mess, char chr)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (ft_strlen(mess) + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (mess && mess[i])
	{
		str[i] = mess[i];
		i++;
	}
	str[i] = chr;
	str[i + 1] = '\0';
	free (mess);
	return (str);
}

static void	make_message(void)
{
	if (!g_mess.chr)
	{
		g_mess.mess = str_add_chr(g_mess.mess, '\n');
		ft_putstr_fd(g_mess.mess, 1);
		free (g_mess.mess);
		g_mess.mess = NULL;
		g_mess.start = 1;
	}
	else
		g_mess.mess = str_add_chr(g_mess.mess, g_mess.chr);
	g_mess.chr = 0;
	g_mess.size = 7;
}

static void	get_message(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	if (signum == SIGUSR1 && g_mess.start == 1)
	{
		g_mess.start = 0;
		if (kill(info->si_pid, SIGUSR1) < 0)
			ft_putstr_fd("error: connect with client\n", 1);
		return ;
	}
	if (signum == SIGUSR1)
		g_mess.chr += (1 << g_mess.size);
	g_mess.size--;
	if (g_mess.size < 0)
	{
		make_message();
		if (g_mess.start == 1)
			return ;
	}
	if (kill(info->si_pid, SIGUSR1) < 0)
		ft_putstr_fd("error kill SIGUSR1\n", 1);
}

int	main(void)
{
	struct sigaction	get_mess;

	write_pid();
	get_mess.sa_flags = SA_SIGINFO;
	get_mess.sa_sigaction = &get_message;
	if (sigaction(SIGUSR1, &get_mess, NULL) < 0)
		ft_putstr_fd("error sigaction SIGUSR1\n", 1);
	if (sigaction(SIGUSR2, &get_mess, NULL) < 0)
		ft_putstr_fd("error sigaction SIGUSR2\n", 1);
	g_mess.chr = 0;
	g_mess.mess = NULL;
	g_mess.size = 7;
	g_mess.start = 1;
	while (1)
		pause();
	return (0);
}
