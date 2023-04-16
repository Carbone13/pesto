@echo OFF
REM call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
cmake -G Ninja -S . -B .build -DCMAKE_C_COMPILER="cl.exe" -DCMAKE_CXX_COMPILER="cl.exe" -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build .build -j12
.build\pesto.exe
