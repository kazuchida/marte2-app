/**
 * @file JASampleGAM.h
 * @brief Header file for class JASampleGAM
 * @date Nov 26, 2018
 * @author aneto
 *
 * @copyright Copyright 2015 F4E | European Joint Undertaking for ITER and
 * the Development of Fusion Energy ('Fusion for Energy').
 * Licensed under the EUPL, Version 1.1 or - as soon they will be approved
 * by the European Commission - subsequent versions of the EUPL (the "Licence")
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at: http://ec.europa.eu/idabc/eupl
 *
 * @warning Unless required by applicable law or agreed to in writing,
 * software distributed under the Licence is distributed on an "AS IS"
 * basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the Licence permissions and limitations under the Licence.

 * @details This header file contains the declaration of the class JASampleGAM
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef GAMS_JASampleGAM_H_
#define GAMS_JASampleGAM_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "GAM.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/
/**
 * @brief GAM Sample Usage. 
 * @details Sample
 *
 * The configuration syntax is:
 *
 * <pre>
 * +SampleGAM = {
 *     Class = JASampleGAM
 *     InputSignals = {
 *         Input1 = {
 *             DataSource = "DDB"
 *             Type = uint32
 *             Default = 0
 *         }
 *         Input2 = {
 *             DataSource = "DDB"
 *             Type = float32
 *             Default = 100
 *         }
 *         InputXXX = {
 *             DataSource = "DDB"
 *             Type = float32
 *             NumberOfElements = 1
 *         }
 *     }
 *     OutputSignals = {
 *         Output1 = {
 *             DataSource = "DDB"
 *             Type = uint32
 *             Default = 0
 *         }
 *         Output2 = {
 *             DataSource = "DDB"
 *             Type = int32
 *             Default = 100
 *         }
 *     }
 * }
 * </pre>
 */


class JASampleGAM : public MARTe::GAM, public MARTe::StatefulI {
public:
    CLASS_REGISTER_DECLARATION()

    JASampleGAM();

    virtual ~JASampleGAM();

    virtual bool Initialise(MARTe::StructuredDataI & data);

    virtual bool Setup();

    virtual bool Execute();

    virtual bool PrepareNextState(const MARTe::char8 * const currentStateName,
                                  const MARTe::char8 * const nextStateName);

private:
    //GAM fixed parameters.
    MARTe::uint32 param1;
    MARTe::float32 param2;

    // Input signals
    MARTe::uint32 *input1;
    MARTe::float32 *input2;
    MARTe::float32 *inputXXX;

    // Output signals
    MARTe::uint32 *output1;
    MARTe::float32 *output2;

};



/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* GAMS_JASampleGAM_H_ */
