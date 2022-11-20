#include <stdio.h>
#include "cpuid.c"

int main() {
    printf("CPUID Information\n");

    struct X64Info cpuid = {};
    bool hasCpuid = getCpuidInfo(&cpuid);
    if (!hasCpuid) {
        printf("This CPU does not support CPUID\n");
        return 1;
    }

    printf("Leaf 0H:\n");
    printf("\tMaximum Input Value for Basic CPUID Information: 0x%x\n", cpuid.maxInputBasicInfo);
    printf("\tVendor: %s\n", cpuid.vendorString);
}
