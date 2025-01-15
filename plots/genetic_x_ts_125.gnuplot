# Configurações básicas
set title "GENETIC x TS (125 variables and 538 clauses)"
set ylabel "Clauses satisfied"
set xlabel "#Test"
set grid
set key inside
set key bottom right
set yrange [510:538]

set terminal png size 700,500
set terminal png font "Arial,16"
set output 'genetic_x_ts_125.png'

# Formato dos dados CSV
set datafile separator ','

# Plotar os dados dos dois arquivos
plot "../test_results/extra_TS_uf538-125.txt" using 1:2 with points pointsize 2 title "Taboo search", \
     "../test_results/extra_GENETIC_uf538-125.txt" using 1:2 with points pointsize 2 title "Genetic"
