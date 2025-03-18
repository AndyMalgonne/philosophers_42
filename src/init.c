/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoulin <gmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:48:20 by gmoulin           #+#    #+#             */
/*   Updated: 2025/03/19 00:36:36 by gmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_settings(t_philo *philo, char **av)
{
	philo->nb_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->max_meals = ft_atoi(av[5]);
	else
		philo->max_meals = -1;
	philo->eating = 0;
	philo->last_meal = 0;
}

void	init_forks(pthread_mutex_t *forks, int nb_philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		printf("||| Initialized Fork %d.\n", i + 1);
		i++;
	}
}

void	init_philo(t_philo *philo, char **av,
	t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		init_settings(&philo[i], av);
		philo[i].id = i + 1;
		philo[i].start_time = get_current_time();
		philo[i].last_meal = philo[i].start_time;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].dead = &program->dead;
		philo[i].right_fork = &forks[i];
		philo[i].left_fork = &forks[(i + 1) % philo->nb_philos];
		philo[i].write_mutex = &program->write_mutex;
		philo[i].eat_mutex = &program->eat_mutex;
		philo[i].dead_mutex = &program->dead_mutex;
		print_philo(&philo[i], "\n== Initialized ==\n");
		ft_usleep(1000);
		i++;
	}
	write(1, "\n", 1);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		print_philo(&philo[i], "\n++ After sleep ++\n");
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos)
{
	program->dead = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_mutex, NULL);
	pthread_mutex_init(&program->eat_mutex, NULL);
	pthread_mutex_init(&program->dead_mutex, NULL);
}
