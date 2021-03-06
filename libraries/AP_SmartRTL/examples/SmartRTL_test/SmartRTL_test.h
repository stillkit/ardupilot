#include <vector>

#include <AP_BoardConfig/AP_BoardConfig.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_Math/AP_Math.h>
#include <AP_SmartRTL/AP_SmartRTL.h>
#include "../../../../ArduCopter/GCS_Copter.h"

// vectors defined below:
// test_path_before
// test_path_after_adding
// test_path_after_simplifying
// test_path_after_pruning
// test_path_complete

// assume that any point without a comment should be kept
std::vector<Vector3f> test_path_before {
    {0.0, 0.0, 0.0},
    {3.0, 0.0, 0.0}, // simplified
    {3.0, 0.0, 0.0}, // not added
    {6.0, 0.0, 0.0}, // simplified
    {10.0, 0.0, 0.0},
    {10.0, 3.0, 0.0},
    {13.0, 3.0, 0.0},
    {13.0, 6.0, 0.0},
    {16.0, 6.0, 0.0},
    {16.0, 6.0, 1.0}, // not added
    {16.0, 8.0, 1.0},
    {18.0, 8.0, 0.0},
    {20.0, 10.0, 0.0},
    {20.0, 10.0, 10.0},
    {23.0, 10.0, 10.0},
    {23.0, 13.0, 10.0},
    {26.0, 13.0, 10.0},
    {26.0, 16.0, 10.0},
    {29.0, 16.0, 10.0},
    {29.0, 19.0, 10.0},
    {32.0, 19.0, 10.0},
    {32.0, 22.0, 10.0},
    {35.0, 22.0, 10.0},
    {35.0, 25.0, 10.0},
    {38.0, 25.0, 10.0},
    {38.0, 28.0, 10.0},
    {41.0, 28.0, 10.0},
    {41.0, 31.0, 10.0},
    {44.0, 31.0, 10.0},
    {44.0, 34.0, 10.0},
    {47.0, 34.0, 10.0},
    {47.0, 37.0, 10.0},
    {51.0, 37.0, 10.0},
    {51.0, 41.0, 10.0},
    {54.0, 41.0, 10.0},
    {54.0, 44.0, 10.0},
    {57.0, 44.0, 10.0},
    {57.0, 47.0, 10.0},
    {60.0, 47.0, 10.0},
    {60.0, 40.0, 10.0},
    {63.0, 40.0, 10.0},
    {63.0, 43.0, 10.0},
    {66.0, 43.0, 10.0},
    {66.0, 46.0, 10.0},
    {69.0, 46.0, 10.0},
    {69.0, 49.0, 10.0},
    {72.0, 49.0, 10.0},
    {72.0, 52.0, 10.0},
    {75.0, 52.0, 10.0},
    {75.0, 55.0, 10.0},
    {100.0, 100.0, 100.0}, // pruned
    {103.0, 100.0, 100.0}, // pruned
    {106.0, 103.0, 100.0}, // pruned
    {103.0, 106.0, 100.0}, // pruned
    {100.0, 103.0, 100.0}, // pruned
    {103.0, 100.0, 100.0}, // pruned
    {200.0, 200.0, 200.0},
    {203.0, 200.0, 200.0},
    {203.0, 203.0, 200.0},
    {206.0, 203.0, 200.0},
    {206.0, 206.0, 200.0},
    {209.0, 206.0, 200.0},
    {209.0, 209.0, 200.0},
    {212.0, 209.0, 200.0},
    {212.0, 212.0, 200.0},
    {220.0, 220.0, 200.0},
    {223.0, 220.0, 200.0}, // pruned
    {226.0, 223.0, 200.0}, // pruned
    {223.0, 226.0, 200.0}, // pruned
    {220.0, 223.0, 200.0}, // pruned
    {223.0, 220.0, 201.0}, // pruned
    {226.0, 223.0, 200.0}, // pruned
    {223.0, 226.0, 200.0}, // pruned
    {220.0, 223.0, 200.0}, // pruned
    {223.0, 220.0, 199.0}, // pruned
    {229.0, 220.0, 200.0},
    {300.0, 300.0, 300.0},
    {305.0, 300.0, 300.0}, // simplified, pruned
    {310.0, 300.0, 300.0}, // simplified, pruned
    {315.0, 300.5, 300.0}, // simplified, pruned
    {320.0, 299.5, 300.0}, // simplified, pruned
    {325.0, 300.5, 300.0}, // simplified, pruned
    {330.0, 299.5, 300.0}, // simplified, pruned
    {335.0, 300.5, 300.0}, // simplified, pruned
    {340.0, 299.5, 300.0}, // simplified, pruned
    {345.0, 300.5, 300.0}, // simplified, pruned
    {350.0, 300.0, 300.0}, // pruned
    {350.0, 300.0, 400.0}, // pruned
    {345.0, 300.5, 400.0}, // simplified, pruned
    {340.0, 299.5, 400.0}, // simplified, pruned
    {335.0, 300.5, 400.0}, // simplified, pruned
    {330.0, 299.5, 400.0}, // simplified, pruned
    {325.0, 300.5, 400.0}, // simplified, pruned
    {320.0, 299.5, 400.0}, // simplified, pruned
    {315.0, 300.5, 400.0}, // simplified, pruned
    {310.0, 300.0, 400.0}, // simplified, pruned
    {305.0, 300.0, 400.0}, // pruned
    {300.0, 300.0, 295.0},
};

std::vector<Vector3f> test_path_after_adding {
    {0.0, 0.0, 0.0},        // 0
    {3.0, 0.0, 0.0},
    {6.0, 0.0, 0.0},
    {10.0, 0.0, 0.0},
    {10.0, 3.0, 0.0},
    {13.0, 3.0, 0.0},
    {13.0, 6.0, 0.0},
    {16.0, 6.0, 0.0},
    {16.0, 8.0, 1.0},
    {18.0, 8.0, 0.0},
    {20.0, 10.0, 0.0},      // 10
    {20.0, 10.0, 10.0},
    {23.0, 10.0, 10.0},
    {23.0, 13.0, 10.0},
    {26.0, 13.0, 10.0},
    {26.0, 16.0, 10.0},
    {29.0, 16.0, 10.0},
    {29.0, 19.0, 10.0},
    {32.0, 19.0, 10.0},
    {32.0, 22.0, 10.0},
    {35.0, 22.0, 10.0},     // 20
    {35.0, 25.0, 10.0},
    {38.0, 25.0, 10.0},
    {38.0, 28.0, 10.0},
    {41.0, 28.0, 10.0},
    {41.0, 31.0, 10.0},
    {44.0, 31.0, 10.0},
    {44.0, 34.0, 10.0},
    {47.0, 34.0, 10.0},
    {47.0, 37.0, 10.0},
    {51.0, 37.0, 10.0},     // 30
    {51.0, 41.0, 10.0},
    {54.0, 41.0, 10.0},
    {54.0, 44.0, 10.0},
    {57.0, 44.0, 10.0},
    {57.0, 47.0, 10.0},
    {60.0, 47.0, 10.0},
    {60.0, 40.0, 10.0},
    {63.0, 40.0, 10.0},
    {63.0, 43.0, 10.0},
    {66.0, 43.0, 10.0},     // 40
    {66.0, 46.0, 10.0},
    {69.0, 46.0, 10.0},
    {69.0, 49.0, 10.0},
    {72.0, 49.0, 10.0},
    {72.0, 52.0, 10.0},
    {75.0, 52.0, 10.0},
    {75.0, 55.0, 10.0},
    {100.0, 100.0, 100.0},
    {103.0, 100.0, 100.0},
    {106.0, 103.0, 100.0},  // 50
    {103.0, 106.0, 100.0},
    {100.0, 103.0, 100.0},
    {103.0, 100.0, 100.0},
    {200.0, 200.0, 200.0},
    {203.0, 200.0, 200.0},
    {203.0, 203.0, 200.0},
    {206.0, 203.0, 200.0},
    {206.0, 206.0, 200.0},
    {209.0, 206.0, 200.0},
    {209.0, 209.0, 200.0},  // 60
    {212.0, 209.0, 200.0},
    {212.0, 212.0, 200.0},
    {220.0, 220.0, 200.0},
    {223.0, 220.0, 200.0},
    {226.0, 223.0, 200.0},
    {223.0, 226.0, 200.0},
    {220.0, 223.0, 200.0},
    {223.0, 220.0, 201.0},
    {226.0, 223.0, 200.0},
    {223.0, 226.0, 200.0},  // 70
    {220.0, 223.0, 200.0},
    {223.0, 220.0, 199.0},
    {229.0, 220.0, 200.0},
    {300.0, 300.0, 300.0},
    {305.0, 300.0, 300.0},
    {310.0, 300.0, 300.0},
    {315.0, 300.5, 300.0},
    {320.0, 299.5, 300.0},
    {325.0, 300.5, 300.0},
    {330.0, 299.5, 300.0},  // 80
    {335.0, 300.5, 300.0},
    {340.0, 299.5, 300.0},
    {345.0, 300.5, 300.0},
    {350.0, 300.0, 300.0},
    {350.0, 300.0, 400.0},
    {345.0, 300.5, 400.0},
    {340.0, 299.5, 400.0},
    {335.0, 300.5, 400.0},
    {330.0, 299.5, 400.0},
    {325.0, 300.5, 400.0},  // 90
    {320.0, 299.5, 400.0},
    {315.0, 300.5, 400.0},
    {310.0, 300.0, 400.0},
    {305.0, 300.0, 400.0},
    {300.0, 300.0, 295.0},
};

std::vector<Vector3f> test_path_after_simplifying {
    {0.0, 0.0, 0.0},        // 0
    {10.0, 0.0, 0.0},
    {10.0, 3.0, 0.0},
    {13.0, 3.0, 0.0},
    {13.0, 6.0, 0.0},
    {16.0, 6.0, 0.0},
    {16.0, 8.0, 1.0},
    {18.0, 8.0, 0.0},
    {20.0, 10.0, 0.0},
    {20.0, 10.0, 10.0},
    {23.0, 10.0, 10.0},     // 10
    {23.0, 13.0, 10.0},
    {26.0, 13.0, 10.0},
    {26.0, 16.0, 10.0},
    {29.0, 16.0, 10.0},
    {29.0, 19.0, 10.0},
    {32.0, 19.0, 10.0},
    {32.0, 22.0, 10.0},
    {35.0, 22.0, 10.0},
    {35.0, 25.0, 10.0},
    {38.0, 25.0, 10.0},     // 20
    {38.0, 28.0, 10.0},
    {41.0, 28.0, 10.0},
    {41.0, 31.0, 10.0},
    {44.0, 31.0, 10.0},
    {44.0, 34.0, 10.0},
    {47.0, 34.0, 10.0},
    {47.0, 37.0, 10.0},
    {51.0, 37.0, 10.0},
    {51.0, 41.0, 10.0},
    {54.0, 41.0, 10.0},     // 30
    {54.0, 44.0, 10.0},
    {57.0, 44.0, 10.0},
    {57.0, 47.0, 10.0},
    {60.0, 47.0, 10.0},
    {60.0, 40.0, 10.0},
    {63.0, 40.0, 10.0},
    {63.0, 43.0, 10.0},
    {66.0, 43.0, 10.0},
    {66.0, 46.0, 10.0},
    {69.0, 46.0, 10.0},     // 40
    {69.0, 49.0, 10.0},
    {72.0, 49.0, 10.0},
    {72.0, 52.0, 10.0},
    {75.0, 52.0, 10.0},
    {75.0, 55.0, 10.0},
    {100.0, 100.0, 100.0},
    {103.0, 100.0, 100.0},
    {106.0, 103.0, 100.0},
    {103.0, 106.0, 100.0},
    {100.0, 103.0, 100.0},  // 50
    {103.0, 100.0, 100.0},
    {200.0, 200.0, 200.0},
    {203.0, 200.0, 200.0},
    {203.0, 203.0, 200.0},
    {206.0, 203.0, 200.0},
    {206.0, 206.0, 200.0},
    {209.0, 206.0, 200.0},
    {209.0, 209.0, 200.0},
    {212.0, 209.0, 200.0},
    {212.0, 212.0, 200.0},  // 60
    {220.0, 220.0, 200.0},
    {223.0, 220.0, 200.0},
    {226.0, 223.0, 200.0},
    {223.0, 226.0, 200.0},
    {220.0, 223.0, 200.0},
    {223.0, 220.0, 201.0},
    {226.0, 223.0, 200.0},
    {223.0, 226.0, 200.0},
    {220.0, 223.0, 200.0},
    {223.0, 220.0, 199.0},  // 70
    {229.0, 220.0, 200.0},
    {300.0, 300.0, 300.0},
    {350.0, 300.0, 300.0},
    {350.0, 300.0, 400.0},
    {305.0, 300.0, 400.0},
    {300.0, 300.0, 295.0},
};

std::vector<Vector3f> test_path_complete {
    {0.0, 0.0, 0.0},        // 0
    {10.0, 0.0, 0.0},
    {10.0, 3.0, 0.0},
    {13.0, 3.0, 0.0},
    {13.0, 6.0, 0.0},
    {16.0, 6.0, 0.0},
    {16.0, 8.0, 1.0},
    {18.0, 8.0, 0.0},
    {20.0, 10.0, 0.0},
    {20.0, 10.0, 10.0},
    {23.0, 10.0, 10.0},     // 10
    {23.0, 13.0, 10.0},
    {26.0, 13.0, 10.0},
    {26.0, 16.0, 10.0},
    {29.0, 16.0, 10.0},
    {29.0, 19.0, 10.0},
    {32.0, 19.0, 10.0},
    {32.0, 22.0, 10.0},
    {35.0, 22.0, 10.0},
    {35.0, 25.0, 10.0},
    {38.0, 25.0, 10.0},     // 20
    {38.0, 28.0, 10.0},
    {41.0, 28.0, 10.0},
    {41.0, 31.0, 10.0},
    {44.0, 31.0, 10.0},
    {44.0, 34.0, 10.0},
    {47.0, 34.0, 10.0},
    {47.0, 37.0, 10.0},
    {51.0, 37.0, 10.0},
    {51.0, 41.0, 10.0},
    {54.0, 41.0, 10.0},     // 30
    {54.0, 44.0, 10.0},
    {57.0, 44.0, 10.0},
    {57.0, 47.0, 10.0},
    {60.0, 47.0, 10.0},
    {60.0, 40.0, 10.0},
    {63.0, 40.0, 10.0},
    {63.0, 43.0, 10.0},
    {66.0, 43.0, 10.0},
    {66.0, 46.0, 10.0},
    {69.0, 46.0, 10.0},     // 40
    {69.0, 49.0, 10.0},
    {72.0, 49.0, 10.0},
    {72.0, 52.0, 10.0},
    {75.0, 52.0, 10.0},
    {75.0, 55.0, 10.0},
    {100.0, 100.0, 100.0},
    {103.0, 100.0, 100.0},
    {103.0, 100.0, 100.0},
    {200.0, 200.0, 200.0},
    {203.0, 200.0, 200.0},  // 50
    {203.0, 203.0, 200.0},
    {206.0, 203.0, 200.0},
    {206.0, 206.0, 200.0},
    {209.0, 206.0, 200.0},
    {209.0, 209.0, 200.0},
    {212.0, 209.0, 200.0},
    {212.0, 212.0, 200.0},
    {220.0, 220.0, 200.0},
    {223.0, 220.0, 200.0},
    {223.2368474, 220.0789542, 199.5263052}, // 60
    {229.0, 220.0, 200.0},
    {300.1223662, 300.0, 300.0696305},
    {300.0, 300.0, 295.0},
};
