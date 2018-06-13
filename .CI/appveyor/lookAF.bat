@ECHO OFF
SET LookForFile="C:\Program Files\ArrayFire\v3\lib\afcuda.dll"

:CheckForFile
IF EXIST %LookForFile% GOTO FoundIt

REM If we get here, the file is not found.

REM Wait 60 seconds and then recheck.
REM If no delay is needed, comment/remove the timeout line.
TIMEOUT /T 60 >nul

GOTO CheckForFile


:FoundIt
ECHO Found: %LookForFile%