#include <cstdint>

// Forward declarations of functions used in the original code
int getSomeValue(int param);
void processData(int value);

// Global variables (assuming these are part of some shared state)
extern uint32_t globalFlag;
extern uint16_t globalValues[4];

// Function 1
void updateData(int baseAddress, uint32_t param) {
    uint16_t index;
    uint16_t* currentEntry;
    int dataPointer;
    uint16_t valueToUpdate;

    // Retrieve current entry
    currentEntry = reinterpret_cast<uint16_t*>(getSomeValue(param));
    index = *currentEntry;
    dataPointer = getSomeValue(index);
    valueToUpdate = static_cast<uint16_t>(param);

    // Update the data structure
    *(reinterpret_cast<uint16_t*>(*(reinterpret_cast<int*>(baseAddress + 4)) + valueToUpdate * 0x50)) = *(reinterpret_cast<uint16_t*>(dataPointer + 2));

    // Check and update additional values
    if (*(reinterpret_cast<uint16_t*>(dataPointer + 2)) != -1) {
        *(reinterpret_cast<uint16_t*>(*(reinterpret_cast<uint16_t*>(dataPointer + 2)) * 0x50 + 4 + *(reinterpret_cast<int*>(baseAddress + 4)))) = valueToUpdate;
    }

    if (index != -1) {
        *(reinterpret_cast<uint16_t*>(index * 0x50 + 4 + *(reinterpret_cast<int*>(baseAddress + 4)))) = *(reinterpret_cast<uint16_t*>(getSomeValue(param) + 4));
    }

    // Update the base address if needed
    if (valueToUpdate == *(reinterpret_cast<uint16_t*>(baseAddress + 0x10))) {
        *(reinterpret_cast<uint16_t*>(baseAddress + 0x10)) = index;
    } else {
        dataPointer = getSomeValue(param);
        dataPointer = getSomeValue(*(reinterpret_cast<uint16_t*>(dataPointer + 4)));
        if (*(reinterpret_cast<uint16_t*>(dataPointer + 2)) == valueToUpdate) {
            *(reinterpret_cast<uint16_t*>(*(reinterpret_cast<uint16_t*>(getSomeValue(param) + 4)) * 0x50 + 2 + *(reinterpret_cast<int*>(baseAddress + 4)))) = index;
        } else {
            *(reinterpret_cast<uint16_t*>(*(reinterpret_cast<uint16_t*>(getSomeValue(param) + 4)) * 0x50 + *(reinterpret_cast<int*>(baseAddress + 4)))) = index;
        }
    }

    *(reinterpret_cast<uint16_t*>(index * 0x50 + 2 + *(reinterpret_cast<int*>(baseAddress + 4)))) = valueToUpdate;
    
    if (valueToUpdate != -1) {
        *(reinterpret_cast<uint16_t*>(*(reinterpret_cast<int*>(baseAddress + 4)) + 4 + valueToUpdate * 0x50)) = index;
    }
}

// Function 2
void manageEntry(int baseAddress, uint16_t entry) {
    uint16_t* entryPtr;
    uint16_t* nextEntryPtr;
    int entryData;
    uint16_t nextEntry;
    uint16_t secondEntry;
    uint16_t lastEntry;

    if (entry != *(reinterpret_cast<uint16_t*>(baseAddress + 0x10))) {
        while (true) {
            if ((globalFlag & 1) == 0) {
                globalFlag |= 1;
                globalValues[0] = 0xffff;
                globalValues[1] = 0xffff;
                globalValues[2] = 0xffff;
                globalValues[3] = 1;
            }

            if (entry == -1) {
                entryPtr = &globalValues[0];
            } else {
                entryPtr = reinterpret_cast<uint16_t*>(entry * 0x50 + *(reinterpret_cast<int*>(baseAddress + 4)));
            }

            if ((globalFlag & 1) == 0) {
                globalFlag |= 1;
                globalValues[0] = 0xffff;
                globalValues[1] = 0xffff;
                globalValues[2] = 0xffff;
                globalValues[3] = 1;
            }

            if (entryPtr[2] == -1) {
                entryPtr = &globalValues[0];
            } else {
                entryPtr = reinterpret_cast<uint16_t*>(entryPtr[2] * 0x50 + *(reinterpret_cast<int*>(baseAddress + 4)));
            }

            if (entryPtr[3] != 0) break;

            if ((globalFlag & 1) == 0) {
                globalFlag |= 1;
                globalValues[0] = 0xffff;
                globalValues[1] = 0xffff;
                globalValues[2] = 0xffff;
                globalValues[3] = 1;
            }

            if (entry == -1) {
                entryPtr = &globalValues[0];
            } else {
                entryPtr = reinterpret_cast<uint16_t*>(entry * 0x50 + *(reinterpret_cast<int*>(baseAddress + 4)));
            }

            entryData = entryPtr[2];
            
            if ((globalFlag & 1) == 0) {
                globalFlag |= 1;
                globalValues[0] = 0xffff;
                globalValues[1] = 0xffff;
                globalValues[2] = 0xffff;
                globalValues[3] = 1;
            }

            if (entryData == -1) {
                entryPtr = &globalValues[0];
            } else {
                entryPtr = reinterpret_cast<uint16_t*>(entryData * 0x50 + *(reinterpret_cast<int*>(baseAddress + 4)));
            }

            nextEntry = entryPtr[2];
            
            if ((globalFlag & 1) == 0) {
                globalFlag |= 1;
                globalValues[0] = 0xffff;
                globalValues[1] = 0xffff;
                globalValues[2] = 0xffff;
                globalValues[3] = 1;
            }

            if (entryData == -1) {
                entryPtr = &globalValues[0];
            } else {
                entryPtr = reinterpret_cast<uint16_t*>(entryData * 0x50 + *(reinterpret_cast<int*>(baseAddress + 4)));
            }

            if (entryPtr[2] == -1) {
                nextEntryPtr = &globalValues[0];
            } else {
                nextEntryPtr = reinterpret_cast<uint16_t*>(entryPtr[2] * 0x50 + *(reinterpret_cast<int*>(baseAddress + 4)));
            }

            if (*nextEntryPtr == entryData) {
                if ((globalFlag & 1) == 0) {
                    globalFlag |= 1;
                    globalValues[0] = 0xffff;
                    globalValues[1] = 0xffff;
                    globalValues[2] = 0xffff;
                    globalValues[3] = 1;
                }

                if (nextEntry == -1) {
                    entryPtr = &globalValues[0];
                } else {
                    entryPtr = reinterpret_cast<uint16_t*>(nextEntry * 0x50 + *(reinterpret_cast<int*>(baseAddress + 4)));
                }

                lastEntry = entryPtr[1];
                
                if ((globalFlag & 1) == 0) {
                    globalFlag |= 1;
                    globalValues[0] = 0xffff;
                    globalValues[1] = 0xffff;
                    globalValues[2] = 0xffff;
                    globalValues[3] = 1;
                }

                if (lastEntry == -1) {
                    entryPtr = &globalValues[0];
                } else {
                    entryPtr = reinterpret_cast<uint16_t*>(lastEntry * 0x50 + *(reinterpret_cast<int*>(baseAddress + 4)));
                }

                if (entryPtr[3] == 0) {
                    *(reinterpret_cast<uint16_t*>(entryData * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 1;
                    *(reinterpret_cast<uint16_t*>(lastEntry * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 1;
                    *(reinterpret_cast<uint16_t*>(nextEntry * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 0;
                    entry = nextEntry;
                } else {
                    if ((globalFlag & 1) == 0) {
                        globalFlag |= 1;
                        globalValues[0] = 0xffff;
                        globalValues[1] = 0xffff;
                        globalValues[2] = 0xffff;
                        globalValues[3] = 1;
                    }

                    if (entry == -1) {
                        entryPtr = &globalValues[0];
                    } else {
                        entryPtr = reinterpret_cast<uint16_t*>(entry * 0x50 + *(reinterpret_cast<int*>(baseAddress + 4)));
                    }

                    if ((globalFlag & 1) == 0) {
                        globalFlag |= 1;
                        globalValues[0] = 0xffff;
                        globalValues[1] = 0xffff;
                        globalValues[2] = 0xffff;
                        globalValues[3] = 1;
                    }

                    if (entryData == -1) {
                        entryPtr = &globalValues[0];
                    } else {
                        entryPtr = reinterpret_cast<uint16_t*>(entryData * 0x50 + *(reinterpret_cast<int*>(baseAddress + 4)));
                    }

                    secondEntry = entryPtr[1];

                    *(reinterpret_cast<uint16_t*>(nextEntry * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 0;
                    *(reinterpret_cast<uint16_t*>(secondEntry * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 1;
                    *(reinterpret_cast<uint16_t*>(nextEntry * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 1;
                    *(reinterpret_cast<uint16_t*>(entryData * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 0;
                    *(reinterpret_cast<uint16_t*>(secondEntry * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 0;
                    *(reinterpret_cast<uint16_t*>(nextEntry * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 1;
                    *(reinterpret_cast<uint16_t*>(entryData * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 1;
                    entry = secondEntry;
                }
            } else {
                *(reinterpret_cast<uint16_t*>(entryData * 0x50 + 2 + *(reinterpret_cast<int*>(baseAddress + 4)))) = entry;
                *(reinterpret_cast<uint16_t*>(entry * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 1;
                *(reinterpret_cast<uint16_t*>(nextEntry * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 1;
                *(reinterpret_cast<uint16_t*>(entryData * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 0;
                entry = nextEntry;
            }
        }

        *(reinterpret_cast<uint16_t*>(entry * 0x50 + 6 + *(reinterpret_cast<int*>(baseAddress + 4)))) = 1;
    }

    // Final processing (not shown in the original code)
    processData(entry);
}