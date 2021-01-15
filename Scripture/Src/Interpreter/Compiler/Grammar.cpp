//
// Created by lsc on 20-10-17.
//

#include <Lsc/Scripture/Interpreter/Compiler/Grammar.h>


namespace Lsc
{

//
// Created by slussier on 19-08-25.
//




Grammar::Dictionary Grammar::TeaGrammarDictionary = {
    {':', &Grammar::EnterRuleDef },
    {',', &Grammar::NewSequence  },
    {'.', &Grammar::EndRule      },
    {'+', &Grammar::SetRepeat    },
    {'*', &Grammar::SetOptional  },
    {'?', &Grammar::SetOneof     }, // One of
    {'\'',&Grammar::EnterLitteral},
    {'"' ,&Grammar::EnterLitteral},
    {'#' ,&Grammar::SetDirective },
};

Rule::collection Grammar::_Rules;
static bool built = false;


std::string TeaccGrammarText = R"(

expression         : +#expr_token.
stmts              : +statement.
statement          : assignstmt ';', declvar ';', expression ';', instruction ';', var_id ';', ';'.
assignstmt         : declvar assign expression, var_id assign expression.
declvar            : *typename #newvar.
funcsig            : *typename function_id '(' *params ')'.
declfunc           : funcsig ';', funcsig bloc.
paramseq           : ',' param.
param              : *typename identifier.
params             : param *+paramseq.
objcarg            : identifier ':' expression.
arg                : objcarg, expression.
argseq             : ',' arg.
args               : arg *+argseq.
typename           : *'static' ?'i8' ?'u8' ?'i16' ?'u16' ?'i32' ?'u32' ?'i64' ?'u64' ?'real' ?'number' ?'string' ?#objectid.
instruction        : ?'if' ?'then'  ?'switch' ?'case' ?'for' ?'while' ?'repeat' ?'until' ?'do'.
if                 : 'if' condexpr ifbody, 'if' '(' condexpr ')' ifbody.
bloc               :  '{' stmts '}'.
truebloc           : *'then' bloc, *'then' statement.
elsebloc           : 'else' bloc, 'else' statement.
ifbody             : truebloc *elsebloc.
condexpr           : assignstmt, expression.
var_id             : identifier.
objectid           : identifier.
function_id        : *'::' #functionid, #objectid '::' #functionid, #var_id '.' #functionid.
objcfncall         : '[' function_id  *args ']'.

)";

//scnotation         : 'E' *?'+' *?'-' number.

Return Grammar::Build()
{
 
    if (Built())
        return Rem::Warning() << "Tea Grammar is already Built";
    
    _Text = TeaccGrammarText;
    Rem::Debug(__PRETTY_FUNCTION__ )
        << Ansi::Color::White << ": [ Building rules :\n"
        << Ansi::Color::Yellow << _Text
        << Ansi::Color::White << ']';

    std::size_t count = _Text.Words(tokens, ":;,|.+*?#", true);
    String::Collection List;
    Rem::Debug() << "building words list...";
    for (auto s : tokens)
        List.push_back(s());
    
    if (!count)
        return Rem::Fatal(__PRETTY_FUNCTION__ ) << ": No Tea Grammar. (internal error)";
    
    Rem::Debug("List done:") << List.size() << " words.";
    auto s = List.begin();
    _state = st_begin;
    do {
        Return r;
        auto p = Grammar::TeaGrammarDictionary.find((*s)[0]);
        if (p != Grammar::TeaGrammarDictionary.end()) {
            r = (this->*(p->second))(s);
        }
        else {
            r = ParseIdentifier(s);
        }
        if (!r)
            return r;
    } while (s != List.end());
    Rem::Debug("Build complete:") << ":";
 //   Dump();
    return Rem::Int::Accepted ;
}

void Grammar::Dump()
{

   Rem::Info() << Ansi::Color::SteelBlue4 << "Mnemonic" << Ansi::Color::Yellow << ',' <<
           Ansi::Color::Red4 << "rule" << Ansi::Color::Yellow6 << ',' <<
           Ansi::Color::Green5 << "semantic" << Ansi::Color::Reset << ":\n";
   String Out;
   for (const auto& rule : _Rules) {
       Out << Ansi::Color::SteelBlue4 << rule.second->_id << Ansi::Color::White << ':';
       
       for (auto seq : rule.second->sequences) {
           Out << Ansi::Color::Aquamarine3 << "{ ";// << Ends;
           for (auto t : seq.terms) {
               if(t.a.IsOneOf())
                   Out << Ansi::Color::Cornsilk1;
               else
                   if(t.a.IsOpt())
                       Out << Ansi::Color::Wheat4;
                   else
                       if(t.a.IsStrict())
                           Out << Ansi::Color::Thistle3;
                       else
                           Out << Ansi::Color::White;
               Out <<  t() << ' ';// << Ends;
           }
           Out << Ansi::Color::Aquamarine3 << " }" << Ansi::Color::White;// << Ends;
       }
       Out << '\n';
   }
   Rem::Application() << '\n' << Out();
}

Return Grammar::ParseIdentifier(String::Iterator & crs)
{
    Rule* r = QueryRule(*crs);
    switch (_state) {
        case st_begin:
            if (r) {
                if (!r->empty())
                    return Rem::Fatal(__PRETTY_FUNCTION__ ) <<  " rule, named: "<<  *crs << " already exists in the context of a new rule definition.";
                _Rule = r;
            }
            else {
                _Rule = new Rule(*crs);
                _Rules[*crs] = _Rule;
            }
            a.Reset();
            _state = st_init_rule; //  expect ':' as next token in main loop.
            break;
        case st_init_rule:
            _state = st_seq;
            break;
        case st_option:
        case st_seq:
            _state = st_seq;
            // lexem::T ?
            /*lexer::lexem::lexer::lexem::mnemonic c = lexem::M(crs->c_str());
            if( c != lexer::lexem::lexer::lexem::mnemonic::knull ) {
                _Rule->a = a;
                (*_Rule) | c;
                a.reset();
                break;
            }*/

            Type::T t = Type::FromStr(*crs);
            if (t & Type::Bloc) // Quick and dirty hack about bypassing the lexer::Type::bloc type:
            {
                
                _Rule->a = a;
                (*_Rule) | t;
                a.Reset();
                break;
            }

            if (r) {
                _Rule->a = a;
                (*_Rule) | r;
                a.Reset();
                break;
            }
            else {
                r = new Rule(*crs);
                _Rules[*crs] = r;
                _Rule->a = a;
                _state = st_seq; //  expect ':' as next token in main loop.
                (*_Rule) | r;
                a.Reset();
            }
            break;
    }
    ++crs;
    return Rem::Int::Accepted;
}

Return Grammar::EnterRuleDef(String::Iterator &crs)
{
        // logdebug
        //     << logger::HCyan << __FUNCTION__
        //     << logger::White << ": ["
        //     << logger::Yellow << *crs
        //     << logger::White << ']'
        //     << Ends;
    if (_state != st_init_rule)
        return Rem::Fatal(__PRETTY_FUNCTION__ ) <<  " syntax error: '" <<  *crs <<  "' is invalid in this context";
    
    _state = st_seq;
    a.Reset();
    ++crs;
    return Rem::Int::Accepted;
}

Return Grammar::NewSequence(String::Iterator & crs)
{
        // logdebug
        //     << logger::HCyan << __FUNCTION__
        //     << logger::White << ": ["
        //     << logger::Yellow << *crs
        //     << logger::White << ']'
        //     << Ends;

    if (_state == st_option)
        return Rem::Fatal(__PRETTY_FUNCTION__ ) <<  " syntax error: " <<  *crs << "' is invalid in this context";

    _Rule->new_sequence();
    _state = st_seq;
    a.Reset();
    ++crs;
    return Rem::Int::Accepted;
}

Return Grammar::EndRule(String::Iterator & crs)
{
        // logdebug
        //     << logger::HCyan << __FUNCTION__
        //     << logger::White << ": ["
        //     << logger::Yellow << *crs
        //     << logger::White << ']'
        //     << Ends;
    _state = st_begin;
    ++crs;
    return {Rem::Int::Accepted };
}

Return Grammar::SetRepeat(String::Iterator & crs)
{
    //logdebug
    //    << logger::HCyan << __FUNCTION__
    //    << logger::White << ": ["
    //    << logger::Yellow << *crs
    //    << logger::White << ']'
    //    << Ends;
    _state = st_option;
    +a;
    ++crs;
    return Rem::Int::Accepted;
}

Return Grammar::SetDirective(String::Iterator& crs)
{
    !a;
    _state = st_option;
    //logdebug
    //    << logger::HCyan << __FUNCTION__
    //    << logger::Yellow << a()
    //    << logger::White << ": ["
    //    << logger::Yellow << *crs
    //    << logger::White << ']'
    //    << Ends;

    ++crs;
    return Rem::Int::Accepted;
}




Return Grammar::SetOptional(String::Iterator & crs)
{
    //logdebug
    //    << logger::HCyan << __FUNCTION__
    //    << logger::White << ": ["
    //    << logger::Yellow << *crs
    //    << logger::White << ']'
    //    << Ends;
    *a;
    ++crs;
    _state = st_option;
    return Rem::Int::Accepted;
}

Return Grammar::EnterLitteral(String::Iterator & crs)
{

        // logdebug
        //     << logger::HCyan << __FUNCTION__
        //     << logger::White << ": ["
        //     << logger::Yellow << *crs
        //     << logger::White << ']'
        //     << Ends;

    if ((_state != st_seq) && (_state != st_option))
        return Rem::Fatal(__PRETTY_FUNCTION__)<< "syntax error '"<< *crs<< "' is not a valid xio++ grammar token in context"<< "(state machine:"<<(int)_state<< ")";

    String::Iterator i = crs;
    ++i;
    if ((*i == "'") || (*i == "\""))
        return Rem::Fatal(__PRETTY_FUNCTION__ ) << "error: litteral Tea Grammar element cannot be empty";

    TokenData token = TokenData::Scan(i->c_str());
    if (token) {
        _Rule->a = a;
        (*_Rule) | token.M;
        a.Reset();
    }
    else
        return Rem::Fatal(__PRETTY_FUNCTION__ )<<
                         "syntax error '"<<
                         *i<<
                         "' is not a valid xio++ grammar token";

    crs = i;
    ++crs;
    if ((*crs == "'") || (*crs == "\""))
        ++crs;
    //++crs; // will be on the next token.

    return Rem::Int::Accepted;
}

Return Grammar::SetOneof(String::Iterator & crs)
{
    //     logdebug
    //         << logger::HCyan << __FUNCTION__
    //         << logger::White << ": ["
    //         << logger::Yellow << *crs
    //         << logger::White << ']'
    //         << Ends;
    ~a;
    ++crs;
    return Rem::Int::Accepted;
}



[[maybe_unused]] int Grammar::Init()
{
    _Text = "";
    return 0;
}

Rule* Grammar::QueryRule(const std::string & a_id)
{
    auto i = _Rules.find(a_id);
    return i == _Rules.end() ? nullptr : i->second;
}


Term::Term(Rule * r, Attr a_)
{
    a = a_;
    _Mem.R = r;
    _type = Term::Type::R;
}

Term::Term(Lsc::Type::T a_sem, Attr a_)
{
    a = a_;
    _Mem.sem = a_sem;
    _type = Term::Type::S;
}

Term::Term(Mnemonic a_code, Attr a_)
{
    a = a_;
    _Mem.c = a_code;
    _type = Term::Type::M;
}

Term::Term(const std::string & a_lexem)
{
    _type = Term::Type::M;
    _Mem.c = Lexem::FromStr(a_lexem);
}

Term::Term(Term && _t)
 noexcept {
    //     logdebugfn << ":" << Ends;
    using std::swap;
    swap(_Mem, _t._Mem);
    _type = _t._type;
    swap(a, _t.a);
}

Term::Term(const Term & _t)
{
    _Mem = _t._Mem;
    _type = _t._type;
    a = _t.a;
}

Term & Term::operator=(Term && _t) noexcept
{
    using std::swap;
    swap(_Mem, _t._Mem);
    _type = _t._type;
    swap(a, _t.a);
    return *this;
}

Term & Term::operator=(const Term & _t)
{
    _Mem = _t._Mem;
    _type = _t._type;
    a = _t.a;
    return *this;
}

bool Term::operator==(const Term& t) const
{
    if (_type != t._type)
        return false;

    switch (_type) {
        case Type::M:
            return _Mem.c == t._Mem.c;
        case Type::R:
            return _Mem.R == t._Mem.R;
        case Type::S:
            return (_Mem.sem & t._Mem.sem) != 0;
        case Type::Nil:
            return false;
    }
    return false;
}

bool Term::operator==(const TokenData& t) const
{
    switch (_type) {
        case Type::M:
            return _Mem.c == t.M;
        case Type::S:
            return (_Mem.sem & t.S) != 0;
        case Type::Nil:
        default:
            return false;
    }
    return false;
}

bool Term::operator!=(const TokenData& t) const
{
    switch (_type) {
        case Type::M:
            return _Mem.c != t.M;
        case Type::S:
            return (_Mem.sem & t.S) == 0;
        case Type::Nil:
        default:
            return true;
    }
    return true;
}

Term::~Term()
{
}

std::string Term::operator()() const
{
    String str;
    str << a();

//    std::map<Term::type, std::string> _{
//        {Term::Type::rule, logger::attribute(logger::HRed)},
//        {Term::Type::S,  logger::attribute(logger::HGreen)},
//        {Term::Type::M, logger::attribute(logger::HBlue)}
//    };
//
//    str << _[_type];
    switch (_type) {
        case Term::Type::M:
        {
            TokenData tok = TokenData()[_Mem.c];
            str << tok.Attr();
        }
            break;
        case Term::Type::R:
            // Can't happen but we never know: (nullptr)
            if (_Mem.R)
                str << _Mem.R->_id;
            break;
        case Term::Type::S:
            str << Lsc::Type::Name(_Mem.sem);
            break;
        default:
            str << "nil";
            break;
    }

    return str();
}

Rule::Rule(const std::string& a_id)
{
    _id = a_id;
    sequences.push_back(Seq());
    seq = sequences.begin();
}

Rule::~Rule()
{
    sequences.clear();
    _id.clear();
}

Rule & Rule::new_sequence()
{
    sequences.push_back(Seq());
    seq = --sequences.end();
    a.Reset();
    return *this;
}

Rule & Rule::operator|(Rule * _r)
{
    Term t = Term(_r);
    t.a = a;
    a.Reset();
    *seq << t;
    return *this;
}

Rule & Rule::operator|(Lsc::Type::T _t)
{
    Term t = Term(_t);
    t.a = a;
    a.Reset();
    *seq << t;
    return *this;
}

Rule & Rule::operator|(Mnemonic _t)
{
    Term t = Term(_t);
    t.a = a;
    a.Reset();
    *seq << t;
    return *this;
}

Term Seq::next(Term::const_iterator& it) const
{
    if (it != terms.end())
        ++it;
    return *it;
}

Seq & Seq::operator<<(Term a_t)
{
    terms.push_back(a_t);
    return *this;
}

Seq & Seq::operator<<(Lsc::Type::T a_t)
{
    terms.emplace_back(a_t);
    return *this;
}

Seq & Seq::operator<<(Mnemonic a_t)
{
    terms.emplace_back(a_t);
    return *this;
}

Seq & Seq::operator<<(Rule * a_t)
{
    terms.emplace_back(a_t);
    return *this;
}

std::string Attr::operator()()
{
    String str;
    if (Z)
        str << "*";
    if (R)
        str << "+";
    if (L)
        str << "?";
    if (X)
        str << "#";
    return str();
}
}
