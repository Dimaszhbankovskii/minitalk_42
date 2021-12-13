#include "minitalk.h"

t_data	data;

// void	send_message(int pid, char *str)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;
// 	len = ft_strlen(str);
// 	while (i <= len)
// 	{
// 		j = 7;
// 		while (j > -1)
// 		{
// 			if ((str[i] >> j) & 1)
// 				if (kill(pid, SIGUSR1) < 0)
// 					ft_putstr_fd("Error kill SIGUSR1\n", 1);
// 			if (!((str[i] >> j) & 1))
// 				if (kill(pid, SIGUSR2) < 0)
// 					ft_putstr_fd("Error kill SIGUSR1\n", 1);
// 			j--;
// 			usleep(100);
// 		}
// 		i++;
// 	}
// }

void	send_bit(int signum, struct __siginfo *info, void *context)
{
	char	c;

	(void)signum;
	(void)info;
	(void)context;
	c = *(data.message);
	if ((c >> data.size) & 1)
		if (kill(data.pid, SIGUSR1) < 0)
			ft_putstr_fd("Error kill SIGUSR1\n", 1);
	if (!((c >> data.size) & 1))
		if (kill(data.pid, SIGUSR2) < 0)
			ft_putstr_fd("Error kill SIGUSR2\n", 1);
	if (data.size == 0)
	{
		if (!(*data.message))
			exit (0);
		data.size = 7;
		data.message++;
	}
	else
		data.size--;
}

// void	send_zero(int signum, struct __siginfo *info, void *context)
// {
// 	(void)signum;
// 	(void)info;
// 	(void)context;
// }

int main(int argc, char **argv)
{
	struct sigaction	send;
	// struct sigaction	zero;	

	if (argc != 3)
		ft_putstr_fd("usage: client server_pid msg_to_send\n", 1);

	send.__sigaction_u.__sa_sigaction = send_bit;
	send.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &send, NULL) < 0)
		ft_putstr_fd("Error sigaction SIGUSR1\n", 1);


	// if (sigaction(SIGUSR2, &send_bit, NULL) < 0)
	// 	ft_putstr_fd("Error sigaction SIGUSR2\n", 1);
	// zero.__sigaction_u.__sa_sigaction = send_one;
	// zero.sa_flags = SA_SIGINFO;
		
	data.message = argv[2];
	data.len_message = ft_strlen(data.message);
	data.message[data.len_message] = '\0'; // проверить, что надо
	data.size = 7;	// какой размер для Unicode
	data.pid = ft_atoi(argv[1]);
	
	if (kill(data.pid, SIGUSR1) < 0)
		ft_putstr_fd("Error kill SIGUSR1\n", 1);
	
	while (1)
		pause ();
	return (0);
}
