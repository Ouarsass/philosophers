/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:36:19 by mouarsas          #+#    #+#             */
/*   Updated: 2022/08/28 23:31:31 by mouarsas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include <time.h>

typedef struct data
{
	long	time;
	int		time_eating;
	int		time_sleep;
	int		time_die;
	int		full;
	int		nbr_philo;
	int		nbr_meals;
}				t_data;

typedef struct mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	out;
}				t_mutex;

typedef struct philo
{
	pthread_mutex_t	*eat_lock;
	int				count_eat;
	pthread_mutex_t	*meal_lock;
	long			last_meal;
	pthread_mutex_t	*full_lock;
	int				id_philo;
	long			start_time;
	pthread_t		thread;
	t_mutex			*mutex;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	t_data			*arguments;
}				t_philo;

typedef struct all
{
	t_philo		*philo;
	t_mutex		*lock;
	t_data		*data;
	pthread_t	die;
}				t_all;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_error(char *string, bool i);
int		ft_parsing(char *av[]);
long	ft_timing(void);
int		ft_if_die(t_philo *philo);
void	*ft_die(void *data);
void	ft_output(t_philo *philo, char *string);
int		ft_eating(t_philo *philo);
void	ft_sleep(long time_waiting);
int		ft_atoi(const char *str);
void	ft_destroing_mutex(t_all *data);
int		ft_mutex_init(t_all *data);
int		ft_making_threads(t_all *data, int full, int i);
int		ft_philo_init(t_all *data);
int		ft_threads(t_all *data);
void	ft_routine(t_philo *start);
void	*ft_starting(void *philo);
void	ft_destroing_mutex(t_all *data);
void	ft_destroy(t_all *all);

#endif
