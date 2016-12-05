#!/usr/bin/gnuplot

set terminal x11
set title "Data Serialized over Unserialized"
set xlabel "Data Unserialized (bytes)"
set ylabel "Data Serialized (bytes)"
set autoscale
set datafile separator ";"
plot for [col=5:40:4] 'feature-comparison-charts.csv' using 3:col with lines title columnheader,\
	'feature-comparison-charts.csv' using 3:3 with lines title columnheader

pause -1
