/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:53:19 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 18:17:53 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_resources(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->philo_count)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&sim->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->log_mutex);
	pthread_mutex_destroy(&sim->stop_mutex);
	free(sim->philos);
	free(sim->forks);
	free(sim);
}

void	*thread_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	handle_routine(philo);
	return (NULL);
}

void	start_simulation(t_sim *sim)
{
	int	i;

	sim->start_time = get_time() + (sim->philo_count * 2) / 1000;
	i = 0;
	while (i < sim->philo_count)
	{
		sim->philos[i].last_meal_eaten = sim->start_time;
		i++;
	}
	i = 0;
	while (i < sim->philo_count)
	{
		pthread_create(&sim->philos[i].thread_handle, NULL,
			thread_start, &sim->philos[i]);
		i++;
	}
	pthread_create(&sim->monitor_handle, NULL, start_monitor, sim);
	pthread_join(sim->monitor_handle, NULL);
	i = 0;
	while (i < sim->philo_count)
		pthread_join(sim->philos[i++].thread_handle, NULL);
	clean_resources(sim);
}
