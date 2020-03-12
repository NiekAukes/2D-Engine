#include "GameInit.h"
bool GameInit::FinishedRendering = false;
BeginV GameInit::bv;
std::chrono::steady_clock::time_point GameInit::prevTime;
double GameInit::fDeltaTime;