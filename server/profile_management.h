#ifndef PROFILE_MANAGEMENT_H
#define PROFILE_MANAGEMENT_H

#include <windows.h>

// Profile management functions
void EnterProfileScope(const char* name, int param_2, const char* param_3, bool param_4, int param_5);
uint CheckAchievementsStatus(void);
void UpdateProfileState(int param);

#endif // PROFILE_MANAGEMENT_H
