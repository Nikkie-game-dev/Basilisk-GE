::1 == solution dir, 2 == outdir, 3 == project dir, 4 == config
@echo "Copying resources"
xcopy "%~3res\assets\" "%~2res\" /i/y/s

@echo "Copying dlls"
xcopy "%~3lib\*.dll" "%~2" /i/y/s

xcopy "%~3bin\%~4\res\" "%~1Game\lib\" /i/y/s
xcopy "%~3bin\%~4\*.lib" "%~1Game\lib\" /i/y/s
xcopy "%~3bin\%~4\*.dll" "%~1Game\lib\" /i/y/s
xcopy "%~3src\BaseGame.h" "%~1\Game\lib\include\Basilisk\" /y
xcopy "%~3src\Renderer.h" "%~1\Game\lib\include\Basilisk\" /y