#include "minitalk.h"

void	send_message(int pid, char *message)
{
	size_t	len;
	size_t	i;
	int 	rank;

	len = ft_strlen(message);
	i = 0;
	while (i < len)
	{
		rank = 0b10000000;
		while (rank)
		{
			if (message[i] & rank)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			rank >>= 1;
			usleep(100);
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	int pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		send_message(pid, argv[2]);
	}
	else
		ft_putstr_fd("usage: client server_pid msg_to_send\n", 1);
	return (0);
}
