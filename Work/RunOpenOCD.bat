@echo off

SET ConfigFile=..\Solutions\STM32F746NUCLEO\vs\netmf_stm32f746nucleo.cfg
SET OCDPath=D:\Backup\Development Tools\OpenOCD-20160901\bin

ECHO ConfigFile = %ConfigFile%
ECHO.

"%OCDPath%\openocd.exe" -s "%OCDPath%" -f "%ConfigFile%"
