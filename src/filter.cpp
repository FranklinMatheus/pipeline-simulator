/* 
 * Assembly::isOPeration()
 * Assembly::isBranch()
 * Assembly::isMemoryAccess()
 * Assembly::isJump()
 * Assembly::filterInstruction()
 * Functions implementations
 * Updates log:
 * >> Skeletron created by Franklin Matheus (29/04/2017 9:24)
 */

#include "assembly.h"

namespace Assembly{

    // <! Auxiliary functions of filterInstruction() [BEGIN]

    void isOPeration( Instruction &instruction_, const string &input_line_, const int &position_ ){

        auto length(0);
        auto position = position_;

        length = position+1;
        position = input_line_.find( ",", position+1 );
        instruction_.setRegistrator1( input_line_.substr( length, position-length ) );
        
        length = position+2;
        position = input_line_.find( ",", position+1 );
        instruction_.setRegistrator2( input_line_.substr( length, position-length ) );

        length = position+2;
        position = input_line_.find( '\0', position+1 );
        instruction_.setRegistrator3( input_line_.substr( length, position-length ) );
    }

    void isBranch( Instruction &instruction_, const string &input_line_, const int &position_ ){

        auto length(0);
        auto position = position_;

        length = position+1;
        position = input_line_.find( ",", position+1 );
        instruction_.setRegistrator2( input_line_.substr( length, position-length ) );
        
        length = position+2;
        position = input_line_.find( ",", position+1 );
        instruction_.setRegistrator3( input_line_.substr( length, position-length ) );

        length = position+2;
        position = input_line_.find( '\0', position+1 );
        auto instructionToJump = stoi( input_line_.substr( length, position-length ) );
        instruction_.setJump( instructionToJump );
    }

    void isMemoryAccess( Instruction &instruction_, const string &input_line_, const int &position_ ){
        auto length(0);
        auto position = position_;

        length = position+1;
        position = input_line_.find( ",", position+1 );
        instruction_.setRegistrator1( input_line_.substr( length, position-length ) );
        
        length = position+2;
        position = input_line_.find( "(", position+1 );
        auto offset = stoi( input_line_.substr( length, position-length ) );
        instruction_.setOffset( offset );

        length = position+1;
        position = input_line_.find( ")", position+1 );
        instruction_.setRegistrator2( input_line_.substr( length, position-length ) );
    }

    void isJump( Instruction &instruction_, const string &input_line_, const int &position_ ){
        auto length(0);
        auto position = position_;

        length = position+1;
        position = input_line_.find( '\0', position+1 );
        auto instructionToJump = stoi( input_line_.substr( length, position-length ) );
        instruction_.setJump( instructionToJump );
    }

    // <! Auxiliary functions of filterInstruction() [END]


    void filterInstruction( vector<Instruction> &inputs, const string &input_line ){
        Instruction auxInstruction;
        auto position(0);
        
        auto instruction_id = inputs.size() + 1;
        auxInstruction.setId( instruction_id );

        position = input_line.find( " ", 0 );
        auxInstruction.setName( input_line.substr( 0, position ) );
        
        if( auxInstruction.getName() == "add" or auxInstruction.getName() == "sub" ){
            isOPeration( auxInstruction, input_line, position );
            auxInstruction.definesBegin( inputs );
        } else if( auxInstruction.getName() == "bne" or auxInstruction.getName() == "beq" ){
            isBranch( auxInstruction, input_line, position );
            auxInstruction.definesBegin( inputs );
        } else if( auxInstruction.getName() == "lw" ){
            isMemoryAccess( auxInstruction, input_line, position );
            auxInstruction.definesBegin( inputs );
        } else if ( auxInstruction.getName() == "sw" ){
            isMemoryAccess( auxInstruction, input_line, position );
            auxInstruction.definesBeginSW( inputs );
        } else if( auxInstruction.getName() == "jump" ){
            isJump( auxInstruction, input_line, position );
            auxInstruction.definesBegin( inputs );
        } else {
            cout << ">>> WRONG SYNTAX! CHECK THE NAMES OF THE INPUT INSTRUCTIONS!\n";
            exit(EXIT_FAILURE);
        }
        inputs.push_back( auxInstruction );
    }
}