@echo off 

REM Test case name: Tst_162prot

echo Running convert....
%FISPACT% convert files  > NUL 2>&1

echo Running collapse....
%FISPACT% collapse files  > NUL 2>&1

echo Running condense....
%FISPACT% condense files  > NUL 2>&1

echo Running print....
%FISPACT% printlib files  > NUL 2>&1

echo Running execution....
%FISPACT% runFile_InAsSb files  > NUL 2>&1
