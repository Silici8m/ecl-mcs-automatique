/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Experience_types.h
 *
 * Code generated for Simulink model 'Experience'.
 *
 * Model version                  : 13.0
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Fri Apr 10 11:53:47 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Experience_types_h_
#define Experience_types_h_
#include "MW_SVD.h"
#include "rtwtypes.h"
#ifndef struct_tag_pMPPJgn69ckPBhypf3vQzD
#define struct_tag_pMPPJgn69ckPBhypf3vQzD

struct tag_pMPPJgn69ckPBhypf3vQzD
{
  MW_Handle_Type MW_ANALOGIN_HANDLE;
};

#endif                                 /* struct_tag_pMPPJgn69ckPBhypf3vQzD */

#ifndef typedef_e_arduinodriver_ArduinoAnalog_T
#define typedef_e_arduinodriver_ArduinoAnalog_T

typedef struct tag_pMPPJgn69ckPBhypf3vQzD e_arduinodriver_ArduinoAnalog_T;

#endif                             /* typedef_e_arduinodriver_ArduinoAnalog_T */

#ifndef struct_tag_FIY6N64L77TlG9jHBRqBuB
#define struct_tag_FIY6N64L77TlG9jHBRqBuB

struct tag_FIY6N64L77TlG9jHBRqBuB
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  e_arduinodriver_ArduinoAnalog_T AnalogInDriverObj;
};

#endif                                 /* struct_tag_FIY6N64L77TlG9jHBRqBuB */

#ifndef typedef_codertarget_arduinobase_inter_T
#define typedef_codertarget_arduinobase_inter_T

typedef struct tag_FIY6N64L77TlG9jHBRqBuB codertarget_arduinobase_inter_T;

#endif                             /* typedef_codertarget_arduinobase_inter_T */

#ifndef struct_tag_IaGxvuMY2mAYbdmBITwwoD
#define struct_tag_IaGxvuMY2mAYbdmBITwwoD

struct tag_IaGxvuMY2mAYbdmBITwwoD
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                                 /* struct_tag_IaGxvuMY2mAYbdmBITwwoD */

#ifndef typedef_DCMotor1Set_Experience_T
#define typedef_DCMotor1Set_Experience_T

typedef struct tag_IaGxvuMY2mAYbdmBITwwoD DCMotor1Set_Experience_T;

#endif                                 /* typedef_DCMotor1Set_Experience_T */

#ifndef struct_tag_V49fwHKKE3bdTqwSMJwL7C
#define struct_tag_V49fwHKKE3bdTqwSMJwL7C

struct tag_V49fwHKKE3bdTqwSMJwL7C
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                                 /* struct_tag_V49fwHKKE3bdTqwSMJwL7C */

#ifndef typedef_DCMotor2Set_Experience_T
#define typedef_DCMotor2Set_Experience_T

typedef struct tag_V49fwHKKE3bdTqwSMJwL7C DCMotor2Set_Experience_T;

#endif                                 /* typedef_DCMotor2Set_Experience_T */

#ifndef struct_tag_Y2edXYj8XK66yHyKeoxJzC
#define struct_tag_Y2edXYj8XK66yHyKeoxJzC

struct tag_Y2edXYj8XK66yHyKeoxJzC
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T SampleTime;
};

#endif                                 /* struct_tag_Y2edXYj8XK66yHyKeoxJzC */

#ifndef typedef_Enc1Read_Experience_T
#define typedef_Enc1Read_Experience_T

typedef struct tag_Y2edXYj8XK66yHyKeoxJzC Enc1Read_Experience_T;

#endif                                 /* typedef_Enc1Read_Experience_T */

#ifndef struct_tag_KoJClDaOsPhIcfOEhAjxOD
#define struct_tag_KoJClDaOsPhIcfOEhAjxOD

struct tag_KoJClDaOsPhIcfOEhAjxOD
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T SampleTime;
};

#endif                                 /* struct_tag_KoJClDaOsPhIcfOEhAjxOD */

#ifndef typedef_Enc1Period_Experience_T
#define typedef_Enc1Period_Experience_T

typedef struct tag_KoJClDaOsPhIcfOEhAjxOD Enc1Period_Experience_T;

#endif                                 /* typedef_Enc1Period_Experience_T */

/* Parameters (default storage) */
typedef struct P_Experience_T_ P_Experience_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Experience_T RT_MODEL_Experience_T;

#endif                                 /* Experience_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
