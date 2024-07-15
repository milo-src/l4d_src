#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <windows.h>
#include <stddef.h>

// Memory management functions
char* AllocateMemory(void);
void* AllocateAndInitializeMemory(size_t size);
void FreeMemory(void* ptr);
void* ReallocateMemory(void* ptr, size_t size);
void* AllocateMemoryForString(const char* str);
bool IsMemoryAvailable(void);
void InitializeMemory();

#endif // MEMORY_MANAGEMENT_H
