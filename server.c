#include "minitalk.h"

t_symbol	symbol;

// void	get_message(int sig)
// {
// 	if (sig == SIGUSR1)
// 	{
// 		symbol.chr += (1 << symbol.size);
// 		symbol.size--;
// 	}
// 	else if (sig == SIGUSR2)
// 		symbol.size--;
// 	if (symbol.size == -1)
// 	{
// 		ft_putchar_fd(symbol.chr, 1);
// 		if (!symbol.chr)
// 			ft_putchar_fd('\n', 1);
// 		symbol.chr = 0;
// 		symbol.size = 7;
// 	}
// }

static void	WritePid(void)
{
	ft_putstr_fd("Server pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
}

// void	get_one(int signum, siginfo_t *info, void *context)
// {
// 	(void)signum;
// 	(void)context;
// 	if (symbol.start == 1)
// 	{
// 		symbol.start = 0;
// 		kill(info->si_pid, SIGUSR1);
// 		return ;
// 	}
// 	symbol.chr += (1 << symbol.size);
// 	symbol.size--;
// 	if (symbol.size < 0)
// 	{
// 		ft_putchar_fd(symbol.chr, 1);
// 		if (!symbol.chr)
// 		{
// 			ft_putchar_fd('\n', 1);
// 			symbol.start = 1;
// 		}
// 		symbol.chr = 0;
// 		symbol.size = 7;
// 	}
// 	kill(info->si_pid, SIGUSR1);
// }

// void	get_zero(int signum, siginfo_t *info, void *context)
// {
// 	(void)signum;
// 	(void)context;
// 	if (symbol.size < 0)
// 	{
// 		ft_putchar_fd(symbol.chr, 1);
// 		if (!symbol.chr)
// 		{
// 			ft_putchar_fd('\n', 1);
// 			symbol.start = 1;
// 		}
// 		symbol.chr = 0;
// 		symbol.size = 7;
// 	}
// 	else
// 		symbol.size--;
// 	kill(info->si_pid, SIGUSR1);
// }

void	get_bit(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (symbol.start == 1)
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
			symbol.start = 1;
			ft_putchar_fd('\n', 1);
			ft_putstr_fd("end\n", 1);
			return ;
		}
		symbol.chr = 0;
		symbol.size = 7;
	}
	kill(info->si_pid, SIGUSR1);
}

int		main(void)
{
	struct sigaction	one;
	struct sigaction	zero;

	WritePid();

	one.__sigaction_u.__sa_sigaction = get_bit;
	one.sa_flags = SA_SIGINFO;
	
	zero.__sigaction_u.__sa_sigaction = get_bit;
	zero.sa_flags = SA_SIGINFO;
	
	symbol.chr = 0;
	symbol.size = 7;
	symbol.start = 1;
	
	if (sigaction(SIGUSR1, &one, NULL) < 0)
		ft_putstr_fd("Error sigaction SIGUSR1\n", 1);
	
	if (sigaction(SIGUSR2, &zero, NULL) < 0)
		ft_putstr_fd("Error sigaction SIGUSR2\n", 1);
	
	while (1)
		pause();
	return (0);
}
