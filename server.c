#include "minitalk.h"

static t_symbol	symbol;

void	get_message(int sig)
{
	if (sig == SIGUSR1)
	{
		symbol.chr += (1 << symbol.size);
		symbol.size--;
	}
	else if (sig == SIGUSR2)
		symbol.size--;
	if (symbol.size == -1)
	{
		ft_putchar_fd(symbol.chr, 1);
		if (!symbol.chr)
			ft_putchar_fd('\n', 1);
		symbol.chr = 0;
		symbol.size = 7;
	}
}

static void	WritePid(void)
{
	ft_putstr_fd("Server pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
}

int		main(void)
{
	WritePid();
	symbol.chr = 0;
	symbol.size = 7;
	signal(SIGUSR1, get_message);
	signal(SIGUSR2, get_message);	
	while (1)
		pause();
	return (0);
}
