//
// Created by lsc on 20-07-07.
//

//#ifndef LSC_EXIO_H
//#define LSC_EXIO_H

#pragma once


#include <Lsc/Rem/Rem.h>
#include <Lsc/Scripture/Alu.h>
#include <Lsc/Scripture/TokenData.h>

namespace Lsc
{



/*!
 * @brief Executable Instruction Object
 *
 * @note Avant de coder sur l'interpréteur, je voudrais bien implémenter AppBook pour y foutre le journal de développement UN MINIMUM
 * FONCTIONNEL ...
 */
class SCRIPTURE_LIB ExIO
{
    Alu::Shared mAlu = nullptr;
    TokenData*  mToken = nullptr;
public:
    
    using Shared = std::shared_ptr<ExIO>;
    using Collection = std::vector<ExIO::Shared>;
    
    ExIO() = delete;
    ExIO(ExIO&&) = delete;
    ExIO(const ExIO&) = delete;
    
    virtual ~ExIO();
    
    explicit ExIO(ExIO::Shared&& ExIO_, TokenData* Token_, Alu::Shared&& Alu_);
private:
    // Parent-Child Hierarchical Links ( Recursive/Embedded Blocs; Ex.: The Interpreter's Bloc is the Root-Global Bloc)
    ExIO::Shared        mParent = nullptr;
    ExIO::Collection    mChildren;
    //----------------------------------------------------------------------
    
    // Binary Tree Links (Arithmetic Expression; Abstract Syntax Tree; ...) :
    ExIO::Shared        mRSH = nullptr;
    ExIO::Shared        mLSH = nullptr;
    ExIO::Shared        mOp = nullptr;
    // ---------------------------------------------------------------------
    
};

}

//#endif //LSC_EXIO_H
