#include "minitalk.h"

static t_symbol	symbol;

void	get_message(int bit)
{
	if (bit == SIGUSR1)
		bit = 1;
	else if (bit == SIGUSR2)
		bit = 0;
	symbol.chr += ((bit & 1) << symbol.size);
	symbol.size++;
	if (symbol.size == 7)
	{
		ft_putchar_fd(symbol.chr, 1);
		if (!symbol.chr)
			ft_putchar_fd('\n', 1);
		symbol.chr = 0;
		symbol.size = 0;
	}
}

int		main(void)
{
	int pid;

	pid = getpid();
	symbol.chr = 0;
	symbol.size = 0;
	ft_putstr_fd("Server pid: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	while (1)
	{
		signal(SIGUSR1, get_message);
		signal(SIGUSR2, get_message);
		pause();
	}
}
