set terminal png
set output 'results/plot_1.png'
set title "Tempo de Execução Serial x Paralelo para Encontrar o Maior Número"
set xlabel "Número de Threads"
set ylabel "Tempo de Execução (ms)"
set ytics format "%.1f" # Formato para exibir os valores do eixo Y em uma casa decimal
set logscale y
plot "results/data_1.txt" using 1:($2*1000) with linespoints title "Tempo de Execução"
