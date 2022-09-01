/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:35:02 by mouarsas          #+#    #+#             */
/*   Updated: 2022/08/30 21:54:33 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char *av[])
{
	t_all	philo;
	t_data	data;

	philo.data = &data;
	if (ac < 5 || ac > 6)
		return (ft_error("Error\n", true));
	if (!ft_parsing(av))
		return (ft_error("Error\n", true));
	philo.data->nbr_philo = ft_atoi(av[1]);
	philo.data->time_die = ft_atoi(av[2]);
	philo.data->time_eating = ft_atoi(av[3]);
	philo.data->time_sleep = ft_atoi(av[4]);
	philo.data->nbr_meals = -1;
	philo.data->full = 0;
	if (av[5] != NULL)
		philo.data->nbr_meals = ft_atoi(av[5]);
	if (ft_mutex_init(&philo))
		return (ft_destroy(&philo), 1);
	if (ft_philo_init(&philo))
		return (ft_destroy(&philo), 1);
	if (ft_threads(&philo))
		return (ft_destroy(&philo), 1);
	return (0);
}
