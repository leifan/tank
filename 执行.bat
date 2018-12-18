@echo off
IF not EXIST Nes_output.nes goto end
echo 正在打开模拟器......
start F:\游戏\模拟器\FC模拟器+VirtuaNes+V0.97中文版\VirtuaNES.exe Nes_output.nes
echo 提示:打开程序成功！
exit
:erro
echo 提示:打开程序出错！
exit
:end
echo 提示:没有可执行的NES文件!
exit
