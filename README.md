# JoePhys

This is a simple physics engine which I decided to make for my TY physics project. I hope that my teacher will like it :)

## Building

### Building on Windows
Requirements:  
* You must have CMake installed (https://cmake.org/download/)  
* You must have Git installed (https://git-scm.com/downloads)

Open powershell and navigate to where you want the JoePhys main folder to be downloaded. You can clone the JoePhys repository using Git:
```sh
git clone https://github.com/Sonryle/JoePhys
cd JoePhys
```
Then build the project:
```sh
mkdir build
cd build
cmake ..
```
In JoePhys/build you will be met with a Visual Studio project file (JoePhys.sln) use this to compile the project.

#### If you don't want to install Visual Studio
If you simply want to enjoy JoePhys without having to install visual studio, the process would look something like this:
```sh
git clone https://github.com/Sonryle/JoePhys
cd JoePhys
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
The resulting JoePhys.exe file will be in JoePhys/build/Release/JoePhys.exe
### Building on Linux
Requirements:  
* You must have CMake installed
* You must have Git installed

In your terminal simply clone the repo, generate the make files with CMake and then build the project
```bash
git clone https://github.com/Sonryle/JoePhys
cd JoePhys
mkdir build
cd build
cmake ..
make
```
The resulting JoePhys executable will be in JoePhys/build/JoePhys

## Other Useful Information

### Resource directory ("JoePhys/res")
If you want to make changes to this code, it is important that I warn you about how the resource directory ("JoePhys/res") is handled.

* All of the resources in this folder are needed during runtime and NOT during the compilation of JoePhys. Whenever the project is compiled,
the resource folder is copied to "${CMAKE_SOURCE_DIR}/res" and "${CMAKE_BINARY_DIR}/res.

  * This is so that the resulting JoePhys executable will always have a copy of the resource folder. The annoying part is that the build commands
which copy the resource directory are ONLY triggered when a file in JoePhys gets compiled.

* "Make" on Linux and "Build" in Visual Studio will only recompile and link the files which have been modified, and if no files have been modified
then they won't do anything and the build commands responsible for copying the resource folder will not be triggered.

  * So when you make any changes to the resource folder, you either have to make a change to a source file so that the file gets recompiled and
the build commands are triggered, OR you have to rebuild the whole project. ("make -B" on Linux, and "Rebuild" on Visual Studio)
