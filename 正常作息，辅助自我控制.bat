at 22:31 /every:M,T,W,Th,F,S,Su shutdown -s -f -t 0
at 23:31 /every:M,T,W,Th,F,S,Su shutdown -s -f -t 0
at 0:30 /every:M,T,W,Th,F,S,Su shutdown -s -f -t 0
at 1:00 /every:M,T,W,Th,F,S,Su shutdown -s -f -t 0
at 1:30 /every:M,T,W,Th,F,S,Su shutdown -s -f -t 0
at 2:00 /every:M,T,W,Th,F,S,Su shutdown -s -f -t 0
at 2:30 /every:M,T,W,Th,F,S,Su shutdown -s -f -t 0
schtasks /create /tn "shutdown22" /tr "shutdown -s -f -t 0" /sc daily /st 22:10