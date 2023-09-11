clear
rm Build/Arkadspel
cc arkadspel.c `pkg-config --libs --cflags raylib` -o Build/Arkadspel
./Arkadspel