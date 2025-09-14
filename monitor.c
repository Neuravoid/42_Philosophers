/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 17:51:03 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 18:57:39 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->stop_mutex);
	if (!philo->sim->stop_flag)
	{
		philo->sim->stop_flag = 1;
		pthread_mutex_lock(&philo->sim->log_mutex);
		printf("%lld %d died\n", get_time() - philo->sim->start_time,
			philo->id);
		pthread_mutex_unlock(&philo->sim->log_mutex);
	}
	pthread_mutex_unlock(&philo->sim->stop_mutex);
}

int	log_checker(t_philo *philo)
{
	int	is_dead;

	is_dead = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	if (get_time() - philo->last_meal_eaten >= philo->sim->time_to_die)
		is_dead = 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (is_dead)
	{
		stop_philo(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->sim->stop_mutex);
	if (philo->sim->stop_flag)
	{
		pthread_mutex_unlock(&philo->sim->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->stop_mutex);
	return (0);
}

static int	check_meals_completed(t_sim *sim)
{
	int	i;
	int	all_ate;

	if (sim->must_eat_count == -1)
		return (0);
	all_ate = 1;
	i = 0;
	while (i < sim->philo_count)
	{
		pthread_mutex_lock(&sim->philos[i].meal_mutex);
		if (sim->philos[i].meals_eaten < sim->must_eat_count)
			all_ate = 0;
		pthread_mutex_unlock(&sim->philos[i].meal_mutex);
		i++;
	}
	return (all_ate);
}

void	*start_monitor(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	while (1)
	{
		i = 0;
		while (i < sim->philo_count)
		{
			if (log_checker(&sim->philos[i]))
				return (NULL);
			i++;
		}
		if (check_meals_completed(sim))
		{
			pthread_mutex_lock(&sim->stop_mutex);
			sim->stop_flag = 1;
			pthread_mutex_unlock(&sim->stop_mutex);
			return (NULL);
		}
	}
	return (NULL);
}
