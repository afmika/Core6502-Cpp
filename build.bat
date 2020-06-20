@echo off
echo Building... 
echo
g++ -std=c++14 -c .\component\*.h
g++ -std=c++14 -c .\component\*.cpp
g++ -std=c++14 -c *.cpp

g++ *.o -o .\bin\cpu6502.exe 
.\bin\cpu6502.exe