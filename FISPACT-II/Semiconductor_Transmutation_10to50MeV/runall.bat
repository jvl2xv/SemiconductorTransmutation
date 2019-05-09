@echo off

set FISPACT=C:\Users\jvl2x\Downloads\FISPACT-II\bin\fispact.exe

cd InSbBi_5Bi
del *.log ARRAYX* COLLAPX* SHORTINDEX* *.out *.gra *.tab* *.sens *.plt  > NUL 2>&1 
call fisprun.bat 
copy runFile_InSbBi_5Bi.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_10to50MeV\ALL_10to50MeV_Results
cd .. 

cd GaAs
del *.log ARRAYX* COLLAPX* SHORTINDEX* *.out *.gra *.tab* *.sens *.plt  > NUL 2>&1 
call fisprun.bat 
copy runFile_GaAs.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_10to50MeV\ALL_10to50MeV_Results
cd .. 

cd HgCdTe
del *.log ARRAYX* COLLAPX* SHORTINDEX* *.out *.gra *.tab* *.sens *.plt  > NUL 2>&1 
call fisprun.bat 
copy runFile_HgCdTe.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_10to50MeV\ALL_10to50MeV_Results
cd .. 

cd InAs
del *.log ARRAYX* COLLAPX* SHORTINDEX* *.out *.gra *.tab* *.sens *.plt  > NUL 2>&1 
call fisprun.bat 
copy runFile_InAs.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_10to50MeV\ALL_10to50MeV_Results
cd .. 

cd InAsSb
del *.log ARRAYX* COLLAPX* SHORTINDEX* *.out *.gra *.tab* *.sens *.plt  > NUL 2>&1 
call fisprun.bat 
copy runFile_InAsSb.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_10to50MeV\ALL_10to50MeV_Results
cd .. 

cd InSb
del *.log ARRAYX* COLLAPX* SHORTINDEX* *.out *.gra *.tab* *.sens *.plt  > NUL 2>&1 

call fisprun.bat 
copy runFile_InSb.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_10to50MeV\ALL_10to50MeV_Results
cd .. 

cd InSbBi_05Bi
del *.log ARRAYX* COLLAPX* SHORTINDEX* *.out *.gra *.tab* *.sens *.plt  > NUL 2>&1 
call fisprun.bat 
copy runFile_InSbBi_05Bi.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_10to50MeV\ALL_10to50MeV_Results
cd .. 

cd Si
del *.log ARRAYX* COLLAPX* SHORTINDEX* *.out *.gra *.tab* *.sens *.plt  > NUL 2>&1 
call fisprun.bat 
copy runFile_Si.out C:\Users\jvl2x\Downloads\FISPACT-II\Semiconductor_Transmutation_10to50MeV\ALL_10to50MeV_Results
cd .. 

