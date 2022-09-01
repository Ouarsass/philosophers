/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:26:55 by mouarsas          #+#    #+#             */
/*   Updated: 2022/08/30 21:20:16 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_if_die(t_philo *philo)
{
	long	i;

	i = 0;
	if (pthread_mutex_lock(philo->meal_lock) == 0)
		i = ft_timing() - philo->last_meal;
	pthread_mutex_unlock(philo->meal_lock);
	if (philo->arguments->time_die < i)
	{
		pthread_mutex_lock(&philo->mutex->out);
		printf("%ld\tphilo %d is dead\n", ft_timing() - philo->start_time,
			philo->id_philo);
		if (pthread_mutex_lock(philo->full_lock) != 0)
			philo->arguments->full = 1;
		return (0);
	}
	return (1);
}

void	*ft_die(void *data)
{
	t_all	*all;
	int		i;
	int		count_meal;

	all = (t_all *)data;
	while (1)
	{
		i = 0;
		count_meal = 0;
		while (i < all->data->nbr_philo)
		{
			if (!ft_if_die(&all->philo[i]))
				return (NULL);
			if (pthread_mutex_lock(all->philo[i].eat_lock) == 0)
				count_meal += all->philo[i].count_eat;
			pthread_mutex_unlock(all->philo[i].eat_lock);
			i++;
		}
		if (count_meal == 0)
		{
			pthread_mutex_lock(&all->lock->out);
			return (NULL);
		}
	}
}
