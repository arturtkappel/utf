#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define NUM_ITERACOES 1000000000  // Ajustar 

int main(int argc, char *argv[]) {
    long long num_pontos = NUM_ITERACOES;
    long long pontos_dentro = 0;
    double pi_estimado;
    int num_threads = omp_get_max_threads();
    
    // Aceita argumento para n de iterações 
    if (argc > 1) {
        num_pontos = atoll(argv[1]);
    }
    
    // Aceita segundo argumento depois do n de iterações para definir número de threads
    if (argc > 2) {
        num_threads = atoi(argv[2]);
        omp_set_num_threads(num_threads);
    }
    
    printf("=== Cálculo de Pi - Monte Carlo (Paralelo OpenMP) ===\n");
    printf("Número de iterações: %lld\n", num_pontos);
    printf("Número de threads: %d\n\n", num_threads);
    
    double inicio = omp_get_wtime();
    
    #pragma omp parallel for reduction(+:pontos_dentro) // Evitar race condition
    for (long long i = 0; i < num_pontos; i++) {
        
        unsigned int seed = i + omp_get_thread_num() * 123456789; // Seed única
        
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        
        double distancia = x * x + y * y;
        
        if (distancia <= 1.0) {
            pontos_dentro++;
        }
    }
    
    double fim = omp_get_wtime();
    double tempo_decorrido = fim - inicio;
    
    pi_estimado = 4.0 * (double)pontos_dentro / (double)num_pontos;
    
    printf("Pontos dentro do círculo: %lld\n", pontos_dentro);
    printf("Pi estimado: %.10f\n", pi_estimado);
    printf("Erro: %.10f\n", fabs(M_PI - pi_estimado));
    printf("Tempo de execução: %.6f segundos\n", tempo_decorrido);
    
    return 0;
}
