@echo off
replace Nes.nes Nes_output.nes chr.chr 32784 8192
del Nes_output.nes
ren Nes.nes Nes_output.nes
echo 提示:替换完成！