::1 == project dir, 2 == outdir,
@echo "Copying resources"
robocopy "%~1res" "%~2res" /E /XD "%~1res\raw"

@echo "Copying dlls"
xcopy "%~1lib\*.dll" "%~2" /i/y/s

