/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:53:00 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 11:51:45 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_sim *simulation)
{
	mutex_t	*forks;
	int		i;

	forks = malloc(sizeof(mutex_t) * simulation->philo_count);
	if (!forks)
		return (-1);
	i = 0;
	while (i < simulation->philo_count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	simulation->forks = forks;
	return (0);
}

int	create_philos(t_sim *sim)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * (sim->philo_count));
	if (!philos)
		return (-1);
	i = 0;
	while (i < sim->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].left_fork_id = i;
		philos[i].right_fork_id = (i + 1) % sim->philo_count;
		if (sim->philo_count == 1)
			philos[i].right_fork_id = i;
		philos[i].meals_eaten = 0;
		philos[i].sim = sim;
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		i++;
	}
	sim->philos = philos;
	return (0);
}

t_sim	*init_simulation(int ac, char **av, t_sim *simulation)
{
	simulation = malloc(sizeof(t_sim));
	if (!simulation)
		return (NULL);
	if (ft_checker(ac, av, simulation) == -1)
	{
		free(simulation);
		return (NULL);
	}
	simulation->stop_flag = 0;
	pthread_mutex_init(&simulation->log_mutex, NULL);
	pthread_mutex_init(&simulation->stop_mutex, NULL);
	if (create_forks(simulation) == -1 || create_philos(simulation) == -1)
	{
		if (simulation->forks)
			free(simulation->forks);
		pthread_mutex_destroy(&simulation->log_mutex);
		pthread_mutex_destroy(&simulation->stop_mutex);
		free(simulation);
		return (NULL);
	}
	return (simulation);
}

