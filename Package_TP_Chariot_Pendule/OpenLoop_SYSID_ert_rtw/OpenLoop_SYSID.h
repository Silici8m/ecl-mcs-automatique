/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: OpenLoop_SYSID.h
 *
 * Code generated for Simulink model 'OpenLoop_SYSID'.
 *
 * Model version                  : 13.1
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Fri Apr 10 09:12:57 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef OpenLoop_SYSID_h_
#define OpenLoop_SYSID_h_
#ifndef OpenLoop_SYSID_COMMON_INCLUDES_
#define OpenLoop_SYSID_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_mode.h"
#include "MW_AnalogIn.h"
#include "MegapiDCMotors.h"
#endif                                 /* OpenLoop_SYSID_COMMON_INCLUDES_ */

#include "OpenLoop_SYSID_types.h"
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T u;                            /* '<Root>/Saturation' */
  real32_T Gain;                       /* '<S5>/Gain' */
  real32_T Gain2;                      /* '<S5>/Gain2' */
  real32_T Phi;                     /* '<S1>/Raw -> rad positif vers l'avant' */
} B_OpenLoop_SYSID_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  Enc1Read_OpenLoop_SYSID_T obj;       /* '<S5>/MATLAB System' */
  Enc1Period_OpenLoop_SYSID_T obj_g;   /* '<S5>/MATLAB System1' */
  codertarget_arduinobase_inter_T obj_p;/* '<S1>/Angle sensor' */
  DCMotor1Set_OpenLoop_SYSID_T obj_i;  /* '<S7>/MATLAB System1' */
  DCMotor2Set_OpenLoop_SYSID_T obj_pv; /* '<S8>/MATLAB System' */
  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWs_PWORK;                      /* '<S2>/FromWs' */

  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWs_PWORK_a;                    /* '<S3>/FromWs' */

  real32_T Delay_DSTATE;               /* '<S6>/Delay' */
  struct {
    int_T PrevIndex;
  } FromWs_IWORK;                      /* '<S2>/FromWs' */

  struct {
    int_T PrevIndex;
  } FromWs_IWORK_d;                    /* '<S3>/FromWs' */

  boolean_T icLoad;                    /* '<S6>/Delay' */
} DW_OpenLoop_SYSID_T;

/* Parameters (default storage) */
struct P_OpenLoop_SYSID_T_ {
  real_T Motor1_Vmax;                  /* Mask Parameter: Motor1_Vmax
                                        * Referenced by: '<S7>/Gain'
                                        */
  real_T Motor2_Vmax;                  /* Mask Parameter: Motor2_Vmax
                                        * Referenced by: '<S8>/Gain'
                                        */
  real_T MATLABSystem_SampleTime;      /* Expression: -1
                                        * Referenced by: '<S5>/MATLAB System'
                                        */
  real_T MATLABSystem1_SampleTime;     /* Expression: -1
                                        * Referenced by: '<S5>/MATLAB System1'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 9
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -9
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_UpperSat_l;        /* Expression: 255
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T Saturation_LowerSat_o;        /* Expression: -255
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T Gain_Gain;                    /* Expression: -1
                                        * Referenced by: '<S4>/Gain'
                                        */
  real_T Saturation_UpperSat_a;        /* Expression: 255
                                        * Referenced by: '<S8>/Saturation'
                                        */
  real_T Saturation_LowerSat_b;        /* Expression: -255
                                        * Referenced by: '<S8>/Saturation'
                                        */
  real32_T Gain_Gain_n;                /* Computed Parameter: Gain_Gain_n
                                        * Referenced by: '<S5>/Gain'
                                        */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S5>/Gain1'
                                        */
  real32_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S5>/Gain2'
                                        */
  real32_T Rawradpositifverslavant_Gain;
                             /* Computed Parameter: Rawradpositifverslavant_Gain
                              * Referenced by: '<S1>/Raw -> rad positif vers l'avant'
                              */
  uint8_T ManualSwitch_CurrentSetting;
                              /* Computed Parameter: ManualSwitch_CurrentSetting
                               * Referenced by: '<Root>/Manual Switch'
                               */
};

/* Real-time Model Data Structure */
struct tag_RTM_OpenLoop_SYSID_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_OpenLoop_SYSID_T OpenLoop_SYSID_P;

/* Block signals (default storage) */
extern B_OpenLoop_SYSID_T OpenLoop_SYSID_B;

/* Block states (default storage) */
extern DW_OpenLoop_SYSID_T OpenLoop_SYSID_DW;

/* Model entry point functions */
extern void OpenLoop_SYSID_initialize(void);
extern void OpenLoop_SYSID_step(void);
extern void OpenLoop_SYSID_terminate(void);

/* Real-time Model object */
extern RT_MODEL_OpenLoop_SYSID_T *const OpenLoop_SYSID_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Add1' : Unused code path elimination
 * Block '<Root>/Sine Wave2' : Unused code path elimination
 * Block '<Root>/Sine Wave3' : Unused code path elimination
 * Block '<S5>/Reshape' : Reshape block reduction
 * Block '<S5>/Reshape1' : Reshape block reduction
 * Block '<S1>/Reshape' : Reshape block reduction
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'OpenLoop_SYSID'
 * '<S1>'   : 'OpenLoop_SYSID/ROBOT'
 * '<S2>'   : 'OpenLoop_SYSID/Signal Builder1'
 * '<S3>'   : 'OpenLoop_SYSID/Signal Builder2'
 * '<S4>'   : 'OpenLoop_SYSID/ROBOT/Moteurs Base Translation'
 * '<S5>'   : 'OpenLoop_SYSID/ROBOT/MotorEncoder Translation'
 * '<S6>'   : 'OpenLoop_SYSID/ROBOT/Offset cancellation'
 * '<S7>'   : 'OpenLoop_SYSID/ROBOT/Moteurs Base Translation/Motor1'
 * '<S8>'   : 'OpenLoop_SYSID/ROBOT/Moteurs Base Translation/Motor2'
 */
#endif                                 /* OpenLoop_SYSID_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
