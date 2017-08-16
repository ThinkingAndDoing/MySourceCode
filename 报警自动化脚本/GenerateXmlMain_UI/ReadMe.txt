# _*_
# author: zhucuicui date:2016-10-31
# description: How to Generate exe
# _*_

Double click Package.bat,generate exe file(./dist)



# _*_
# author: zhucuicui date:2016-10-31
# description: How to use the small tool
# _*_
#Rules

1. "GenerateXmlMain_UI.exe" and "python.gif" and "Geely_FE6_WarningConfiguration.xlsm" must be placed in the same folder; 
2. Modify the configure file "Geely_FE6_WarningConfiguration.xlsm",you should flow the file's structure.
3. Please check the checkbox to choose which item you want to generate,then click Genertating button.
4. If Generated failed,Please check the relevant generated log files.
5. [Press check Image],it will check configured Image items which configured in "Geely_FE6_WarningConfiguration.xlsm" whether correspond to the Generated Image files.
6. [Press check String],it will check configured String items which configured in "Geely_FE6_WarningConfiguration.xlsm" whether correspond to the Generated String files.
7. [Press Open--] Choose the path of pictures which you want to add prefix.
8. Enter the prefix you want to add ,then click Rename button to batch rename pictures.

usage:
如果脚本没有应用程序界面，只有命令提示符窗口
pyinstaller -F test.py
如果脚本有应用程序界面
pyinstaller -F -w test.py 
