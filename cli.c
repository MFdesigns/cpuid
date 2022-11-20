#include <stdio.h>
#include "cpuid.c"

int main() {
    printf("==============================================\n"
           "               CPUID Information\n"
           "==============================================\n");

    struct X64Info cpuid = {};
    bool hasCpuid = getCpuidInfo(&cpuid);
    if (!hasCpuid) {
        printf("This CPU does not support CPUID\n");
        return 1;
    }

    printf("%s\n\n", cpuid.brandString);

    printf("Leaf 0H:\n");
    printf("\tMaximum Input Value for Basic CPUID Information: 0x%x\n", cpuid.maxInputBasicInfo);
    printf("\tVendor: %s\n", cpuid.vendorString);


    printf("Leaf 1H:\n");

    char* processorTypeStr = "Intel reserved";
    switch (cpuid.processorType) {
    case CPUID_PROCESSOR_TYPE_ORIGINAL_OEM: 
        processorTypeStr = "Original OEM Processor"; 
        break;
    case CPUID_PROCESSOR_TYPE_INTEL_OVERDRIVE: 
        processorTypeStr = "Intel OverDrive Processor"; 
        break;
    case CPUID_PROCESSOR_TYPE_DUAL: 
        processorTypeStr = "Dual processor"; 
        break;
    }

    printf("\tStepping ID: %u\n", cpuid.steppingId);
    uint32_t displayModel = cpuid.modelId;
    if (cpuid.familyId == 0xF || cpuid.familyId == 0x6) {
        displayModel = (cpuid.extendedModelId << 4) + cpuid.modelId;
    }
    printf("\tModel: %x\n", displayModel);

    uint32_t displayFamily = cpuid.familyId;
    if (cpuid.familyId == 0xF) {
        displayFamily = cpuid.extendedFamilyId + cpuid.familyId;
    }
    printf("\tFamily: %x\n", displayFamily);
    printf("\tProcessor Type: %s\n", processorTypeStr);

    char* brandString = 0;
    bool validBrandIndex = x64TranslateBrandIndex(cpuid.brandIndex, &brandString);
    if (validBrandIndex) {
        printf("\t%s\n", brandString);
    }


    printf("\tCache line size: %u\n", cpuid.cacheLineSize);
    printf("\tMaximum number of addressable IDs for logical processors in this physical package: %u\n", 
            cpuid.maxNumberLogicalProcessorIds);
    printf("\tInitial APIC ID: %u\n", cpuid.initialApicId);

    printf("\nFeature Set:\n");
    x64PrintFeatureSet(&cpuid);


    printf("Leaf 2H:\n");
}
