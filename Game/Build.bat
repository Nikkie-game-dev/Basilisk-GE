::1 == project dir, 2 == outdir,
@echo "Copying resources"
xcopy "%~1res\assets\" "%~2res\" /i/y/s

@echo "Copying dlls"
xcopy "%~1lib\*.dll" "%~2" /i/y/s

