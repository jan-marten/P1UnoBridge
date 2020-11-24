rem Compile en link de code;
C:\HTSOFT\PIC18\bin\picc18.exe -C -E"Error.Compile.log" "main.c" -O"main.obj" -Zg9 -O -ASMLIST -18F452
type "Error.Compile.log" | code -

C:\HTSOFT\PIC18\bin\picc18.exe -E"Error.Link.log" "main.obj" -M"Projectmain.map" -O"Projectmain.cof" -O"Projectmain.hex" -18F452
type "Error.Link.log" | code -
