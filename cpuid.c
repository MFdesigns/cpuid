#include <stdbool.h>

bool getCpuidInfo() {
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

    return true;
}
