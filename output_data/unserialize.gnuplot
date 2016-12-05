#!/usr/bin/gnuplot

set terminal x11
set title "Time Unserializing over size"
set xlabel "Data Unserialized (bytes)"
set ylabel "Time Unserializing (us)"
set autoscale
set datafile separator ";"
plot for [col=8:40:4] 'feature-comparison-charts.csv' using 3:col with lines title columnheader
pause -1
