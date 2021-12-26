#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <malloc.h>

// у нас есть стуктр compare, потом мы создаем объект этого класса под названием тугезер
// потом мы создаем новый поток с помощью pthread_create и вызваем в нем функцию determinant и передаем в нее созданный ранее объект together 
//в determinant мы говорим, что перданная ссылка на участок памяти это объект структуры compare и он сам ее преобразует в ссылку на объект этого класса
pthread_mutex_t mutex;

typedef struct {
	int **matrix; // matrix
	int size; // size
} compare; // структура 


void* determinant(void *together) {
	compare* tmp = (compare*) together;
	int i,j;
	double det = 0;
//Pthreads определяет набор типов и функций на Си
// pthread_t идентификатор потока

// malloc выделяет блок памяти в байтах(динамически)
// (int**) приведение типов
// tmp->size * sizeof(compare) сколько байт выделить
// sizeof(compare)  размер одного элемента массива
	pthread_t *array = malloc(sizeof(pthread_t) * tmp->size);
	compare   *mtarr = malloc(sizeof(compare)   * tmp->size);

	if (tmp->size == 1) {
		det = tmp->matrix[0][0];
	} else if (tmp->size == 2) {
		det = tmp->matrix[0][0] * tmp->matrix[1][1] - tmp->matrix[0][1] * tmp->matrix[1][0];
	} else {

		for (i = 0; i < tmp->size; ++i) {
			mtarr[i].matrix = (int **)malloc(sizeof(int *) * tmp->size);
			mtarr[i].size = tmp->size - 1;

			for (j = 0; j < tmp->size - 1; ++j) {
				if (j < i)
					mtarr[i].matrix[j] = tmp->matrix[j];
				else
					mtarr[i].matrix[j] = tmp->matrix[j + 1];
			}
// pthread_create создает новый поток
			pthread_create(&array[i], NULL, determinant, mtarr + i);
// NULL атрибуты по умолчанию
//  determinant функция, которая будет выполняться в новом потоке
		}

		for (i = 0; i < tmp->size; ++i) {
			void *res;
			for (j = 0; j < tmp->size - 1; ++j) {
// pthread_join откладывает выполнение вызывающего (эту функцию) потока, до тех пор, пока не будет выполнен поток thread

			pthread_join(array[i], &res);
			double x = *(double *)&res;
			det += (-1 + 2 * !(i % 2)) * x * tmp->matrix[i][tmp->size - 1];


			double answer = *(double*)&det;
			free(mtarr[i].matrix);
		}


	}
//free освобождает место в памяти
	free(mtarr);
	free(array);

	void* ans = *(void **)&det;
	return ans;
}


int main(int argc, char const *argv[]) {
	srand(time(NULL)); // рандом чисел
	int **matrix;
	int n = 0;
	int a;
// pthread_attr_t — перечень атрибутов потока
// pthread_attr_init – инициализация описателя атрибутов потока управления
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr); // attr – указатель на описатель атрибутов потока

	printf("Insert the demention of matrix:\n");
	scanf("%d", &n);
// malloc выделяет блок памяти в байтах(динамически)
// (int**) приведение типов
// n * sizeof(int*) сколько байт выделить
// sizeof(int*)  размер одного элемента массива
	matrix = (int**)malloc(n * sizeof(int*));

	for (int i=0; i<n; ++i)
		matrix[i] = (int*)malloc(n * sizeof(int));


	printf("Insert matrix:\n");


	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			matrix[i][j]=0+rand()%5-1+1;
			//matrix[i][j] = i;
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}


	compare* together = (compare*)malloc(sizeof(compare));
	together->matrix = matrix;
	together->size = n;

	void *det;
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&tid, NULL, determinant, together); 
// &tid указатель на поток
// NULL атрибуты по умолчанию
// determinant функция которая будет выполняться в новом потоке
//together передаем параметр


// у нас есть структура compare, мы создаем объект этого класса под названием together
// потом мы создаем новый поток с помощью pthread_create и вызваем в нем функцию determinant и передаем в нее созданный ранее объект together 
//в determinant мы говорим, что перданная ссылка на участок памяти это объект структуры compare и он сам ее преобразует в ссылку на объект этого класса
	pthread_join(tid, &det); 
//tid поток
// &det возвращаем результат

	double answer = *(double*)&det;
	printf("Det is: %f\n", answer);

	for (int i = 0; i < n; ++i)
		free(matrix[i]);
	free(matrix);
	free(together);

	return 0;
}
