#include "memory_management.h"
#include <cstring>

// Allocate memory and get module file name without extension
char* AllocateMemory(void) {
    char cVar1;
    HANDLE hHeap;
    char *lpFilename;
    char *pcVar2;
    char *pcVar3;
    DWORD dwFlags;
    SIZE_T dwBytes;
    _MEMORY_BASIC_INFORMATION _Stack_1c;

    cVar1 = (**(code **)(**(int **)g_pMemAlloc_exref + 100))();
    if (cVar1 != '\0') {
        dwBytes = 0x104;
        dwFlags = 0;
        hHeap = GetProcessHeap();
        lpFilename = (char *)HeapAlloc(hHeap, dwFlags, dwBytes);
        VirtualQuery(&DAT_105c8dec, &_Stack_1c, 0x1c);
        GetModuleFileNameA((HMODULE)_Stack_1c.AllocationBase, lpFilename, 0x104);
        pcVar2 = strrchr(lpFilename, '.');
        if (pcVar2 != nullptr) {
            pcVar3 = strrchr(lpFilename, '\\');
            if (pcVar3 != nullptr) {
                lpFilename = pcVar3 + 1;
                *pcVar2 = '\0';
            }
        }
        return lpFilename;
    }
    return nullptr;
}

// Allocate and initialize memory with zero
void* AllocateAndInitializeMemory(size_t size) {
    void *pvVar1;
    
    if ((_DAT_105c8df4 & 1) == 0) {
        _DAT_105c8df4 |= 1;
        DAT_105c8df0 = AllocateMemory();
    }
    if (DAT_105c8df0 != nullptr) {
        pvVar1 = (void *)(**(code **)**(undefined4 **)g_pMemAlloc_exref)(size, DAT_105c8df0, 0);
        memset(pvVar1, 0, size);
        return pvVar1;
    }
    pvVar1 = (void *)(**(code **)(**(int **)g_pMemAlloc_exref + 4))(size);
    memset(pvVar1, 0, size);
    return pvVar1;
}

// Free allocated memory
void FreeMemory(void* ptr) {
    (**(code **)(**(int **)g_pMemAlloc_exref + 0x14))(ptr);
}

// Reallocate memory
void* ReallocateMemory(void* ptr, size_t size) {
    void *pvVar1;

    if ((_DAT_105c8dfc & 1) == 0) {
        _DAT_105c8dfc |= 1;
        DAT_105c8df8 = AllocateMemory();
    }
    if (DAT_105c8df8 != nullptr) {
        pvVar1 = (void *)(**(code **)(**(int **)g_pMemAlloc_exref + 8))(ptr, size, DAT_105c8df8, 0);
        memset(pvVar1, 0, size);
        return pvVar1;
    }
    pvVar1 = (void *)(**(code **)(**(int **)g_pMemAlloc_exref + 0xc))(ptr, size);
    memset(pvVar1, 0, size);
    return pvVar1;
}

// Allocate memory for a string
void* AllocateMemoryForString(const char* str) {
    char cVar1;
    const char *pcVar2;
    void *_Dst;
    
    pcVar2 = str;
    do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    pcVar2 = pcVar2 + (1 - (int)(str + 1));
    if ((_DAT_105c8df4 & 1) == 0) {
        _DAT_105c8df4 |= 1;
        DAT_105c8df0 = AllocateMemory();
    }
    if (DAT_105c8df0 == 0) {
        _Dst = (void *)(**(code **)(**(int **)g_pMemAlloc_exref + 4))(pcVar2);
    }
    else {
        _Dst = (void *)(**(code **)**(undefined4 **)g_pMemAlloc_exref)(pcVar2, DAT_105c8df0, 0);
    }
    if (_Dst != (void *)0x0) {
        memcpy(_Dst, str, (size_t)pcVar2);
    }
    return _Dst;
}

// Check if memory is available
bool IsMemoryAvailable(void) {
    return *(int *)g_pMemAlloc_exref != 0;
}

// Initialize memory allocation base
void InitializeMemory() {
    if ((_DAT_105c8df4 & 1) == 0) {
        _DAT_105c8df4 |= 1;
        DAT_105c8df0 = AllocateMemory();
    }
}

