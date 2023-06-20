#include "raylib.h"
#include <stdio.h>
#include "display.h"
#include "wordle.h"
#include "sound.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame(void);

const int screenWidth = 540, screenHeight = 810;
const char *FJORD = "FJORDGUCKSNYMPHVIBEXWALTZ";

int isGameActive = 0, score = 0;
float timer = 20.;

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Fjordle");
    InitAudioDevice();
    
    LoadFonts();
    LoadSounds();

    AllocateWordleBuffers();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        UpdateDrawFrame();
    }
#endif

    UnloadFonts();
    UnloadSounds();

    CloseAudioDevice();
    CloseWindow();

    FreeWordleBuffers();

    return 0;
}

void UpdateDrawFrame(void)
{
    if (isGameActive)
    {
        int didBackspace = IsKeyPressed(KEY_BACKSPACE);
        int didTypeLetter = FillBufferFromInput(GetCharPressed, didBackspace);

        if (didTypeLetter || didBackspace)
        {
            PlayTypeSound(guessBufferLength);
        }

        if (didTypeLetter && IsSolutionCorrect())
        {
            PlayWinSound();
            timer += 5.;
            score++;
            RefreshSolution(FJORD, 1);
        }

        if (IsKeyPressed(KEY_TAB))
        {
            PlayTypeSound(-1);
            PlaySkipSound();
            RefreshSolution(FJORD, 0);
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            PlayTypeSound(-1);
            ClearGuessBuffer(0);
        }

        timer -= GetFrameTime();

        if (timer <= 0)
        {
            PlayLoseSound();
            ClearGuessBuffer(1);
            timer = 0.;
            isGameActive = 0;
        }
    }
    else
    {
        if (IsKeyPressed(KEY_GRAVE))
        {
            PlayWinSound();
            timer = 20.;
            score = 0;
            isGameActive = 1;
            RefreshSolution(FJORD, 1);
        }
    }

    UpdateDisplayInfo();

    BeginDrawing();
    {
        DrawBackground();
        DrawLetterBoxes(FJORD, solutionPattern);
        DrawGuessBuffer(guessBuffer);
        DrawMissBuffer(missBuffer);

        DrawGameData(isGameActive, score, timer);
    }
    EndDrawing();
}