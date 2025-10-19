::1 == solution dir, 2 == outdir, 3 == project dir, 4 == config
@echo "Copying resources"
robocopy "%~1res" "%~2res" /E /XD "%~1res\raw"

@echo "Copying dlls"
xcopy "%~3lib\*.dll" "%~2" /i/y/s

xcopy "%~3bin\%~4\res\" "%~1Game\lib\" /i/y/s
xcopy "%~3bin\%~4\*.lib" "%~1Game\lib\" /i/y/s
xcopy "%~3bin\%~4\*.dll" "%~1Game\lib\" /i/y/s
xcopy "%~3src\*.h" "%~1\Game\lib\include\Basilisk\" /y
