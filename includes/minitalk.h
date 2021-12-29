#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "../libft/libft.h"

#include <stdio.h>

typedef struct	s_send
{
	int		pid;
	char	*mess;
	int		size;
}				t_send;

typedef struct	s_get
{
	char	*mess;
	char 	chr;
	int		size;
	int		start;
}				t_get;

#endif
