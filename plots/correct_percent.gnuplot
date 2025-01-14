# Configurações básicas
set title "% of correct answers"
set ylabel "Correct (%)"
set xlabel "# of variables"
set grid
set key outside
set key top right

set terminal png size 700,500
set terminal png font "Arial,16"
set output 'correct_percent.png'

set ytics 0, 10
# Formato dos dados CSV
set datafile separator ','

set style data histograms
set style histogram cluster gap 2
set style fill solid border -1
set boxwidth 1 relative

# Plotar os dados dos dois arquivos
plot "../test_results/processed_results_CIDPLL_5rep.txt" using ($5*100):xtic(1) title "CIDPLL", \
      "../test_results/processed_results_TS_5rep.txt" using ($5*100):xtic(1) title "TS", \
      "../test_results/processed_results_GENETIC_5rep.txt" using ($5*100):xtic(1) title "GENETIC"
     
