 rem Compile en link de code;
 C:\HTSOFT\PIC18\bin\picc18.exe -C -E"Error.log" "main.c" -O"main.obj" -Zg9 -O -ASMLIST -18F452
 C:\HTSOFT\PIC18\bin\picc18.exe -E"Error.log" "main.obj" -M"Projectmain.map" -O"Projectmain.cof" -O"Projectmain.hex" -18F452

rem TODO, gebruik gaan maken van nieuwe XC8 compiler, parameters uitzoeken
rem "C:\Program Files\Microchip\xc8\v2.31\pic\bin\picc18.exe" -C -E"ErrorXC8.log" "main.c" -O"mainXC8.obj" -Zg9 -O -ASMLIST --chip=18F452
rem "C:\Program Files\Microchip\xc8\v2.31\pic\bin\picc18.exe" -E"ErrorXC8.log" "mainXC8.obj" -M"P1Bridge.map" -O"P1Bridge.cof" -O"P1Bridge.hex" --chip=18F452
