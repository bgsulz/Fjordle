extern char guessBuffer[6];
extern char *solutionPattern, *missBuffer;
extern int guessBufferLength;

void AllocateWordleBuffers();
void FreeWordleBuffers();

int FillBufferFromInput(int (*getCharPressed)(void), int backspacePressed);
void ClearGuessBuffer(int param);
void RefreshSolution(const char* FJORD, int didGetCorrect);
int IsSolutionCorrect();