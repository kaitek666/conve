# conve
A C++ program for fixing missing extensions.

![...](https://img.shields.io/badge/license-CC%20BY--NC--SA%204.0-lightgrey.svg)
![...](https://img.shields.io/github/followers/kaitek666.svg?label=Follow&style=social)

This program is released on under Creative Commons BY-NC-SA 4.0 license. Please refer to LICENSE.txt file for more info.

Currently supported extensions:
* JPG
* PDF
* DOC
* DOCX
* XLS
* XLSX

Finds every file in given directory and judging by their content, renames each file. Guaranteed to work in 99% of cases. Tested on large and small files.

## Requirements
1. Visual Studio 2017 or basically anything that supports C++17
2. LibXL library. Grab it here: http://www.libxl.com/


## How to compile
1. Clone, obviously
2. Download LibXL library.
3. Copy `.lib` file from `lib`, copy all headers into `inc` folder and remember to include the `dll` file from `bin`.
4. Create a solution, use the conve.cpp as a main file.
5. Set C++ version to 17, include the LibXL library
6. Compile. Launch.
7. If it fails to launch, you must have forgotten about the dll file.

## Usage
`conve.exe "path"`

![...](https://i.imgur.com/yd6LXs0.png)

Example: `conve.exe "pliki/"`.

Example output:

![...](https://i.imgur.com/tVIk7S0.png)


## Download precompiled build
https://www113.zippyshare.com/v/Wj3HlS5N/file.html
