@echo off

pyuic5 -o ui.py untitled.ui

python maindialog.py
rem python mainwindow.py

pause