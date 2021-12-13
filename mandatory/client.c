#include "minitalk.h"

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

static void	send_message(int pid, char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i <= len)
	{
		j = 7;
		while (j > -1)
		{
			if ((str[i] >> j) & 1)
				if (kill(pid, SIGUSR1) < 0)
					ft_putstr_fd("Error kill SIGUSR1\n", 1);
			if (!((str[i] >> j) & 1))
				if (kill(pid, SIGUSR2) < 0)
					ft_putstr_fd("Error kill SIGUSR1\n", 1);
			j--;
			usleep(100);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !input_validation(argv[1]))
		ft_putstr_fd("error: uninvalid pid or no message to send\n", 1);
	else
		send_message(ft_atoi(argv[1]), argv[2]);
	return (0);
}
