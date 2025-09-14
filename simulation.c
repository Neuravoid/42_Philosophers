/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:53:19 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 11:52:17 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	i = 0;
	sim->start_time = get_time() + (sim->philo_count / 100);

	while (i < sim->philo_count)
	{
		pthread_create(&sim->philos[i].thread_handle, NULL,
			thread_start, &sim->philos[i]);
		i++;
	}
	i = 0;
	while (i < sim->philo_count)
	{
		pthread_mutex_lock(&sim->philos[i].meal_mutex);
		sim->philos[i].last_meal_eaten = sim->start_time;
		pthread_mutex_unlock(&sim->philos[i].meal_mutex);
		i++;
	}
	pthread_create(&sim->monitor_handle, NULL, start_monitor, sim);
	pthread_join(sim->monitor_handle, NULL);
	i = 0;
	while (i < sim->philo_count)
		pthread_join(sim->philos[i++].thread_handle, NULL);
	clean_resources(sim);
}
