#include "GameInit.h"
bool GameInit::FinishedRendering = false;
Box* GameInit::b;
Box* GameInit::ground;
std::chrono::steady_clock::time_point GameInit::prevTime;
double GameInit::fDeltaTime;