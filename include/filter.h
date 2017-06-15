/* 
 * Assembly::isOPeration()
 * Assembly::isBranch()
 * Assembly::isMemoryAccess()
 * Assembly::isJump()
 * Assembly::filterInstruction()
 * Updates log:
 * >> Definition created by Franklin Matheus (29/04/2017 9:00)
 */

#ifndef _FILTER_H_
#define _FILTER_H_

namespace Assembly{

    void isOPeration( Instruction &, const string &, const int & );
    void isBranch( Instruction &, const string &, const int & );
    void isMemoryAccess( Instruction &, const string &, const int & );
    void isJump( Instruction &, const string &, const int & );
    void filterInstruction( vector<Instruction> &, const string & );
}

#endif