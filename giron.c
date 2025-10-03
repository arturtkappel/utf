/*
 * Cálculo de Pi usando Método Monte Carlo - VERSÃO SEQUENCIAL
 * 
 * Método: Gera pontos aleatórios em um quadrado [0,1] x [0,1]
 * e conta quantos caem dentro do círculo de raio 1.
 * Pi ≈ 4 * (pontos_dentro_do_circulo / total_pontos)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_ITERACOES 1000000000  // 2 bilhões (ajuste conforme necessário)

int main(int argc, char *argv[]) {
    long long num_pontos = NUM_ITERACOES;
    long long pontos_dentro = 0;
    double x, y, distancia;
    double pi_estimado;
    
    if (argc > 1) {
        num_pontos = atoll(argv[1]);
    }
    
    printf("=== Cálculo de Pi - Monte Carlo (Sequencial) ===\n");
    printf("Número de iterações: %lld\n\n", num_pontos);
    
    srand(time(NULL));
    
    clock_t inicio = clock();
    
    for (long long i = 0; i < num_pontos; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        
        distancia = x * x + y * y;
        
        if (distancia <= 1.0) {
            pontos_dentro++;
        }
    }
    
    clock_t fim = clock();
    double tempo_decorrido = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    pi_estimado = 4.0 * (double)pontos_dentro / (double)num_pontos;
    
    printf("Pontos dentro do círculo: %lld\n", pontos_dentro);
    printf("Pi estimado: %.10f\n", pi_estimado);
    printf("Erro: %.10f\n", fabs(M_PI - pi_estimado));
    printf("Tempo de execução: %.6f segundos\n", tempo_decorrido);
    
    return 0;
}
