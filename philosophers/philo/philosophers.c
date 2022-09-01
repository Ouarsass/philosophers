/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:37:00 by mouarsas          #+#    #+#             */
/*   Updated: 2022/08/29 00:00:34 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_mutex_init(t_all *data)
{
	int	i;

	i = 0;
	data->lock = malloc(sizeof(t_mutex));
	if (!data->lock)
		return (ft_error("Error: allocation memory\n", false));
	data->lock->forks = malloc(sizeof(pthread_mutex_t) * data->data->nbr_philo);
	if (!data->lock->forks)
		return (ft_error("Error: allocation memory\n", false));
	if (pthread_mutex_init(&data->lock->out, NULL) != 0)
		return (ft_error("Error: Problem in the Mutex\n", false));
	while (i < data->data->nbr_philo)
	{
		if (pthread_mutex_init(&data->lock->forks[i], NULL) != 0)
			return (ft_error("Error: Problem in the mutex\n", false));
		i++;
	}
	return (0);
}

int	ft_lock(t_philo *philo)
{
	philo->meal_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo->meal_lock)
		return (1);
	philo->full_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo->full_lock)
		return (1);
	philo->eat_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philo->eat_lock)
		return (1);
	if (pthread_mutex_init(philo->meal_lock, NULL) != 0)
		return (ft_error("Error: Mutex can't initialized", false), 1);
	if (pthread_mutex_init(philo->full_lock, NULL) != 0)
		return (ft_error("Error: Mutex can't initialized", false), 1);
	if (pthread_mutex_init(philo->eat_lock, NULL) != 0)
		return (ft_error("Error: Mutex can't initialized", false), 1);
	return (0);
}

int	ft_philo_init(t_all *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo)
			* data->data->nbr_philo);
	if (!data->philo)
		return (1);
	while (i < data->data->nbr_philo)
	{
		if (ft_lock(&data->philo[i]) == 1)
			return (1);
		data->philo[i].id_philo = i + 1;
		data->philo[i].last_meal = 0;
		data->philo[i].count_eat = data->data->nbr_meals;
		data->philo[i].arguments = data->data;
		data->philo[i].mutex = data->lock;
		data->philo[i].right_f = &data->lock->forks[i];
		if ((i + 1) == data->data->nbr_philo)
			data->philo[i].left_f = &data->lock->forks[0];
		else
			data->philo[i].left_f = &data->lock->forks[i + 1];
		i++;
	}
	return (0);
}
