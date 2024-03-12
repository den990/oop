@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% 1.bmp %OUT% || goto err
fc %OUT% 1.txt || goto err

%PROGRAM% 2.bmp %OUT% || goto err
fc %OUT% 2.txt || goto err

%PROGRAM% empty.txt %OUT% >%OUT%
fc %OUT% out_empty.txt || goto err

%PROGRAM% >%OUT%
fc %OUT% out_not_input_file.txt || goto err

echo All tests passed
exit/B 0

:err
echo Program testing failed :-(
exit/B 1