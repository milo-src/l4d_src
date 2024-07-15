#include "profile_management.h"

// Enter profiling scope
void EnterProfileScope(const char* name, int param_2, const char* param_3, bool param_4, int param_5) {
    CVProfile::EnterScope((CVProfile *)g_VProfCurrentProfile_exref, name, param_2, param_3, param_4, param_5);
}

// Check achievements status
uint CheckAchievementsStatus(void) {
    uint uVar1;

    uVar1 = DAT_105c8e74;
    if (*(int *)(DAT_105c8e74 + 0x30) == 0) {
        uVar1 = Msg("Achievements disabled: Steam not running.\n");
    }
    return uVar1 & 0xffffff00;
}

// Update profile state
void UpdateProfileState(int param) {
    ushort uVar1;
    ushort uVar2;
    short *psVar3;
    uint uVar4;

    uVar4 = DAT_105c8e08;
    uVar1 = *(ushort *)(param + 0x10);
    while (true) {
        uVar2 = uVar1;
        if ((uVar4 & 1) == 0) {
            uVar4 |= 1;
            DAT_105c8e00 = 0xffff;
            DAT_105c8e02 = 0xffff;
            DAT_105c8e04 = 0xffff;
            _DAT_105c8e06 = 1;
            DAT_105c8e08 = uVar4;
        }
        if (uVar2 == 0xffff) {
            psVar3 = (short *)&DAT_105c8e00;
        } else {
            psVar3 = (short *)((uint)uVar2 * 0x10 + *(int *)(param + 4));
        }
        if (*psVar3 == -1) break;
        if ((uVar4 & 1) == 0) {
            uVar4 |= 1;
            DAT_105c8e00 = 0xffff;
            DAT_105c8e02 = 0xffff;
            DAT_105c8e04 = 0xffff;
            _DAT_105c8e06 = 1;
            DAT_105c8e08 = uVar4;
        }
        uVar1 = DAT_105c8e00;
        if (uVar2 != 0xffff) {
            uVar1 = *(ushort *)((uint)uVar2 * 0x10 + *(int *)(param + 4));
        }
    }
}
