/* 
 * Render::begin()
 * Render::render()
 * Render::beforeAfterJumps()
 * Updates log:
 * >> Skeletron created by Franklin Matheus (30/04/2017 13:44)
 */

#include "assembly.h"

namespace Render{

    void begin( const std::vector<Assembly::Instruction> &inputs, const int &lastClock ){
        std::cout << ">>>> The inputs were: \n";
        std::cout << "_______________________________________\n";

        for( auto input : inputs )
            input.printInstruction();

        std::cout << "_______________________________________\n";
        
        std::cout << "\n\n>>>> Output: \n";
        std::cout << "     The number of cycles was: " << lastClock << "\n\n";
    }

    void render( const std::vector<Assembly::Instruction> &instructionsPhases, const int &currentClock ){
        std::vector<std::string> phases = { "IF", "ID", "EX", "MEM", "WB" };
        std::cout << "=======================================\n";
        std::cout << ">>>> Current cycle: " << currentClock << "\n\n";

        for( auto i(0u); i < phases.size(); ++i ){
            std::cout << phases[i] << ":\t";
            auto instruction = instructionsPhases[i];
            instruction.printInstruction();
        }
    }

    void beforeAfterJumps( const std::vector<Assembly::Instruction> &inputs ){
        std::cout << "BEFORE JUMPS:\n";
        for( auto input : inputs )
            input.printInstruction();

        std::cout << "\n";

        std::cout << "AFTER JUMPS:\n";
        for( auto input : inputs )
            input.printInstruction();
    }
}