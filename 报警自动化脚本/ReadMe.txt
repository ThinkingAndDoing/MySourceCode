# _*_
# description: How to Generate exe
# _*_

Double click Package.bat,generate exe file(./dist)


usage:
如果脚本没有应用程序界面，只有命令提示符窗口
pyinstaller -F test.py
如果脚本有应用程序界面
pyinstaller -F -w test.py 
