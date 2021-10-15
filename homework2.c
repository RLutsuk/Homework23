#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 


void write_dot(FILE* fname, int** mas, int size) // Ввод графа на языке Dot.
{
	fprintf(fname, "graph G{\n");

	for (int j = 0; j < size; j++) {
		for (int i = j; i < size; i++)
			for (int k = 0; k < mas[i][j]; k++)
				fprintf(fname, "%d -- %d;\n", j, i);
	}
	fprintf(fname, "}");

	fclose(fname);
}

void checking_graph(int** mas, int size) {

	for (int  j = 0; j < size; j++) {			// Проверка графа на отсутствие петель.
		if (mas[j][j] != 0) {
			printf("Введенный граф не является простым циклом\n");
			return;
		}
	}

	for (int j = 0; j < size; j++)				// Проверка графа на отсутствие кратных ребер.
		for (int i = 0; i < size; i++) {
			if (mas[i][j] > 1) {
				printf("Введенный граф не является простым циклом\n");
				return;
			}
		}

	for (int k, j = 0; j < size; j++) {			// Проверка на принадлежность вершине только 2-х ребер, так как если у вершины больше двух ребер, то граф не является простым,
		if (size == 2)							// так как если у вершины больше двух ребер, то граф не является простым.
			break;								
		k = 0; 									
		for (int i = 0; i < size; i++) {
			if (mas[i][j] == 1)
				k++;
		}
		if (k != 2) {
			printf("Введенный  не граф  является простым циклом\n");
			return;
		}
	}
	printf("Введенный граф является простым циклом.\n");
}


int main(void) {
	int width;									
	printf("Введите размер квадратной матрицы\n");
	scanf("%d", &width);						//Пользователь вводит размер матрицы.
	printf("\nВведите строки вашей матрицы. При нажатии \"ENTER\" вы перейдёте на новый столбец.");
	printf("Если не указать число, оно будет равнно '0'.\n");
	getchar();											
	int** mas = NULL;									// Создание двумерного массива.
	mas = (int**)malloc(sizeof(*mas) * width);			
	for (int i = 0; i < width; i++) {					
		mas[i] = (int*)malloc(sizeof(**mas) * width);		}

	char* s, c;

	s = (char*)malloc(sizeof(char) * CHAR_MAX);

	for (int i = 0, m = 0, j = 0; j < width; j++) {					//Заполняем массив числами.

		while ((c = getchar()) != '\n') {

			if (c != ' ')
				s[m++] = c;

			else {
				s[m] = '\0';

				if (i >= width) {
					printf("ОШИБКА: ширина матрицы превышает введенное ранее значение!\n ");
					return -1;
				}

				mas[i][j] = atoi(s);
				i++;
				free(s);
				s = (char*)malloc(sizeof(char) * CHAR_MAX);
				m = 0;

			}

		}

		s[m] = '\0';
		m = 0;

		if (i >= width) {
			printf("ОШИБКА: ширина матрицы превышает введенное ранее значение!\n ");
			return -1;
		}

		mas[i][j] = atoi(s);

		if (i < width) {             // Замена числа на 0, если оно не введено.
			++i;					 // Следующий элемент.
			while (i < width)
				mas[i++][j] = 0;
		}

		i = 0;
		free(s);
		s = (char*)malloc(sizeof(char) * CHAR_MAX);
	}
	free(s);
	
	FILE* fout;
	fout = fopen("graph.gv", "w");

	if (fout == NULL) {
		perror("fopen()");
		return EXIT_FAILURE;
	}

	write_dot(fout, mas, width);

	free(mas); 						// Очищение массива.
	mas = NULL;
	system("sudo dot -Tjpg graph.gv -o file.jpg"); // Создание файла через консоль в формате .jpg.
	return 0;
}

