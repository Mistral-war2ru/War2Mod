@echo off
set PATH=C:\MinGW\bin;C:\MinGW\msys\1.0\bin
@rem set PATH=C:\Win-builds\bin
@rem ;C:\win-builds-patch-32\bin
@rem gmake clean
mingw32-make clean
mingw32-make
@rem gmake
pause
