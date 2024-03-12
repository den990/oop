set PROGRAM="%~1"

set OUT="%TEMP%\out.txt"


%PROGRAM% 6 %OUT% || goto err
fc %OUT% Result_from_6.txt || goto err

%PROGRAM% 0 %OUT% || goto err
fc %OUT% Result_from_0.txt || goto err

%PROGRAM% 255 %OUT% || goto err
fc %OUT% Result_from_255.txt || goto err

%PROGRAM% 209 %OUT% || goto err
fc %OUT% Result_from_209.txt || goto err

%PROGRAM% fkds %OUT% >%OUT% 
fc %OUT% Result_from_fkds.txt || goto err

%PROGRAM% >%OUT%
fc %OUT% empty.txt || goto err

echo All tests passed
exit/B 0

:err
echo Program testing failed :-(
exit/B 1