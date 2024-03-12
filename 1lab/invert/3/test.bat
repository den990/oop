@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% matrix1.txt >%OUT% || goto err
fc %OUT% invert_matrix1.txt || goto err

%PROGRAM% matrix2.txt >%OUT% || goto err
fc %OUT% invert_matrix2.txt || goto err

%PROGRAM% matrix3.txt >%OUT%
fc %OUT% invert_matrix3.txt || goto err

%PROGRAM% matrix4.txt >%OUT%
fc %OUT% invert_matrix4.txt || goto err

%PROGRAM% matrix5.txt >%OUT%
fc %OUT% invert_matrix5.txt || goto err

echo All tests passed
exit/B 0

:err
echo Program testing failed :-(
exit/B 1