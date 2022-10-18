/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:52:51 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/10/18 11:41:03 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* This function is the detailed eating function for each philosopher. */

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lfk);
	message(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->rfk);
	message(philo, "has taken a fork\n");
	message(philo, "is eating\n");
	pthread_mutex_lock(&philo->data->eat);
	philo->last_meal = current_time();
	philo->meals++;
	if (philo->meals == philo->data->max_meals)
		philo->data->full++;
	pthread_mutex_unlock(&philo->data->eat);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(philo->lfk);
	pthread_mutex_unlock(philo->rfk);
}

/* This function is the main routine for each philosopher. It starts with odd 
numbered philosophers grabbing forks first. */

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->n == 1)
	{
		message(philo, "has taken a fork\n");
		ft_usleep(philo->data->t_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(2);
	while (!philo->data->death)
	{
		philo_eat(philo);
		if (philo->data->death)
			break ;
		message(philo, "is sleeping\n");
		ft_usleep(philo->data->t_sleep);
		if (philo->data->death)
			break ;
		message(philo, "is thinking\n");
		if (philo->data->death)
			break ;
	}
	return (NULL);
}

/* This function checks for cases when one philosopher dies. */

static void	check_death(t_data *data, int i)
{
	unsigned long	time;

	pthread_mutex_lock(&data->eat);
	if ((int)(current_time() - data->philo[i].last_meal)
		>= data->t_die)
	{
		pthread_mutex_lock(&data->write);
		data->death = 1;
		time = current_time();
		printf("%lu %d %s", time - data->start, data->philo[i].id, "died\n");
		pthread_mutex_unlock(&data->write);
	}
	pthread_mutex_unlock(&data->eat);
}

/* This function checks for cases where the programme should stop, ie when one
philosopher dies or when all have eaten at least the maximum of meals. */

static void	check_threads(t_data *data)
{
	int	i;

	while (1)
	{
		usleep(20);
		i = 0;
		while (i < data->n)
		{
			check_death(data, i);
			if (data->death)
				break ;
			else if (data->max_meals && data->full == data->n)
			{
				pthread_mutex_lock(&data->write);
				data->death = 1;
				pthread_mutex_unlock(&data->write);
				break ;
			}
			else
				i++;
		}
		if (data->death || data->full == data->n)
			break ;
	}
}

/* This function creates one thread per philosopher and runs them with
the function routine. The main thread will at the same time check for 
cases where the programme should stop through check_threads. */

int	run_philo(t_data *data)
{
	int	i;

	i = -1;
	data->start = current_time();
	while (++i < data->n)
	{
		data->philo[i].last_meal = data->start;
		if (pthread_create(&data->philo[i].th_id, NULL, routine,
				(void *)&data->philo[i]))
			return (ft_error(data));
	}
	check_threads(data);
	i = -1;
	while (++i < data->n)
	{
		if (pthread_join(data->philo[i].th_id, NULL))
			return (ft_error(data));
	}
	return (0);
}
