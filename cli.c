#include <stdio.h>
#include "cpuid.c"

int main() {
    printf("CPUID Information\n");

    bool hasCpuid = getCpuidInfo();
    if (!hasCpuid) {
        printf("This CPU does not support CPUID\n");
        return 1;
    }
}
