@echo off
IF not EXIST Nes_output.nes goto build
del Nes_output.nes
:build
echo ���ڱ���.....
cl65 -o Nes_output.nes -t nes *.c
IF not EXIST Nes_output.nes goto end
replace Nes.nes Nes_output.nes chr.chr 32784 8192
del Nes_output.nes
ren Nes.nes Nes_output.nes
echo ��ʾ:������ɣ�
exit
:end
echo ��ʾ:����ʧ�ܣ�




