@echo off
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -c SWD -ME -V "while_programming" -p "Output\Tinybooter.hex" -p "Output\ER_CONFIG.hex" -p "Output\ER_FLASH.hex" -Rst

pause
