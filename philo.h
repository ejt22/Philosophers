/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejoo-tho <ejoo-tho@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:29:19 by ejoo-tho          #+#    #+#             */
/*   Updated: 2022/10/14 12:15:25 by ejoo-tho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int				id;
	pthread_t		th_id;
	t_mutex			*rfk;
	t_mutex			*lfk;
	int				meals;
	unsigned long	last_meal;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				n;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_meals;
	int				death;
	int				full;
	t_philo			*philo;
	t_mutex			*forks;
	t_mutex			eat;
	t_mutex			write;
	unsigned long	start;
}	t_data;

// utils

int				ft_atoi(char *s);
unsigned long	current_time(void);
void			ft_usleep(int msec);
void			message(t_philo *philo, char *s);

// routine

int				run_philo(t_data *data);

// error

int				input_error(void);
int				ft_error(t_data *data);

#endif