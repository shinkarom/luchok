#pragma once

void CreateLua();
bool LoadFile(char* fileName);
void RunLua();
void CallVBlank();
void ProcessDelayTimer();
void ProcessSoundTimer();
void DeleteLua();