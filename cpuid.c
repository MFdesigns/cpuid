#include <stdbool.h>
#include <stdint.h>

#define CPUID_VENDOR_STRING_SIZE 12

struct X64Info {
    uint32_t maxInputBasicInfo;
    uint32_t vendorEbx;
    uint32_t vendorEcx;
    uint32_t vendorEdx;

    char vendorString[CPUID_VENDOR_STRING_SIZE + 1];
};

bool getCpuidInfo(struct X64Info* cpuid) {
    // Check if cpu supports the CPUID instruction by changing the id flag
    // in the FLAGS register and see if that worked
    bool supportsCpuid = false;
    asm(
        // Get rflags into r8 and swap the id bit
        "pushfq             \n"
        "pop r8             \n"
        "btc r8, $21        \n"
        "push r8            \n"
        // Now check if the id flag change worked
        "popfq              \n"
        "pushfq             \n"
        "pop r9             \n"
        "cmp r8, r9         \n"
        "sete %0            \n"
        : "=m" (supportsCpuid)
        :
        : "r8", "r9"
    );
    if (!supportsCpuid) {
        return false;
    }

    // -------------------------------------------------
    //                      Leaf 0
    // -------------------------------------------------

    { 
        uint32_t leaf = 0;
        asm(
            "mov eax, %4                \n"
            "cpuid                      \n"
            "mov %0, eax                \n"
            "mov %1, ebx                \n"
            "mov %2, ecx                \n"
            "mov %3, edx                \n"
            : "=m" (cpuid->maxInputBasicInfo), "=m" (cpuid->vendorEbx), "=m" (cpuid->vendorEcx), "=m" (cpuid->vendorEdx)
            : "m" (leaf)
            : "eax", "ebx", "ecx", "edx"
        );

        // Convert vendor id in registers to string
        *(uint32_t*)cpuid->vendorString     = cpuid->vendorEbx;
        *(uint32_t*)&cpuid->vendorString[4] = cpuid->vendorEdx;
        *(uint32_t*)&cpuid->vendorString[8] = cpuid->vendorEcx;
    }

    return true;
}
