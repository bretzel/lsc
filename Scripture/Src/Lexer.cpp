//
// Created by lsc on 20-05-18.
//

#include <Lsc/Scripture/Lexer.h>
#include <array>
namespace Lsc
{



Lexer::ScanTable  Lexer::_ScanTable = {

    {Type::Null,    &Lexer::_InputDefault},
    {Type::Binary, &Lexer::_InputBinaryOperator },
    {Type::Hex, &Lexer::_InputHex},
    {Type::Punctuation, &Lexer::_InputPunctuation},
    {Type::Prefix, &Lexer::ScanPrefix},
    {Type::Keyword, &Lexer::_InputKeyword}


};

Lexer::ConfigData &Lexer::Config()
{
    return mConfig;
}

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
    while((C <= E) && (isspace(*C)))
    {
        ++Col;
        if(*C == '\n' || *C == '\r')
        {
            ++L;
            Col=1;
        }
        
        ++C;
    }
    return C <= E;
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
 * @brief Synchronize the Location data from the IC pointer.
 *
 * @return none.
 */
void Lexer::InternalCursor::Sync()
{
    const char *C_;
    L = 1;
    Col = 1;
    C_  = B;
    while((C_ >= B)  && (C_ <= E) && (C_ < C))
    {
        if((*C_ == '\n') || (*C_ == '\r'))
        {
            Col=1;
            L++;
        }
        else
            ++Col;
        ++C_;
    }
    
    Rem::Debug(__PRETTY_FUNCTION__) << ": " << Location();
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
    
    while((eb <= E) && (*eb != '\r') && (*eb != '\n'))
        ++eb;
    
    for(; lb < eb; lb++)
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
    for(int x = 1; x < Col; x++)
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
    Rem::Debug(__PRETTY_FUNCTION__ +':'+ __LINE__) << '\n';
    const char  *be    = C;
    char        Quote_ = *be;
    std::string Str;
    Str += *be;
    ++be;
    
    while((be <= E) && (*be != Quote_))
        Str += *be++;
    
    if((*be != Quote_) && (be > E))
    {
        Sync();
        return (Rem::Push() << Rem::Type::Error << Rem::Int::Eof << " : Unterminated string constant:\n" << Mark());
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

Lexer::NumScanner::NumScanner(const char *_c, const char *_eos) : B(_c), C(_c), E(nullptr), Eos(_eos)
{}

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
    return E >= B;
}

/*!
 * @brief Computes the numeric scale and 'best gess' base.
 * @return one [combined] of {{u,i}{8,16,32,64}} | fp| oct | hex | bin.
 *
 * @note Numeric Base is omitted as of this version. Thus it only computes the Scale.
 */
Type::T Lexer::NumScanner::operator()() const
{
    if (!Real)
    {
        String   Str = String::MakeStr(B, E);
        uint64_t D;
        Str >> D;
        uint64_t I = 0;
        std::array<uint64_t, 3> R = { 0x100, 0x10000, 0x100000000 };
        while (D >= R[I])
            ++I;
        std::array<Type::T, 4> Capacity = { Type::U8, Type::U16, Type::U32, Type::U64 };
        Type::T T_ = Capacity[I];
        return T_;
    }
    
    return Type::Float;
}

#pragma endregion NumScanner

#pragma region Scanners



//Lexer::ProductionAssocTable Lexer::_AssocTable = {
//    {{Type::Punctuation|Type::Null|Type::Operator,                          Type::Hex},     &Lexer::_InputHex},
//    {{Type::Null|Type::Operator|Type::Leaf|Type::Punctuation,               Type::Keyword}, &Lexer::_InputKeyword},
//    {{Type::Null|Type::Operator|Type::Punctuation|Type::Unary|Type::Binary, Type::Binary},  &Lexer::_InputBinaryOperator},
//    {{Type::Null|Type::Punctuation|Type::Binary|Type::Leaf,                 Type::Binary},  &Lexer::_InputBinaryOperator},
//    {{Type::Null|Type::Operator|Type::Binary|Type::Punctuation|Type::OpenPair, Type::Unary},&Lexer::ScanPrefix},
//    {{Type::Null|Type::Operator|Type::Leaf,                                 Type::Hex},     &Lexer::_InputHex},
//    {{Type::Leaf| Type::Operator|Type::ClosePair,                           Type::Postfix}, &Lexer::ScanPostfix},
//    {{Type::Null|Type::Operator|Type::Punctuation|Type::Keyword,            Type::Text},    &Lexer::_InputText},
//    {{Type::Null|Type::Operator,                                            Type::Unary},   &Lexer::_InputUnaryOperator},
//    {{Type::Number|Type::Id|Type::OpenPair,                                 Type::Null},    &Lexer::ScanFactorNotation},
//    {{Type::Leaf | Type::Operator | Type::ClosePair,                        Type::Punctuation}, &Lexer::_InputPunctuation},
//    {{Type::Null|Type::Operator|Type::Punctuation|Type::Keyword|Type::Leaf, Type::Null},    &Lexer::_InputDefault}
//};


// + 4ac(x^2+y+b)


Lexer::Scanner Lexer::GetScanner(TokenData& T_)
{
    for (const auto& T : Lexer::_ScanTable)
    {
        if (T_.S & T.first) return T.second;
    }
    return Rem::Debug(__PRETTY_FUNCTION__) << " Not yet implemented";
}


Return Lexer::_InputBinaryOperator(TokenData &Token_)
{
    Rem::Debug() << __PRETTY_FUNCTION__ << ":\n";
    if (Token_.M == Mnemonic::Sub || Token_.M == Mnemonic::Add)
    {
        if (ScanSignPrefix(Token_)) 
            return Rem::Int::Accepted;
    }

    if (mCursor._F)
    {
        if (Token_.M == Mnemonic::Openpar)
        {
            InsertMultiply(Token_);
            mCursor._F = false;
        }
    }

    return Push(Token_);
}

/*!
 * @brief Unknown Input Token (Either Number litteral or Identifier).
 * @return Expect<>
 */
Return Lexer::_InputDefault(TokenData &Token_)
{
    Rem::Debug(__PRETTY_FUNCTION__) << ":\n";
    if(*ScanNumber(Token_) != Rem::Int::Accepted)
    {
        Rem::Debug() << " Not a Number Trying ScanIdentifier:";
        if(*ScanIdentifier(Token_) != Rem::Int::Accepted)
        {
            Rem::Push() << mCursor.Mark() << ":";
            return Rem::Push() << Rem::Type::Fatal << ": " << Rem::Int::UnExpected << " Token type " << Token_.TypeName();
        }
    }
    
    return Rem::Int::Rejected;
}

Return Lexer::_InputUnaryOperator(TokenData &T_)
{
    
    // Possible Prefix and Postfix unary operators:
    if ((T_.M == Mnemonic::Bitnot) || (T_.M == Mnemonic::Decr) || (T_.M == Mnemonic::Incr))
    {
        if (mConfig.Tokens->empty() || (mConfig.Tokens->back().S & Type::Binary))
            return ScanPrefix(T_);
        return ScanPostfix(T_);
    }
    if (T_.T == Type::Prefix)
        return ScanPrefix(T_);
    return ScanPostfix(T_);
}

Return Lexer::_InputPunctuation(TokenData &Token_)
{
    Rem::Debug(__PRETTY_FUNCTION__) << '\n' << mCursor.Mark();
    if (Token_.M == Mnemonic::Dot)
        return ScanNumber(Token_);
    return Push(Token_);
}

Return Lexer::_InputKeyword(TokenData &Token_)
{
    return Push(Token_);
}


Return Lexer::_InputHex(TokenData &Token_)
{    
    Rem::Debug(__PRETTY_FUNCTION__) << ":\n";
    const char *C_ = mCursor.C;
    C_ += Token_.Attr().length();
    const char* E_ = C_;
    if (isspace(*E_))
        return Rem::Int::Rejected;

    while (*E_ && !isspace(*E_) && 
        ( 
            ((*E_ >= '0') && (*E_ <= '9')) || 
            ((*E_ >= 'A') && (*E_ <= 'F')) || 
            ((*E_ >= 'a') && (*E_ <= 'f')) 
        )
    ) ++E_;
    if (E_ > C_) --E_;

    Token_.mLoc.End = E_;
    return Push(Token_);
}


/*!
 * @brief Scans conste numeric constrtuct
 * @param Token_
 * @return Rem::Int::Accepted;
 * @todo Scan Scientific Notation!!!
 */
Return Lexer::ScanNumber(TokenData &Token_)
{

    
    NumScanner Num = NumScanner(mCursor.C, mCursor.E);
    while(Num++);
    if(!Num)
        return Rem::Int::Rejected;

    if (mCursor._F)
        mCursor._F = false;

    Token_.T          = Type::Number;
    Token_.S          = Type::Number | Num()|Type::Leaf;
    Token_.mLoc.Begin = Num.B;
    Token_.mLoc.End   = Num.E;
    Rem::Debug() << "Lexer::ScanNumber: Cursor on \n" << mCursor.Mark();
    if(!(Token_.S & Type::Float))
    {
        String str;
        str << Token_.Attr();
        uint64_t           D = 0;
        std::istringstream i(str.c_str());
        switch(Num.Num)
        {
            case NumScanner::Bin:
                //????????? ah!
                break;
            case NumScanner::Oct:i >> std::oct >> D;
                break;
            case NumScanner::Dec:i >> D;
                break;
            case NumScanner::Hex:i >> std::hex >> D;
                break;
            default:str >> D;
                break;
        }
        
        //std::cout << __PRETTY_FUNCTION__ << " Parsed number:" << D << '\n';
        uint64_t                n = 0;
        std::array<uint64_t, 3> R = {0x100, 0x10000, 0x100000000};
        while(D >= R[n])
            ++n;
        
        switch(n)
        {
            case 0:Token_.S = (Token_.S & ~Type::U64) | Type::U8;
                break;
            case 1:Token_.S = (Token_.S & ~Type::U64) | Type::U16;
                break;
            case 2:Token_.S = (Token_.S & ~Type::U64) | Type::U32;
                break;
            default:Token_.S |= Type::U64;
                break;
        }
    }
    Token_.M = Mnemonic::Noop;
    return Push(Token_);
    //return Rem::Int::Accepted;
}

Return Lexer::ScanIdentifier(TokenData &Token_)
{
    
    Rem::Debug(__PRETTY_FUNCTION__);
    const char *C = mCursor.C;
    if((!isalpha(*C)) && (*C != '_'))
        return Rem::Int::Rejected;

    if (mCursor._F)
        goto IDOK;
    else
    {
        if (!mConfig.Tokens->empty())
        {
            if (mConfig.Tokens->back().T == Type::Number)
            {
                mCursor._F = true;
                goto IDOK;
            }
        }
    }
    while(*C && (isalnum(*C) || (*C == '_'))) ++C;
    --C;
IDOK:
    Token_.mLoc.Begin = mCursor.C;
    Token_.mLoc.End   = C;
    Token_.T          = Type::Id;
    Token_.S          = Type::Id|Type::Leaf;
    Token_.M          = Mnemonic::Noop;
    Token_.mLoc.L     = mCursor.L;
    Token_.mLoc.C     = mCursor.Col;
    Token_.mFlags.V   = 1; //Subject to be modified
    Rem::Debug() << "Lexer::ScanIdentifier: Cursor on \n" << mCursor.Mark();
    if (mCursor._F)
        InsertMultiply(Token_);
    return Push(Token_);
}



void Lexer::InsertMultiply(TokenData& Token_)
{
    TokenData Mul;
    Mul = Token_; // Push Token_ properties in the incoming virtual multiply operator
    Mul.T = Type::Binary;
    Mul.S = Type::Binary | Type::Operator;
    Mul.mFlags.M = Mul.mFlags.V = 1;
    Mul.M = Mnemonic::Mul;
    mConfig.Tokens->push_back(Mul);
    mCursor.C = Mul.mLoc.Begin;
    Rem::Debug(__PRETTY_FUNCTION__) << " Details:" << Mul.Details() << "\n" << Mul.Mark();
}

/*!
 * @brief  Scans for std maths factor notation, RESTRICTED (limited) syntax style:
 *         4ac => 4 x a x c
 *         4(ac...) => 4 x ( a x c ...)
 *         4pi/sin/cos/atan/asin/acos ... => 4 x p x i / 4 x s x i x n ... And NOT 4 x pi or 4 x sin ...
 * *
 * 
 * @note   Required that the Left hand side token is a ContNumber and that the Input token is contiguous and of unknown type (Type::Null) to be scanned as an identifier.
 *         Input Token_ is either scanned in the Ref Table or not.
 * @return Execp<>
 *
Return Lexer::ScanFactorNotation(TokenData &Token_)
{
    // Tokens stream is NOT EMPTY here.
    
    // Required that the next Token_ is contiguous ( no [white]space between lhs and Token_ ).
    Rem::Debug() << __PRETTY_FUNCTION__ << ":";
    TokenData Mul;
    if((mCursor.C - mConfig.Tokens->back().mLoc.End) != (ptrdiff_t) 1)
    {
        Rem::Debug() << "No factor notation style seq:[ptrdiff_t:" << mCursor.C - mConfig.Tokens->back().mLoc.End << "]:\n" << mCursor.Mark();
        Rem::Debug() << "Lexer::ScanFactorNotation: mCursor:" << mCursor.C - mCursor.B << " <::> Tail[Begin]:" << mConfig.Tokens->back().mLoc.Begin - mCursor.B;
        return Rem::Fatal() << Rem::Int::Expected << " Factor notation style sequence.";
    }
    // Set _F "state" flag :
    if(!mCursor._F)
    {
        // LHS is Restricted to Number, triggering the Factor notation sequence flag.
        if(!mConfig.Tokens->back().IsNumber())
            return Rem::Fatal() << Rem::Int::Expected << " Factor notation style sequence.";
    }
    
    // Expecting RHS to be an identifier Token
    if(*ScanIdentifier(Token_) != Rem::Int::Accepted)
        return Rem::Int::Rejected;
    
    // triggering the Factor notation sequence flag.
    mCursor._F = true;
    
    Token_.mLoc.End = Token_.mLoc.Begin; // Adjust (CUT) the Identifier Attribute to ONE char.
    //Rem::Debug() << "Confirmed Lexer::ScanFactorNotation: " << Token_.Details(true);
    Mul = Token_; // Push Token_ properties in the incoming virtual multiply operator
    Mul.T        = Type::Binary;
    Mul.S        = Type::Binary | Type::Operator;
    Mul.mFlags.M = Mul.mFlags.V = 1;
    Mul.M        = Mnemonic::Mul;
    mCursor.Sync();
    Mul.mLoc.L = mCursor.L;
    Mul.mLoc.C = mCursor.Col;
    mConfig.Tokens->push_back(Mul);
    mCursor.C = Mul.mLoc.Begin;
    return Push(Token_);
}


*/

Return Lexer::ScanSignPrefix(TokenData &Token_)
{
    Token_.T = Type::Prefix;
    Token_.S = (Token_.S & ~Type::Binary) | Type::Sign | Type::Unary | Type::Prefix; // Type::Operator bit already set
    return Push(Token_);
}

/*!
 * @brief  Operators such as '--', '++', '!' can be prefix or postfix unary operators.
 *
 * @return
 */
Return Lexer::ScanPrefix(TokenData &Token_)
{
    return Push(Token_);
}

/*!
 * @brief  Operators such as '--', '++', '!' can be prefix or postfix unary operators.
 *
 * @return
 */
Return Lexer::ScanPostfix(TokenData &Token_)
{
    if(!((Token_.M == Mnemonic::Decr) || (Token_.M == Mnemonic::Incr) || (Token_.M == Mnemonic::Bitnot))) return Rem::Int::Rejected;
    Token_.T = Type::Postfix;
    Token_.S = (Token_.S & ~Type::Prefix) | Type::Postfix; // Unary/Operator ...  already set.
    if(Token_.M == Mnemonic::Bitnot) Token_.M = Mnemonic::Factorial;
    
    //mCursor.Sync();
    return Push(Token_);
}


#pragma endregion Scanners

Return Lexer::Push(TokenData &Token_)
{
    if(!Token_)
        return Rem::Push() << Rem::Type::Error << ": Attempt to push a Null TokenData into the Tokens stream.";
    
    //mCursor.Sync();
    Token_.mLoc.L = mCursor.L;
    Token_.mLoc.C = mCursor.Col;
    
    std::size_t sz = Token_.mLoc.End - Token_.mLoc.Begin + 1;
    Token_.mLoc.I = static_cast<ptrdiff_t>(Token_.mLoc.Begin - mCursor.B);
    mCursor.C += sz;
    mCursor.Col += sz;
    mConfig.Tokens->push_back(Token_);
    mCursor.SkipWS();
    Rem::Debug(__PRETTY_FUNCTION__) << "Lexer::Push: Size of Token:" << sz << ", TokenData " << Token_.Details(true);
    Rem::Debug() << "Cursor(Next Token):" << mCursor.Location() << '\n' << mCursor.Mark();
    return Rem::Int::Accepted;
}

Return Lexer::operator()()
{
    return Exec();
}





void Lexer::Flush(std::function<void(TokenData)> F_)
{
    for(const auto& T : *mConfig.Tokens)
        if(F_)
            F_(T);
}


Return Lexer::_InputText(TokenData &Token_)
{
    Rem::Debug() << __PRETTY_FUNCTION__ << ":\n";
    Expect<std::string> R =  mCursor.ScanString();
    std::string str = *R;
    Token_.mLoc.Begin = mCursor.C;
    Token_.mLoc.End   = mCursor.C + str.length()-1;
    Token_.mLoc.L     = mCursor.L;
    Token_.mLoc.C     = mCursor.Col;
    Token_.mLoc.I     = mCursor.Index();
    
    Rem::Debug() << "Scanned String: " << *R << '\n';
    
    Push(Token_);
    return Rem::Int::Accepted;
}

Return Lexer::Exec()
{
    Return R;

    if (!mConfig)
        return Rem::Fatal() << "Lexer::Exec(): Config Data is missing crucial informations...";
    //...
    TokenData Token_;

    mCursor = Lexer::InternalCursor(mConfig.Source);
    mCursor.SkipWS();
    Rem::Debug() << "Lexer::Exec(): Scanning '" << mCursor.C << "':\n";

    const char* C = nullptr;
    while (!mCursor.Eof())
    {
        if (C == mCursor.C)
            return Rem::Internal() << ": Lexer::Exec() : Aborted :  Force breaking infinite loop.";

        C = mCursor.C;
        //Rem::Debug() << "mCursor on '" << *mCursor.C << '\'';

        Token_ = TokenData::Scan(mCursor.C);
        Rem::Debug(__PRETTY_FUNCTION__) << " Details: " << Token_.Details();
        Scanner S = GetScanner(Token_);
        if (S)
        {
            
            if (!(R = (this->**S)(Token_)))
                return Rem::Fatal("Lexer:") << "Aborted: Unexpected token:\n" << mCursor.Mark();
        }
        else
        {
            return Rem::Fatal("Lexer loop:") << Rem::Type::Internal << " No scanner for token:\n" << mCursor.Mark();
        }

    }
    return Rem::Int::Ok;
}
}
