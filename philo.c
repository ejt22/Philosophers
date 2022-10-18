/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:11:31 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/10/18 11:01:40 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* This function initialises the main data structure and deals with input 
errors. */

int	init_data(int ac, char **av, t_data *data)
{
	data->forks = NULL;
	data->philo = NULL;
	if (ac < 5 || ac > 6)
		return (input_error());
	data->n = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	else
		data->max_meals = 0;
	data->death = 0;
	data->full = 0;
	data->start = 0;
	if (data->n == -1 || data->t_die == -1 || data->t_eat == -1
		|| data->t_sleep == -1 || data->max_meals == -1)
		return (input_error());
	if (pthread_mutex_init(&data->eat, NULL)
		|| pthread_mutex_init(&data->write, NULL))
		return (ft_error(data));
	return (0);
}

/* This function initialises the array of forks and initialises the 
mutexes. */

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_mutex) * data->n);
	if (!data->forks)
		return (ft_error(data));
	i = -1;
	while (++i < data->n)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ft_error(data));
	return (0);
}

/* This function initialises the array of philosophers. It points each 
philosopher's forks to the right one in the array of forks. */

int	init_philo(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->n);
	if (!data->philo)
		return (ft_error(data));
	i = -1;
	while (++i < data->n)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals = 0;
		data->philo[i].data = data;
		data->philo[i].lfk = &data->forks[i];
		if (i < data->n - 1)
			data->philo[i].rfk = &data->forks[i + 1];
		else
			data->philo[i].rfk = &data->forks[0];
	}
	return (0);
}

/* This function prepares for a clean exit of the programme by freeing 
all the resources that needs to be freed. */

int	exit_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n)
	{
		data->philo[i].data = NULL;
	}
	if (pthread_mutex_destroy(&data->eat)
		|| pthread_mutex_destroy(&data->write))
		return (ft_error(data));
	i = -1;
	while (++i < data->n)
		if (pthread_mutex_destroy(&data->forks[i]))
			return (ft_error(data));
	free(data->forks);
	free(data->philo);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (init_data(ac, av, &data) == -1)
		return (1);
	if (init_forks(&data) == -1)
		return (1);
	if (init_philo(&data) == -1)
		return (1);
	if (run_philo(&data) == -1)
		return (1);
	if (exit_philo(&data) == -1)
		return (1);
	return (0);
}
