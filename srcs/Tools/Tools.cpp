#include "Tools.hpp"

int	getRandomNumber(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	srand(time.tv_usec);

	return (rand());
}
