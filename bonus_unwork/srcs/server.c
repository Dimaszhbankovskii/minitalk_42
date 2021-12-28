#include "../includes/minitalk.h"

t_symbol	symbol;

static void	WritePid(void)
{
	ft_putstr_fd("Server pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
}

char	*ft_add_chr(char *s, char c)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(*s) * (ft_strlen(s) + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free (s);
	return (str);
}

void	get_message(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
	{
		symbol.chr += (1 << symbol.size);
		symbol.size++;
	}
	else if (signum == SIGUSR2)
		symbol.size++;
	if (symbol.size > 7)
	{
		symbol.mess = ft_add_chr(symbol.mess, symbol.chr);
		if (!symbol.mess)
			ft_putstr_fd("error memory\n", 1);
		if (symbol.chr == '\0')
		{
			ft_putstr_fd(symbol.mess, 1);
			ft_putchar_fd('\n', 1);
			free (symbol.mess);
			symbol.mess = NULL;
			symbol.chr = 0;
			symbol.size = 0;
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		symbol.chr = 0;
		symbol.size = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int		main(void)
{
	struct sigaction	get;

	WritePid();
	get.sa_flags = SA_SIGINFO;
	get.sa_sigaction = get_message;
	symbol.chr = 0;
	symbol.size = 0;
	symbol.mess = NULL;
	if (sigaction(SIGUSR1, &get, NULL) < 0)
		ft_putstr_fd("Error sigaction SIGUSR1\n", 1);
	if (sigaction(SIGUSR2, &get, NULL) < 0)
		ft_putstr_fd("Error sigaction SIGUSR2\n", 1);
	while (1)
		pause();
	return (0);
}
