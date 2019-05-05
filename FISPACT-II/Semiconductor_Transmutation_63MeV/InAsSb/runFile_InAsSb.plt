set terminal postscript landscape enhanced colour
set output "runFile_InAsSb.gra.ps"
#--------------------------------------------------
#          Activity (Bq/k
set title "Quasi-MonE(63 MeV) 3.20200E+11 cm^-2s^-"
set xlabel "Time after irradiation (years)"
set ylabel "Activity (Bq/kg)"
set logscale xy
set xrange [ 1.00000E-06: 1.00000E+00]
set yrange [*:]
#
set bmargin 6
set label "file name = runFile_InAsSb.gra          run timestamp = 21:26:02 4 May 2019" \
 at character 1,1 font "Helvetica,8pt"
plot \
     "runFile_InAsSb.gra" index   0 using 1:($2)-($3):($2)+($3)  with filledcurves linecolor rgbcolor "#cbcbcb" notitle, \
     "runFile_InAsSb.gra" index   0 using 1:2 title  "         Activity (Bq/kg)" with lines linetype 1 linecolor rgbcolor "red", \
     "runFile_InAsSb.gra" index   0 using 1:2:3 with yerrorbars title "Uncertainty" linetype 1 linecolor rgb "black", \
     "runFile_InAsSb.gra" index   1 using 1:2 title "value/t-half for nuclide" pointtype 1 linecolor rgbcolor "forest-green", \
     "runFile_InAsSb.gra" index   1 using (0.8*$1):2:3 with labels notitle textcolor rgbcolor "forest-green" right font "helveticabold,11"
unset label
# pause -1  "Hit return to continue"
#--------------------------------------------------
#          Dose Rate (Sv/
set title "Quasi-MonE(63 MeV) 3.20200E+11 cm^-2s^-"
set xlabel "Time after irradiation (years)"
set ylabel "Dose Rate (Sv/h)"
set logscale xy
set xrange [ 1.00000E-06: 1.00000E+00]
set yrange [*:]
#
set bmargin 6
set label "file name = runFile_InAsSb.gra          run timestamp = 21:26:02 4 May 2019" \
 at character 1,1 font "Helvetica,8pt"
plot \
     "runFile_InAsSb.gra" index   2 using 1:($2)-($3):($2)+($3)  with filledcurves linecolor rgbcolor "#cbcbcb" notitle, \
     "runFile_InAsSb.gra" index   2 using 1:2 title  "         Dose Rate (Sv/h)" with lines linetype 1 linecolor rgbcolor "red", \
     "runFile_InAsSb.gra" index   2 using 1:2:3 with yerrorbars title "Uncertainty" linetype 1 linecolor rgb "black", \
     "runFile_InAsSb.gra" index   3 using 1:2 title "value/t-half for nuclide" pointtype 1 linecolor rgbcolor "forest-green", \
     "runFile_InAsSb.gra" index   3 using (0.8*$1):2:3 with labels notitle textcolor rgbcolor "forest-green" right font "helveticabold,11"
unset label
# pause -1  "Hit return to continue"
#--------------------------------------------------
#       Heat Output (kW/k
set title "Quasi-MonE(63 MeV) 3.20200E+11 cm^-2s^-"
set xlabel "Time after irradiation (years)"
set ylabel "Heat Output (kW/kg)"
set logscale xy
set xrange [ 1.00000E-06: 1.00000E+00]
set yrange [*:]
#
set bmargin 6
set label "file name = runFile_InAsSb.gra          run timestamp = 21:26:02 4 May 2019" \
 at character 1,1 font "Helvetica,8pt"
plot \
     "runFile_InAsSb.gra" index   4 using 1:($2)-($3):($2)+($3)  with filledcurves linecolor rgbcolor "#cbcbcb" notitle, \
     "runFile_InAsSb.gra" index   4 using 1:2 title  "      Heat Output (kW/kg)" with lines linetype 1 linecolor rgbcolor "red", \
     "runFile_InAsSb.gra" index   4 using 1:2:3 with yerrorbars title "Uncertainty" linetype 1 linecolor rgb "black", \
     "runFile_InAsSb.gra" index   5 using 1:2 title "value/t-half for nuclide" pointtype 1 linecolor rgbcolor "forest-green", \
     "runFile_InAsSb.gra" index   5 using (0.8*$1):2:3 with labels notitle textcolor rgbcolor "forest-green" right font "helveticabold,11"
unset label
# pause -1  "Hit return to continue"
#--------------------------------------------------
#    Ingestion Dose (Sv/k
set title "Quasi-MonE(63 MeV) 3.20200E+11 cm^-2s^-"
set xlabel "Time after irradiation (years)"
set ylabel "Ingestion Dose (Sv/kg)"
set logscale xy
set xrange [ 1.00000E-06: 1.00000E+00]
set yrange [*:]
#
set bmargin 6
set label "file name = runFile_InAsSb.gra          run timestamp = 21:26:02 4 May 2019" \
 at character 1,1 font "Helvetica,8pt"
plot \
     "runFile_InAsSb.gra" index   6 using 1:($2)-($3):($2)+($3)  with filledcurves linecolor rgbcolor "#cbcbcb" notitle, \
     "runFile_InAsSb.gra" index   6 using 1:2 title  "   Ingestion Dose (Sv/kg)" with lines linetype 1 linecolor rgbcolor "red", \
     "runFile_InAsSb.gra" index   6 using 1:2:3 with yerrorbars title "Uncertainty" linetype 1 linecolor rgb "black", \
     "runFile_InAsSb.gra" index   7 using 1:2 title "value/t-half for nuclide" pointtype 1 linecolor rgbcolor "forest-green", \
     "runFile_InAsSb.gra" index   7 using (0.8*$1):2:3 with labels notitle textcolor rgbcolor "forest-green" right font "helveticabold,11"
unset label
# pause -1  "Hit return to continue"
#--------------------------------------------------
#   Inhalation Dose (Sv/k
set title "Quasi-MonE(63 MeV) 3.20200E+11 cm^-2s^-"
set xlabel "Time after irradiation (years)"
set ylabel "Inhalation Dose (Sv/kg)"
set logscale xy
set xrange [ 1.00000E-06: 1.00000E+00]
set yrange [*:]
#
set bmargin 6
set label "file name = runFile_InAsSb.gra          run timestamp = 21:26:02 4 May 2019" \
 at character 1,1 font "Helvetica,8pt"
plot \
     "runFile_InAsSb.gra" index   8 using 1:($2)-($3):($2)+($3)  with filledcurves linecolor rgbcolor "#cbcbcb" notitle, \
     "runFile_InAsSb.gra" index   8 using 1:2 title  "  Inhalation Dose (Sv/kg)" with lines linetype 1 linecolor rgbcolor "red", \
     "runFile_InAsSb.gra" index   8 using 1:2:3 with yerrorbars title "Uncertainty" linetype 1 linecolor rgb "black", \
     "runFile_InAsSb.gra" index   9 using 1:2 title "value/t-half for nuclide" pointtype 1 linecolor rgbcolor "forest-green", \
     "runFile_InAsSb.gra" index   9 using (0.8*$1):2:3 with labels notitle textcolor rgbcolor "forest-green" right font "helveticabold,11"
unset label
# pause -1  "Hit return to continue"
