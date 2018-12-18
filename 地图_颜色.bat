@echo off
anytoc tank_strat_map.h tank_strat_map.dat 32 "const uint8 strat_map[]="
anytoc tank_strat_col.h tank_strat_map.col 8 "const uint8 strat_col[]="

anytoc tank_sp_col.h tank_sp_col.col 8 "const uint8 sp_col[]="

anytoc tank_stage_map.h tank_stage_map.dat 32 "const uint8 stage_map[]="
anytoc tank_stage_col.h tank_stage_map.col 8 "const uint8 stage_col[]="

anytoc tank_task_map.h  tank_task_map.dat 32 "uint8 task_map[]="
anytoc tank_task_map_back.h  tank_task_map.dat 32 "uint8 task_map_back[]="
anytoc tank_task_col.h tank_task_map.col 8 "const uint8 task_col[]="

anytoc tank_about_map.h  tank_about_map.dat 32 "const uint8 about_map[]="
anytoc tank_about_col.h tank_about_map.col 8 "const uint8 about_col[]="

echo 提示:转换完成！

