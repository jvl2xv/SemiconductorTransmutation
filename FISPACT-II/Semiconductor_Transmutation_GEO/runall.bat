@echo off

set FISPACT=C:\Users\jvl2x\Downloads\FISPACT-II\bin\fispact.exe

cd GaAs
call fisprun.bat 
copy runFile_GaAs.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_GEO\ALL_RESULTS
cd .. 

cd HgCdTe
call fisprun.bat 
copy runFile_HgCdTe.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_GEO\ALL_RESULTS
cd .. 

cd InAs
call fisprun.bat 
copy runFile_InAs.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_GEO\ALL_RESULTS
cd .. 

cd InAsSb
call fisprun.bat 
copy runFile_InAsSb.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_GEO\ALL_RESULTS
cd .. 

cd InSb
call fisprun.bat 
copy runFile_InSb.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_GEO\ALL_RESULTS
cd .. 

cd InSbBi_05Bi
call fisprun.bat 
copy runFile_InSbBi_05Bi.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_GEO\ALL_RESULTS
cd .. 

cd InSbBi_5Bi
call fisprun.bat 
copy runFile_InSbBi_5Bi.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_GEO\ALL_RESULTS
cd .. 

cd Si
call fisprun.bat 
copy runFile_Si.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_GEO\ALL_RESULTS
cd .. 

