@echo off
echo ���ڱ���.....
cc65 -t nes Nes.c 
cc65 -t nes comm.c
ca65 -t nes Nes.s
ca65 -t nes comm.s
pause
