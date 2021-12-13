#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "./libft/libft.h"

typedef struct	s_data
{
	char	*message;
	int		len_message;
	int		index;
	int		size;
	int		pid;
}				t_data;

typedef struct	s_symbol
{
	char 	chr;
	int		size;
	int		start;
}				t_symbol;

#endif
