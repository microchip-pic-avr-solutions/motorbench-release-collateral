# Microchip Motor Control Library v0.3.x

This version of the Microchip Motor Control Library
supports the following architectures:

- dsPIC33E
- dsPIC33F
- dsPIC33C
- dsPIC33A

NOTE:
    -    No changes have been made to any assembly source code nor to the API of generic names since v0.10 
    ---
    -    See the 0.10 user manual documentation for assembly implementations specifics
    -    Use the header files with "declarations" as reference of the different function prototypes
    -    33A devices only support C implementations
    -    16 bit devices support both, C implementations and assembly

## Content

The following functions are included:

- MC_CalculateSineCosine_Assembly_Ram
- MC_CalculateSpaceVector_Assembly
- MC_CalculateSpaceVectorPhaseShifted_Assembly
- MC_ControllerPIUpdate_Assembly
- MC_TransformClarke_Assembly
- MC_TransformClarkeInverse_Assembly
- MC_TransformClarkeInverseNoAccum_Assembly
- MC_TransformClarkeInverseSwappedInput_Assembly
- MC_TransformPark_Assembly
- MC_TransformParkInverse_Assembly

- MC_CalculateSineCosine_InlineC_Ram
- MC_CalculateSpaceVectorPhaseShifted_InlineC
- MC_CalculateZeroSequenceModulation_InlineC
- MC_ControllerPIUpdate_InlineC
- MC_TransformClarke_InlineC
- MC_TransformClarkeABC_InlineC
- MC_TransformPark_InlineC
- MC_TransformParkInverse_InlineC
- MC_TransformClarkeInverseSwappedInput_InlineC
- MC_TransformClarkeInverse_InlineC
- MC_TransformClarkeInverseNoAccum_InlineC

## Testing

Unit tests were performed on all functions,
with the following exceptions:

- MC_ControllerPIUpdate_Assembly
- MC_ControllerPIUpdate_InlineC

As well as in the case of 33A, there's no assembly implementations to test.

These tests were performed on the 33EP256MC506, 33CK256MP508 and 33AK128MC106.
Unit tests have not been performed on the 33F architecture due
to technical limitations. (The source code is identical
with the exception of the declaration of the table for sine/cosine
calculations.)

## Revision History
- **0.3.13** --- 2025 Nov 25
  0.3.2 to 0.3.12 were registered in build-archives/MOTOR_LIB-249 (from r50534 to r50566)
    - Fix, motor_control.h, replicate fix from trunk, add trailing underscores to dsPIC33E macro
    - MC LIB 0.3.12, Enhancement/comment, MC_CalculateSpaceVectorPhaseShifted_InlineC, remove redundant comment to sacr 'using corcon rounding', 33AK MC LIB test report PASSING
    - MC LIB 0.3.11, Refactor, MC_CalculateSpaceVectorPhaseShifted_InlineC, use MULUS builtins to calculate the T1 and T2 periods on all sectors, instead of leaving integer promotion take place
    - MC LIB 0.3.10, Fix, use _16 in msc builtin for ClarkeInverse swapped inputs for 33A inline dspic MC core functions (fixing 0.3.8, r50551) in MC_lib MOTOR_LIB-249 branch
    - MC LIB 0.3.8, Refactor,...inline_dspic_33A.h, MC_TransformClarkeInverseSwappedInput_InlineC uses builtins again to use accumulator and dsp functions, instead of C (fixing 0.3.7)
    - Rollback to MC LIB 0.3.6, since 0.3.7 has an error, missing equal sign in MC_TransformClarkeInverseSwappedInput_InlineC
    - MC LIB 0.3.7, Refactor,...inline_dspic_33A.h, MC_TransformClarkeInverseSwappedInput_InlineC uses builtins again to use accumulator and dsp functions, instead of C
    - MC LIB 0.3.6, Fix, MC_UTIL_MinMax3_S16, use sacr with 16 bit left shift to read 33A accumulator 32 bits correctly, Fix, motor_control_inline_dspic_33A.h, TransformPark, ControllerPIUpdate nd TransformParkInverse now use sacr with a 16 bit left shift to extract the right accumulator location
    - MC LIB 0.3.5, Fix, MC_TransformClarkeInverse_InlineC, uses 16 bit shift left on builtin sacr to extract the right accumulator section
    - MC LIB 0.3.4, Fix, MC_TransformClarke_InlineC, for 33A, use a 16 bit shift left on sacr to get the right accumulator result
    - MC LIB 0.3.3, Fix, ..._inline_dspic_33A.h, typo, remainder instead of 'reminder' in sine interpolation in MC_CalculateSineCosine function
    - MC LIB 0.3.2, Refactor, ..inline_dspic_33A.h, use builtin mulus function to replace the scaling of the remainder for non exact sine or cosine values
    - Use builtin_muluu, to avoid C integer promotion to assume MULUU and create a negative index in
    - MC_CalculateSineCosine function. Add C++ guards to ..._inline_internal and ..._inline_internal_33A header files

- **0.3.0** --- 2024 July 31
    - Include 33A support for xc-dsc builtin names (_16 suffix)
    - Include 33A support for sine tables (ram and flash), it's the only assembly files that are included for this architecture
    - The sine table file generation is now part of the build proccess
    - 33A has it's own implementation of the MC Library C functions

- **0.21** --- 2019 Dec 17
    
    - Rebuilt library with generic targets rather than device specific targets

- **0.2** --- 2019 Oct 15

    - Adds support for 33CK architectures
    - Functions added:
    
         - MC_CalculateSpaceVector_Assembly ---
           does not have the unconventional phase shift of
           MC_CalculateSpaceVectorPhaseShifted_Assembly 
         - MC_CalculateZeroSequenceModulation_InlineC --- 
           zero sequence modulation handles overmodulation 
           more gracefully than the implementation of SVM
         - MC_TransformClarkeABC_InlineC --- ABC -> alpha,beta 
           (other Clarke transforms are AB -> alpha,beta)
         - MC_TransformClarkeInverse_Assembly ---
           this and the following functions do not have 
           swapped inputs of 
           MC_TransformClarkeInverseSwappedInput_Assembly
         - MC_TransformClarkeInverse_InlineC
         - MC_TransformClarkeInverseNoAccum_Assembly --- 
           avoids use of DSP accumulator
         - MC_TransformClarkeInverseNoAccum_InlineC

- **0.1** --- 2013 Dec 13: original release

