#include <sys/time.h>
#include <stdio.h>
# include <pthread.h>

long	gettime_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (1);
	return (time.tv_usec + time.tv_sec * 1000000);
}

int	log_msg(long time, int ID, const char *msg)
{
	if (time == -1)
		time = gettime_ms();
	if (time == 1)
		return (1);
	if (0 > printf("%li %i %s\n", time, ID, msg))
		return (1);
	return (0);
}

int main(void)
{
	pthread_mutex_t	mutex;
	pthread_mutex_init(&mutex, NULL);
	log_msg(-1, 1, "test");
	log_msg(-1, 1, "test");
	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);
	log_msg(-1, 1, "test");
}
