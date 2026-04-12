/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: OpenLoop_SYSID.c
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

#include "OpenLoop_SYSID.h"
#include "rt_nonfinite.h"
#include <math.h>
#include "rtwtypes.h"
#include "OpenLoop_SYSID_private.h"
#include <string.h>

/* Block signals (default storage) */
B_OpenLoop_SYSID_T OpenLoop_SYSID_B;

/* Block states (default storage) */
DW_OpenLoop_SYSID_T OpenLoop_SYSID_DW;

/* Real-time model */
static RT_MODEL_OpenLoop_SYSID_T OpenLoop_SYSID_M_;
RT_MODEL_OpenLoop_SYSID_T *const OpenLoop_SYSID_M = &OpenLoop_SYSID_M_;

/* Model step function */
void OpenLoop_SYSID_step(void)
{
  /* local block i/o variables */
  real_T rtb_ManualSwitch;
  real_T rtb_Saturation;
  real32_T rtb_Delay;
  real_T sampleTime;
  real_T sampleTime_0;
  int32_T rtb_MATLABSystem1_0;
  int16_T rtb_MATLABSystem_0;
  uint16_T b_varargout_1;
  boolean_T b;

  /* FromWorkspace: '<S2>/FromWs' */
  {
    real_T *pDataValues = (real_T *) OpenLoop_SYSID_DW.FromWs_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) OpenLoop_SYSID_DW.FromWs_PWORK.TimePtr;
    int_T currTimeIndex = OpenLoop_SYSID_DW.FromWs_IWORK.PrevIndex;
    real_T t = OpenLoop_SYSID_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[13]) {
      currTimeIndex = 12;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    OpenLoop_SYSID_DW.FromWs_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_ManualSwitch = pDataValues[currTimeIndex];
        } else {
          rtb_ManualSwitch = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex = currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_ManualSwitch = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 14;
      }
    }
  }

  /* FromWorkspace: '<S3>/FromWs' */
  {
    real_T *pDataValues = (real_T *) OpenLoop_SYSID_DW.FromWs_PWORK_a.DataPtr;
    real_T *pTimeValues = (real_T *) OpenLoop_SYSID_DW.FromWs_PWORK_a.TimePtr;
    int_T currTimeIndex = OpenLoop_SYSID_DW.FromWs_IWORK_d.PrevIndex;
    real_T t = OpenLoop_SYSID_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[11]) {
      currTimeIndex = 10;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    OpenLoop_SYSID_DW.FromWs_IWORK_d.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Saturation = pDataValues[currTimeIndex];
        } else {
          rtb_Saturation = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex = currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Saturation = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 12;
      }
    }
  }

  /* ManualSwitch: '<Root>/Manual Switch' */
  if (OpenLoop_SYSID_P.ManualSwitch_CurrentSetting != 1) {
    /* ManualSwitch: '<Root>/Manual Switch' */
    rtb_ManualSwitch = rtb_Saturation;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch' */

  /* Saturate: '<Root>/Saturation' */
  if (rtb_ManualSwitch > OpenLoop_SYSID_P.Saturation_UpperSat) {
    /* Saturate: '<Root>/Saturation' */
    OpenLoop_SYSID_B.u = OpenLoop_SYSID_P.Saturation_UpperSat;
  } else if (rtb_ManualSwitch < OpenLoop_SYSID_P.Saturation_LowerSat) {
    /* Saturate: '<Root>/Saturation' */
    OpenLoop_SYSID_B.u = OpenLoop_SYSID_P.Saturation_LowerSat;
  } else {
    /* Saturate: '<Root>/Saturation' */
    OpenLoop_SYSID_B.u = rtb_ManualSwitch;
  }

  /* End of Saturate: '<Root>/Saturation' */
  /* MATLABSystem: '<S5>/MATLAB System' */
  if (OpenLoop_SYSID_DW.obj.SampleTime !=
      OpenLoop_SYSID_P.MATLABSystem_SampleTime) {
    b = rtIsInf(OpenLoop_SYSID_P.MATLABSystem_SampleTime);
    if (((!b) && (!rtIsNaN(OpenLoop_SYSID_P.MATLABSystem_SampleTime))) || b) {
      sampleTime = OpenLoop_SYSID_P.MATLABSystem_SampleTime;
    }

    OpenLoop_SYSID_DW.obj.SampleTime = sampleTime;
  }

  /*         %% Define output properties */
  /*  Call C-function implementing device output */
  rtb_MATLABSystem_0 = EncPortRead1();

  /* Gain: '<S5>/Gain' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  MATLABSystem: '<S5>/MATLAB System'
   */
  OpenLoop_SYSID_B.Gain = OpenLoop_SYSID_P.Gain_Gain_n * (real32_T)
    rtb_MATLABSystem_0;

  /* MATLABSystem: '<S5>/MATLAB System1' */
  if (OpenLoop_SYSID_DW.obj_g.SampleTime !=
      OpenLoop_SYSID_P.MATLABSystem1_SampleTime) {
    b = rtIsInf(OpenLoop_SYSID_P.MATLABSystem1_SampleTime);
    if (((!b) && (!rtIsNaN(OpenLoop_SYSID_P.MATLABSystem1_SampleTime))) || b) {
      sampleTime_0 = OpenLoop_SYSID_P.MATLABSystem1_SampleTime;
    }

    OpenLoop_SYSID_DW.obj_g.SampleTime = sampleTime_0;
  }

  /*         %% Define output properties */
  /*  Call C-function implementing device output */
  rtb_MATLABSystem1_0 = EncPeriodRead1();

  /* Gain: '<S5>/Gain2' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion1'
   *  Gain: '<S5>/Gain1'
   *  MATLABSystem: '<S5>/MATLAB System1'
   *  Math: '<S5>/Math Function'
   *
   * About '<S5>/Math Function':
   *  Operator: reciprocal
   */
  OpenLoop_SYSID_B.Gain2 = 1.0F / (OpenLoop_SYSID_P.Gain1_Gain * (real32_T)
    rtb_MATLABSystem1_0) * OpenLoop_SYSID_P.Gain2_Gain;

  /* MATLABSystem: '<S1>/Angle sensor' */
  OpenLoop_SYSID_DW.obj_p.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogIn_GetHandle(64UL);
  MW_AnalogInSingle_ReadResult
    (OpenLoop_SYSID_DW.obj_p.AnalogInDriverObj.MW_ANALOGIN_HANDLE,
     &b_varargout_1, MW_ANALOGIN_UINT16);

  /* Delay: '<S6>/Delay' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   *  MATLABSystem: '<S1>/Angle sensor'
   * */
  if (OpenLoop_SYSID_DW.icLoad) {
    OpenLoop_SYSID_DW.Delay_DSTATE = b_varargout_1;
  }

  /* Delay: '<S6>/Delay' */
  rtb_Delay = OpenLoop_SYSID_DW.Delay_DSTATE;

  /* Gain: '<S1>/Raw -> rad positif vers l'avant' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   *  MATLABSystem: '<S1>/Angle sensor'
   *  Sum: '<S6>/Sum'
   * */
  OpenLoop_SYSID_B.Phi = ((real32_T)b_varargout_1 - rtb_Delay) *
    OpenLoop_SYSID_P.Rawradpositifverslavant_Gain;

  /* Saturate: '<S8>/Saturation' incorporates:
   *  Gain: '<S7>/Gain'
   */
  rtb_Saturation = 255.0 / OpenLoop_SYSID_P.Motor1_Vmax * OpenLoop_SYSID_B.u;

  /* Saturate: '<S7>/Saturation' */
  if (rtb_Saturation > OpenLoop_SYSID_P.Saturation_UpperSat_l) {
    /* Saturate: '<S8>/Saturation' */
    rtb_Saturation = OpenLoop_SYSID_P.Saturation_UpperSat_l;
  } else if (rtb_Saturation < OpenLoop_SYSID_P.Saturation_LowerSat_o) {
    /* Saturate: '<S8>/Saturation' */
    rtb_Saturation = OpenLoop_SYSID_P.Saturation_LowerSat_o;
  }

  /* End of Saturate: '<S7>/Saturation' */

  /* DataTypeConversion: '<S7>/Data Type Conversion' */
  /*         %% Define input properties */
  /*  Call C-function implementing device output */
  sampleTime = floor(rtb_Saturation);
  if (rtIsNaN(sampleTime) || rtIsInf(sampleTime)) {
    sampleTime = 0.0;
  } else {
    sampleTime = fmod(sampleTime, 65536.0);
  }

  /* MATLABSystem: '<S7>/MATLAB System1' incorporates:
   *  DataTypeConversion: '<S7>/Data Type Conversion'
   */
  DCMotor1Set(sampleTime < 0.0 ? -(int16_T)(uint16_T)-sampleTime : (int16_T)
              (uint16_T)sampleTime);

  /* Saturate: '<S8>/Saturation' incorporates:
   *  Gain: '<S4>/Gain'
   *  Gain: '<S8>/Gain'
   */
  rtb_Saturation = 255.0 / OpenLoop_SYSID_P.Motor2_Vmax *
    (OpenLoop_SYSID_P.Gain_Gain * OpenLoop_SYSID_B.u);

  /* Saturate: '<S8>/Saturation' */
  if (rtb_Saturation > OpenLoop_SYSID_P.Saturation_UpperSat_a) {
    /* Saturate: '<S8>/Saturation' */
    rtb_Saturation = OpenLoop_SYSID_P.Saturation_UpperSat_a;
  } else if (rtb_Saturation < OpenLoop_SYSID_P.Saturation_LowerSat_b) {
    /* Saturate: '<S8>/Saturation' */
    rtb_Saturation = OpenLoop_SYSID_P.Saturation_LowerSat_b;
  }

  /* End of Saturate: '<S8>/Saturation' */

  /* DataTypeConversion: '<S8>/Data Type Conversion' */
  /*         %% Define input properties */
  /*  Call C-function implementing device output */
  sampleTime = floor(rtb_Saturation);
  if (rtIsNaN(sampleTime) || rtIsInf(sampleTime)) {
    sampleTime = 0.0;
  } else {
    sampleTime = fmod(sampleTime, 65536.0);
  }

  /* MATLABSystem: '<S8>/MATLAB System' incorporates:
   *  DataTypeConversion: '<S8>/Data Type Conversion'
   */
  DCMotor2Set(sampleTime < 0.0 ? -(int16_T)(uint16_T)-sampleTime : (int16_T)
              (uint16_T)sampleTime);

  /* Update for Delay: '<S6>/Delay' */
  OpenLoop_SYSID_DW.icLoad = false;
  OpenLoop_SYSID_DW.Delay_DSTATE = rtb_Delay;

  {                                    /* Sample time: [0.005s, 0.0s] */
    extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
    extmodeSimulationTime_T extmodeTime = (extmodeSimulationTime_T)
      ((OpenLoop_SYSID_M->Timing.clockTick1 * 1) + 0);

    /* Trigger External Mode event */
    errorCode = extmodeEvent(1, extmodeTime);
    if (errorCode != EXTMODE_SUCCESS) {
      /* Code to handle External Mode event errors
         may be added here */
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  OpenLoop_SYSID_M->Timing.t[0] =
    ((time_T)(++OpenLoop_SYSID_M->Timing.clockTick0)) *
    OpenLoop_SYSID_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.005s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.005, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    OpenLoop_SYSID_M->Timing.clockTick1++;
  }
}

/* Model initialize function */
void OpenLoop_SYSID_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)OpenLoop_SYSID_M, 0,
                sizeof(RT_MODEL_OpenLoop_SYSID_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&OpenLoop_SYSID_M->solverInfo,
                          &OpenLoop_SYSID_M->Timing.simTimeStep);
    rtsiSetTPtr(&OpenLoop_SYSID_M->solverInfo, &rtmGetTPtr(OpenLoop_SYSID_M));
    rtsiSetStepSizePtr(&OpenLoop_SYSID_M->solverInfo,
                       &OpenLoop_SYSID_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&OpenLoop_SYSID_M->solverInfo, (&rtmGetErrorStatus
      (OpenLoop_SYSID_M)));
    rtsiSetRTModelPtr(&OpenLoop_SYSID_M->solverInfo, OpenLoop_SYSID_M);
  }

  rtsiSetSimTimeStep(&OpenLoop_SYSID_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&OpenLoop_SYSID_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&OpenLoop_SYSID_M->solverInfo, false);
  rtsiSetSolverName(&OpenLoop_SYSID_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(OpenLoop_SYSID_M, &OpenLoop_SYSID_M->Timing.tArray[0]);
  rtmSetTFinal(OpenLoop_SYSID_M, 15.0);
  OpenLoop_SYSID_M->Timing.stepSize0 = 0.005;

  /* External mode info */
  OpenLoop_SYSID_M->Sizes.checksums[0] = (3951556716U);
  OpenLoop_SYSID_M->Sizes.checksums[1] = (3316185911U);
  OpenLoop_SYSID_M->Sizes.checksums[2] = (36711401U);
  OpenLoop_SYSID_M->Sizes.checksums[3] = (2936794777U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[6];
    OpenLoop_SYSID_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(OpenLoop_SYSID_M->extModeInfo,
      &OpenLoop_SYSID_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(OpenLoop_SYSID_M->extModeInfo,
                        OpenLoop_SYSID_M->Sizes.checksums);
    rteiSetTFinalTicks(OpenLoop_SYSID_M->extModeInfo, 3000);
  }

  /* block I/O */
  (void) memset(((void *) &OpenLoop_SYSID_B), 0,
                sizeof(B_OpenLoop_SYSID_T));

  /* states (dwork) */
  (void) memset((void *)&OpenLoop_SYSID_DW, 0,
                sizeof(DW_OpenLoop_SYSID_T));

  {
    real_T sampleTime;
    real_T sampleTime_0;
    boolean_T b;

    /* Start for FromWorkspace: '<S2>/FromWs' */
    {
      static real_T pTimeValues0[] = { 0.0, 1.0, 1.0, 2.0, 2.0,
        4.0200000000000005, 4.0200000000000005, 6.0, 6.0, 7.36, 7.36, 7.68, 7.68,
        10.0 } ;

      static real_T pDataValues0[] = { 0.0, 0.0, 5.0, 5.0, 3.0, 3.0, -3.19,
        -3.23, 2.5, 2.5, 0.0, 0.0, 0.0, 0.04 } ;

      OpenLoop_SYSID_DW.FromWs_PWORK.TimePtr = (void *) pTimeValues0;
      OpenLoop_SYSID_DW.FromWs_PWORK.DataPtr = (void *) pDataValues0;
      OpenLoop_SYSID_DW.FromWs_IWORK.PrevIndex = 0;
    }

    /* Start for FromWorkspace: '<S3>/FromWs' */
    {
      static real_T pTimeValues0[] = { 0.0, 1.0, 1.0, 2.39, 2.39, 3.72, 3.72,
        6.0, 6.0, 8.0, 8.0, 10.0 } ;

      static real_T pDataValues0[] = { 0.0, 0.0, 7.0, 3.0, 0.0, 0.0, -4.0, -3.0,
        3.0, 6.0, 0.0, 0.04 } ;

      OpenLoop_SYSID_DW.FromWs_PWORK_a.TimePtr = (void *) pTimeValues0;
      OpenLoop_SYSID_DW.FromWs_PWORK_a.DataPtr = (void *) pDataValues0;
      OpenLoop_SYSID_DW.FromWs_IWORK_d.PrevIndex = 0;
    }

    /* InitializeConditions for Delay: '<S6>/Delay' */
    OpenLoop_SYSID_DW.icLoad = true;

    /* Start for MATLABSystem: '<S5>/MATLAB System' */
    OpenLoop_SYSID_DW.obj.matlabCodegenIsDeleted = false;
    b = rtIsInf(OpenLoop_SYSID_P.MATLABSystem_SampleTime);
    if (((!b) && (!rtIsNaN(OpenLoop_SYSID_P.MATLABSystem_SampleTime))) || b) {
      sampleTime = OpenLoop_SYSID_P.MATLABSystem_SampleTime;
    }

    OpenLoop_SYSID_DW.obj.SampleTime = sampleTime;
    OpenLoop_SYSID_DW.obj.isInitialized = 1L;

    /*         %% Define output properties */
    /*  Call C-function implementing device initialization */
    EncPort1Setup();
    OpenLoop_SYSID_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S5>/MATLAB System' */

    /* Start for MATLABSystem: '<S5>/MATLAB System1' */
    OpenLoop_SYSID_DW.obj_g.matlabCodegenIsDeleted = false;
    b = rtIsInf(OpenLoop_SYSID_P.MATLABSystem1_SampleTime);
    if (((!b) && (!rtIsNaN(OpenLoop_SYSID_P.MATLABSystem1_SampleTime))) || b) {
      sampleTime_0 = OpenLoop_SYSID_P.MATLABSystem1_SampleTime;
    }

    OpenLoop_SYSID_DW.obj_g.SampleTime = sampleTime_0;
    OpenLoop_SYSID_DW.obj_g.isInitialized = 1L;

    /*         %% Define output properties */
    /*  Call C-function implementing device initialization */
    EncPort1Setup();
    OpenLoop_SYSID_DW.obj_g.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S5>/MATLAB System1' */

    /* Start for MATLABSystem: '<S1>/Angle sensor' */
    OpenLoop_SYSID_DW.obj_p.matlabCodegenIsDeleted = false;
    OpenLoop_SYSID_DW.obj_p.isInitialized = 1L;
    OpenLoop_SYSID_DW.obj_p.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
      MW_AnalogInSingle_Open(64UL);
    OpenLoop_SYSID_DW.obj_p.isSetupComplete = true;

    /* Start for MATLABSystem: '<S7>/MATLAB System1' */
    OpenLoop_SYSID_DW.obj_i.matlabCodegenIsDeleted = false;
    OpenLoop_SYSID_DW.obj_i.isInitialized = 1L;

    /*         %% Define input properties */
    /*  Call C-function implementing device initialization */
    DCMotor1Setup();
    OpenLoop_SYSID_DW.obj_i.isSetupComplete = true;

    /* Start for MATLABSystem: '<S8>/MATLAB System' */
    OpenLoop_SYSID_DW.obj_pv.matlabCodegenIsDeleted = false;
    OpenLoop_SYSID_DW.obj_pv.isInitialized = 1L;

    /*         %% Define input properties */
    /*  Call C-function implementing device initialization */
    DCMotor2Setup();
    OpenLoop_SYSID_DW.obj_pv.isSetupComplete = true;
  }
}

/* Model terminate function */
void OpenLoop_SYSID_terminate(void)
{
  /* Terminate for MATLABSystem: '<S5>/MATLAB System' */
  if (!OpenLoop_SYSID_DW.obj.matlabCodegenIsDeleted) {
    OpenLoop_SYSID_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S5>/MATLAB System' */
  /* Terminate for MATLABSystem: '<S5>/MATLAB System1' */
  if (!OpenLoop_SYSID_DW.obj_g.matlabCodegenIsDeleted) {
    OpenLoop_SYSID_DW.obj_g.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S5>/MATLAB System1' */
  /* Terminate for MATLABSystem: '<S1>/Angle sensor' */
  if (!OpenLoop_SYSID_DW.obj_p.matlabCodegenIsDeleted) {
    OpenLoop_SYSID_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((OpenLoop_SYSID_DW.obj_p.isInitialized == 1L) &&
        OpenLoop_SYSID_DW.obj_p.isSetupComplete) {
      OpenLoop_SYSID_DW.obj_p.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
        MW_AnalogIn_GetHandle(64UL);
      MW_AnalogIn_Close
        (OpenLoop_SYSID_DW.obj_p.AnalogInDriverObj.MW_ANALOGIN_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S1>/Angle sensor' */
  /* Terminate for MATLABSystem: '<S7>/MATLAB System1' */
  if (!OpenLoop_SYSID_DW.obj_i.matlabCodegenIsDeleted) {
    OpenLoop_SYSID_DW.obj_i.matlabCodegenIsDeleted = true;
    if ((OpenLoop_SYSID_DW.obj_i.isInitialized == 1L) &&
        OpenLoop_SYSID_DW.obj_i.isSetupComplete) {
      /*  Call C-function implementing device termination */
      /* coder.ceval('sink_terminate'); */
      DCMotor1Set(0.0);
    }
  }

  /* End of Terminate for MATLABSystem: '<S7>/MATLAB System1' */

  /* Terminate for MATLABSystem: '<S8>/MATLAB System' */
  if (!OpenLoop_SYSID_DW.obj_pv.matlabCodegenIsDeleted) {
    OpenLoop_SYSID_DW.obj_pv.matlabCodegenIsDeleted = true;
    if ((OpenLoop_SYSID_DW.obj_pv.isInitialized == 1L) &&
        OpenLoop_SYSID_DW.obj_pv.isSetupComplete) {
      /*  Call C-function implementing device termination */
      DCMotor2Set(0.0);
    }
  }

  /* End of Terminate for MATLABSystem: '<S8>/MATLAB System' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
