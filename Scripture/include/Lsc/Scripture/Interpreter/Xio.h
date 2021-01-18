//
// Created by lsc on 20-07-07.
//

//#ifndef LSC_EXIO_H
//#define LSC_EXIO_H

#pragma once


#include <Lsc/Rem/Rem.h>
#include <Lsc/Scripture/Interpreter/Alu.h>
#include <Lsc/Scripture/TokenData.h>

namespace Lsc
{



/*!
 * @brief Executable Instruction Object
 *
 * @note Avant de coder sur l'interpréteur, je voudrais bien implémenter Book pour y foutre le journal de développement UN MINIMUM
 * FONCTIONNEL ...
 */
class SCRIPTURE_LIB Xio
{
    Alu::Shared _A = nullptr;
    TokenData*  _T = nullptr;
    
    
public:
    
    using Shared = std::shared_ptr<Xio>;
    using SharedCollection = std::vector<Xio::Shared>;
    using Collection = std::vector<Xio*>;
    
    
    Xio() = delete;
    Xio(Xio&&) = delete;
    Xio(const Xio&) = delete;
    
    virtual ~Xio();
    
    explicit Xio(Xio::Shared xIO_, TokenData* Token_, Alu::Shared Alu_);
    static Xio::Shared New(Xio::Shared Parent_, TokenData* Token_, Alu::Shared Alu_);
    
private:
    // Parent-Child Hierarchical Links ( Recursive/Embedded Blocs; Ex.: The Interpreter's Bloc is the Root-Global Bloc)
    Xio::Shared          _Parent = nullptr;
    Xio::SharedCollection _Children;
    //----------------------------------------------------------------------
    
    // Binary Tree Links (Arithmetic Expression; Abstract Syntax Tree; ...) :
    Xio::Shared        _R = nullptr;
    Xio::Shared        _L = nullptr;
    Xio::Shared        _O = nullptr;
    // ---------------------------------------------------------------------
    
    // Execution:
    virtual Alu Exe();
    // Arithmetics
    
    using ExeFN = Alu(Xio::*)();
    using ExeTable = std::map<Mnemonic, Xio::ExeFN>;
    static ExeTable _ExeTable;
    
    ExeFN* _Operator = nullptr; ///< Assigned at the creation of this instance.
    
    virtual Alu Lshift();
    virtual Alu Radical();
    virtual Alu Exponent();
    virtual Alu Rshift();
    virtual Alu Decr();
    virtual Alu Incr();
    virtual Alu Assignadd();
    virtual Alu Assignsub();
    virtual Alu Assignmul();
    virtual Alu Assigndiv();
    virtual Alu Assignmod();
    virtual Alu Assignand();
    virtual Alu Assignor();
    virtual Alu Assignxor();
    virtual Alu Assignx1();
    virtual Alu Assignlshift();
    virtual Alu Assignrshift();
    virtual Alu Leq();
    virtual Alu Geq();
    virtual Alu Eq();
    virtual Alu Neq();  // != <>
    virtual Alu Add();
    virtual Alu Sub();
    virtual Alu Mul();
    virtual Alu Modulo();
    virtual Alu Lt();
    virtual Alu Gt();
    virtual Alu Assign();
    virtual Alu Binand();
    virtual Alu Binor();
    virtual Alu Bitxor();
    virtual Alu X1();           // complement a 1
    virtual Alu X2();
    virtual Alu Bitnot();          //
    virtual Alu Booland();
    virtual Alu Boolor();
    virtual Alu Division();
    virtual Alu Factorial();
    virtual Alu Positive();
    virtual Alu Negative();
    virtual Alu Hash(); // #
    virtual Alu Dollard();
    virtual Alu Dot();
    virtual Alu Kpi();
    virtual Alu Kcos();
    virtual Alu Kacos();
    virtual Alu Ktan();
    virtual Alu Katan();
    virtual Alu Ksin();
    virtual Alu Kasin();
    virtual Alu Noop();
    
};

}

//#endif //LSC_EXIO_H
