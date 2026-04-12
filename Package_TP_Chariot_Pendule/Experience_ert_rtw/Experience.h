/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Experience.h
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

#ifndef Experience_h_
#define Experience_h_
#ifndef Experience_COMMON_INCLUDES_
#define Experience_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_mode.h"
#include "MW_AnalogIn.h"
#include "MegapiDCMotors.h"
#endif                                 /* Experience_COMMON_INCLUDES_ */

#include "Experience_types.h"
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
  real_T CastToDouble1[2];             /* '<Root>/Cast To Double1' */
  real_T CastToDouble2[2];             /* '<Root>/Cast To Double2' */
  real_T e;                            /* '<Root>/Commande FF' */
  real32_T Gain;                       /* '<S4>/Gain' */
  real32_T Delay;                      /* '<S5>/Delay' */
  real32_T Phi;                     /* '<S2>/Raw -> rad positif vers l'avant' */
  real32_T u;                          /* '<Root>/Saturation' */
  real32_T Gain2;                      /* '<S4>/Gain2' */
  real32_T xhat[4];                    /* '<Root>/Commande FF' */
  real32_T fv[4];
  real_T sampleTime;
  real_T sampleTime_m;
} B_Experience_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  Enc1Read_Experience_T obj;           /* '<S4>/MATLAB System' */
  Enc1Period_Experience_T obj_g;       /* '<S4>/MATLAB System1' */
  codertarget_arduinobase_inter_T obj_p;/* '<S2>/Angle sensor' */
  DCMotor1Set_Experience_T obj_i;      /* '<S6>/MATLAB System1' */
  DCMotor2Set_Experience_T obj_pv;     /* '<S7>/MATLAB System' */
  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<Root>/Scope' */

  struct {
    void *LoggedData[2];
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  real32_T UnitDelay1_DSTATE[4];       /* '<Root>/Unit Delay1' */
  real32_T Delay_DSTATE;               /* '<S5>/Delay' */
  boolean_T icLoad;                    /* '<S5>/Delay' */
  boolean_T doneDoubleBufferReInit;    /* '<Root>/Commande FF' */
} DW_Experience_T;

/* Parameters (default storage) */
struct P_Experience_T_ {
  real_T A[16];                        /* Variable: A
                                        * Referenced by: '<Root>/Commande FF'
                                        */
  real_T B[4];                         /* Variable: B
                                        * Referenced by: '<Root>/Commande FF'
                                        */
  real_T C[8];                         /* Variable: C
                                        * Referenced by: '<Root>/Commande FF'
                                        */
  real_T H;                            /* Variable: H
                                        * Referenced by: '<Root>/Commande FF'
                                        */
  real_T K[4];                         /* Variable: K
                                        * Referenced by: '<Root>/Commande FF'
                                        */
  real_T L[8];                         /* Variable: L
                                        * Referenced by: '<Root>/Commande FF'
                                        */
  real_T MATLABSystem_SampleTime;      /* Expression: -1
                                        * Referenced by: '<S4>/MATLAB System'
                                        */
  real_T MATLABSystem1_SampleTime;     /* Expression: -1
                                        * Referenced by: '<S4>/MATLAB System1'
                                        */
  real_T SignalGenerator_Amplitude;    /* Expression: 0
                                        * Referenced by: '<Root>/Signal Generator'
                                        */
  real_T SignalGenerator_Frequency;    /* Expression: .2
                                        * Referenced by: '<Root>/Signal Generator'
                                        */
  real32_T UnitDelay1_InitialCondition[4];
                              /* Computed Parameter: UnitDelay1_InitialCondition
                               * Referenced by: '<Root>/Unit Delay1'
                               */
  real32_T Gain_Gain;                  /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S4>/Gain'
                                        */
  real32_T Rawradpositifverslavant_Gain;
                             /* Computed Parameter: Rawradpositifverslavant_Gain
                              * Referenced by: '<S2>/Raw -> rad positif vers l'avant'
                              */
  real32_T Saturation_UpperSat;       /* Computed Parameter: Saturation_UpperSat
                                       * Referenced by: '<Root>/Saturation'
                                       */
  real32_T Saturation_LowerSat;       /* Computed Parameter: Saturation_LowerSat
                                       * Referenced by: '<Root>/Saturation'
                                       */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S4>/Gain1'
                                        */
  real32_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S4>/Gain2'
                                        */
  real32_T Gain_Gain_i;                /* Computed Parameter: Gain_Gain_i
                                        * Referenced by: '<S6>/Gain'
                                        */
  real32_T Saturation_UpperSat_l;   /* Computed Parameter: Saturation_UpperSat_l
                                     * Referenced by: '<S6>/Saturation'
                                     */
  real32_T Saturation_LowerSat_o;   /* Computed Parameter: Saturation_LowerSat_o
                                     * Referenced by: '<S6>/Saturation'
                                     */
  real32_T Gain_Gain_k;                /* Computed Parameter: Gain_Gain_k
                                        * Referenced by: '<S3>/Gain'
                                        */
  real32_T Gain_Gain_o;                /* Computed Parameter: Gain_Gain_o
                                        * Referenced by: '<S7>/Gain'
                                        */
  real32_T Saturation_UpperSat_a;   /* Computed Parameter: Saturation_UpperSat_a
                                     * Referenced by: '<S7>/Saturation'
                                     */
  real32_T Saturation_LowerSat_b;   /* Computed Parameter: Saturation_LowerSat_b
                                     * Referenced by: '<S7>/Saturation'
                                     */
};

/* Real-time Model Data Structure */
struct tag_RTM_Experience_T {
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
extern P_Experience_T Experience_P;

/* Block signals (default storage) */
extern B_Experience_T Experience_B;

/* Block states (default storage) */
extern DW_Experience_T Experience_DW;

/* Model entry point functions */
extern void Experience_initialize(void);
extern void Experience_step(void);
extern void Experience_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Experience_T *const Experience_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Cast To Single' : Eliminate redundant data type conversion
 * Block '<S4>/Reshape' : Reshape block reduction
 * Block '<S4>/Reshape1' : Reshape block reduction
 * Block '<S2>/Reshape' : Reshape block reduction
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
 * '<Root>' : 'Experience'
 * '<S1>'   : 'Experience/Commande FF'
 * '<S2>'   : 'Experience/ROBOT'
 * '<S3>'   : 'Experience/ROBOT/Moteurs Base Translation'
 * '<S4>'   : 'Experience/ROBOT/MotorEncoder Translation'
 * '<S5>'   : 'Experience/ROBOT/Offset cancellation'
 * '<S6>'   : 'Experience/ROBOT/Moteurs Base Translation/Motor1'
 * '<S7>'   : 'Experience/ROBOT/Moteurs Base Translation/Motor2'
 */
#endif                                 /* Experience_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
