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

// Função para encontrar o maior número no vetor de forma serializada
int serial_max(int *vector, int size) {
    int max = vector[0];
    for (int i = 1; i < size; i++) {
        if (vector[i] > max) {
            max = vector[i];
        }
    }
    return max;
}

int main() {
    int *vector = (int *)malloc(N * sizeof(int));

    // Inicialização do vetor com números aleatórios
    initialize_vector(vector, N);

    FILE *fp = fopen("results/data_1.txt", "w"); // Abrir arquivo para escrever os resultados
    if (fp == NULL) {
        printf("Erro ao abrir arquivo para escrever os resultados.\n");
        return 1;
    }

    // Versão serializada
    double start_time = omp_get_wtime();
    int max_serial = serial_max(vector, N);
    double end_time = omp_get_wtime();
    fprintf(fp, "1 %.5f\n", end_time - start_time);

    // Versão paralela
    for (int num_threads = 2; num_threads <= 16; num_threads *= 2) {
        omp_set_num_threads(num_threads);
        start_time = omp_get_wtime();
        int max = vector[0];

        // Paralelização do loop para encontrar o maior número
        #pragma omp parallel for reduction(max:max)
        for (int i = 1; i < N; i++) {
            if (vector[i] > max) {
                max = vector[i];
            }
        }

        end_time = omp_get_wtime();
        fprintf(fp, "%d %.5f\n", num_threads, end_time - start_time);
    }

    fclose(fp);
    free(vector);

    // Chamar o script Gnuplot para plotar o gráfico
    system("gnuplot -persist results/plot_script_1.gnu");

    return 0;
}
