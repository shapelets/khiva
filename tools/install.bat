@echo off
REM Usage: install.bat <path_to_vcpkg>

IF "%1"=="" (
	echo "Please, provide your path to vcpkg"
	EXIT
)
IF NOT exist %1\vcpkg.exe (
	echo "Incorrect path to your vcpkg installation. Please, check that the file vcpkg.exe exists in the provided location."
	EXIT
)
set path_to_vpkg=%1
CALL :checkCommand "choco install cmake.install" "Please, check your chocolatey installation"
CALL :checkCommand "choco install doxygen.install" "Please, check your chocolatey installation"
CALL :checkCommand "choco install graphviz" "Please, check your chocolatey installation"
CALL :checkCommand "python -m pip install --upgrade pip" "Please, check your python installation"
CALL :checkCommand "pip3 install sphinx breathe sphinx_rtd_theme" "Please, check your pip3 installation"
CALL :checkCommand "vcpkg install --triplet x64-windows gtest eigen3 benchmark boost" "Please, check your vcpkg installation and make sure it is in your path"
mkdir ..\build
cd ..\build
cmake .. -DCMAKE_TOOLCHAIN_FILE="%path_to_vpkg%/scripts/buildsystems/vcpkg.cmake" -DKHIVA_USE_CONAN=OFF -G "Visual Studio 15 2017 Win64"
cmake --build . --config Release -- /m


GOTO:EOF

:checkCommand
%~1
IF %ERRORLEVEL%==0 (
	echo "Command exists"
) ELSE (
	echo %~2
	EXIT
)
