/**
 * @file JASampleGAM.cpp
 * @brief Source file for class JASampleGAM
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

 * @details This source file contains the definition of all the methods for
 * the class JASampleGAM (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "JASampleGAM.h"

#include "AdvancedErrorManagement.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

JASampleGAM::JASampleGAM() {
    // initialize member variables.
    param1 = 0;
    param2 = 0;

    //Input signals.
    input1 = NULL_PTR(MARTe::uint32 *);
    input2 = NULL_PTR(MARTe::float32 *);
    //Output signals.
    output1= NULL_PTR(MARTe::uint32 *);
    output2 = NULL_PTR(MARTe::float32 *);

}

JASampleGAM::~JASampleGAM() {
}

bool JASampleGAM::Initialise(MARTe::StructuredDataI & data) {
    //GAM parameters are initialized.
    using namespace MARTe;
    bool ok = GAM::Initialise(data);
    if (ok) {
        ok = data.Read("param1", param1);
        if (!ok) {
            REPORT_ERROR(MARTe::ErrorManagement::ParametersError, "The param1 shall be specified");
        }
    }
    if (ok) {
        ok = data.Read("param2", param2);
        if (!ok) {
            REPORT_ERROR(MARTe::ErrorManagement::ParametersError, "The param2 shall be specified");
        }
    }
    return ok;
}

bool JASampleGAM::PrepareNextState(const MARTe::char8 * const currentStateName, const MARTe::char8 * const nextStateName) {
    //This method changes internal parameter based on next realtime state.
    return true;
}

bool JASampleGAM::Setup() {
    // Setup memory for input/output signals on the GAM.
    using namespace MARTe;
    bool ok = (numberOfInputSignals == 2u);
    if (ok) {
        ok = (numberOfOutputSignals == 2u);
        if (!ok) {
            REPORT_ERROR(MARTe::ErrorManagement::ParametersError, "Two output signals shall be defined");
        }
    }
    else {
        REPORT_ERROR(MARTe::ErrorManagement::ParametersError, "Two input signals shall be defined");
    }
    // Do type check for input signals.
    if (ok) {
        uint32 c;
        for (c = 0u; c < numberOfInputSignals; c++) {
            TypeDescriptor inputType = GetSignalType(InputSignals, c);
            ok = ((inputType == UnsignedInteger32Bit) || (inputType == Float32Bit));
            if (!ok) {
                StreamString signalName;
                (void) GetSignalName(InputSignals, c, signalName);
                REPORT_ERROR(MARTe::ErrorManagement::ParametersError, "Signal %s shall be defined as uint32 or flaot32", signalName.Buffer());
            }

        }
    }
    // Do type check for output signals
    if (ok) {
        uint32 c;
        for (c = 0u; c < numberOfOutputSignals; c++) {
            TypeDescriptor outputType = GetSignalType(OutputSignals, c);
            ok = ((outputType == UnsignedInteger32Bit) || (outputType == Float32Bit));
            if (!ok) {
                StreamString signalName;
                (void) GetSignalName(InputSignals, c, signalName);
                REPORT_ERROR(MARTe::ErrorManagement::ParametersError, "Signal %s shall be defined as uint32 or float32", signalName.Buffer());
            }
        }
    }

    // Signal id can get by signal name in configuration file
    if (ok) {
        StreamString signalName = "InputXXX"; //Variable name in configuration file.
        uint32 signalxxxIndex; //Index is copied to this variable by using signal name.
        ok = GetSignalIndex(InputSignals, signalxxxIndex, signalName.Buffer());
        if (!ok) {
            REPORT_ERROR(MARTe::ErrorManagement::ParametersError, "InputXXX input signal shall be defined");
        }
        else {
            TypeDescriptor inputType = GetSignalType(InputSignals, signalxxxIndex);
            ok = (inputType == Float32Bit);
            if (!ok) {
                StreamString signalName;
                (void) GetSignalName(InputSignals, signalxxxIndex, signalName);
                REPORT_ERROR(MARTe::ErrorManagement::ParametersError, "Signal %s shall be defined as float32", signalName.Buffer());
            } else {
                inputXXX = reinterpret_cast<float32 *>(GetInputSignalMemory(signalxxxIndex));
            }
        }
    }

    // Do type cast. with explicit signal id.
    if (ok) {
        input1 = reinterpret_cast<uint32 *>(GetInputSignalMemory(0));
        input2 = reinterpret_cast<float32 *>(GetInputSignalMemory(1));

        output1 = reinterpret_cast<uint32 *>(GetOutputSignalMemory(0));
        output2 = reinterpret_cast<float32 *>(GetOutputSignalMemory(1));

    }
    return ok;
}

bool JASampleGAM::Execute() {
    // This method is called every realtime state thread cycle.
    using namespace MARTe;
    REPORT_ERROR(ErrorManagement::Information, "input1 is %d.", *input1);
    REPORT_ERROR(ErrorManagement::Information, "input2 is %f.", *input2);
    REPORT_ERROR(ErrorManagement::Information, "inputXXX is %f.", *inputXXX);

    REPORT_ERROR(ErrorManagement::Information, "maltiply param value to input.");

    *output1 = *input1 * param1;
    *output2 = *input2 * param2;

    REPORT_ERROR(ErrorManagement::Information, "output1 is %d.", *output1);
    REPORT_ERROR(ErrorManagement::Information, "output2 is %f.", *output2);

    return true;
}

CLASS_REGISTER(JASampleGAM, "1.0")
