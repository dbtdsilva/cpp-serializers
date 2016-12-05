#!/bin/bash

killall gnuplot_x11

gnuplot -persist serialize.gnuplot &
gnuplot -persist size.gnuplot &
gnuplot -persist unserialize.gnuplot &
gnuplot -persist total.gnuplot &
