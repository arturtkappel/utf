# Cálculo de Pi - Monte Carlo com OpenMP

Trabalho de avaliação de desempenho de diretivas OpenMP no Raspberry Pi.

## 📝 Descrição

Implementação do método Monte Carlo para estimar o valor de Pi, comparando versões sequencial e paralela usando OpenMP.

### Método Monte Carlo

O método gera pontos aleatórios em um quadrado [0,1] x [0,1] e conta quantos caem dentro de um quarto de círculo de raio 1. A relação entre os pontos dentro e o total permite estimar Pi:

```
Pi ≈ 4 × (pontos_dentro_do_círculo / total_pontos)
```

## 🗂️ Arquivos

- `giron.c` - Versão sequencial
- `giron_paralelo.c` - Versão paralela com OpenMP
- `Makefile` - Automação de compilação e testes

## 🔧 Compilação

### No Raspberry Pi (compilação nativa):

```bash
make all
```

### Em PC Linux para Raspberry Pi (cross-compilation):

```bash
# Instalar compilador cruzado
sudo apt-get install gcc-arm-linux-gnueabihf

# Compilar
make cross

# Transferir para Raspberry Pi
scp giron giron_paralelo pi@raspberrypi.local:~/
```

## ▶️ Execução

### Versão Sequencial:

```bash
./giron [num_iteracoes]

# Exemplo com 100 milhões de pontos
./giron 100000000
```

### Versão Paralela:

```bash
# Usando variável de ambiente
OMP_NUM_THREADS=4 ./giron_paralelo [num_iteracoes]

# Ou passando como argumento
./giron_paralelo 2000000000 4
```

## 📊 Testes e Benchmark

### Teste rápido (100M pontos):

```bash
make test
```

### Benchmark completo:

```bash
make benchmark
```

## 🎯 Configuração Recomendada para Raspberry Pi 4

### Iterações por tempo estimado:
- **5-10s**: 500 milhões de pontos
- **10-20s**: 1-2 bilhões de pontos
- **Teste rápido**: 100 milhões de pontos

### Preparação do ambiente:

```bash
# Definir modo de performance (evita throttling)
sudo cpufreq-set -g performance

# Monitorar temperatura
watch -n 1 vcgencmd measure_temp

# Verificar número de núcleos
nproc
```

## 📈 Análise de Resultados

### Métricas importantes:

1. **Tempo de execução** (T)
2. **Speedup**: S = T_sequencial / T_paralelo
3. **Eficiência**: E = S / num_threads
4. **Erro**: |Pi_real - Pi_estimado|

### Speedup esperado:
- 1 thread: ~1.0x
- 2 threads: ~1.8-2.0x
- 4 threads: ~3.5-3.8x

## 🔍 Diretivas OpenMP Utilizadas

```c
#pragma omp parallel for reduction(+:pontos_dentro)
```

- `parallel for`: Paraleliza o loop distribuindo iterações entre threads
- `reduction(+:var)`: Cada thread tem cópia local, soma no final (evita race condition)

## ⚠️ Pontos de Atenção

1. **Geração de números aleatórios**: Usa `rand_r()` thread-safe com seed único por thread
2. **Race conditions**: Evitadas com `reduction` clause
3. **Temperatura**: Monitorar para evitar throttling
4. **Memória**: Programa usa pouca memória (~MB)

## 🧪 Exemplo de Saída

```
=== Cálculo de Pi - Monte Carlo (Paralelo OpenMP) ===
Número de iterações: 2000000000
Número de threads: 4

Pontos dentro do círculo: 1570796327
Pi estimado: 3.1415926540
Erro: 0.0000000000
Tempo de execução: 5.234567 segundos
```

## 📝 Validação

O programa está correto se:
- Pi estimado ≈ 3.14159... (erro < 0.01 para bilhões de pontos)
- Versão paralela produz resultados similares à sequencial
- Speedup aumenta com número de threads

## 🧹 Limpeza

```bash
make clean
```


# utf
