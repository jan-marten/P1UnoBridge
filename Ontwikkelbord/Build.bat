@echo off

rem Compile
rem C:\HTSOFT\PIC18\bin\picc18.exe -C -E"Error.log" "main.c" -O"main.obj" -Zg9 -O -ASMLIST -18F452
rem -C: Compile to Object File
rem -Efile: Redirect Compiler Errors to a File
rem -Ofile: Specify Output File
rem -Zg9 -Zg[level]: Global Optimization 1-9
rem -O: Invoke Optimizer
rem -ASMLIST Generate assembler .LST file for each compilation
rem -18F452 

rem Link
rem C:\HTSOFT\PIC18\bin\picc18.exe -E"Error.log" "main.obj" -M"Projectmain.map" -O"Projectmain.cof" -O"Projectmain.hex" -18F452
rem -Efile: Redirect Compiler Errors to a File
rem -Mfile: Generate Map File
rem -Ofile: Specify Output File


rem TODO, gebruik gaan maken van nieuwe XC8 compiler, parameters uitzoeken
rem "C:\Program Files\Microchip\xc8\v2.31\pic\bin\picc18.exe" --chip=18F452 "main.c" -c -E"ErrorXC8.log" -O3 -a"mainXC8.lst"
rem "C:\Program Files\Microchip\xc8\v2.31\pic\bin\picc18.exe" -E"ErrorXC8.log" "mainXC8.obj" -M"P1Bridge.map" -O"P1Bridge.cof" -O"P1Bridge.hex" --chip=18F452



rem Online samples;
rem make -f Makefile CONF=free 
rem make -f nbproject/Makefile-free.mk SUBPROJECTS= .build-conf
rem make  -f nbproject/Makefile-free.mk dist/free/production/testjmr.production.hex
rem "\bin\xc8-cc.exe"  -mcpu=18F452 -c  -fno-short-double -fno-short-float -memi=wordwrite -O0 -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -mext=cci -Wa,-a -DXPRJ_free=free  -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits   -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o build/free/production/newmain.p1 newmain.c 
rem "\bin\xc8-cc.exe"  -mcpu=18F452 -Wl,-Map=dist/free/production/testjmr.production.map  -DXPRJ_free=free  -Wl,--defsym=__MPLAB_BUILD=1  -fno-short-double -fno-short-float -memi=wordwrite -O0 -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -mext=cci -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx032 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto      -Wl,--memorysummary,dist/free/production/memoryfile.xml -o dist/free/production/testjmr.production.elf  build/free/production/newmain.p1     

echo "Done, press enter to close"
pause
