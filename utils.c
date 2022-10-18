/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:50:18 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/10/18 10:59:58 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* This ft_atoi has been modified to return (-1) in case of a negative number
and a number greater than INT_MAX. */

int	ft_atoi(char *s)
{
	long	res;
	int		i;

	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
		return (-1);
	res = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		while (s[i] >= '0' && s[i] <= '9')
			res = res * 10 + (s[i++] - '0');
		if (res > INT_MAX)
			return (-1);
	}
	if (!res)
		return (-1);
	return ((int)res);
}

/* This function return the current time in msec. */

unsigned long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/* This ft_usleep enables a more precise usleep than the one already in the 
library. If you increment it too often (every 10 msec for example), it will
cause your programme to run much more slowly, especially if you have lots of 
philosophers. */

void	ft_usleep(int msec)
{
	unsigned long	time;

	time = current_time();
	while ((int)(current_time() - time) < msec)
		usleep(100);
}

/* This function prints the various messages (eating, sleeping, thinking).
It is important to protect it with a mutex. */

void	message(t_philo *philo, char *s)
{
	unsigned long	time;

	pthread_mutex_lock(&philo->data->write);
	if (!philo->data->death)
	{
		time = current_time();
		printf("%lu %d %s", time - philo->data->start, philo->id, s);
	}
	pthread_mutex_unlock(&philo->data->write);
}
