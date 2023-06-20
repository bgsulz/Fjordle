#include "raylib.h"
#include "display.h"
#include <ctype.h>
#include <stdio.h>

static int boxSize, boxMargin, fontSize, xOffset;

static Font pixantiqua;
static Color greenLetterbox = {0, 120, 110, 255};   //{125, 255, 150, 255};
static Color yellowLetterbox = {255, 195, 55, 255}; //{255, 225, 125, 255};
static Color blankLetterbox = {220, 220, 220, 255};
static Color background = {20, 25, 30, 255};
static Color subtitleText = {60, 75, 90, 255};

static void DrawTextPixantiqua(const char *text, int x, int y, Color color, int fontSize)
{
    DrawTextEx(pixantiqua, text, (Vector2){x, y}, fontSize, fontSize * 0.2, color);
}

static Color CharToColor(char letter)
{
    switch (letter)
    {
    case 'g':
        return greenLetterbox;
        break;
    case 'y':
        return yellowLetterbox;
        break;
    case 'b':
        return blankLetterbox;
        break;
    default:
        return background;
        break;
    }
}

static Color CharToTextColor(char letter)
{
    switch (letter)
    {
    case 'g':
        return blankLetterbox;
        break;
    case 'y':
        return background;
        break;
    case 'b':
        return background;
        break;
    default:
        return subtitleText;
        break;
    }
}

static void DrawLetterBox(int x, int y, char letter, char color)
{
    char letterTerminated[2] = {(char)toupper(letter), '\0'};
    int textWidth = MeasureTextEx(pixantiqua, letterTerminated, fontSize, fontSize * 0.2).x;

    if (color != 'x')
    {
        const float roundness = 0.1;
        const int segments = 1;
        DrawRectangleRounded((Rectangle){x, y + boxMargin * 2, boxSize, boxSize}, roundness, segments, subtitleText);
        DrawRectangleRounded((Rectangle){x, y, boxSize, boxSize}, roundness, segments, CharToColor(color));

        Rectangle innerRect = (Rectangle){x + boxMargin * 2, y + boxMargin * 2, boxSize - boxMargin * 4, boxSize - boxMargin * 4};
        DrawRectangleRoundedLines(innerRect, roundness / 2, segments, boxMargin, CharToTextColor(color));
    }

    int xPosLetter = x + boxSize / 2 - textWidth / 2;
    int yPosLetter = y + boxSize * 0.3;
    Color colorLetter = CharToTextColor(color);
    DrawTextPixantiqua(letterTerminated, xPosLetter, yPosLetter, colorLetter, fontSize);
}

static void DrawBuffer(char *buffer, const int y, char color)
{
    bool terminated = false;
    for (int i = 0; i < 5; i++)
    {
        const int x = xOffset + i * (boxSize + boxMargin);
        const char letter = buffer[i];
        if (letter == '\0')
            terminated = true;
        DrawLetterBox(x, y, terminated ? ' ' : letter, color);
    }
}

void LoadFonts()
{
    pixantiqua = LoadFont("res/pixantiqua.png");
}

void UnloadFonts()
{
    UnloadFont(pixantiqua);
}

void UpdateDisplayInfo()
{
    boxSize = (int)(GetScreenHeight() / 13.5);
    boxMargin = boxSize / 20;
    fontSize = boxSize / 2;
    xOffset = (GetScreenWidth() - (5 * boxSize) - (4 * boxMargin)) / 2;
}

void DrawBackground()
{
    ClearBackground(background);
}

void DrawGameData(int isGameActive, int score, float timer)
{
    int y = GetScreenHeight() - boxSize * 3;

    if (!isGameActive)
    {
        DrawTextPixantiqua("Skip: TAB", xOffset, y - fontSize * 3.3, subtitleText, fontSize);
        DrawTextPixantiqua("Start: ~ KEY", xOffset, y - fontSize * 2.2, subtitleText, fontSize);
    }

    const char *scoreBuffer = TextFormat("Score: %i", score);
    const char *timerBuffer = TextFormat("Time: %.2f", timer);

    DrawTextPixantiqua(scoreBuffer, xOffset, y - fontSize * 1.1, blankLetterbox, fontSize);
    DrawTextPixantiqua(timerBuffer, xOffset, y, blankLetterbox, fontSize);
}

void DrawLetterBoxes(const char *FJORD, char *solutionPattern)
{
    int y = boxSize;

    for (int i = 0; i < 25; i++)
    {
        int xPos = xOffset + (i % 5) * (boxSize + boxMargin);
        int yPos = y + (i / 5) * (boxSize + boxMargin);

        DrawLetterBox(xPos, yPos, FJORD[i], solutionPattern[i]);
    }
}

void DrawGuessBuffer(char *buffer)
{
    const int y = GetScreenHeight() - boxSize * 2 - boxMargin * 2;
    DrawBuffer(buffer, y, 'b');
}

void DrawMissBuffer(char *buffer)
{
    const int y = GetScreenHeight() - boxSize - boxMargin;
    DrawBuffer(buffer, y, 'x');
}