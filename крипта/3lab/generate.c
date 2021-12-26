#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	meaningful_text(int fd_in, char *file, int n)
{
	int		fd_out;
	char	buff[10240];

	fd_out = open(file, O_WRONLY);
	read(fd_in, buff, n);
	buff[n] = '\0';
	write(fd_out, buff, n);
	close(fd_out);
}

void	random_letters(char *file, int n)
{
	int		i;
	int		fd_out;
	char	buff[10240];

	fd_out = open(file, O_WRONLY);
	i = 0;
	while (i < n)
	{
		if ((rand() % 10) % 2 == 0)
			buff[i] = 97 + rand() % 26;
		else
			buff[i] = 65 + rand() % 26;
		i++;
	}
	buff[n] = '\0';
	write(fd_out, buff, n);
	close(fd_out);
}

void	random_words(int fd_in, char *file, int n)
{
	int		fd_out;
	char	buff[10240];

	fd_out = open(file, O_WRONLY);
	read(fd_in, buff, n);
	buff[n] = '\0';
	write(fd_out, buff, n);
	close(fd_out);
}

int		main(void)
{
	int		fd_in;

	fd_in = open("data/Austin Pride and Prejudice.txt", O_RDONLY);

	meaningful_text(fd_in, "data/meaningful_text1_500.txt", 500);
	meaningful_text(fd_in, "data/meaningful_text2_500.txt", 500);
	meaningful_text(fd_in, "data/meaningful_text1_2500.txt", 2500);
	meaningful_text(fd_in, "data/meaningful_text2_2500.txt", 2500);
	meaningful_text(fd_in, "data/meaningful_text1_10000.txt", 10000);
	meaningful_text(fd_in, "data/meaningful_text2_10000.txt", 10000);

	close(fd_in);

	random_letters("data/random_letters1_500.txt", 500);
	random_letters("data/random_letters2_500.txt", 500);
	random_letters("data/random_letters1_2500.txt", 2500);
	random_letters("data/random_letters2_2500.txt", 2500);
	random_letters("data/random_letters1_10000.txt", 10000);
	random_letters("data/random_letters2_10000.txt", 10000);

	fd_in = open("data/random_words.txt", O_RDONLY);

	random_words(fd_in, "data/random_words1_500.txt", 500);
	random_words(fd_in, "data/random_words2_500.txt", 500);
	random_words(fd_in, "data/random_words1_2500.txt", 2500);
	random_words(fd_in, "data/random_words2_2500.txt", 2500);
	random_words(fd_in, "data/random_words1_10000.txt", 10000);
	random_words(fd_in, "data/random_words2_10000.txt", 10000);

	return (0);
}
