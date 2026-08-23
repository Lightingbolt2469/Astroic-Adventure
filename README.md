# Astroic Adventure

A game made in C++ Raylib. You are a alien which wants to go to his planet and deals with asteroids on his way. If you hit 100 asteroids you win, and if you lose all your lives or get 0 as your score you lose

# How to install (Windows)

Go to code.visualstudio.com, click the big Download for Windows button, run the installer, and click Next through all the default options. This is the program you'll write and run code in.

Go to github.com/skeeto/w64devkit, click Releases on the right side, download the newest w64devkit-x.x.x.zip file. Right-click the downloaded zip, choose 'Extract All', and extract it to C:\ so you end up with a folder at C:\w64devkit. This gives you the C++ compiler.

Press the Windows key, type 'env', click 'Edit the system environment variables'. In the window that opens, click the 'Environment Variables' button. Under 'System variables', find the row called 'Path', click it, click 'Edit'. Click 'New' and type C:\w64devkit\bin. Click OK on every window until they're all closed.

Open VS Code. Click Terminal at the top, then New Terminal. A black text box opens at the bottom. Type g++ --version and press Enter. If you see a version number printed, it worked. If you see 'not recognized', restart your computer and try again (Windows sometimes needs a restart to notice the Path change).

Go to github.com/raysan5/raylib/releases. Scroll to the newest release, click 'Assets' to expand the list, and download the file that ends in win64_mingw-w64.zip (do NOT pick the one that says msvc or the plain source code zip). Extract it to C:\ so you get a folder at C:\raylib.

Go to github.com/Lightingbolt2469/Astroic-Adventure, click the green 'Code' button, click 'Download ZIP'. Right-click the downloaded zip and 'Extract All' to a simple folder like C:\MyGame. In VS Code, click File then 'Open Folder', and select that C:\MyGame folder.

In the VS Code terminal (Terminal > New Terminal), make sure you're inside the project folder, then paste this command, replacing main.cpp with your actual file name if different: g++ main.cpp -o game.exe -I C:\raylib\include -L C:\raylib\lib -lraylib -lopengl32 -lgdi32 -lwinmm -static-libgcc -static-libstdc++ then press Enter.