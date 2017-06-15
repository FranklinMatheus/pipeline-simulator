/* 
 * Assembly::advanceAClock()
 * Updates log:
 * >> Skeletron created by Franklin Matheus (01/05/2017 14:38)
 */

#include "assembly.h"

namespace Assembly{

    /*!
     * @brief Returns a vector with 5 instructions. Each one of these instructions
     *        are in one phase of the pipeline.
     */
    std::vector<Assembly::Instruction> advanceAClock( std::vector<Assembly::Instruction> &inputs
                                                    , int &currentClock ){

        std::vector<Assembly::Instruction> instructionsPhases = { Assembly::Instruction()
                                                                , Assembly::Instruction()
                                                                , Assembly::Instruction()
                                                                , Assembly::Instruction()
                                                                , Assembly::Instruction() 
                                                                };

        for( auto &input : inputs ){
            if( input.getPhase() == Assembly::Phase::IF ){
                input.setPhase( Assembly::Phase::ID );
                instructionsPhases[1] = input;
            } else if( input.getPhase() == Assembly::Phase::ID ){ 
                input.setPhase( Assembly::Phase::EX );
                instructionsPhases[2] = input;
            } else if( input.getPhase() == Assembly::Phase::EX ){
                input.setPhase( Assembly::Phase::MEM );
                instructionsPhases[3] = input;
            } else if( input.getPhase() == Assembly::Phase::MEM ){ 
                input.setPhase( Assembly::Phase::WB );
                instructionsPhases[4] = input;
            } else if( input.getPhase() == Assembly::Phase::WB ){ 
                input.setPhase( Assembly::Phase::ENDED );
            }

            if( input.getBegin() == currentClock ){
                input.setPhase( Assembly::Phase::IF );
                instructionsPhases[0] = input;
            }
        }

        return instructionsPhases;
    }
}