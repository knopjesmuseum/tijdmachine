@echo off


set src=plant2.mov
set dst=plant2-gop1.mov
ffmpeg -i %src% -sameq -g 1 %dst%

rem ---------------------------------------





rem ffmpeg --help




rem -startframe 1500 
rem -fs 100000000 