::1 == solution dir
@echo "Copying dlls"
xcopy "%~3lib\*.dll" "%~1\Engine\lib\" /i/y/s
xcopy "%~3lib\*.lib" "%~1\Engine\lib\" /i/y/s
xcopy "%~3lib\include\*.h" "%~1\Engine\lib\include\" /y
xcopy "%~3bin\%~4\*.lib" "%~1\Engine\lib\" /i/y/s
xcopy "%~3bin\%~4\*.dll" "%~1\Engine\lib\" /i/y/s
xcopy "%~3src\*.h" "%~1\Engine\lib\include\" /y
