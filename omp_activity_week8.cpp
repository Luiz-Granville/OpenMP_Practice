#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 6  // Tamanho do vetor

int main() {
    int vetor[N] = {2, 8, 1, 4, 7, 3};
    int num_threads = 4;
    int max_values[num_threads];
    
    // Definir o número de threads
    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int start = id * (N / num_threads);
        int end = (id + 1) * (N / num_threads);
        if (id == num_threads - 1) {
            end = N;  // A última thread pode pegar o restante dos elementos
        }
        
        int local_max = vetor[start];
        for (int i = start + 1; i < end; i++) {
            if (vetor[i] > local_max) {
                local_max = vetor[i];
            }
        }
        max_values[id] = local_max;
    }

    // Encontrar o maior número entre os valores máximos parciais
    int global_max = max_values[0];
    for (int i = 1; i < num_threads; i++) {
        if (max_values[i] > global_max) {
            global_max = max_values[i];
        }
    }

    printf("O maior número do vetor é: %d\n", global_max);
    return 0;
}
