#include "raylib.h"

void LoadFonts();
void UnloadFonts();

void UpdateDisplayInfo();

void DrawBackground();
void DrawGameData(int isGameActive, int score, float timer);
void DrawLetterBoxes(const char *FJORD, char *solutionPattern);

void DrawGuessBuffer(char *buffer);
void DrawMissBuffer(char *buffer);