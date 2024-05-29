#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 200000000 // Tamanho do vetor

// Função para inicializar o vetor com números aleatórios
void initialize_vector(int *vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100; // Números aleatórios de 0 a 99
    }
}

// Função para calcular a soma dos elementos de um vetor de forma serializada
int serial_sum(int *vector, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += vector[i];
    }
    return sum;
}

int main() {
    int *vector = (int *)malloc(N * sizeof(int));

    // Inicialização do vetor com números aleatórios
    initialize_vector(vector, N);

    FILE *fp = fopen("results/data_0.txt", "w"); // Abrir arquivo para escrever os resultados
    if (fp == NULL) {
        printf("Erro ao abrir arquivo para escrever os resultados.\n");
        return 1;
    }

    // Versão serializada
    double start_time = omp_get_wtime();
    int sum_serial = serial_sum(vector, N);
    double end_time = omp_get_wtime();
    fprintf(fp, "1 %.5f\n", end_time - start_time);

    // Versão paralela
    for (int num_threads = 2; num_threads <= 16; num_threads *= 2) {
        omp_set_num_threads(num_threads);
        start_time = omp_get_wtime();
        int sum = 0;

        // Paralelização do loop para calcular a soma
        #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < N; i++) {
            sum += vector[i];
        }

        end_time = omp_get_wtime();
        fprintf(fp, "%d %.5f\n", num_threads, end_time - start_time);
    }

    fclose(fp);
    free(vector);

    // Chamar o script Gnuplot para plotar o gráfico
    system("gnuplot -persist results/plot_script_0.gnu");

    return 0;
}
