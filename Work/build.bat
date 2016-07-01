@echo off

SET ProjectName=SPE_Controller
REM SET ProjectName=STM32F411NUCLEO

REM SET Flavor=debug
SET Flavor=release

call ..\setenv_mdk.cmd 5.05 c:\Keil_v5\ARM

@echo If you want to rebuild, please add "rebuild" argument. Default build mode is "build".

IF "%1" == "" (
	SET BuildMode=build
) ELSE (
	SET BuildMode=%1
)

echo Build Mode :  %BuildMode%

msbuild ..\Solutions\%ProjectName%\dotnetmf.proj /p:flavor=%Flavor% /filelogger /t:%BuildMode% /flp:verbosity=detailed /clp:verbosity=minimal

rem msbuild ..\Solutions\%ProjectName%\TinyBooter\TinyBooter.proj /p:flavor=%Flavor% /filelogger /t:%BuildMode%
rem msbuild ..\Solutions\%ProjectName%\TinyClr\TinyClr.proj /p:flavor=%Flavor% /filelogger /t:%BuildMode%

echo -------------------------------------------------------------------
echo -------------------- Copying output files -------------------------
echo -------------------------------------------------------------------

del Output\*.* /q

mkdir Output
mkdir Output\Bin
copy ..\BuildOutput\THUMB2FP\MDK5.05\le\FLASH\%Flavor%\%ProjectName%\bin\Tinybooter.hex Output\.
copy ..\BuildOutput\THUMB2FP\MDK5.05\le\FLASH\%Flavor%\%ProjectName%\bin\tinyclr.hex\ER_CONFIG Output\ER_CONFIG.hex
copy ..\BuildOutput\THUMB2FP\MDK5.05\le\FLASH\%Flavor%\%ProjectName%\bin\tinyclr.hex\ER_FLASH Output\ER_FLASH.hex
copy ..\BuildOutput\THUMB2FP\MDK5.05\le\FLASH\%Flavor%\%ProjectName%\bin\Tinybooter.bin Output\bin\.
copy ..\BuildOutput\THUMB2FP\MDK5.05\le\FLASH\%Flavor%\%ProjectName%\bin\tinyclr.bin\ER_CONFIG Output\bin\ER_CONFIG.bin
copy ..\BuildOutput\THUMB2FP\MDK5.05\le\FLASH\%Flavor%\%ProjectName%\bin\tinyclr.bin\ER_FLASH Output\bin\ER_FLASH.bin

echo --- Ready to program hex files ---
pause
rem program.bat


