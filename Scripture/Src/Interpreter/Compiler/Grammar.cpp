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
ifbody             : truebloc *elsebloc, truebloc.
condexpr           : assignstmt, expression.
var_id             : identifier.
objectid           : identifier.
function_id        : *'::' #functionid, #objectid '::' #functionid, #var_id '.' #functionid.
objcfncall         : '[' function_id  *args ']'.
scnotation         : 'E' *?'+' *?'-' number.
)";


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
    Dump();
    return {Rem::Int::Accepted };
}

void Grammar::Dump()
{

   Rem::Info() << Ansi::Color::Blue4 << "Mnemonic" << Ansi::Color::Yellow << ',' <<
           Ansi::Color::Red4 << "rule" << Ansi::Color::Yellow6 << ',' <<
           Ansi::Color::Green5 << "semantic" << Ansi::Color::Reset << ":\n";

   for (const auto& rule : _Rules) {
       Rem::Info() << Ansi::Color::Orchid1 << rule.second->_id << Ansi::Color::White << ':';
       String Out;
       for (auto seq : rule.second->sequences) {
           Out << Ansi::Color::MediumOrchid3; Out << "{ " << Ansi::Color::Yellow;// << Ends;
           for (auto t : seq.terms) {
               Out << Ansi::Color::Yellow; Out << t() << ' ';// << Ends;
           }
           Out << Ansi::Color::MediumOrchid2; Out << " }" << Ansi::Color::White;// << Ends;
       }
       Out << "\n";
       Rem::Debug() << Out();
   }
}

Return Grammar::ParseIdentifier(String::Iterator & crs)
{
    //logdebugfn << logger::White << " : token: '" << logger::Yellow << *crs << logger::White << "':" << Ends;
    Rule* r = QueryRule(*crs);
    //logdebugfn << logger::White << " rule: " << logger::Yellow << (r ? r->_id : "null")  << logger::White << ":" << Ends;
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
            /*lexer::lexem::lexer::lexem::mnemonic c = lexem::code(crs->c_str());
            if( c != lexer::lexem::lexer::lexem::mnemonic::knull ) {
                _Rule->a = a;
                (*_Rule) | c;
                a.reset();
                break;
            }*/

            Type::T t;
            t << *crs;
            if (t != lexer::type::bloc) // Quick and dirty hack about bypassing the lexer::type::bloc type:
            {
                if (t != 0) {
                    _Rule->a = a;
                    (*_Rule) | t;
                    a.reset();
                    break;
                }
            }

            //logdebug << " ***code: " << static_cast<uint64_t>(c) << " ***" << Ends;
            if (r) {
                _Rule->a = a;
                (*_Rule) | r;
                a.reset();
                break;
            }
            else {
                r = new rule_t(*crs);
                _Rules[*crs] = r;
                _Rule->a = a;
                _state = st_seq; //  expect ':' as next token in main loop.
                (*_Rule) | r;
                a.reset();
            }
            break;
            //return { (utils::notification::push(utils::notification::type::error), "identifier '", *crs, "' is invalid in this context") };
    }
    ++crs;
    return {Rem::Int::Accepted };
}

Return Grammar::enter_rule_def(utils::xstr::iterator &crs)
{
        // logdebug
        //     << logger::HCyan << __FUNCTION__
        //     << logger::White << ": ["
        //     << logger::Yellow << *crs
        //     << logger::White << ']'
        //     << Ends;
    if (_state != st_init_rule) {
        return { (utils::notification::push(utils::notification::type::error), "syntax error '", *crs, "' is invalid in this context") };
    }
    _state = st_seq;
    a.reset();
    ++crs;
    return {Rem::Int::Accepted };
}

Return Grammar::new_sequence(utils::xstr::iterator & crs)
{
        // logdebug
        //     << logger::HCyan << __FUNCTION__
        //     << logger::White << ": ["
        //     << logger::Yellow << *crs
        //     << logger::White << ']'
        //     << Ends;

    if (_state == st_option)
        return { (utils::notification::push(utils::notification::type::error), "syntax error '", *crs, "' is invalid in this context") };

    _Rule->new_sequence();
    _state = st_seq;
    a.reset();
    ++crs;
    return {Rem::Int::Accepted };
}

Return Grammar::end_rule(utils::xstr::iterator & crs)
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

Return Grammar::set_repeat(utils::xstr::iterator & crs)
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
    return {Rem::Int::Accepted };
}

Return Grammar::set_directive(utils::xstr::iterator& crs)
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
    return {Rem::Int::Accepted };
}




Return Grammar::set_optional(utils::xstr::iterator & crs)
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
    return {Rem::Int::Accepted };
}

Return Grammar::enter_litteral(utils::xstr::iterator & crs)
{

        // logdebug
        //     << logger::HCyan << __FUNCTION__
        //     << logger::White << ": ["
        //     << logger::Yellow << *crs
        //     << logger::White << ']'
        //     << Ends;

    if ((_state != st_seq) && (_state != st_option))
        return { (
                     utils::notification::push(utils::notification::type::error),
                         "syntax error '",
                         *crs,
                         "' is not a valid xio++ grammar token in context",
                         "(state machine:",(int)_state,
                         ")"
                 ) };

    utils::xstr::iterator i = crs;
    // logdebugfn << logger::HBlue << "token: '" << logger::HRed << *i << logger::HBlue << "'" << Ends;
    ++i;
    // logdebugfn << logger::HBlue << "token[++i]: '" << logger::HRed << *i << logger::HBlue << "'" << Ends;
    if ((*i == "'") || (*i == "\""))
        return { (utils::notification::push(utils::notification::type::error), "error: litteral x.i.o grammar element cannot be empty") };

    // logdebugfn << logger::White << " Checking token: '" << logger::Yellow << *i << logger::White << "'" << Ends;
    lexer::type::token_t token = lexer::type::token_t::scan(i->c_str());
    if (token) {
        _Rule->a = a;
        (*_Rule) | token.c;
        a.reset();
    }
    else
        return { (
                     utils::notification::push(utils::notification::type::error),
                         "syntax error '",
                         *i,
                         "' is not a valid xio++ grammar token"
                 ) };

    // logdebugfn << logger::White << "Term : '" << logger::Yellow << *i << logger::White << "':" << Ends;
    crs = i;
    ++crs;
    if ((*crs == "'") || (*crs == "\""))
        ++crs;
    //++crs; // will be on the next token.

    return Rem::Int::Accepted;
}

Return Grammar::set_oneof(utils::xstr::iterator & crs)
{
    //     logdebug
    //         << logger::HCyan << __FUNCTION__
    //         << logger::White << ": ["
    //         << logger::Yellow << *crs
    //         << logger::White << ']'
    //         << Ends;
    ~a;
    ++crs;
    return {Rem::Int::Accepted };
}

Grammar::Grammar()
{
}

Grammar::~Grammar()
{
}

int Grammar::Init()
{
    return 0;
}

rule_t * Grammar::QueryRule(const std::string & a_id)
{
    auto i = _Rules.find(a_id);
    return i == _Rules.end() ? nullptr : i->second;
}

Term::Term()
{
}

Term::Term(rule_t * r, Attr a_)
{
    a = a_;
    mem.r = r;
    _type = Term::type::rule;
}

Term::Term(lexer::type::T a_sem, Attr a_)
{
    a = a_;
    mem.sem = a_sem;
    _type = Term::type::sem;
}

Term::Term(lexer::lexem::mnemonic a_code, Attr a_)
{
    a = a_;
    mem.c = a_code;
    _type = Term::type::code;
}

Term::Term(const std::string & a_lexem)
{
    _type = Term::type::code;
    mem.c = lexer::lexem::code(a_lexem.c_str());
}

Term::Term(Term && _t)
{
    //     logdebugfn << ":" << Ends;
    using std::swap;
    swap(mem, _t.mem);
    _type = _t._type;
    swap(a, _t.a);
}

Term::Term(const Term & _t)
{
    mem = _t.mem;
    _type = _t._type;
    a = _t.a;
}

Term & Term::operator=(Term && _t)
{
    using std::swap;
    swap(mem, _t.mem);
    _type = _t._type;
    swap(a, _t.a);
    return *this;
}

Term & Term::operator=(const Term & _t)
{
    mem = _t.mem;
    _type = _t._type;
    a = _t.a;
    return *this;
}

bool Term::operator==(const Term& t) const
{
    if (_type != t._type)
        return false;

    switch (_type) {
        case type::code:
            return mem.c == t.mem.c;
        case type::rule:
            return mem.r == t.mem.r;
        case type::sem:
            return (mem.sem & t.mem.sem) != 0;
        case type::nil:
            return false;
    }
    return false;
}

bool Term::operator==(const lexer::type::token_t& t) const
{
    switch (_type) {
        case type::code:
            return mem.c == t.c;
        case type::sem:
            return (mem.sem & t.s) != 0;
        case type::nil:
            return false;
        default:
            return false;
    }
    return false;
}

bool Term::operator!=(const lexer::type::token_t& t) const
{
    switch (_type) {
        case type::code:
            return mem.c != t.c;
        case type::sem:
            return (mem.sem & t.s) == 0;
        case type::nil:
            return true;
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
    utils::xstr str;
    str << a();

//    std::map<Term::type, std::string> _{
//        {Term::type::rule, logger::attribute(logger::HRed)},
//        {Term::type::sem,  logger::attribute(logger::HGreen)},
//        {Term::type::code, logger::attribute(logger::HBlue)}
//    };
//
//    str << _[_type];
    switch (_type) {
        case Term::type::code:
        {
            lexer::type::token_t tok = lexer::type::token_t()[mem.c];
            str << tok.attribute();
        }
            break;
        case Term::type::rule:
            // Can't happen but we never know: (nullptr)
            if (mem.r)
                str << mem.r->_id;
            break;
        case Term::type::sem:
            str << lexer::type::to_s(mem.sem);
            break;
        default:
            str << "nil";
            break;
    }

    return str();
}

rule_t::rule_t(const std::string& a_id)
{
    _id = a_id;
    sequences.push_back(seq_t());
    seq = sequences.begin();
}

rule_t::~rule_t()
{
    sequences.clear();
    _id.clear();
}

rule_t & rule_t::new_sequence()
{
    sequences.push_back(seq_t());
    seq = --sequences.end();
    a.reset();
    return *this;
}

rule_t & rule_t::operator|(rule_t * _r)
{
    Term t = Term(_r);
    t.a = a;
    a.reset();
    *seq << t;
    return *this;
}

rule_t & rule_t::operator|(lexer::type::T _t)
{
    Term t = Term(_t);
    t.a = a;
    a.reset();
    *seq << t;
    return *this;
}

rule_t & rule_t::operator|(lexer::lexem::mnemonic _t)
{
    Term t = Term(_t);
    t.a = a;
    a.reset();
    *seq << t;
    return *this;
}

Term seq_t::next(Term::const_iterator& it) const
{
    if (it != terms.end())
        ++it;
    return *it;
}

seq_t & seq_t::operator<<(Term a_t)
{
    terms.push_back(a_t);
    return *this;
}

seq_t & seq_t::operator<<(lexer::type::T a_t)
{
    terms.emplace_back(a_t);
    return *this;
}

seq_t & seq_t::operator<<(lexer::lexem::mnemonic a_t)
{
    terms.emplace_back(a_t);
    return *this;
}

seq_t & seq_t::operator<<(rule_t * a_t)
{
    terms.emplace_back(a_t);
    return *this;
}

std::string Attr::operator()()
{
    utils::xstr str;
    if (z)
        str << "*";
    if (r)
        str << "+";
    if (l)
        str << "?";
    if (x)
        str << "#";
    return str();
}
}

}
 */