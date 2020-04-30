
#ifndef GAMS_SampleGAM_H_
#define GAMS_SampleGAM_H_

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
 *     Class = SampleGAM
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


class SampleGAM : public MARTe::GAM, public MARTe::StatefulI {
public:
    CLASS_REGISTER_DECLARATION()

    SampleGAM();

    virtual ~SampleGAM();

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

#endif /* GAMS_SampleGAM_H_ */
