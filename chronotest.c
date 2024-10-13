#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char	buffer[100];
	long	last_timestamp = 0;
	long	new_timestamp = 0;
	int		message_count = 1;

	while (fgets(buffer, sizeof(buffer), stdin) != NULL)
	{
		printf("%s", buffer);
		last_timestamp = new_timestamp;
		new_timestamp = atol(buffer);
		if (last_timestamp > new_timestamp)
			return (printf("\nError: timestamp missmatch, msg %i", message_count), 1);
		message_count++;
	}

	// int	i;
	// while (fgets(buffer, sizeof(buffer), stdin) != NULL)
	// {
	// 	i = 0;
	// 	while (buffer[i] != ' ')
	// 		i++;
	// 	printf("%s", buffer);
	// 	last_timestamp = new_timestamp;
	// 	new_timestamp = atol(buffer + i);
	// 	if (last_timestamp > new_timestamp)
	// 		return (printf("\nError: timestamp missmatch, msg %i", message_count), 1);
	// 	message_count++;
	// }

	return (0);
}
