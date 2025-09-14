/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:00:00 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 18:52:57 by ualkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	spend_time(long long ms)
{
	long long	start;
	long long	target;
	long long	remaining;

	start = get_time();
	target = start + ms;
	while (get_time() < target)
	{
		remaining = target - get_time();
		if (remaining > 10)
			usleep(remaining * 80);
		else if (remaining > 2)
			usleep(200);
		else if (remaining > 1)
			usleep(100);
	}
}

void	spend_time_interruptible(long long ms, t_philo *philo)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		if (check_stop_flag(philo))
			break ;
		usleep(500);
	}
}

void	ft_even_wait(t_philo *philo)
{
	long long	stagger_delay;

	if (philo->id % 2 == 0)
	{
		stagger_delay = (philo->sim->philo_count / 2)
			+ (philo->id / 2);
		if (stagger_delay > 15)
			stagger_delay = 15;
		spend_time_interruptible(stagger_delay, philo);
	}
}
