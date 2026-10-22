@echo off
setlocal

set "TARGET=RGBLighting"
set "PORT=COM3"

set "ROOT=%~dp0"
set "SKETCH=%ROOT%%TARGET%\main"
set "LIBRARIES=%ROOT%libraries"
set "BUILD=%ROOT%build"

echo Batch file location: %ROOT%
echo Sketch folder: %SKETCH%
echo Libraries folder: %LIBRARIES%
echo Build folder: %BUILD%

echo.
echo Building LittleFS image...

mklittlefs.exe -c "%ROOT%data" -p 256 -b 4096 -s 0x1E0000 "%BUILD%\littlefs.bin"

if errorlevel 1 (
    echo ERROR: LittleFS image build failed.
    pause
    exit /b 1
)

echo.
echo Uploading LittleFS image to %PORT%...

esptool.exe --chip esp32 --port "%PORT%" write-flash 0x210000 "%BUILD%\littlefs.bin"

if errorlevel 1 (
    echo ERROR: LittleFS upload failed.
    pause
    exit /b 1
)

echo.
echo LittleFS upload complete!
pause