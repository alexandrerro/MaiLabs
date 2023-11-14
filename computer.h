#ifndef computer_h
#define computer_h

#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE 50

// ѕеречислени€ дл€ человекочитаемых названий
enum ProcessorType {
    INTEL_CORE_I5,
    AMD_RYZEN_7,
    INTEL_CORE_I7,
    INTEL_CORE_I3,
    AMD_A10_9700,
    INTEL_PENTIUM_GOLD_G5420,
    INTEL_CORE_I9,
    AMD_RYZEN_THREADRIPPER_3990X,
    INTELCELERON_G5905,
    INTEL_XEON_E5_2690
};

enum VideoControllerType {
    NVIDIA_GEFORCE_GTX_1050,
    AMD_RADEON_RX_580,
    NVIDIA_GEFORCE_RTX_3060,
    INTEL_UHD_GRAPHICS_620,
    AMD_RADEON_R7,
    INTEL_UHD_GRAPHICS_610,
    NVIDIA_GEFORCE_GTX_1080_TI,
    AMD_RADEON_PRO_WX_9100,
    INTEL_UHD_GRAPHICS_610,
    NVIDIA_TESLA_T4
};

enum DiskType {
    SSD,
    HDD
};

enum OS {
    WINDOWS_10,
    WINDOWS_11,
    UBUNTU_20_04,
    LINUX_MINT_20_2,
    WINDOWS_SERVER_2019
};

typedef struct {
    char surname[STR_SIZE];
    enum ProcessorType processorType;
    int memorySize;
    enum VideoControllerType videoControllerType;
    int videoMemorySize;
    enum DiskType diskType;
    int diskNumber;
    int diskCapacity;
    int intcontrNumber;
    int deviceNumber;
    enum OS os;
} Computer;

#endif