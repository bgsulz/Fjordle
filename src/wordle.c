#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

#define SOLUTION_COUNT 2221
#define CLEAR_BUFFER "\0XXXX"

static char **solutions;
static char *solutionBuffer;

int guessBufferLength = 0;
char guessBuffer[6] = CLEAR_BUFFER;
char *solutionPattern, *missBuffer = CLEAR_BUFFER;

static char GetLetterBoxColor(char letter, int index, char *solution)
{
    // printf("Solving letter %c at index %i for solution %s", letter, index, solution);
    char lowerLetter = tolower(letter);
    if (solution[index % 5] == lowerLetter)
        return 'g';
    if (strchr(solution, lowerLetter) != NULL)
        return 'y';
    return 'b';
}

void AllocateWordleBuffers()
{
    solutionPattern = malloc(25 + 1);
    strcpy(solutionPattern, "bbbbbbbbbbbbbbbbbbbbbbbbb\0");

    solutions = malloc(sizeof(char *) * SOLUTION_COUNT);
    ReadLines(solutions, SOLUTION_COUNT, "res/unique_answers.txt");
}

void FreeWordleBuffers()
{
    free(solutionPattern);

    for (int i = 0; i < SOLUTION_COUNT; i++)
        free(solutions[i]);
    free(solutions);
}

int FillBufferFromInput(int (*getCharPressed)(void), int backspacePressed)
{
    int didPress = 0;
    int key = getCharPressed();

    while (key > 0)
    {
        if ((key >= 32) && (key <= 125) && (guessBufferLength < 5))
        {
            guessBuffer[guessBufferLength] = (char)tolower(key);
            guessBuffer[guessBufferLength + 1] = '\0';
            guessBufferLength++;
            didPress = 1;
        }

        key = getCharPressed();
    }

    if (backspacePressed)
    {
        guessBufferLength--;
        if (guessBufferLength < 0)
            guessBufferLength = 0;
        guessBuffer[guessBufferLength] = '\0';
    }

    return didPress;
}

void ClearGuessBuffer(int param)
{
    if (param > 0) missBuffer = CLEAR_BUFFER;
    strcpy(guessBuffer, param == 0 ? CLEAR_BUFFER : solutionBuffer);
    guessBufferLength = param * 5;
}

void RefreshSolution(const char *FJORD, int didGetCorrect)
{
    if (didGetCorrect < 1 && solutionBuffer != NULL)
        missBuffer = solutionBuffer;
    else
        missBuffer = CLEAR_BUFFER;

    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand(tv.tv_usec * 100000);
    solutionBuffer = solutions[rand() % SOLUTION_COUNT];

    for (int i = 0; i < 25; i++)
        solutionPattern[i] = GetLetterBoxColor(FJORD[i], i, solutionBuffer);
    solutionPattern[26] = '\0';

    ClearGuessBuffer(0);

    // printf("%s / %s\n", solutionBuffer, solutionPattern);
}

int IsSolutionCorrect()
{
    return strcmp(solutionBuffer, guessBuffer) == 0;
}