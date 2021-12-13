#include "minitalk.h"

t_data	data;

// void	send_bit(int signum, siginfo_t *info, void *context)
// {
// 	char	c;

// 	(void)signum;
// 	(void)info;
// 	(void)context;
// 	c = *(data.message);
// 	if ((c >> data.size) & 1)
// 		if (kill(data.pid, SIGUSR1) < 0)
// 			ft_putstr_fd("Error kill SIGUSR1\n", 1);
// 	if (!((c >> data.size) & 1))
// 		if (kill(data.pid, SIGUSR2) < 0)
// 			ft_putstr_fd("Error kill SIGUSR2\n", 1);
// 	if (data.size == 0)
// 	{
// 		if (!(*data.message))
// 			exit (0);
// 		data.size = 7;
// 		data.message++;
// 	}
// 	else
// 		data.size--;
// }

void	send_bit(int signum)
{
	if (signum != SIGUSR1)
		ft_putstr_fd("error SIG1\n", 1);
	if ((data.message[data.index] >> data.size) & 1)
		if (kill(data.pid, SIGUSR1) < 0)
			ft_putstr_fd("Error kill SIGUSR1\n", 1);	
	if (!((data.message[data.index] >> data.size) & 1))
		if (kill(data.pid, SIGUSR2) < 0)
			ft_putstr_fd("Error kill SIGUSR2\n", 1);
	if (data.size == 0)
	{
		if (!data.message[data.index])
			exit (0);
		data.size = 7;
		data.index++;
	}
	else
		data.size--;
}

int main(int argc, char **argv)
{
	// struct sigaction	send;

	if (argc != 3)
		ft_putstr_fd("usage: client server_pid msg_to_send\n", 1);
	// send.__sigaction_u.__sa_sigaction = send_bit;
	// send.sa_flags = SA_SIGINFO;
	// if (sigaction(SIGUSR1, &send, NULL) < 0)
		// ft_putstr_fd("Error sigaction SIGUSR1\n", 1);
	data.message = argv[2];
	data.len_message = ft_strlen(data.message);
	data.index = 0;
	data.message[data.len_message] = '\0'; // проверить, что надо
	data.size = 7;	// какой размер для Unicode
	data.pid = ft_atoi(argv[1]);
	signal(SIGUSR1, &send_bit);	
	if (kill(data.pid, SIGUSR1) < 0)
		ft_putstr_fd("Error kill SIGUSR1\n", 1);
	while (1)
		pause ();
	return (0);
}
