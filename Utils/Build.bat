::1 == solution dir
@echo "Copying dlls"
xcopy "%~3lib\*.dll" "%~1\Rendering\lib\" /i/y/s
xcopy "%~3bin\%~4\*.lib" "%~1\Rendering\lib\" /i/y/s
xcopy "%~3bin\%~4\*.dll" "%~1\Rendering\lib\" /i/y/s
xcopy "%~3src\*.h" "%~1\Rendering\lib\include\" /y
