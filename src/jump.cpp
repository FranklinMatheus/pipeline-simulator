/* 
 * Assembly::findPosition()
 * Assembly::hasJump()
 * Assembly::nextJump()
 * Assembly::redefineBegin()
 * Functions implementations
 * Updates log:
 * >> Skeletron created by Franklin Matheus (29/04/2017 14:15)
 */

#include "assembly.h"

namespace Assembly{

    // <! Auxiliary functions of makeJumps() [BEGIN]
     
    int findPosition( const vector<Instruction> &inputs, const int id_ ){
        for( auto i(0u); i < inputs.size(); ++i ){
            auto input = inputs[i];
            if( input.getId() == id_ )
                return i + 1;
        }
        return 0;
    }

    bool hasJump( const vector<Instruction> &inputs, const unsigned int &lastJumpPosition ){
        for(auto i( lastJumpPosition ); i < inputs.size(); ++i ){
            auto input = inputs[i];
            if( input.getName() == "jump" or input.getName() == "beq" or input.getName() == "bne" ){
                return true;
            }
        }
        return false;
    }

    Instruction nextJump( const vector<Instruction> &inputs, const unsigned int &lastJumpPosition ){
        for( auto i( lastJumpPosition ); i < inputs.size(); ++i ){
            auto input = inputs[i];
            if( input.getName() == "jump" or input.getName() == "beq" or input.getName() == "bne" ){
                return input;
            }
        }
        return Instruction(); // <! This return exists only to avoid the warning: control reaches end of non-void function.
    }

    
    void redefineBegin( vector<Instruction> &inputs, const int &origin, const int &destiny ){
        auto instructionOrigin = inputs[ origin-1 ];
        auto instructionDestiny = inputs[ destiny-1 ];
        auto lastInstruction = inputs.back();

        auto differenceOfClocks = instructionDestiny.getBegin() - instructionOrigin.getBegin() - 1;

        for( auto &input : inputs ){
            if( ( input.getId() >= instructionDestiny.getId() ) and ( input.getId() <= lastInstruction.getId() ) ){
                int newBegin = input.getBegin() - differenceOfClocks;
                input.setBegin( newBegin );    
            }
        }
    }

    // <! Auxiliary functions of makeJumps() [END]

    void makeJumps( vector<Instruction> &inputs ){
        int total = inputs.size();

        auto positionOrigin = 0;
        auto positionDestiny = 0;

        while( hasJump( inputs, positionOrigin ) ){
            auto auxJump = nextJump( inputs, positionOrigin );

            positionOrigin = findPosition( inputs, auxJump.getId() );
            positionDestiny = findPosition( inputs, auxJump.getJump() );
            
            if( auxJump.getJump() > total ){
                cout << ">>> ERROR! SOME JUMP EXCEEDS THE INSTRUCTION RANGE!\n";
                cout << ">>> INSTRUCTION NUMBER [" << auxJump.getId() << "] "
                << "JUMPS TO A INVALID INSTRUCTION!\n"; 
                exit(EXIT_FAILURE);
            }

            if( auxJump.getJump() <= auxJump.getId() ){
                cout << ">>> SORRY! BUT THIS CODE ONLY MAKES JUMPS TO FOLLOWING INSTRUCTIONS.\n";
                exit(EXIT_FAILURE);
            }

            inputs.erase( inputs.begin() + positionOrigin, inputs.begin() + positionDestiny - 1 );

            positionOrigin = findPosition( inputs, auxJump.getId() );
            positionDestiny = findPosition( inputs, auxJump.getJump() );

            redefineBegin( inputs, positionOrigin, positionDestiny );    
        }
    }
}