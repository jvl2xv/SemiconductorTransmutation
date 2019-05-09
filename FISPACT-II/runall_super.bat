@echo off

set FISPACT=C:\Users\jvl2x\Downloads\FISPACT-II\bin\fispact.exe

cd Semiconductor_Transmutation_LEO-900KM
call runall.bat 
cd .. 

cd Semiconductor_Transmutation_MEO
call runall.bat 
cd .. 

cd Semiconductor_Transmutation_GEO
call runall.bat 
cd .. 

cd Semiconductor_Transmutation_LEO-ISS
call runall.bat 
cd .. 

