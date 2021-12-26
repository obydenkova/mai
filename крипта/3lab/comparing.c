#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	calc_func(char *file1, char *file2, int n)
{
	int		i;
	int		fd1;
	int		fd2;
	char	buff1[10240];
	char	buff2[10240];
	float	res;

	printf("\t%d знаков: ", n);
	fd1 = open(file1, O_RDONLY);
	read(fd1, buff1, n);
	buff1[n] = '\0';
	close(fd1);
	fd2 = open(file2, O_RDONLY);
	read(fd2, buff2, n);
	buff2[n] = '\0';
	close(fd2);
	i = 0;
	res = 0;
	while (buff1[i] != '\0' && buff2[i] != '\0')
	{
		if (buff1[i] == buff2[i])
			res++;
		i++;
	}
	res = res / n;
	printf("%f\n", res);
}

int		main(void)
{
	printf("Результаты сравнения:\n\n");

	printf("Два осмысленных текста:\n");
	calc_func("data/meaningful_text1_500.txt", "data/meaningful_text2_500.txt", 500);
	calc_func("data/meaningful_text1_2500.txt", "data/meaningful_text2_2500.txt", 2500);
	calc_func("data/meaningful_text1_10000.txt", "data/meaningful_text2_10000.txt", 10000);
	printf("\n");

	printf("Осмысленный текст и текст из случайных букв:\n");
	calc_func("data/meaningful_text1_500.txt", "data/random_letters1_500.txt", 500);
	calc_func("data/meaningful_text1_2500.txt", "data/random_letters1_2500.txt", 2500);
	calc_func("data/meaningful_text1_10000.txt", "data/random_letters1_10000.txt", 10000);
	printf("\n");

	printf("Осмысленный текст и текст из случайных слов:\n");
	calc_func("data/meaningful_text1_500.txt", "data/random_words1_500.txt", 500);
	calc_func("data/meaningful_text1_2500.txt", "data/random_words1_2500.txt", 2500);
	calc_func("data/meaningful_text1_10000.txt", "data/random_words1_10000.txt", 10000);
	printf("\n");

	printf("Два текста из случайных букв:\n");
	calc_func("data/random_letters1_500.txt", "data/random_letters2_500.txt", 500);
	calc_func("data/random_letters1_2500.txt", "data/random_letters2_2500.txt", 2500);
	calc_func("data/random_letters1_10000.txt", "data/random_letters2_10000.txt", 10000);
	printf("\n");

	printf("Два текста из случайных слов:\n");
	calc_func("data/random_words1_500.txt", "data/random_words2_500.txt", 500);
	calc_func("data/random_words1_2500.txt", "data/random_words2_2500.txt", 2500);
	calc_func("data/random_words1_10000.txt", "data/random_words2_10000.txt", 10000);
	printf("\n");

	return (0);
}

