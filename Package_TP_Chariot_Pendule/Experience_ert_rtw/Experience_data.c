/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Experience_data.c
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

/* Block parameters (default storage) */
P_Experience_T Experience_P = {
  /* Variable: A
   * Referenced by: '<Root>/Commande FF'
   */
  { 0.8995690173413442, 0.0047444943845814753, 0.0016028714107953427,
    4.0829018903466247E-6, 0.0, 1.0, 0.0, 0.0, 4.3358250162972994E-8,
    7.29393893846765E-11, 0.99285283843155336, 0.0049831795566961977,
    1.7072697640048414E-5, 4.344413629397345E-8, -0.51117603918131627,
    0.99872053235956315 },

  /* Variable: B
   * Referenced by: '<Root>/Commande FF'
   */
  { 4.7097547211350479, 0.011982047239126419, -0.071992306832591363,
    -0.00018352235933530913 },

  /* Variable: C
   * Referenced by: '<Root>/Commande FF'
   */
  { 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 },

  /* Variable: H
   * Referenced by: '<Root>/Commande FF'
   */
  0.010310275974563217,

  /* Variable: K
   * Referenced by: '<Root>/Commande FF'
   */
  { 0.0034911369369698278, 0.010310275974563217, -0.62689487564212432,
    -17.928873757557426 },

  /* Variable: L
   * Referenced by: '<Root>/Commande FF'
   */
  { 38.158246793839908, 0.952750896396552, -0.54857850831905242,
    -0.006056167474856872, 0.22756385772395091, 0.0029888572646870671,
    51.68235816627589, 1.0253142448375476 },

  /* Expression: -1
   * Referenced by: '<S4>/MATLAB System'
   */
  -1.0,

  /* Expression: -1
   * Referenced by: '<S4>/MATLAB System1'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<Root>/Signal Generator'
   */
  0.0,

  /* Expression: .2
   * Referenced by: '<Root>/Signal Generator'
   */
  0.2,

  /* Computed Parameter: UnitDelay1_InitialCondition
   * Referenced by: '<Root>/Unit Delay1'
   */
  { 0.0F, 0.0F, 0.0F, 0.0F },

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S4>/Gain'
   */
  0.496956527F,

  /* Computed Parameter: Rawradpositifverslavant_Gain
   * Referenced by: '<S2>/Raw -> rad positif vers l'avant'
   */
  -0.00615998544F,

  /* Computed Parameter: Saturation_UpperSat
   * Referenced by: '<Root>/Saturation'
   */
  9.0F,

  /* Computed Parameter: Saturation_LowerSat
   * Referenced by: '<Root>/Saturation'
   */
  -9.0F,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<S4>/Gain1'
   */
  1.0E-6F,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<S4>/Gain2'
   */
  0.496956527F,

  /* Computed Parameter: Gain_Gain_i
   * Referenced by: '<S6>/Gain'
   */
  21.25F,

  /* Computed Parameter: Saturation_UpperSat_l
   * Referenced by: '<S6>/Saturation'
   */
  255.0F,

  /* Computed Parameter: Saturation_LowerSat_o
   * Referenced by: '<S6>/Saturation'
   */
  -255.0F,

  /* Computed Parameter: Gain_Gain_k
   * Referenced by: '<S3>/Gain'
   */
  -1.0F,

  /* Computed Parameter: Gain_Gain_o
   * Referenced by: '<S7>/Gain'
   */
  21.25F,

  /* Computed Parameter: Saturation_UpperSat_a
   * Referenced by: '<S7>/Saturation'
   */
  255.0F,

  /* Computed Parameter: Saturation_LowerSat_b
   * Referenced by: '<S7>/Saturation'
   */
  -255.0F
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
