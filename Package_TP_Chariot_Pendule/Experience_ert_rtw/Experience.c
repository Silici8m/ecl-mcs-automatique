/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Experience.c
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

#include "Experience.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "Experience_private.h"
#include <string.h>

/* Block signals (default storage) */
B_Experience_T Experience_B;

/* Block states (default storage) */
DW_Experience_T Experience_DW;

/* Real-time model */
static RT_MODEL_Experience_T Experience_M_;
RT_MODEL_Experience_T *const Experience_M = &Experience_M_;

/* Model step function */
void Experience_step(void)
{
  real_T rtb_SignalGenerator;
  int32_T rtb_MATLABSystem1_0;
  real32_T tmp[2];
  real32_T tmp_0;
  real32_T tmp_1;
  real32_T tmp_2;
  real32_T tmp_3;
  real32_T u0;
  real32_T xhat;
  real32_T y_idx_0;
  real32_T y_idx_1;
  int16_T rtb_MATLABSystem_0;
  int16_T y_idx_0_tmp;
  uint16_T b_varargout_1;
  boolean_T b;

  /* SignalGenerator: '<Root>/Signal Generator' */
  rtb_SignalGenerator = sin(6.2831853071795862 * Experience_M->Timing.t[0] *
    Experience_P.SignalGenerator_Frequency) *
    Experience_P.SignalGenerator_Amplitude;

  /* MATLABSystem: '<S4>/MATLAB System' */
  if (Experience_DW.obj.SampleTime != Experience_P.MATLABSystem_SampleTime) {
    b = rtIsInf(Experience_P.MATLABSystem_SampleTime);
    if (((!b) && (!rtIsNaN(Experience_P.MATLABSystem_SampleTime))) || b) {
      Experience_B.sampleTime = Experience_P.MATLABSystem_SampleTime;
    }

    Experience_DW.obj.SampleTime = Experience_B.sampleTime;
  }

  /*         %% Define output properties */
  /*  Call C-function implementing device output */
  rtb_MATLABSystem_0 = EncPortRead1();

  /* Gain: '<S4>/Gain' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion'
   *  MATLABSystem: '<S4>/MATLAB System'
   */
  Experience_B.Gain = Experience_P.Gain_Gain * (real32_T)rtb_MATLABSystem_0;

  /* MATLABSystem: '<S2>/Angle sensor' */
  Experience_DW.obj_p.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
    MW_AnalogIn_GetHandle(64UL);
  MW_AnalogInSingle_ReadResult
    (Experience_DW.obj_p.AnalogInDriverObj.MW_ANALOGIN_HANDLE, &b_varargout_1,
     MW_ANALOGIN_UINT16);

  /* Delay: '<S5>/Delay' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   *  MATLABSystem: '<S2>/Angle sensor'
   * */
  if (Experience_DW.icLoad) {
    Experience_DW.Delay_DSTATE = b_varargout_1;
  }

  /* Delay: '<S5>/Delay' */
  Experience_B.Delay = Experience_DW.Delay_DSTATE;

  /* Gain: '<S2>/Raw -> rad positif vers l'avant' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion'
   *  MATLABSystem: '<S2>/Angle sensor'
   *  Sum: '<S5>/Sum'
   * */
  Experience_B.Phi = ((real32_T)b_varargout_1 - Experience_B.Delay) *
    Experience_P.Rawradpositifverslavant_Gain;

  /* DataTypeConversion: '<Root>/Cast To Double1' */
  Experience_B.CastToDouble1[0] = Experience_B.Gain;
  Experience_B.CastToDouble1[1] = Experience_B.Phi;

  /* MATLAB Function: '<Root>/Commande FF' incorporates:
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  Experience_B.e = rtb_SignalGenerator - Experience_B.CastToDouble1[0];
  xhat = Experience_DW.UnitDelay1_DSTATE[0];
  Experience_B.xhat[0] = xhat;

  /* MATLAB Function: '<Root>/Commande FF' incorporates:
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  u0 = (real32_T)-Experience_P.K[0] * xhat;
  xhat = Experience_DW.UnitDelay1_DSTATE[1];
  Experience_B.xhat[1] = xhat;

  /* MATLAB Function: '<Root>/Commande FF' incorporates:
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  u0 += (real32_T)-Experience_P.K[1] * xhat;
  xhat = Experience_DW.UnitDelay1_DSTATE[2];
  Experience_B.xhat[2] = xhat;

  /* MATLAB Function: '<Root>/Commande FF' incorporates:
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  u0 += (real32_T)-Experience_P.K[2] * xhat;
  xhat = Experience_DW.UnitDelay1_DSTATE[3];
  Experience_B.xhat[3] = xhat;

  /* MATLAB Function: '<Root>/Commande FF' */
  xhat = ((real32_T)-Experience_P.K[3] * xhat + u0) + (real32_T)(Experience_P.H *
    rtb_SignalGenerator);
  y_idx_0 = 0.0F;
  y_idx_1 = 0.0F;
  for (rtb_MATLABSystem_0 = 0; rtb_MATLABSystem_0 < 4; rtb_MATLABSystem_0++) {
    u0 = Experience_B.xhat[rtb_MATLABSystem_0];
    y_idx_0_tmp = rtb_MATLABSystem_0 << 1;
    y_idx_0 += (real32_T)Experience_P.C[y_idx_0_tmp] * u0;
    y_idx_1 += (real32_T)Experience_P.C[y_idx_0_tmp + 1] * u0;
    Experience_B.fv[rtb_MATLABSystem_0] = ((((real32_T)
      Experience_P.A[rtb_MATLABSystem_0 + 4] * Experience_B.xhat[1] + (real32_T)
      Experience_P.A[rtb_MATLABSystem_0] * Experience_B.xhat[0]) + (real32_T)
      Experience_P.A[rtb_MATLABSystem_0 + 8] * Experience_B.xhat[2]) + (real32_T)
      Experience_P.A[rtb_MATLABSystem_0 + 12] * Experience_B.xhat[3]) +
      (real32_T)Experience_P.B[rtb_MATLABSystem_0] * xhat;
  }

  tmp[0] = (real32_T)Experience_B.CastToDouble1[0] - y_idx_0;
  tmp[1] = (real32_T)Experience_B.CastToDouble1[1] - y_idx_1;
  u0 = 0.0F;
  tmp_1 = 0.0F;
  tmp_2 = 0.0F;
  tmp_3 = 0.0F;
  for (rtb_MATLABSystem_0 = 0; rtb_MATLABSystem_0 < 2; rtb_MATLABSystem_0++) {
    tmp_0 = tmp[rtb_MATLABSystem_0];
    y_idx_0_tmp = rtb_MATLABSystem_0 << 2;
    u0 += (real32_T)Experience_P.L[y_idx_0_tmp] * tmp_0;
    tmp_1 += (real32_T)Experience_P.L[y_idx_0_tmp + 1] * tmp_0;
    tmp_2 += (real32_T)Experience_P.L[y_idx_0_tmp + 2] * tmp_0;
    tmp_3 += (real32_T)Experience_P.L[y_idx_0_tmp + 3] * tmp_0;
  }

  Experience_B.xhat[0] = Experience_B.fv[0] + u0;
  Experience_B.xhat[1] = Experience_B.fv[1] + tmp_1;
  Experience_B.xhat[2] = Experience_B.fv[2] + tmp_2;
  Experience_B.xhat[3] = Experience_B.fv[3] + tmp_3;

  /* DataTypeConversion: '<Root>/Cast To Double2' incorporates:
   *  MATLAB Function: '<Root>/Commande FF'
   */
  Experience_B.CastToDouble2[0] = y_idx_0;
  Experience_B.CastToDouble2[1] = y_idx_1;

  /* Saturate: '<Root>/Saturation' incorporates:
   *  MATLAB Function: '<Root>/Commande FF'
   */
  if (xhat > Experience_P.Saturation_UpperSat) {
    /* Saturate: '<Root>/Saturation' */
    Experience_B.u = Experience_P.Saturation_UpperSat;
  } else if (xhat < Experience_P.Saturation_LowerSat) {
    /* Saturate: '<Root>/Saturation' */
    Experience_B.u = Experience_P.Saturation_LowerSat;
  } else {
    /* Saturate: '<Root>/Saturation' */
    Experience_B.u = xhat;
  }

  /* End of Saturate: '<Root>/Saturation' */
  /* MATLABSystem: '<S4>/MATLAB System1' */
  if (Experience_DW.obj_g.SampleTime != Experience_P.MATLABSystem1_SampleTime) {
    b = rtIsInf(Experience_P.MATLABSystem1_SampleTime);
    if (((!b) && (!rtIsNaN(Experience_P.MATLABSystem1_SampleTime))) || b) {
      Experience_B.sampleTime_m = Experience_P.MATLABSystem1_SampleTime;
    }

    Experience_DW.obj_g.SampleTime = Experience_B.sampleTime_m;
  }

  /*         %% Define output properties */
  /*  Call C-function implementing device output */
  rtb_MATLABSystem1_0 = EncPeriodRead1();

  /* Gain: '<S4>/Gain2' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   *  Gain: '<S4>/Gain1'
   *  MATLABSystem: '<S4>/MATLAB System1'
   *  Math: '<S4>/Math Function'
   *
   * About '<S4>/Math Function':
   *  Operator: reciprocal
   */
  Experience_B.Gain2 = 1.0F / (Experience_P.Gain1_Gain * (real32_T)
    rtb_MATLABSystem1_0) * Experience_P.Gain2_Gain;

  /* Gain: '<S6>/Gain' */
  /*         %% Define input properties */
  /*  Call C-function implementing device output */
  u0 = Experience_P.Gain_Gain_i * Experience_B.u;

  /* Saturate: '<S6>/Saturation' */
  if (u0 > Experience_P.Saturation_UpperSat_l) {
    u0 = Experience_P.Saturation_UpperSat_l;
  } else if (u0 < Experience_P.Saturation_LowerSat_o) {
    u0 = Experience_P.Saturation_LowerSat_o;
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
   *  Saturate: '<S6>/Saturation'
   */
  u0 = (real32_T)floor(u0);
  if (rtIsNaNF(u0) || rtIsInfF(u0)) {
    u0 = 0.0F;
  } else {
    u0 = (real32_T)fmod(u0, 65536.0);
  }

  /* MATLABSystem: '<S6>/MATLAB System1' incorporates:
   *  DataTypeConversion: '<S6>/Data Type Conversion'
   */
  DCMotor1Set(u0 < 0.0F ? -(int16_T)(uint16_T)-u0 : (int16_T)(uint16_T)u0);

  /* Gain: '<S7>/Gain' incorporates:
   *  Gain: '<S3>/Gain'
   */
  /*         %% Define input properties */
  /*  Call C-function implementing device output */
  u0 = Experience_P.Gain_Gain_k * Experience_B.u * Experience_P.Gain_Gain_o;

  /* Saturate: '<S7>/Saturation' */
  if (u0 > Experience_P.Saturation_UpperSat_a) {
    u0 = Experience_P.Saturation_UpperSat_a;
  } else if (u0 < Experience_P.Saturation_LowerSat_b) {
    u0 = Experience_P.Saturation_LowerSat_b;
  }

  /* DataTypeConversion: '<S7>/Data Type Conversion' incorporates:
   *  Saturate: '<S7>/Saturation'
   */
  u0 = (real32_T)floor(u0);
  if (rtIsNaNF(u0) || rtIsInfF(u0)) {
    u0 = 0.0F;
  } else {
    u0 = (real32_T)fmod(u0, 65536.0);
  }

  /* MATLABSystem: '<S7>/MATLAB System' incorporates:
   *  DataTypeConversion: '<S7>/Data Type Conversion'
   */
  DCMotor2Set(u0 < 0.0F ? -(int16_T)(uint16_T)-u0 : (int16_T)(uint16_T)u0);

  /* Update for UnitDelay: '<Root>/Unit Delay1' */
  Experience_DW.UnitDelay1_DSTATE[0] = Experience_B.xhat[0];
  Experience_DW.UnitDelay1_DSTATE[1] = Experience_B.xhat[1];
  Experience_DW.UnitDelay1_DSTATE[2] = Experience_B.xhat[2];
  Experience_DW.UnitDelay1_DSTATE[3] = Experience_B.xhat[3];

  /* Update for Delay: '<S5>/Delay' */
  Experience_DW.icLoad = false;
  Experience_DW.Delay_DSTATE = Experience_B.Delay;

  {                                    /* Sample time: [0.005s, 0.0s] */
    extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
    extmodeSimulationTime_T extmodeTime = (extmodeSimulationTime_T)
      ((Experience_M->Timing.clockTick1 * 1) + 0);

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
  Experience_M->Timing.t[0] =
    ((time_T)(++Experience_M->Timing.clockTick0)) *
    Experience_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.005s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.005, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    Experience_M->Timing.clockTick1++;
  }
}

/* Model initialize function */
void Experience_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Experience_M, 0,
                sizeof(RT_MODEL_Experience_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Experience_M->solverInfo,
                          &Experience_M->Timing.simTimeStep);
    rtsiSetTPtr(&Experience_M->solverInfo, &rtmGetTPtr(Experience_M));
    rtsiSetStepSizePtr(&Experience_M->solverInfo,
                       &Experience_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&Experience_M->solverInfo, (&rtmGetErrorStatus
      (Experience_M)));
    rtsiSetRTModelPtr(&Experience_M->solverInfo, Experience_M);
  }

  rtsiSetSimTimeStep(&Experience_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&Experience_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&Experience_M->solverInfo, false);
  rtsiSetSolverName(&Experience_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(Experience_M, &Experience_M->Timing.tArray[0]);
  rtmSetTFinal(Experience_M, 30.0);
  Experience_M->Timing.stepSize0 = 0.005;

  /* External mode info */
  Experience_M->Sizes.checksums[0] = (2969327155U);
  Experience_M->Sizes.checksums[1] = (4275142844U);
  Experience_M->Sizes.checksums[2] = (1774279565U);
  Experience_M->Sizes.checksums[3] = (1543446538U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    Experience_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Experience_M->extModeInfo,
      &Experience_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Experience_M->extModeInfo, Experience_M->Sizes.checksums);
    rteiSetTFinalTicks(Experience_M->extModeInfo, 6000);
  }

  /* block I/O */
  (void) memset(((void *) &Experience_B), 0,
                sizeof(B_Experience_T));

  /* states (dwork) */
  (void) memset((void *)&Experience_DW, 0,
                sizeof(DW_Experience_T));

  {
    real_T sampleTime;
    real_T sampleTime_0;
    boolean_T b;

    /* InitializeConditions for UnitDelay: '<Root>/Unit Delay1' */
    Experience_DW.UnitDelay1_DSTATE[0] =
      Experience_P.UnitDelay1_InitialCondition[0];
    Experience_DW.UnitDelay1_DSTATE[1] =
      Experience_P.UnitDelay1_InitialCondition[1];
    Experience_DW.UnitDelay1_DSTATE[2] =
      Experience_P.UnitDelay1_InitialCondition[2];
    Experience_DW.UnitDelay1_DSTATE[3] =
      Experience_P.UnitDelay1_InitialCondition[3];

    /* InitializeConditions for Delay: '<S5>/Delay' */
    Experience_DW.icLoad = true;

    /* Start for MATLABSystem: '<S4>/MATLAB System' */
    Experience_DW.obj.matlabCodegenIsDeleted = false;
    b = rtIsInf(Experience_P.MATLABSystem_SampleTime);
    if (((!b) && (!rtIsNaN(Experience_P.MATLABSystem_SampleTime))) || b) {
      sampleTime = Experience_P.MATLABSystem_SampleTime;
    }

    Experience_DW.obj.SampleTime = sampleTime;
    Experience_DW.obj.isInitialized = 1L;

    /*         %% Define output properties */
    /*  Call C-function implementing device initialization */
    EncPort1Setup();
    Experience_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S4>/MATLAB System' */

    /* Start for MATLABSystem: '<S2>/Angle sensor' */
    Experience_DW.obj_p.matlabCodegenIsDeleted = false;
    Experience_DW.obj_p.isInitialized = 1L;
    Experience_DW.obj_p.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
      MW_AnalogInSingle_Open(64UL);
    Experience_DW.obj_p.isSetupComplete = true;

    /* Start for MATLABSystem: '<S4>/MATLAB System1' */
    Experience_DW.obj_g.matlabCodegenIsDeleted = false;
    b = rtIsInf(Experience_P.MATLABSystem1_SampleTime);
    if (((!b) && (!rtIsNaN(Experience_P.MATLABSystem1_SampleTime))) || b) {
      sampleTime_0 = Experience_P.MATLABSystem1_SampleTime;
    }

    Experience_DW.obj_g.SampleTime = sampleTime_0;
    Experience_DW.obj_g.isInitialized = 1L;

    /*         %% Define output properties */
    /*  Call C-function implementing device initialization */
    EncPort1Setup();
    Experience_DW.obj_g.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S4>/MATLAB System1' */

    /* Start for MATLABSystem: '<S6>/MATLAB System1' */
    Experience_DW.obj_i.matlabCodegenIsDeleted = false;
    Experience_DW.obj_i.isInitialized = 1L;

    /*         %% Define input properties */
    /*  Call C-function implementing device initialization */
    DCMotor1Setup();
    Experience_DW.obj_i.isSetupComplete = true;

    /* Start for MATLABSystem: '<S7>/MATLAB System' */
    Experience_DW.obj_pv.matlabCodegenIsDeleted = false;
    Experience_DW.obj_pv.isInitialized = 1L;

    /*         %% Define input properties */
    /*  Call C-function implementing device initialization */
    DCMotor2Setup();
    Experience_DW.obj_pv.isSetupComplete = true;
  }
}

/* Model terminate function */
void Experience_terminate(void)
{
  /* Terminate for MATLABSystem: '<S4>/MATLAB System' */
  if (!Experience_DW.obj.matlabCodegenIsDeleted) {
    Experience_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S4>/MATLAB System' */

  /* Terminate for MATLABSystem: '<S2>/Angle sensor' */
  if (!Experience_DW.obj_p.matlabCodegenIsDeleted) {
    Experience_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((Experience_DW.obj_p.isInitialized == 1L) &&
        Experience_DW.obj_p.isSetupComplete) {
      Experience_DW.obj_p.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
        MW_AnalogIn_GetHandle(64UL);
      MW_AnalogIn_Close(Experience_DW.obj_p.AnalogInDriverObj.MW_ANALOGIN_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S2>/Angle sensor' */
  /* Terminate for MATLABSystem: '<S4>/MATLAB System1' */
  if (!Experience_DW.obj_g.matlabCodegenIsDeleted) {
    Experience_DW.obj_g.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S4>/MATLAB System1' */
  /* Terminate for MATLABSystem: '<S6>/MATLAB System1' */
  if (!Experience_DW.obj_i.matlabCodegenIsDeleted) {
    Experience_DW.obj_i.matlabCodegenIsDeleted = true;
    if ((Experience_DW.obj_i.isInitialized == 1L) &&
        Experience_DW.obj_i.isSetupComplete) {
      /*  Call C-function implementing device termination */
      /* coder.ceval('sink_terminate'); */
      DCMotor1Set(0.0);
    }
  }

  /* End of Terminate for MATLABSystem: '<S6>/MATLAB System1' */

  /* Terminate for MATLABSystem: '<S7>/MATLAB System' */
  if (!Experience_DW.obj_pv.matlabCodegenIsDeleted) {
    Experience_DW.obj_pv.matlabCodegenIsDeleted = true;
    if ((Experience_DW.obj_pv.isInitialized == 1L) &&
        Experience_DW.obj_pv.isSetupComplete) {
      /*  Call C-function implementing device termination */
      DCMotor2Set(0.0);
    }
  }

  /* End of Terminate for MATLABSystem: '<S7>/MATLAB System' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
