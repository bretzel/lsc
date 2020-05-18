//
// Created by lsc on 20-05-18.
//

#include <Lsc/Scripture/Lexer.h>



namespace Lsc{


#pragma region InternalCursor

/*!
 * @brief Skips white spaces character, advancing(/consuming) M pointer
 *
 * Prefix increment operator
 * @return true if M is not on EOF, false otherwise.
 */
bool Lexer::InternalCursor::operator++()
{
    if(C >= E)
        return false;
    ++C;
    while((C < E) && (isspace(*C))) ++C;
    return true;
}

/*!
 * @brief Skips white spaces character, advancing(/consuming) M pointer
 *
 * Postfix increment operator, just calls the prefix increment operator.
 * @return true if M is not on EOF, false otherwise.
 */
bool Lexer::InternalCursor::operator++(int)
{
    return ++(*this);
}

 /*!
 * @brief Skips white spaces character, advancing(/consuming) M pointer
 *
 * Named method, just calls the prefix increment operator.
 * @return true if M is not on EOF, false otherwise.
 */
[[maybe_unused]] bool Lexer::InternalCursor::SkipWS()
{
    return ++(*this);
}

/*!
 * @brief Tests if P is on or past EOF.
 * @param P
 * @return true if P is EOF, false otherwise.
 */
bool Lexer::InternalCursor::Eof(const char *P) const
{
    if(P)
        return P > E;
    return C > E;
}

/*!
 * @brief Synchronize the Location data from the M pointer.
 *
 * @return none.
 */
void Lexer::InternalCursor::Sync()
{
    L = 1;
    while(C > B)
    {
        if((*C == '\n') || (*C == '\r'))
            ++L;
        --C;
    }
    
    Col = 1;
    while((C > B) && (*C != '\n') && (*C != '\r'))
    {
        --C;
        ++Col;
    }
}


/*!
 * @brief Get the ptrdiff between the M pointer and the beginning of the source text (B pointer).
 * @return int.
 */
long Lexer::InternalCursor::Index() const
{
    return (ptrdiff_t) (C - B);
}

/*!
 * @brief Advances/Consume the M pointer till the next NewLine{'\r'; '\n'}  code in the source text
 * @return distinct std::string of the sequence.
 */
[[maybe_unused]] std::string Lexer::InternalCursor::ScanToEol()
{
    std::string Str;
    while((C <= E) && (*C != '\n') && (*C != '\r'))
        Str += *C++;
    return Str;
}

/*!
 * @brief Get a std::string copy of the current line from the M pointer
 * @return string.
 */
std::string Lexer::InternalCursor::Line() const
{
    std::string Str;
    
    const char *lb, *eb;
    lb = eb = C;
    while((lb > B) && (*lb != '\r') && (*lb != '\n'))
        --lb;
    if(lb > B)
        ++lb;
    while((eb < E) && (*eb != '\r') && (*eb != '\n'))
        ++eb;
    --eb;
    
    for(; lb <= eb; lb++)
        Str += *lb;
    return Str;
}

/*!
 * @brief Build a line String from the current position then Mark at the current columns.

  * @return std::string
  * @note : Must be Sync()'ed before calling Mark();
 
 */
std::string Lexer::InternalCursor::Mark() const
{
    String Str = Line();
    Str << '\n';
    for(int x = 0; x < Col; x++)
        Str << ' ';
    Str << '^';
    return Str();
}

/*!
 * @brief Get the string representation of the [internal]cursor location in the source text.
 * @return std::string
 */
[[maybe_unused]] std::string Lexer::InternalCursor::Location() const
{
    String Str = "%d,%d";
    Str << L << Col;
    return Str();
}



/*!
 * @brief Advances/Consumes the M pointer to Skip till SubStr_ match.
 * @param SubStr_
 * @return Expect code.
 */
[[maybe_unused]] Rem::Int Lexer::InternalCursor::ScanTo(const char *SubStr_)
{
    
    return Rem::Int::Ok;
}

Expect<std::string> Lexer::InternalCursor::ScanString()
{
    const char *be = C;
    char Quote_ = *be;
    std::string Str;
    ++be;
    
    while((be <= E) && (*be != Quote_))
        Str += *be++;
    
    if((*be != Quote_) && (be > E))
    {
        Sync();
        return (Rem::Save() << Rem::Type::Error << Rem::Int::Eof << " : Unterminated string constant:\n" << Mark());
    }
    Str += *be; // Include the rhs Quote.
    return Str;
}



Lexer::InternalCursor::InternalCursor(const char *Source_)
{
    C = Source_;
    E = C + std::strlen(C) - 1;
    B = C;
    L = Col = 1;
}

#pragma endregion InternalCursor


#pragma region NumScanner
Lexer::NumScanner::NumScanner(const char *_c, const char *_eos) :
B(_c), C(_c), E(nullptr), Eos(_eos){}



/*!
 * @brief For now a bare minimum digit with some rough floating point scan.
 * @return true if the M pointer is consumed and advanced
 */
bool Lexer::NumScanner::operator++(int)
{
    if(C >= Eos)
        return false;
    
    if(!isdigit(*C))
    {
        if(*C == '.')
            if(!Real)
                Real = true;
            else
                return false;
        else
            return false;
    }
    E = C;
    ++C;
    return true;
}

/*!
 * @brief Implements boolean operator
 * @return true if this NumScanner was  a valid numeric sequence, false otherwise.
 */
Lexer::NumScanner::operator bool() const
{
    return E>=B;
    //return false;
}

/*!
 * @brief Computes the numeric scale and 'best gess' base.
 * @return one [combined] of {{u,i}{8,16,32,64}} | fp| oct | hex | bin.
 *
 * @note Numeric Base is omitted as of this version. Thus it only computes the Scale.
 */
Type::T Lexer::NumScanner::operator()() const
{
    if(!Real)
    {
        String Str = String::MakeStr(B, E);
        uint64_t D;
        Str >> D;
        uint64_t I = 0;
        std::array<uint64_t, 3> R = {0x100, 0x10000, 0x100000000};
        while(D >= R[I])
            ++I;
        std::array<Type::T, 4> Cap = {Type::U8, Type::U16, Type::U32, Type::U64};
        return Cap[I];
    }
    
    ///@todo SCAN SCIENTIFIC NOTATION !!!!!!
    return Type::Float;
}

#pragma endregion NumScanner





}
