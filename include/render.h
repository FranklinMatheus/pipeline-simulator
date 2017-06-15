/* 
 * Render::begin()
 * Render::render()
 * Render::beforeAfterJumps()
 * Updates log:
 * >> Definition created by Franklin Matheus (30/04/2017 13:10)
 */

#ifndef _RENDER_H_
#define _RENDER_H_

namespace Render{

    void begin( const std::vector<Assembly::Instruction> &, const int & );
    void render( const std::vector<Assembly::Instruction> &, const int & );
    void beforeAfterJumps( const std::vector<Assembly::Instruction> & );
}

#endif