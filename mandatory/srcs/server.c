#include "minitalk.h"

t_symbol	g_symbol;

static void	write_pid(void)
{
	ft_putstr_fd("Server pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
}

static void	get_message(int signum)
{
	if (signum == SIGUSR1)
	{
		g_symbol.chr += (1 << g_symbol.size);
		g_symbol.size--;
	}
	else if (signum == SIGUSR2)
		g_symbol.size--;
	if (g_symbol.size < 0)
	{
		ft_putchar_fd(g_symbol.chr, 1);
		if (!g_symbol.chr)
			ft_putchar_fd('\n', 1);
		g_symbol.chr = 0;
		g_symbol.size = 7;
	}
}

int	main(void)
{
	write_pid();
	g_symbol.chr = 0;
	g_symbol.size = 7;
	signal(SIGUSR1, get_message);
	signal(SIGUSR2, get_message);
	while (1)
		pause();
	return (0);
}
