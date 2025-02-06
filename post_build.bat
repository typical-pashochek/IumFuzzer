@echo off
python ../build/trustlet_prepare.py -i ..\x64\Release\IumFuzzer.exe -o ..\IumFuzzer.exe
copy ..\x64\Release\IumFuzzerController.exe ..\IumFuzzerController.exe
pause
