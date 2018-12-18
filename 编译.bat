@echo off
IF not EXIST Nes_output.nes goto build
del Nes_output.nes
:build
echo 正在编译.....
cl65 -o Nes_output.nes -t nes *.c
IF not EXIST Nes_output.nes goto end
replace Nes.nes Nes_output.nes chr.chr 32784 8192
del Nes_output.nes
ren Nes.nes Nes_output.nes
echo 提示:编译完成！
exit
:end
echo 提示:编译失败！




