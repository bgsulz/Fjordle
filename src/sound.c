#include "raylib.h"

static Sound win, skip, type, lose;

void LoadSounds()
{
    win = LoadSound("res/win.wav");
    skip = LoadSound("res/skip.wav");
    type = LoadSound("res/key.wav");
    lose = LoadSound("res/lose.wav");
}

void UnloadSounds()
{
    UnloadSound(win);
    UnloadSound(skip);
    UnloadSound(type);
    UnloadSound(lose);
}

void PlayWinSound()
{
    PlaySound(win);
}

void PlaySkipSound()
{
    PlaySound(skip);
}

void PlayTypeSound(int pitch)
{
    SetSoundPitch(type, pitch < 0 ? 1 : 0.3 + 0.2 * pitch);
    PlaySound(type);
}

void PlayLoseSound()
{
    PlaySound(lose);
}