# GameOfLife
My SFML+TGUI, feature-rich GameOfLife implementation

![Example](https://i.imgur.com/VT5odZD.mp4)

# Build it!
To build it, you need to have SFML and TGUI libraries compiled.
I don't trust CMake find-scripts, so you have to set SFML and TGUI paths in cmake-gui or with command line.
Everything is explained in CMakeLists, but you don't have to open it - just use cmake-gui and check out the variables.

After generating Makefile, just open cmd/terminal window in Makefile directory, and use ``make`` (or ``mingw32-make`` if you are using MinGW) command to build it.

Windows notes: don't forget to copy SFML (graphics, window and *probably* system) and TGUI DLL's to executable directory!

Note: Did not tested the compilation under Linux. If it won't work, make a bug report or something, pretty please, or just wait until i'll run VM.

# Features

For now, GOL logic is inside GameOfLife class. You can set up rules, tickrate and stuff using methods or constructor. It also features responsive tooltip with acutal cell information.
More features (like rule/tickrate/stuff settings GUI) will come later.

Tooltip is disabled by default, uncomment #define in main.cpp to show it.