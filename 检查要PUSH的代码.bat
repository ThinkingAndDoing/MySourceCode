@echo off
set g_boHasNewCommit=0

rem step1: goto target dir
cd /d D:\\03SourceCode

rem step2: commit current changes
CALL :CheckStatus
if %g_boHasNewCommit% equ 1 (
	git add .
	git commit --amend
	) else (
	rem commit
	git add .
	git commit -m "Test"
)

rem goto startRun

rem step3: compare the new commit with last commit
for /f "delims=" %%i in ('git rev-parse HEAD') do (set commitid1=%%i)
for /f "delims=" %%i in ('git rev-parse HEAD~1') do (set commitid2=%%i)
echo %commitid1%
echo %commitid2%

git difftool -y -d %commitid1% %commitid2%

:startRun


pause


rem check if is there a new commit to be pushed
:CheckStatus
git status > tmp
findstr "ahead" tmp>nul
if %errorlevel% equ 0 (
  set "g_boHasNewCommit=1"
  ) else (
  set "g_boHasNewCommit=0"
)
del tmp
EXIT /B 0
