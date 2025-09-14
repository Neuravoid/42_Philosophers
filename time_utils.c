/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ualkan <ualkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:00:00 by ualkan            #+#    #+#             */
/*   Updated: 2025/09/14 15:13:02 by ualkan           ###   ########.fr       */
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
		// CoT Final: Ultra-precise timing with conservative sleep scaling
		if (remaining > 10)
			usleep(remaining * 80);   // Conservative sleep reduction  
		else if (remaining > 2)
			usleep(200);              // Fine-tuned sleep for final milliseconds
		else if (remaining > 1)
			usleep(100);              // Ultra-fine sleep 
		// Final 1ms: Pure busy-wait for microsecond precision
	}
}
void	spend_time_interruptible(long long ms, t_philo *philo)
{
	long long	start;
	long long	target;
	long long	remaining;

	start = get_time();
	target = start + ms;
	
	while (get_time() < target)
	{
		if (check_stop_flag(philo))
			break ;
		
		remaining = target - get_time();
		// CoT Final: Ultra-precise interruptible timing with conservative scaling
		if (remaining > 10)
			usleep(remaining * 80);   // Conservative sleep reduction
		else if (remaining > 2)
			usleep(200);              // Fine-tuned sleep for final milliseconds
		else if (remaining > 1)
			usleep(100);              // Ultra-fine sleep  
		// Final 1ms: Pure busy-wait for microsecond precision
	}
}
