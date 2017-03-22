
#ifndef Boolean
#define Boolean int
#endif

#ifndef TRUE
#define TRUE 0
#endif

#ifndef FALSE
#define FALSE 1
#endif

// Default X/U/Y/Th/Ps/Ph value
#define DEFAULT_WC 9999

// FERA virtual station number connected to the scintillators
#define FERA_PS_VS 1
// FERA channel connected to the 1st/2nd scintillators, Left/Right
#define FERA_PS_CH_1L 0
#define FERA_PS_CH_1R 1
#define FERA_PS_CH_2L 2
#define FERA_PS_CH_2R 3

// FERA virtual station number connected to the scintillators
#define FERET_PS_VS 0x81
// FERET channel connected to the 1st/2nd scintillators, Left/Right and RF
#define FERET_PS_CH_1L 0
#define FERET_PS_CH_1R 1
#define FERET_PS_CH_2L 2
#define FERET_PS_CH_2R 3
#define FERET_PS_CH_RF 4

// 1BlockのWord数(*2Bytes)
#define BL_WORD_8 8192
#define BL_WORD_16 16384
#define BL_WORD_24 24576
#define BL_WORD_32 32768
#define BL_WORD_40 40960
#define BL_WORD_48 49152

// Number of wires in each wire plane
#define N_WIRE_X1 192
#define N_WIRE_U1 208
#define N_WIRE_X2 192
#define N_WIRE_U2 208

// first wireID of each chamber(本数はX:198,Y:16のハズ)
#define FIRSTWIRE_X1 40
#define FIRSTWIRE_X2 264
#define FIRSTWIRE_U1 480
#define FIRSTWIRE_U2 680

#define FIRSTWIRE_Y 480

// maximum drift length in wire chamber [mm]
#define X1_DRIFT 10.0
#define U1_DRIFT 10.0
#define X2_DRIFT 10.0
#define U2_DRIFT 10.0

// sin, cos and tan^-1 of tilting angle of U wires, 48.19 degrees
#define U_SIN 0.745359656
#define U_COS 0.66666257
#define U_TAN_INV 0.894417298
// sin(48.19)+(tan(90-48.19)*cos(48.19))
#define U_CONST 1.341634191

#define DEG2MRAD 17.45329252

#define SIN4181 0.6666625702
#define COS4181 0.745359656467
#define TAN4181 0.894417298306

// Z distance between X1 and X2 chambers
// (中西値は225mm。0にあう様に調整した)
#define z_X1X2 226.0

// X difference between X1 and X2 chambers (中西値)
#define x_X1X2 244.0

// sence wire spacing [mm]
#define X_WIRESPACE 6.0
#define U_WIRESPACE 4.0
