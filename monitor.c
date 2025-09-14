/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:41:58 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 17:12:21 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_philo(t_philo *philo, long long now)
{
	philo->sim->stop_flag = 1;
	pthread_mutex_unlock(&philo->sim->stop_mutex);
	pthread_mutex_lock(&philo->sim->log_mutex);
	printf("%lld %d died\n", now - philo->sim->start_time, philo->id);
	pthread_mutex_unlock(&philo->sim->log_mutex);
}

int	log_checker(t_philo *philo)
{
	long long	now;
	long long	last;
	long long	time_since_meal;

	pthread_mutex_lock(&philo->sim->stop_mutex);
	if (philo->sim->stop_flag)
	{
		pthread_mutex_unlock(&philo->sim->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->stop_mutex);
	now = get_time();
	pthread_mutex_lock(&philo->meal_mutex);
	last = philo->last_meal_eaten;
	pthread_mutex_unlock(&philo->meal_mutex);
	time_since_meal = now - last;
	if (time_since_meal >= philo->sim->time_to_die)
	{
		pthread_mutex_lock(&philo->sim->stop_mutex);
		if (!philo->sim->stop_flag)
		{
			stop_philo(philo, now);
			return (1);
		}
		pthread_mutex_unlock(&philo->sim->stop_mutex);
	}
	return (0);
}

static int	check_all_eaten(t_sim *sim)
{
	int	i;
	int	all_done;

	if (sim->must_eat_count <= 0)
		return (0);
	all_done = 1;
	i = 0;
	while (i < sim->philo_count)
	{
		pthread_mutex_lock(&sim->philos[i].meal_mutex);
		if (sim->philos[i].meals_eaten < sim->must_eat_count)
			all_done = 0;
		pthread_mutex_unlock(&sim->philos[i].meal_mutex);
		i++;
	}
	return (all_done);
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
		if (check_all_eaten(sim))
		{
			pthread_mutex_lock(&sim->stop_mutex);
			sim->stop_flag = 1;
			pthread_mutex_unlock(&sim->stop_mutex);
			return (NULL);
		}
	}
	return (NULL);
}
