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

	for (int k, j = 0; j < size; j++) {			// Проверка графа на количество ребер, выходящих из вершины.
		if (size == 2)							
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
	int sizeM;									
	printf("Введите размер квадратной матрицы\n");
	scanf("%d", &sizeM);						//Пользователь вводит размер матрицы.
	printf("\nВведите строки вашей матрицы. При нажатии \"ENTER\" вы перейдёте на новый столбец.\n");
	printf("Учтите, что данная матрица является матрицой смежности, поэтому должна быть симметричной.\n");
	printf("Если не указать число, оно будет равнно '0'.\n");
	getchar();											
	int** mas = NULL;									// Создание двумерного массива.
	mas = (int**)malloc(sizeof(*mas) * sizeM);			
	for (int i = 0; i < sizeM; i++) {					
		mas[i] = (int*)malloc(sizeof(**mas) * sizeM);		}

	char* s, c;

	s = (char*)malloc(sizeof(char) * CHAR_MAX);

	for (int i = 0, m = 0, j = 0; j < sizeM; j++) {					//Заполняем массив числами.

		while ((c = getchar()) != '\n') {

			if (c < '0' && c > '9' && c != ' ') {
				printf("ERROR: the entered values is wrong!\n");
				return -1;
			}

			if (c != ' ')
				s[m++] = c;

			else {
				s[m] = '\0';

				if (i >= sizeM) {
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

		if (i >= sizeM) {
			printf("ОШИБКА: ширина матрицы превышает введенное ранее значение!\n ");
			return -1;
		}

		mas[i][j] = atoi(s);

		if (i < sizeM) {             // Замена числа на 0, если оно не введено.
			++i;					
			while (i < sizeM)
				mas[i++][j] = 0;
		}

		i = 0;
		free(s);
		s = (char*)malloc(sizeof(char) * CHAR_MAX);
	}
	free(s);
	
	FILE* fout;
	fout = fopen("graph.gv", "w");
	
	checking_graph(mas, sizeM);
	
	write_dot(fout, mas, sizeM);

	free(mas); 						// Очищение массива.
	mas = NULL;
	system("sudo dot -Tjpg graph.gv -o file.jpg"); // Создание файла через консоль в формате .jpg.
	return 0;
}

