#!/usr/bin/gnuplot

set terminal x11
set title "Time Serializing over size"
set xlabel "Data Serializing (bytes)"
set ylabel "Time Serializing (us)"
set autoscale
set datafile separator ";"
plot for [col=7:40:4] 'feature-comparison-charts.csv' using 3:col with lines title columnheader

pause -1
