#include <windows.h>
#include <cstring>
#include <cstdint>
#include <cassert>

namespace MemoryUtils {

    // Function to retrieve the module filename of the process
    char* GetModuleFilename() {
        char resultFilename[MAX_PATH];
        HANDLE processHeap = GetProcessHeap();
        char* filenameBuffer = (char*)HeapAlloc(processHeap, 0, MAX_PATH);
        if (filenameBuffer) {
            MEMORY_BASIC_INFORMATION memInfo;
            VirtualQuery(&resultFilename, &memInfo, sizeof(memInfo));
            GetModuleFileNameA((HMODULE)memInfo.AllocationBase, filenameBuffer, MAX_PATH);

            char* extensionPos = strrchr(filenameBuffer, '.');
            if (extensionPos) {
                char* lastSlashPos = strrchr(filenameBuffer, '\\');
                if (lastSlashPos) {
                    filenameBuffer = lastSlashPos + 1;
                    *extensionPos = '\0';
                }
            }
        }
        return filenameBuffer;
    }

    // Memory allocation function
    void* AllocateMemory(size_t size) {
        static char* moduleFilename = nullptr;
        static bool initialized = false;

        if (!initialized) {
            initialized = true;
            moduleFilename = GetModuleFilename();
        }

        void* allocatedMemory = nullptr;
        if (moduleFilename) {
            // Assume some external memory allocation function is called here
            allocatedMemory = externalAlloc(size, moduleFilename, 0);
        } else {
            allocatedMemory = externalAllocDefault(size);
        }
        memset(allocatedMemory, 0, size);
        return allocatedMemory;
    }

    // Memory deallocation function
    void DeallocateMemory(void* ptr) {
        // Assume some external deallocation function is called here
        externalDealloc(ptr);
    }

    // Allocate memory with additional parameters
    void* AllocateMemoryWithParams(int param1, size_t size) {
        return AllocateMemory(param1 * size);
    }

    // Perform some operation with external memory allocation function
    void PerformOperation(int param1, int param2) {
        // Assume some external operation function is called here
        externalOperation(param1, param2);
    }

    // Additional function example
    void AnotherOperation(int param1, int param2, int param3) {
        AllocateMemoryWithParams(param1, param2 * param3);
    }

    // Dummy function returning 1
    uint32_t DummyFunction() {
        return 1;
    }

    // Check if external memory allocation is initialized
    bool IsMemoryInitialized() {
        return externalMemoryInitialized != 0;
    }

    // Perform some action with parameters
    void PerformAction(uint32_t param) {
        if (!IsMemoryInitialized()) {
            externalMemoryInitialized = 1;
            // Assume some initialization function is called here
            externalInitFunction();
        }
        if (externalMemoryInitialized) {
            externalAction(param);
        } else {
            externalDefaultAction(param);
        }
    }

    // Copy string with memory allocation
    int CopyString(const char* str) {
        if (str) {
            size_t length = strlen(str) + 1;
            char* newStr = (char*)externalAlloc(length);
            if (newStr) {
                strcpy(newStr, str);
                return length;
            }
        }
        return 0;
    }

    // Check some condition and perform an action
    void CheckAndPerformAction(int param1, int param2) {
        if (externalCheckCondition(param1)) {
            externalPerformAction(param2);
        }
    }

    // Initialize some data
    void InitializeData() {
        externalDataInit();
    }

    // Reset some data
    void ResetData() {
        externalDataReset();
    }

    // Handle some complex data operation
    void HandleComplexOperation(int param1) {
        uint32_t someData = externalGetData();
        if (someData == 0) {
            externalLog("Data not available.");
        }
    }
}