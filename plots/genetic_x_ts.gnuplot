# Configurações básicas
set title "GENETIC x TS (50 variables and 218 clauses)"
set ylabel "Clauses satisfied"
set xlabel "#Test"
set grid
set key inside
set key bottom right

set terminal png size 700,500
set terminal png font "Arial,16"
set output 'genetic_x_ts.png'

# Formato dos dados CSV
set datafile separator ','

# Plotar os dados dos dois arquivos
plot "../test_results/extra_TS_uf218-50.txt" using 1:2 with points pointsize 2 title "Taboo search", \
     "../test_results/extra_GENETIC_uf218-50.txt" using 1:2 with points pointsize 2 title "Genetic"
