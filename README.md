## Log:
- 23/12/28 : Reconstructed directory structure branch
- 23/12/31 : Complete README 
- 24/ 9/24 : Fix wget agent

## 3rdParty:
- [Jsoncpp](https://github.com/open-source-parsers/jsoncpp)

## Warning:
- Garbled characters will appear under Windows and have not been fixed yet

## Require:
- Debian or other Linux : `sudo apt install wget cmake`
- Windows : <https://cmake.org/download/>

## Usage:
- Compile(Already conclude the COMPILED file in build):
    1. `git clone https://github.com/890mn/NovaPortable-Extract.git`
    2. `cd NovaPortable-Extract/build`
    3. `cmake ..`
    4. `make`
- Run: 
    1. if **Windows** use `$OutputEncoding = [Console]::OutputEncoding = [Text.UTF8Encoding]::UTF8` in **Powershell** before run
    2. `./Nova_Debian`

## Example:
- show list of wallpaper
  - `ls -l`
  ![ls -l](https://github.com/890mn/NovaPortable-Extract/blob/master/example/ls%20-l.png)
  - `ls -x`
  ![ls -x](https://github.com/890mn/NovaPortable-Extract/blob/master/example/ls%20-x.png)
  - `do -s`
  ![do -s](https://github.com/890mn/NovaPortable-Extract/blob/master/example/do%20-s.png)
  - `do -x`
  ![do -x](https://github.com/890mn/NovaPortable-Extract/blob/master/example/do%20-x.png)

## All wallpaper copyright 米哈游miHoYo

