## What is Cim-Obs-Monitors-Info
Cim OBS Monitors is a small command line tool to get the information of monitors.

This program was a prototype to add the function to https://github.com/obsproject/obs-websocket and to the https://github.com/obsproject/obs-studio plugin-api

It is used as a temporory workaround before the changes is accept by obs-websocket. And later I realized it maybe useful as a standalone program.

## Usage
Run the program `obs-monitors-info.exe`. You may also copy the `obs-monitors-info.exe` into OBS bin folder to save size. (Skip the supporting Qt5Core.dll, etc. which are shipped with OBS)

## Example Output
```json
{
    "monitors": [
        {
            "height": 1440,
            "name": "DELL U3419W",
            "width": 3440,
            "x": 0,
            "y": 0
        },
        {
            "height": 1200,
            "name": "DELL U2412M",
            "width": 1920,
            "x": -1920,
            "y": 234
        }
    ]
}
```

## License
It's distributed under the GNU General Public License v2 (or any later version) - see the accompanying COPYING file for more details.

This program copy a large chunk of code from https://github.com/obsproject/obs-studio, which is under GPL.

## Build Instruction
1. Get the qt library
See instruction in https://github.com/obsproject/obs-studio/wiki/Install-Instructions

2. set `CMAKE_PREFIX_PATH` to the Qt path.
- In cmake-gui, set the `CMAKE_PREFIX_PATH` to the Qt path.
  E.g. if the qt is extracted to `C:\github\obs-build\qt`, set the `CMAKE_PREFIX_PATH` to `C:\github\obs-build\qt\msvc2019_64` for x64
- If you are using vscode's cmake, just copy the qt into `qt5` folder. It is already set in the `.vscode/settings.json`

3. build
