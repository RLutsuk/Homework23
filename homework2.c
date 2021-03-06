#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void write_dot(FILE* fname, int** mas, int size)
{
	fprintf(fname, "graph G{\n");

	for (int i = 0; i < size; i++)
		fprintf(fname, "%d;\n", i);

	for (int j = 0; j < size; j++) {
		for (int i = j; i < size; i++)
			for (int k = 0; k < mas[i][j]; k++)
				fprintf(fname, "%d -- %d;\n", j, i);
	}
	fprintf(fname, "}");

	fclose(fname);
}

void checking_graph(int** mas, int size) {

	for (int i, j = 0; j < size; j++) {			// Проверка графа на отсутствие петель.
		i = j;
		if (mas[i][j] != 0) {
			printf("Введенный граф не является простым циклом.\n");
			return;
		}
	}

	for (int j = 0; j < size; j++)				// Проверка графа на отсутствие кратных ребер.
		for (int i = 0; i < size; i++) {
			if (mas[i][j] > 1) {
				printf("Введенный граф не является простым циклом.\n");
				return;
			}
		}

 	for (int k, j = 0; j < size; j++) { // Проверка на принадлежность вершине только 2-х ребер
    k = 0;
    	for (int i = 0; i < size; i++) {
   		   if (mas[i][j] == 1)
        k++;
    	}

    	if (size == 2) { // Так как дальше будет условие k!=2, а в матрице 2х2 может быть только одно ребро, чтобы она была простым графом.
      		if (k == 1)
        	break;
      		else {
        	printf("Введенный граф не является простым циклом.\n");
        	return;
      		}
    	}
		if (k != 2) {
			printf("Введенный  не граф  является простым циклом.\n");
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
	int** mas = NULL;									
	mas = (int**)malloc(sizeof(*mas) * sizeM);			
	for (int i = 0; i < sizeM; i++) {					
		mas[i] = (int*)malloc(sizeof(**mas) * sizeM);	
	}

	char* s, c;

	s = (char*)malloc(sizeof(char) * CHAR_MAX);

	for (int i = 0, m = 0, j = 0; j < sizeM; j++) {					// çàïîëíÿåì ìàññèâ ÷èñëàìè 

		while ((c = getchar()) != '\n') {

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
	fout = fopen("graph.gv", "w");  //Открытие файла и запись.
	
	write_dot(fout, mas, sizeM);

	checking_graph(mas, sizeM);

	free(mas);
	mas = NULL;
	system("sudo dot -Tjpg graph.gv -o file.jpg");
	return 0;
}
