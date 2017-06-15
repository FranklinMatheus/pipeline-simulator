#include "assembly.h"

using namespace std; // string, vector
using namespace Assembly; // Instruction, filterInstruction(), makeJumps(), advanceAClock()

int main(){
    string input_line;
    vector<Instruction> inputs;

    getline( cin, input_line );

    while ( input_line != "" ){
        filterInstruction( inputs, input_line );
        
        getline( cin, input_line );
    }
    vector<Instruction> old_inputs = inputs; // <! Copies the original inputs before make the jumps.

    makeJumps( inputs );

    auto currentClock(1);
    auto lastClock( inputs.back().getBegin()+4 );

    Render::begin( old_inputs , lastClock ); 

    while( currentClock <= lastClock ){
        auto instructionsPhases = advanceAClock( inputs, currentClock );
        Render::render( instructionsPhases, currentClock );
        currentClock++;
    }

    return EXIT_SUCCESS;
}