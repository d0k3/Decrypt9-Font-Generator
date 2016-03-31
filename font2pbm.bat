@echo off
rd /s /q output
md output
cfont2raw
makepgm -pbm -w8 font.raw
move font.raw output
move font_raw.pbm output
