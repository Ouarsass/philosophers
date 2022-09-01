/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 02:04:38 by mouarsas          #+#    #+#             */
/*   Updated: 2022/08/30 21:44:30 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	ft_output(philo, "take the right fork");
	pthread_mutex_lock(philo->left_f);
	ft_output(philo, "take the left fork");
	ft_output(philo, "is eating");
	return (0);
}

void	ft_output(t_philo *philo, char *string)
{
	pthread_mutex_lock(&philo->mutex->out);
	if (philo->arguments->full == 1)
		return ;
	else if (philo->arguments->full == 0)
	{
		printf("%ld\tphilo %d %s\n", ft_timing() - philo->start_time,
			philo->id_philo, string);
		pthread_mutex_unlock(&philo->mutex->out);
	}
}

void	ft_destroing_mutex(t_all *data)
{
	int	i;

	i = 0;
	while (i < data->data->nbr_philo)
		pthread_mutex_destroy(&data->lock->forks[i++]);
	pthread_mutex_destroy(&data->lock->out);
}

void	ft_sleep(long time_waiting)
{
	long	time_start;
	long	count;

	time_start = ft_timing();
	count = ft_timing() + time_waiting;
	while (count > time_start)
	{
		usleep(100);
		time_start = ft_timing();
	}
}
