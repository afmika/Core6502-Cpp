echo Building... 
echo

g++ -fpermissive -std=c++14 -c ./../component/*.h
g++ -fpermissive -std=c++14 -c ./../component/*.cpp
g++ -fpermissive -std=c++14 -c *.cpp

g++ *.o -o ./bin/cpu6502
./bin/cpu6502