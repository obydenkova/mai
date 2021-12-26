#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void parentProces(int* pipe_fd, int m, char *fname) {
	int d;
	close(pipe_fd[0]);
	printf("Enter number\n");

	for (int i = 0; i < m; ++i) 
		write(pipe_fd[1], &i, sizeof(i));
	
	close(pipe_fd[1]);
}

void childProces(int* pipe_fd, char *fname) {
	int d;
	int fd;
	printf("Child\n");
	close(pipe_fd[1]);

	fd = open(fname, O_CREAT | O_APPEND | O_WRONLY, S_IWUSR | S_IRUSR); // Открыть на дозапись, если нет создать с правами без sudo 
	dup2(fd, 1); // Перенаправить вывод в файл fd

	while(read(pipe_fd[0], &d, sizeof(d)) > 0) {
		printf("%d ", d);
	}
	printf("\n");
	close(fd);
}

int main(int argc, char const *argv[]) {
	int pipe_fd[2];
	pid_t pid;
	char name_file[20];
	int count_process;
	int m;
	int err = 0;

	err = -1;
perror("FORK");
			
	printf("\n==========\nEnter name file\n");
	scanf ("%s", name_file);
	printf("Enter n\n");
	scanf ("%d", &count_process);
	printf("Enter m\n");
	scanf ("%d", &m);

	int i = 0;

	for (i; i < count_process; ++i) {
		if(pipe(pipe_fd) == -1) {
			perror("PIPE");
			err = -2;
		}

		pid = fork();

		if(pid == -1) {
			perror("FORK");
			err = -1;
		}
		else if (pid == 0) {
			childProces(pipe_fd, name_file);
			break;
		} else 
			parentProces(pipe_fd, m, name_file);
		
		printf("End Enter\n");
		
	}
	
	return err;
}
