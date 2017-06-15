/* 
 * Assembly::findPosition()
 * Assembly::hasJump()
 * Assembly::nextJump()
 * Assembly::redefineBegin()
 * Updates log:
 * >> Definition created by Franklin Matheus (29/04/2017 14:00)
 */

#ifndef _JUMP_H_
#define _JUMP_H_

namespace Assembly{

    bool hasJump( const vector<Instruction> &, const unsigned int & );
    Instruction nextJump( const vector<Instruction> &, const unsigned int & );
    int findPosition( const vector<Instruction> &, const int );
    void makeJumps( vector<Instruction> & );
    void redefineBegin( vector<Instruction> &, const int &, const int & );
}

#endif