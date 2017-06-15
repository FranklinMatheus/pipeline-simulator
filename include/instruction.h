/* 
 * Assembly::Instruction class implementation
 * Updates log:
 * >> Skeletron created by Franklin Matheus (20/04/2017 11:30)
 */

#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

    namespace Assembly{

        using namespace std; // string, cout, vector

        typedef enum { WAITING = 0, IF, ID, EX, MEM, WB, ENDED}Phase;

        class Instruction{
            int m_id;
            string m_name;
            string m_registrator1;
            string m_registrator2;
            string m_registrator3;
            int m_offset;
            int m_jump;
            int m_begin;
            Phase m_phase;

        public:
            // default constructor
            Instruction()
            : m_id (0)
            , m_name ("default")
            , m_registrator1 ("default")
            , m_registrator2 ("default")
            , m_registrator3 ("default")
            , m_offset (0)
            , m_jump (-1)
            , m_begin (1)
            , m_phase (WAITING)
            {
                /* < empty > */
            }

            int getId() { return m_id; }
            string getName() { return m_name; }
            string getRegistrator1() { return m_registrator1; }
            string getRegistrator2() { return m_registrator2; }
            string getRegistrator3() { return m_registrator3; }
            int getOffset() { return m_offset; }
            int getJump() { return m_jump; }
            int getBegin() { return m_begin; }
            Phase getPhase() { return m_phase; }
            
            void setId( int id ) { m_id = id; }
            void setName( string name ) { m_name = name; }
            void setRegistrator1( string registrator1 ) { m_registrator1 = registrator1; };
            void setRegistrator2( string registrator2 ) { m_registrator2 = registrator2; };
            void setRegistrator3( string registrator3 ) { m_registrator3 = registrator3; };
            void setOffset( int offset ) { m_offset = offset; }
            void setJump( int jump ) { m_jump = jump; }
            void setBegin( int begin ) { m_begin = begin; }
            void setPhase( Phase phase ) { m_phase = phase; }

            void printInstruction(){
                if( m_name == "add" or m_name == "sub" ){
                    cout << m_name << " " 
                         << m_registrator1 << ", " 
                         << m_registrator2 << ", " 
                         << m_registrator3 << 
                         #ifdef DEBUG
                            "\t(NUMBER: " <<
                            m_id << ")" <<
                         #endif
                         "\n";
                } else if( m_name == "bne" or m_name == "beq" ) {
                    cout << m_name << " " 
                         << m_registrator2 << ", " 
                         << m_registrator3 << ", " 
                         << m_jump <<
                         #ifdef DEBUG
                            "\t(NUMBER: " <<
                            m_id << ")" <<
                         #endif
                         "\n";
                } else if( m_name == "lw" or m_name == "sw" ) {
                    cout << m_name << " " 
                         << m_registrator1 << ", " 
                         << m_offset << "(" 
                         << m_registrator2 << ")" <<
                         #ifdef DEBUG
                            "\t(NUMBER: " <<
                            m_id << ")" <<
                         #endif
                         "\n";
                } else if( m_name == "jump") {
                    cout << m_name << " "  
                         << m_jump <<
                         #ifdef DEBUG
                            "\t(NUMBER: " <<
                            m_id << ")" <<
                         #endif
                        "\n";

                } else {
                    cout << "0\n";
                }
            }

            // add, sub, beq, bne, lw 
            void definesBegin( vector<Instruction> &inputs_ ){
                
                for( auto &input : inputs_ ){
                    if( input.getId() >= m_id-4 ){
                        if( input.getName() != "sw" ){
                            
                            if( ( input.getRegistrator1().compare( m_registrator2 ) == 0 or input.getRegistrator1().compare( m_registrator3 ) == 0 )
                            and ( input.getRegistrator1() != "default" ) 
                            and ( input.getName() != "beq" or input.getName() != "bne" ) ){
                                auto tempBegin = input.getBegin() + 4;

                                if( m_begin > tempBegin ) continue;
                                else setBegin( tempBegin );
                            } else {
                                auto tempBegin = input.getBegin() + 1;

                                if( m_begin > tempBegin ) continue;
                                else setBegin( tempBegin );
                            }
                        } else {
                            if( ( input.getRegistrator2().compare( m_registrator2 ) == 0 or input.getRegistrator2().compare( m_registrator3 ) == 0 )
                            and ( input.getRegistrator1() != "default" ) 
                            and ( input.getName() != "beq" or input.getName() != "bne" ) ){
                                auto tempBegin = input.getBegin() + 4;

                                if( m_begin > tempBegin ) continue;
                                else setBegin( tempBegin );
                            } else {
                                auto tempBegin = input.getBegin() + 1;

                                if( m_begin > tempBegin ) continue;
                                else setBegin( tempBegin );
                            }
                        }
                    }
                }
            }

            // sw
            void definesBeginSW( vector<Instruction> &inputs_ ){
                
                for( auto &input : inputs_ ){
                    if( input.getId() >= m_id-4 ){

                        if( ( input.getRegistrator1().compare( m_registrator1 ) == 0 )
                        and ( input.getRegistrator1() != "default" )
                        and ( input.getName() != "beq" or input.getName() != "bne" ) ){
                            auto tempBegin = input.getBegin() + 4;

                            if( m_begin > tempBegin ) continue;
                            else setBegin( tempBegin );
                        } else {
                            auto tempBegin = input.getBegin() + 1;

                            if( m_begin > tempBegin ) continue;
                            else setBegin( tempBegin );
                        }
                    }
                }
            }

            void definesBeginBranch( vector<Instruction> &inputs_ ){
                m_begin = inputs_.back().getBegin()+1;
            }        
        };
    }

#endif