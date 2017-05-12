set app=mailwatching.exe
(echo Set objShell = CreateObject("Wscript.Shell"^)
echo objShell.Run("%app%"^), 0, TRUE)>runapp.vbs
start "" runapp.vbs