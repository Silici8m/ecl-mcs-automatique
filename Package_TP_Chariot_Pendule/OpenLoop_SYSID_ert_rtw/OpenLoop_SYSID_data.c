/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: OpenLoop_SYSID_data.c
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

/* Block parameters (default storage) */
P_OpenLoop_SYSID_T OpenLoop_SYSID_P = {
  /* Mask Parameter: Motor1_Vmax
   * Referenced by: '<S7>/Gain'
   */
  12.0,

  /* Mask Parameter: Motor2_Vmax
   * Referenced by: '<S8>/Gain'
   */
  12.0,

  /* Expression: -1
   * Referenced by: '<S5>/MATLAB System'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S5>/MATLAB System1'
   */
  -1.0,

  /* Expression: 9
   * Referenced by: '<Root>/Saturation'
   */
  9.0,

  /* Expression: -9
   * Referenced by: '<Root>/Saturation'
   */
  -9.0,

  /* Expression: 255
   * Referenced by: '<S7>/Saturation'
   */
  255.0,

  /* Expression: -255
   * Referenced by: '<S7>/Saturation'
   */
  -255.0,

  /* Expression: -1
   * Referenced by: '<S4>/Gain'
   */
  -1.0,

  /* Expression: 255
   * Referenced by: '<S8>/Saturation'
   */
  255.0,

  /* Expression: -255
   * Referenced by: '<S8>/Saturation'
   */
  -255.0,

  /* Computed Parameter: Gain_Gain_n
   * Referenced by: '<S5>/Gain'
   */
  0.496956527F,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<S5>/Gain1'
   */
  1.0E-6F,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<S5>/Gain2'
   */
  0.496956527F,

  /* Computed Parameter: Rawradpositifverslavant_Gain
   * Referenced by: '<S1>/Raw -> rad positif vers l'avant'
   */
  -0.00615998544F,

  /* Computed Parameter: ManualSwitch_CurrentSetting
   * Referenced by: '<Root>/Manual Switch'
   */
  0U
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
