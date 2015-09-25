@echo off
@echo if you want to do full chip erase, please add "-ME" option
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -c SWD %1 -V "while_programming" -p "Output\Tinybooter.hex" -p "Output\ER_CONFIG.hex" -p "Output\ER_FLASH.hex" -Rst

