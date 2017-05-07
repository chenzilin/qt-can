#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <stdint.h>

namespace CanProtocol {

enum {
    CANID_0x068 = 0x068,
    CANID_0x07A = 0x07A,
    CANID_0x08B = 0x08B,
    CANID_0x115 = 0x115,
    CANID_0x210 = 0x210,
    CANID_0x268 = 0x268,
    CANID_0x4D4 = 0x4D4,
    CANID_0x10D = 0x10D
};

struct CAN_0x068 {	// fixedPeriodic: 20
    uint16_t: 2,
    ebdFailed: 1,						// num 2
    absFailed: 1,						// num 3
    : 2,
    tcsWarning: 1,						// num 6
    tcsActive: 1,						// num 7
    vehicleSpeed2: 8;					// num 8~15
    uint8_t pataResponse: 1,				// num 16
        : 1,
        vehicleSpeedInvaild: 1,				// num 18
        vehicleSpeed1: 5;					// num 19~23
    uint8_t: 8;
    uint32_t: 32;
} __attribute__((packed));

struct CAN_0x07A {	// fixedPeriodic: 10
    uint16_t : 16;
    uint16_t epsFailed: 1,					// num 16
        : 15;
    uint32_t: 32;
} __attribute__((packed));

struct CAN_0x08B {	// fixedPeriodic: 20
    uint32_t: 32;
    uint8_t: 8;
    uint16_t actRotSpd2: 8,					// num 40~47
        : 4,
        actRotSpd1: 4;						// num 52~55
    uint8_t: 8;
} __attribute__((packed));

struct CAN_0x115 {	// fixedPeriodic: 10
    uint8_t vehicleMode: 2,					// num 0~1
        :4,
        cruiseSts: 1,						// num 6
        tcuWarning: 1;						// num 7
    uint16_t: 16;							// num 8~23
    uint8_t transGearPos: 8;				// num 24-31
    uint32_t: 32;
} __attribute__((packed));

struct CAN_0x210 {	// fixedPeriodic: 10
    uint8_t emoterOverHight: 1,				// num 0
        batChargeIndicate: 1,				// num 1
        emoterSystermFault: 1,				// num 2
        chargeDischargeIndicate: 1,			// num 3
        chargeWireConnect: 1,				// num 4
        batteryCutoff: 1,					// num 5
        batteryFault: 1,					// num 6
        insulationResistanceLow: 1;			// num 7
    uint8_t : 7,
    powerLimitIndicate: 1;				// num 15
    uint16_t : 8,
    battSOC2: 8;						// num 24~31
    uint32_t battVolt2: 6,					// num 32~37
        battSOC1: 2,						// num 38~39
        hvBusCur2: 4,						// num 40~43
        battVolt1: 4,						// num 44~47
        hvBusCur1: 8,						// num 48~55
        : 8;
} __attribute__((packed));

struct CAN_0x268 {	// fixedPeriodic: 100
    uint16_t driverSeatBelt: 1,				// num 0
        copilotSeatBelts: 1,
        copilotSeatOccupantState : 1,
        airBagWarningChime: 1,				// num 3
        : 12;
    uint8_t: 8;
} __attribute__((packed));

struct CAN_0x4D4 {	// fixedPeriodic: 150
    uint16_t turnLeft: 1,
        turnRight: 1,
        hoodStatus: 1,
        trunckStatus: 1,
        frontLeftDoor: 1,
        frontRightDoor: 1,
        rearLeftDoor: 1,
        rearRightDoor: 1,					// num 7
        : 3,
        anyDoor: 1,							// num 11
        : 1,
        lightLeftOn: 1,						// num 13
        : 1,
        keyInSwitch: 1;						// num 15
    uint16_t: 16;
    uint32_t: 32;
} __attribute__((packed));

struct CAN_0x10D {	// fixedPeriodic: 20
    uint8_t :5,
    epbErrorStatus: 1,                  // num 5
    epbStatus: 2;						// num 6~7
    uint16_t: 16;							// num 8~23
    uint8_t : 8;							// num 24-31
    uint32_t: 32;
} __attribute__((packed));
}
#endif
