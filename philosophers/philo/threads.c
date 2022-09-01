/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:29:22 by mouarsas          #+#    #+#             */
/*   Updated: 2022/08/30 21:20:57 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_making_threads(t_all *data, int full, int i)
{
	if (data->philo[i].id_philo % 2 == full)
	{
		data->philo[i].start_time = data->data->time;
		if (pthread_create(&data->philo[i].thread, NULL,
				&ft_starting, &data->philo[i]) != 0)
		{
			ft_destroing_mutex(data);
			free(data->lock);
			free(data->lock->forks);
			return (ft_error("Thread is not created", false));
		}
	}
	usleep(30);
	return (0);
}

void	*ft_starting(void *philo)
{
	t_philo	*start;

	start = (t_philo *)philo;
	if (pthread_mutex_lock(start->meal_lock) == 0)
		start->last_meal = ft_timing();
	pthread_mutex_unlock(start->meal_lock);
	while (1)
	{
		if (start->count_eat != 0)
			ft_routine(start);
		else
			break ;
	}
	return (NULL);
}

void	ft_routine(t_philo *start)
{
	ft_eating(start);
	if (pthread_mutex_lock(start->meal_lock) == 0)
		start->last_meal = ft_timing();
	pthread_mutex_unlock(start->meal_lock);
	if (pthread_mutex_lock(start->eat_lock) == 0)
		start->count_eat--;
	pthread_mutex_unlock(start->eat_lock);
	ft_sleep(start->arguments->time_eating);
	pthread_mutex_unlock(start->left_f);
	pthread_mutex_unlock(start->right_f);
	ft_output(start, "is sleeping");
	ft_sleep(start->arguments->time_sleep);
	ft_output(start, "is thinking");
}

int	ft_threads(t_all *data)
{
	int	i;

	i = -1;
	data->data->time = ft_timing();
	while (++i < data->data->nbr_philo)
		ft_making_threads(data, 0, i);
	i = -1;
	usleep(50);
	while (++i < data->data->nbr_philo)
		ft_making_threads(data, 1, i);
	if (pthread_create(&data->die, NULL, &ft_die, data) != 0)
		return (ft_error("thread is not created", false));
	if (pthread_join(data->die, NULL) != 0)
		return (ft_error("thread can't be joined", 0));
	ft_destroy(data);
	return (0);
}

void	ft_destroy(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data->nbr_philo)
	{
		free(all->philo[i].eat_lock);
		free(all->philo[i].full_lock);
		free(all->philo[i].meal_lock);
		pthread_mutex_destroy(all->philo[i].left_f);
		pthread_mutex_destroy(all->philo[i].right_f);
		i++;
	}
	pthread_mutex_destroy(&all->lock->out);
	pthread_mutex_destroy(all->philo->meal_lock);
	pthread_mutex_destroy(all->philo->full_lock);
	pthread_mutex_destroy(all->philo->eat_lock);
	free(all->lock->forks);
	free(all->lock);
	free(all->philo);
}
