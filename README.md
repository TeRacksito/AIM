# AIM

Simple clone of VIM

## Installation

There is a [pkglist.txt](https://github.com/TeRacksito/AIM/blob/main/pkglist.txt) that contains all apt dependecies. You can install all together using:

```bash
sudo apt install $(cat pkglist.txt) -y
```
## Setup

If you want to build and run easily with VSCode, then you should have some kind of running process. You can copy this one:

#### `.vscode/launch.json`
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "CMake Launch (gdb)",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/AIM",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "CMake Build",
        }
    ]
}
```

#### `.vscode/tasks.json`
```json
{
    "tasks": [
        {
            "label": "CMake Build",
            "type": "shell",
            "command": "cmake",
            "args": [
                "--build",
                "${workspaceFolder}/build"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Build CMake project",
            "problemMatcher": "$gcc"
        }
    ],
    "version": "2.0.0"
}
```