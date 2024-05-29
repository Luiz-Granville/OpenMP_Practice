set terminal png
set output 'results/plot_0.png'
set title "Tempo de Execução Serial x Paralelo com Diferentes Números de Threads"
set xlabel "Número de Threads"
set ylabel "Tempo de Execução (ms)"
set logscale y
plot "results/data_0.txt" using 1:($2*1000) with linespoints title "Tempo de Execução"
