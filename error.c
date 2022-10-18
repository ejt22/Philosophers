/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:50:20 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/10/11 11:16:29 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_error(void)
{
	printf("Error in your input\n");
	printf("The format should be:\n");
	printf("./philo <nb philos> <t_die> <t_eat> <t_sleep>\n");
	printf("and <nb meals all philos must eat> which is optional\n");
	return (-1);
}

int	ft_error(t_data *data)
{
	int	i;

	i = -1;
	while (data->philo && ++i < data->n)
	{
		data->philo[i].data = NULL;
		if (pthread_detach(data->philo[i].th_id))
			return (ft_error(data));
	}
	free(data->philo);
	data->philo = NULL;
	i = -1;
	while (data->forks && ++i < data->n)
		if (pthread_mutex_destroy(&data->forks[i]))
			return (ft_error(data));
	free(data->forks);
	data->forks = NULL;
	printf("An error has occurred.\n");
	return (-1);
}
