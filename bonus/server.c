#include "minitalk.h"

t_symbol	symbol;

static void	WritePid(void)
{
	ft_putstr_fd("Server pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
}

void	get_bit(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1 && symbol.start == 1)
	{
		symbol.start = 0;
		kill(info->si_pid, SIGUSR1);
		return ;
	}
	if (signum == SIGUSR1)
	{
		symbol.chr += (1 << symbol.size);
		symbol.size--;
	}
	else if (signum == SIGUSR2)
		symbol.size--;
	if (symbol.size < 0)
	{
		ft_putchar_fd(symbol.chr, 1);
		if (!symbol.chr)
		{
			symbol.chr = 0;
			symbol.size = 7;
			symbol.start = 1;
			ft_putchar_fd('\n', 1);
			return ;
		}
		symbol.chr = 0;
		symbol.size = 7;
	}
	kill(info->si_pid, SIGUSR1);
}

int		main(void)
{
	struct sigaction	get;

	WritePid();
	get.__sigaction_u.__sa_sigaction = get_bit;
	get.sa_flags = SA_SIGINFO;
	symbol.chr = 0;
	symbol.size = 7;
	symbol.start = 1;
	if (sigaction(SIGUSR1, &get, NULL) < 0)
		ft_putstr_fd("Error sigaction SIGUSR1\n", 1);
	if (sigaction(SIGUSR2, &get, NULL) < 0)
		ft_putstr_fd("Error sigaction SIGUSR2\n", 1);
	while (1)
		pause();
	return (0);
}
