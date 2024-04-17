clear
gcc arkadspel.c -o .\build\program.exe -O1 -Wall -std=c99 -Wno-missing-braces -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm 
if %errorlevel% == 0 .\build\program.exe