# Chess tournament viewer

## Supported operating systems
 - Linux(tested on debian based distros - LM21, Ubuntu 22/24)
 - Windows10, Windows11 
 
### Linux
Intall these to libraries.

`sudo apt install qt6-base-dev qt6-webengine-dev libqt6webenginewidgets6 qmake6 build-essential`

Download project and navigete to folder with the Open License Service

`cd /path/to/project`

Run qmake

`qmake6`

Make

`make`

Copy the application binary to a folder (e.g., /opt/chessViewer/)

`cp UltraWide /opt/chessViewer/`

Create deskop file

### Windows
install Qt6 with QtCreator

install MS Visual Studio 19 Tools

The most straightforward is to build the project with QT6 kit in release mode directly in Qt Creator IDE. For the demostration Qt 6.3.2 will be used, but feel free to substitute the version.

Copy the compiled binary to an empty folder.

Create an environment by running the command in command prompt

`C:\Qt\6.3.2\msvc2019_64\bin\qtenv2.bat`
`C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat`

use windeploy tool to deploy the application

`C:\Qt\6.3.2\msvc2019_64\bin\windeployqt.exe /path/to/UltraWide.exe`

Since building QT applications on Windows is quite a pain, the releases come with prebuild windows application


## How to use
Copy tournament url from chess-results (without query parameters, ends with .aspx)
Save the settings.

Choose what kind of information about the tournament you want to show (pairing, standings, starting rank).
Choose number of tabs, round and refresh interval. 

Click show to display N tabs of browser.
