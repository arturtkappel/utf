# Makefile para compilação dos programas Monte Carlo Pi

CC = gcc
CFLAGS = -O3 -Wall -Wextra
LDFLAGS = -lm

# Para Raspberry Pi (compilação nativa)
all: giron giron_paralelo

# Versão sequencial
giron: giron.c
	$(CC) $(CFLAGS) -o giron giron.c $(LDFLAGS)

# Versão paralela com OpenMP
giron_paralelo: giron_paralelo.c
	$(CC) $(CFLAGS) -fopenmp -o giron_paralelo giron_paralelo.c $(LDFLAGS)

# Compilação cruzada para Raspberry Pi (a partir de PC Linux)
cross: giron_cross giron_paralelo_cross

giron_cross: giron.c
	arm-linux-gnueabihf-gcc $(CFLAGS) -static -o giron giron.c $(LDFLAGS)

giron_paralelo_cross: giron_paralelo.c
	arm-linux-gnueabihf-gcc $(CFLAGS) -fopenmp -static -o giron_paralelo giron_paralelo.c $(LDFLAGS)

# Limpeza
clean:
	rm -f giron giron_paralelo *.o

# Teste rápido (poucos pontos)
test:
	@echo "=== Teste Sequencial (100M pontos) ==="
	./giron 100000000
	@echo ""
	@echo "=== Teste Paralelo (100M pontos, 4 threads) ==="
	OMP_NUM_THREADS=4 ./giron_paralelo 100000000

# Benchmark completo
benchmark:
	@echo "Threads,Tempo,Pi,Erro" > resultados.csv
	@echo "=== Sequencial ==="
	@./giron | tee -a resultados.csv
	@echo ""
	@echo "=== 2 Threads ==="
	@OMP_NUM_THREADS=2 ./giron_paralelo | tee -a resultados.csv
	@echo ""
	@echo "=== 4 Threads ==="
	@OMP_NUM_THREADS=4 ./giron_paralelo | tee -a resultados.csv

.PHONY: all cross clean test benchmark


