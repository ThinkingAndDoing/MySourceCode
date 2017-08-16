@echo off
rem delete the files which last time generated.
del .\\GeneratorMainUI.spec

rd __pycache__  /s /q
rd build /s /q
rd dist /s /q

pyinstaller -F -w --windowed --noconsole -i .\\ico.ico .\\GeneratorMainUI.py
echo wait one second
rem The number followed n,is the second need to wait. 
ping -n 3 127.0.0.1>nul  
copy .\dist\GeneratorMainUI.exe .\..\
copy .\python.gif .\..\

del .\\GeneratorMainUI.spec
rd __pycache__  /s /q
rd build /s /q
rd dist /s /q

echo excute finish .....
