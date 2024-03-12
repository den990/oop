@echo off

set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"

%PROGRAM% input1.txt %OUT% Cyberpunk CYBERPUNK || goto err
fc %OUT% out1.txt || goto err

%PROGRAM% input2.txt %OUT% Annette WOMAN || goto err
fc %OUT% out2.txt || goto err

%PROGRAM% input3.txt %OUT% ма мама || goto err
fc %OUT% out3.txt || goto err

%PROGRAM% input4.txt %OUT% ifstream "" || goto arr
fc %OUT% out4.txt || goto err

%PROGRAM% input4.txt >%OUT% 
fc %OUT% empty.txt || goto err

echo All tests passed
exit/B 0

:err
echo Program testing failed :-(
exit/B 1