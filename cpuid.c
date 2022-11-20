#include <stdbool.h>
#include <stdint.h>

#define CPUID_VENDOR_STRING_SIZE    12
#define CPUID_BRAND_STRING_SIZE     48

#define x64EaxGetStepping(eax)          (eax & 0b1111)
#define x64EaxGetModel(eax)             ((eax & 0b11110000) >> 4)
#define x64EaxGetFamily(eax)            ((eax & 0b111100000000) >> 8)
#define x64EaxGetProcessorType(eax)     ((eax & 0b11000000000000) >> 10)
#define x64EaxGetExtendedModel(eax)     ((eax & 0b11110000000000000000) >> 16)
#define x64EaxGetExtendedFamily(eax)    ((eax & 0b1111111100000000000000000000) >> 20)

#define X64_FEATURE_FLAG_ECX_SSE3           1
#define X64_FEATURE_FLAG_ECX_PCLMULQDQ      (1 << 1)
#define X64_FEATURE_FLAG_ECX_DTES64         (1 << 2)  
#define X64_FEATURE_FLAG_ECX_MONITOR        (1 << 3)
#define X64_FEATURE_FLAG_ECX_DS_CPL         (1 << 4)
#define X64_FEATURE_FLAG_ECX_VMX            (1 << 5)
#define X64_FEATURE_FLAG_ECX_SMX            (1 << 6)
#define X64_FEATURE_FLAG_ECX_EIST           (1 << 8)
#define X64_FEATURE_FLAG_ECX_TM2            (1 << 9)
#define X64_FEATURE_FLAG_ECX_SSSE2          (1 << 10)
#define X64_FEATURE_FLAG_ECX_CNXT_ID        (1 << 11)
#define X64_FEATURE_FLAG_ECX_SDBG           (1 << 12)
#define X64_FEATURE_FLAG_ECX_FMA            (1 << 13)
#define X64_FEATURE_FLAG_ECX_CMPXCHG16B     (1 << 14)
#define X64_FEATURE_FLAG_ECX_XTPR           (1 << 15)
#define X64_FEATURE_FLAG_ECX_PDCM           (1 << 16)
#define X64_FEATURE_FLAG_ECX_PCID           (1 << 18)
#define X64_FEATURE_FLAG_ECX_DCA            (1 << 19)
#define X64_FEATURE_FLAG_ECX_SSE4_1         (1 << 20)
#define X64_FEATURE_FLAG_ECX_SSE4_2         (1 << 21)
#define X64_FEATURE_FLAG_ECX_X2APIC         (1 << 22)
#define X64_FEATURE_FLAG_ECX_MOVBE          (1 << 23)
#define X64_FEATURE_FLAG_ECX_POPCNT         (1 << 24)
#define X64_FEATURE_FLAG_ECX_TSC_DEADLINE   (1 << 25)
#define X64_FEATURE_FLAG_ECX_AES            (1 << 26)
#define X64_FEATURE_FLAG_ECX_XSAVE          (1 << 27)
#define X64_FEATURE_FLAG_ECX_OSXSAVE        (1 << 28)
#define X64_FEATURE_FLAG_ECX_AVX            (1 << 29)
#define X64_FEATURE_FLAG_ECX_F16C           (1 << 30)
#define X64_FEATURE_FLAG_ECX_RDRAND         (1 << 31)

#define X64_FEATURE_FLAG_ECX_PBE            (1 << 31)
#define X64_FEATURE_FLAG_ECX_TM             (1 << 29)
#define X64_FEATURE_FLAG_ECX_HTT            (1 << 28)
#define X64_FEATURE_FLAG_ECX_SS             (1 << 27)
#define X64_FEATURE_FLAG_ECX_SSE2           (1 << 26)
#define X64_FEATURE_FLAG_ECX_SSE            (1 << 25)
#define X64_FEATURE_FLAG_ECX_FXSR           (1 << 24)
#define X64_FEATURE_FLAG_ECX_MMX            (1 << 23)
#define X64_FEATURE_FLAG_ECX_ACPI           (1 << 22)
#define X64_FEATURE_FLAG_ECX_DS             (1 << 21)
#define X64_FEATURE_FLAG_ECX_CLFSH          (1 << 19)
#define X64_FEATURE_FLAG_ECX_PSN            (1 << 18)
#define X64_FEATURE_FLAG_ECX_PSE_36         (1 << 17)
#define X64_FEATURE_FLAG_ECX_PAT            (1 << 16)
#define X64_FEATURE_FLAG_ECX_CMOV           (1 << 15)
#define X64_FEATURE_FLAG_ECX_MCA            (1 << 14)
#define X64_FEATURE_FLAG_ECX_PGE            (1 << 13)
#define X64_FEATURE_FLAG_ECX_MTRR           (1 << 12)
#define X64_FEATURE_FLAG_ECX_SEP            (1 << 11)
#define X64_FEATURE_FLAG_ECX_APIC           (1 << 9)
#define X64_FEATURE_FLAG_ECX_CX8            (1 << 8)
#define X64_FEATURE_FLAG_ECX_MCE            (1 << 7)
#define X64_FEATURE_FLAG_ECX_PAE            (1 << 6)
#define X64_FEATURE_FLAG_ECX_MSR            (1 << 5)
#define X64_FEATURE_FLAG_ECX_TSC            (1 << 4)
#define X64_FEATURE_FLAG_ECX_PSE            (1 << 3)
#define X64_FEATURE_FLAG_ECX_DE             (1 << 2)
#define X64_FEATURE_FLAG_ECX_VME            (1 << 1)
#define X64_FEATURE_FLAG_ECX_FPU            1

enum CpuidProcessorType {
    CPUID_PROCESSOR_TYPE_ORIGINAL_OEM       = 0,
    CPUID_PROCESSOR_TYPE_INTEL_OVERDRIVE    = 1,
    CPUID_PROCESSOR_TYPE_DUAL               = 2,
    CPUID_PROCESSOR_TYPE_RESERVED           = 3,
};

struct X64Info {
    // Leaf 0
    uint32_t    maxInputBasicInfo;
    char        vendorString[CPUID_VENDOR_STRING_SIZE + 1];
    // Leaf 1
    uint8_t     steppingId;
    uint8_t     modelId;
    uint8_t     familyId;
    uint8_t     processorType;
    uint8_t     extendedModelId;
    uint8_t     extendedFamilyId;
    uint8_t     brandIndex;
    uint8_t     cacheLineSize;
    uint8_t     maxNumberLogicalProcessorIds;
    uint8_t     initialApicId;
    uint32_t    feature1;
    uint32_t    feature2;
    char        brandString[CPUID_BRAND_STRING_SIZE];

};

struct X64CpuidResult {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
};

// TODO: this function might be optimized out by the compiler
void executeCpuidWithLeaf(uint32_t leaf, struct X64CpuidResult* result) {
    asm(
        "mov eax, %4                \n"
        "cpuid                      \n"
        "mov %0, eax                \n"
        "mov %1, ebx                \n"
        "mov %2, ecx                \n"
        "mov %3, edx                \n"
        : "=m" (result->eax), "=m" (result->ebx), "=m" (result->ecx), "=m" (result->edx)
        : "m" (leaf)
        : "eax", "ebx", "ecx", "edx"
    );
}

// Returns true if the brand index is valid and points brandString to the correct brand name
// otherwise returns false
bool x64TranslateBrandIndex(uint8_t brandIndex, char* brandString) {
    if (brandIndex == 0 || brandIndex > 0x17) {
        return false;
    }

    switch (brandIndex) {
    case 0x1: brandString = "Intel(R) Celeron(R) processor"; break;
    case 0x2: brandString = "Intel(R) Pentium(R) III processor"; break;
    // TODO: If processor signature = 000006B1h, then Intel(R) Celeron(R) processor
    case 0x3: brandString = "Intel(R) Pentium(R) III Xeon(R) processor"; break;
    case 0x4: brandString = "Intel(R) Pentium(R) III processor"; break;
    case 0x6: brandString = "Mobile Intel(R) Pentium(R) III processor-M"; break;
    case 0x7: brandString = "Mobile Intel(R) Celeron(R) processor"; break;
    case 0x8: brandString = "Intel(R) Pentium(R) 4 processor"; break;
    case 0x9: brandString = "Intel(R) Pentium(R) 4 processor"; break;
    case 0xA: brandString = "Intel(R) Celeron(R) processor"; break;
    // TODO: If processor signature = 00000F13h, then Intel(R) Xeon(R) processor MP
    case 0xB: brandString = "Intel(R) Xeon(R) processor"; break;
    case 0xC: brandString = "Intel(R) Xeon(R) processor MP"; break;
    // TODO: If processor signature = 00000F13h, then Intel(R) Xeon(R) processor
    case 0xE: brandString = "Mobile Intel(R) Pentium(R) 4 processor-M"; break;
    case 0xF: brandString = "Mobile Intel(R) Celeron(R) processor"; break;
    case 0x11: brandString = "Mobile Genuine Intel(R) processor"; break;
    case 0x12: brandString = "Intel(R) Celeron(R) M processor"; break;
    case 0x13: brandString = "Mobile Intel(R) Celeron(R) processor"; break;
    case 0x14: brandString = "Intel(R) Celeron(R) processor"; break;
    case 0x15: brandString = "Mobile Genuine Intel(R) processor"; break;
    case 0x16: brandString = "Intel(R) Pentium(R) M processor"; break;
    case 0x17: brandString = "Mobile Intel(R) Celeron(R) processor"; break;
    }

    return true;
}

void x64PrintFeatureSet(struct X64Info* cpuid) {
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_SSE3)            printf("\tSSE3\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_PCLMULQDQ)       printf("\tPCLMULQDQ\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_DTES64)          printf("\tDTES64\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_MONITOR)         printf("\tMONITOR\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_DS_CPL)          printf("\tDS-CPL\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_VMX)             printf("\tVMX\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_SMX)             printf("\tSMX\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_EIST)            printf("\tEIST\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_TM2)             printf("\tTM2\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_SSSE2)           printf("\tSSSE3\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_CNXT_ID)         printf("\tCNXT-ID\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_SDBG)            printf("\tSDBG\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_FMA)             printf("\tFMA\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_CMPXCHG16B)      printf("\tCMPXCHG16B\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_XTPR)            printf("\txTPR\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_PDCM)            printf("\tPDCM\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_PCID)            printf("\tPCID\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_DCA)             printf("\tDCA\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_SSE4_1)          printf("\tSSE4.1\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_SSE4_2)          printf("\tSSE4.2\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_X2APIC)          printf("\tx2APIC\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_MOVBE)           printf("\tMOVBE\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_POPCNT)          printf("\tPOPCNT\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_TSC_DEADLINE)    printf("\tTSC-Deadline\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_AES)             printf("\tAES\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_XSAVE)           printf("\tXSAVE\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_OSXSAVE)         printf("\tOSXSAVE\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_AVX)             printf("\tAVX\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_F16C)            printf("\tF16C\n");
    if (cpuid->feature1 & X64_FEATURE_FLAG_ECX_RDRAND)          printf("\tRDRAND\n");

    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_PBE)     printf("\tPBE\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_TM)      printf("\tTM\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_HTT)     printf("\tHTT\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_SS)      printf("\tSS\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_SSE2)    printf("\tSSE2\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_SSE)     printf("\tSSE\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_FXSR)    printf("\tFXSR\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_MMX)     printf("\tMMX\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_ACPI)    printf("\tACPI\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_DS)      printf("\tDS\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_CLFSH)   printf("\tCLFSH\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_PSN)     printf("\tPSN\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_PSE_36)  printf("\tPSE-36\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_PAT)     printf("\tPAT\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_CMOV)    printf("\tCMOV\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_MCA)     printf("\tMCA\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_PGE)     printf("\tPGE\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_MTRR)    printf("\tMTRR\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_SEP)     printf("\tSEP\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_APIC)    printf("\tAPIC\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_CX8)     printf("\tCX8\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_MCE)     printf("\tMCE\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_PAE)     printf("\tPAE\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_MSR)     printf("\tMSR\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_TSC)     printf("\tTSC\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_PSE)     printf("\tPSE\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_DE)      printf("\tDE\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_VME)     printf("\tVME\n");
    if (cpuid->feature2 & X64_FEATURE_FLAG_ECX_FPU)     printf("\tFPU\n");
}

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
        const uint32_t leaf = 0;
        struct X64CpuidResult result = {};
        executeCpuidWithLeaf(leaf, &result);

        cpuid->maxInputBasicInfo = result.eax;

        // Convert vendor id in registers to string
        *(uint32_t*)cpuid->vendorString     = result.ebx;
        *(uint32_t*)&cpuid->vendorString[4] = result.edx;
        *(uint32_t*)&cpuid->vendorString[8] = result.ecx;
    }
    
    // -------------------------------------------------
    //                      Leaf 1
    // -------------------------------------------------

    { 
        const uint32_t leaf = 1;
        struct X64CpuidResult result = {};
        executeCpuidWithLeaf(leaf, &result);

        cpuid->steppingId         = x64EaxGetStepping(result.eax);
        cpuid->modelId            = x64EaxGetModel(result.eax);
        cpuid->familyId           = x64EaxGetFamily(result.eax);
        cpuid->processorType      = x64EaxGetProcessorType(result.eax);
        cpuid->extendedModelId    = x64EaxGetExtendedModel(result.eax);
        cpuid->extendedFamilyId   = x64EaxGetExtendedFamily(result.eax);
        cpuid->brandIndex         = (uint8_t)result.ebx;

        cpuid->cacheLineSize = ((result.ebx & 0b1111111100000000) >> 8) * 8;
        // TODO: this field is only valid if CPUID.1.EDX.HTT[bit 28] = 1
        cpuid->maxNumberLogicalProcessorIds = (result.ebx & 0b111111110000000000000000) >> 16;
        cpuid->initialApicId = (result.ebx & 0b11111111000000000000000000000000) >> 24;
        
        cpuid->feature1 = result.ecx;
        cpuid->feature2 = result.edx;

    }

    {
        const uint32_t leaf = 0x80000000;
        struct X64CpuidResult result = {};
        executeCpuidWithLeaf(leaf, &result);

        if ((result.eax & leaf) && result.eax >= 0x80000004) {
            uint32_t startLeaf = 0x80000002;

            char* brandStringCursor = cpuid->brandString;
            for (uint32_t i = 0; i < 3; i++) {
                struct X64CpuidResult result2 = {};
                executeCpuidWithLeaf(startLeaf + i, &result2);

                *(uint32_t*)brandStringCursor = result2.eax;
                *(uint32_t*)&brandStringCursor[4] = result2.ebx;
                *(uint32_t*)&brandStringCursor[8] = result2.ecx;
                *(uint32_t*)&brandStringCursor[12] = result2.edx;

                brandStringCursor += 16;
            }
        }
    }

    return true;
}
