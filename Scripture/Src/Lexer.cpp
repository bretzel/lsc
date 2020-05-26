//
// Created by lsc on 20-05-18.
//

#include <Lsc/Scripture/Lexer.h>
#include <array>
namespace Lsc
{

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
    while((C < E) && (isspace(*C)))
        ++C;
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
    while((C < E) && (isspace(*C)))
        ++C;
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
 * @brief Synchronize the Location data from the M pointer.
 *
 * @return none.
 */
void Lexer::InternalCursor::Sync()
{
    const char *C_ = C;
    L = 1;
    while(C_ > B)
    {
        if((*C_ == '\n') || (*C_ == '\r'))
            ++L;
        --C_;
    }
    
    Col = 1;
    C_  = C;
    while((C_ > B) && (*C_ != '\n') && (*C_ != '\r'))
    {
        --C_;
        ++Col;
    }
    
    //Rem::Debug() << __PRETTY_FUNCTION__ << ": " << Location();
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
        String   Str = String::MakeStr(B, E);
        uint64_t D;
        Str >> D;
        uint64_t                I = 0;
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

#pragma region Scanners

std::map<Lexer::InputPair, Lexer::ScannerFn> Lexer::_ProductionTable = {
    // Begin from empty tokens stream:
    {{Type::Null,         Type::Null},        &Lexer::_InputDefault},
    {{0xFFFFFFFFFFFFFFFF, Type::Punctuation}, &Lexer::_InputPunctuation},
    {{0xFFFFFFFFFFFFFFFF, Type::Text},        &Lexer::_InputText},
    {{Type::Operator,     Type::Hex},         &Lexer::_InputHex},
    {{Type::Null,         Type::Unary},       &Lexer::_InputUnaryOperator},
    {{Type::Null,         Type::Keyword},     &Lexer::_InputKeyword},
    {{Type::Null,         Type::Binary},      &Lexer::ScanSignPrefix},
    {{Type::ClosePair,    Type::Binary},      &Lexer::_InputBinaryOperator},
    {{Type::ClosePair,    Type::Unary},       &Lexer::ScanPostfix},
    {{Type::Number,       Type::Unary},       &Lexer::ScanPostfix},
    {{Type::Id,           Type::Unary},       &Lexer::ScanPostfix},
    {{Type::Binary,       Type::Unary},       &Lexer::ScanPrefix},
    {{Type::Null,         Type::Unary},       &Lexer::ScanPrefix},
    {{Type::Punctuation,  Type::Unary},       &Lexer::ScanPrefix},
    {{Type::Postfix,      Type::Binary},      &Lexer::_InputBinaryOperator},
    {{Type::Id,           Type::Binary},      &Lexer::_InputBinaryOperator},
    {{Type::Number,       Type::Binary},      &Lexer::_InputBinaryOperator},
    {{Type::Text,         Type::Binary},      &Lexer::_InputBinaryOperator},
    {{Type::Binary,       Type::Binary},      &Lexer::ScanSignPrefix},
    {{Type::Binary,       Type::Null},        &Lexer::_InputDefault},
    {{Type::Operator,     Type::Null},        &Lexer::_InputDefault}, // Required mCursor._F flag to be set.
    {{Type::Id,           Type::Unary},       &Lexer::_InputUnaryOperator},
    {{Type::Id,           Type::Unary},       &Lexer::_InputUnaryOperator},
    
    // ----------------------------------------------------------------
    
    // (Restricted) Factor Notation Syntax Style:
    {{Type::Number,       Type::Null},        &Lexer::ScanFactorNotation},
    {{Type::Id,           Type::Null},        &Lexer::ScanFactorNotation}, // Required mCursor._F flag to be set.
    //{{Type::Id,           Type::OpenPair},    &Lexer::ScanFactorNotation}, // Required mCursor._F flag to be set.
    
    
    //...
};

Lexer::Scanner Lexer::GetScanner(Lexer::InputPair Pair)
{
    std::string F_;
    std::string R_;
    Rem::Internal() << "Lexer::GetScanner():\n";
    for(auto M : Lexer::_ProductionTable)
    {
        String Str;
        Str << "    {" << (F_ << M.first.first) << ", " << (R_ << M.first.second) << "} <- ";
        F_.clear();
        R_.clear();
        Str << "    {" << (F_ << Pair.first) << ", " << (R_ << Pair.second) << "}:";
        F_.clear();
        R_.clear();
        Rem::Internal() << Str();
        
        if(M.first && Pair)
        {
            Rem::Internal() << "{" << (F_ << Pair.first) << ", " << (R_ << Pair.second) << "}: MATCH\n";
            F_.clear();
            R_.clear();
            return M.second; // That's it! :)
        }
    }
    Rem::Debug() << "Lexer::GetScanner():\n    " << "{" << (F_ << Pair.first) << ", " << (R_ << Pair.second) << "}: NO MATCH";
    return Rem::Push() << Rem::Int::Rejected;
}

Return Lexer::_InputBinaryOperator(TokenData &Token_)
{
    Rem::Debug() << __PRETTY_FUNCTION__ << ":\n";
    return Push(Token_);
}

/*!
 * @brief Unknown Input Token.
 * @return Expect<>
 */
Return Lexer::_InputDefault(TokenData &Token_)
{
    Rem::Debug() << ": " << __PRETTY_FUNCTION__ << ":\n";
    if(*ScanNumber(Token_) != Rem::Int::Accepted)
    {
        Rem::Debug() << " Not a Number Trying ScanIdentifier:";
        if(*ScanIdentifier(Token_) != Rem::Int::Accepted)
        {
            Rem::Push() << mCursor.Mark() << ":";
            return Rem::Push() << Rem::Type::Fatal << ": " << Rem::Int::UnExpected << " Token type " << Token_.TypeName();
        }
    }
    
    return Push(Token_);
}

Return Lexer::_InputUnaryOperator(TokenData &)
{
    
    
    return (Rem::Push() << Rem::Int::Implement);
}

Return Lexer::_InputPunctuation(TokenData &Token_)
{
    return Push(Token_);
}

Return Lexer::_InputKeyword(TokenData &Token_)
{
    return Push(Token_);
}


Return Lexer::_InputString(TokenData &)
{
    return (Rem::Push() << Rem::Int::Implement);
}



Return Lexer::_InputHex(TokenData &Token_)
{    
    Rem::Internal() << __PRETTY_FUNCTION__ << ":\n";
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



Return Lexer::ScanNumber(TokenData &Token_)
{
    NumScanner Num = NumScanner(mCursor.C, mCursor.E);
    while(Num++);
    if(!Num)
        return Rem::Int::Rejected;
    
    Token_.T          = Type::Number;
    Token_.S          = Type::Number | Num();
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
            default:Token_.S = (Token_.S & ~Type::U64) | Type::U64;
                break;
        }
    }
    return Rem::Int::Accepted;
}

Return Lexer::ScanIdentifier(TokenData &Token_)
{
    
    Rem::Debug() << __PRETTY_FUNCTION__ << ": ";
    const char *C = mCursor.C;
    if((!isalpha(*C)) && (*C != '_'))
        return Rem::Int::Rejected;
    while(*C && isalnum(*C))
        ++C;
    --C;
    Token_.mLoc.Begin = mCursor.C;
    Token_.mLoc.End   = C;
    Token_.T          = Type::Id;
    Token_.S          = Type::Id;
    Token_.M          = Mnemonic::Noop;
    Token_.mLoc.L     = mCursor.L;
    Token_.mLoc.C     = mCursor.Col;
    Token_.mFlags.V   = 1; //Subject to be modified
    Rem::Debug() << "Lexer::ScanIdentifier: Cursor on \n" << mCursor.Mark();
    return Rem::Int::Accepted;
}

/*!
 * @brief  Scans for std maths factor notation, RESTRICTED (limited) syntax style:
 *         4ac => 4 x a x c
 *         4(ac...) => 4 x ( a x c ...)
 *         4pi/sin/cos/atan/asin/acos ... => 4 x p x i / 4 x s x i x n ... And NOT 4 x pi or 4 x sin ...
 *
 *         Rejected sequences:
 *         ac4 => Id; a4c => Id ...;
 *         4pi/sin/cos/atan/asin/acos ...;
 *
 * @note   Required that the Left hand side token is a Number and that the Input token is contiguous and of unknown type (Type::Null) to be scanned as an identifier.
 *         Input Token_ is either scanned in the Ref Table or not.
 * @return Execp<>
 */
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
        return Rem::Push() << Rem::Type::Fatal << " error: " << Rem::Int::Expected << " Factor notation style sequence.";
    }
    // Set _F "state" flag :
    if(!mCursor._F)
    {
        // LHS is Restricted to Number, triggering the Factor notation sequence flag.
        if(!mConfig.Tokens->back().IsNumber())
            return Rem::Push() << Rem::Type::Fatal << " error: " << Rem::Int::Expected << " Factor notation style sequence.";
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
    //Rem::Debug() << "Lexer::ScanFactorNotation: Mul Opertor:" << Mul.Details(true);
    return Push(Token_);
}

Return Lexer::ScanSignPrefix(TokenData &Token_)
{
    if(Token_.M == Mnemonic::Add || Token_.M == Mnemonic::Sub)
    {
        Token_.T = Type::Prefix;
        Token_.S = (Token_.S & ~Type::Binary) | Type::Sign | Type::Unary | Type::Prefix; // Type::Operator bit already set
        return Push(Token_);
    }
    return _InputBinaryOperator(Token_);
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
    Token_.M = Mnemonic::Factorial;
    //mCursor.Sync();
    return Push(Token_);
}

#pragma endregion Scanners

Return Lexer::Push(TokenData &Token_)
{
    if(!Token_)
        return (Rem::Push() << Rem::Type::Error << ": Attempt to push a Null TokenData into the Tokens stream.");
    
    mCursor.Sync();
    Token_.mLoc.L = mCursor.L;
    Token_.mLoc.C = mCursor.Col;
    
    std::size_t sz = Token_.mLoc.End - Token_.mLoc.Begin + 1;
    Token_.mLoc.I = static_cast<ptrdiff_t>(Token_.mLoc.Begin - mCursor.B);
    mCursor.C += sz;
    mConfig.Tokens->push_back(Token_);
    mCursor.SkipWS();
    mCursor.Sync();
    Rem::Debug() << "Lexer::Push: Size of Token:" << sz << ", TokenData " << Token_.Details(true);
    Rem::Debug() << "Lexer::Push: Cursor(Next Token):" << mCursor.Location() << '\n' << mCursor.Mark();
    return Rem::Int::Accepted;
}

Return Lexer::operator()()
{
    return Exec();
}



Return Lexer::Exec()
{
    Return R;
    
    if(!mConfig)
        return (Rem::Push() << "Lexer::Exec(): " << Rem::Type::Error << " Config Data is missing informations...");
    //...
    TokenData Token_;
    
    mCursor = Lexer::InternalCursor(mConfig.Source);
    mCursor.SkipWS();
    Rem::Debug() << "Lexer::Exec(): Scanning '" << mCursor.C << "':\n";
    
    const char *C = nullptr;
    while(!mCursor.Eof())
    {
        if(C == mCursor.C)
            return Rem::Push() << Rem::Type::Fatal << ": Lexer::Exec() : Aborted :  Force breaking infinite loop.";
        
        C = mCursor.C;
        //Rem::Debug() << "mCursor on '" << *mCursor.C << '\'';
        
        Token_ = TokenData::Scan(mCursor.C);
        
        std::pair<Type::T, Type::T> P = {mConfig.Tokens->empty() ? Type::Null : mConfig.Tokens->back().S, Token_.S};
        Scanner                     S = GetScanner(P);
        if(S)
            if(!(R = (this->**S)(Token_)))
                return R;
        
        //...
        
    }
    return Rem::Int::Ok;
}

void Lexer::Flush(std::function<void(TokenData)> F_)
{
    for(auto T : *mConfig.Tokens)
        if(F_)
            F_(T);
}
Return Lexer::_InputText(TokenData &Token_)
{

    Rem::Debug() << __PRETTY_FUNCTION__ << ":\n";
    Expect<std::string> R =  mCursor.ScanString();
    Rem::Debug() << "Scanned String: " << *R << '\n';
    return Rem::Internal() << __PRETTY_FUNCTION__ << ": " << Rem::Int::Implement;
}

}


bool operator&&(std::pair<Lsc::Type::T, Lsc::Type::T> L, std::pair<Lsc::Type::T, Lsc::Type::T> R)
{
    return (L.first & R.first) && (L.second & R.second);
}
