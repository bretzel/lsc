//
// Created by slussier on 19-08-25.
//

#pragma once

#include <Lsc/Scripture/Lexer.h>
#include <Lsc/Rem/Rem.h>
#include <map>
#include <stack>
#include <memory>

/************************************* NOTE *****************************************************

 one-of : *t *t2 *t3 *t4 *t5 *t6

 */

namespace Lsc
{

    struct Rule;
    class Grammar;


struct  Attr
{
    int8_t Z : 1; ///< Zero or one (optional * )
    int8_t R : 1; ///< Repeat      (        + )
    int8_t L : 1; ///< List        (one of  ~ ?)
    int8_t X : 1; ///< directive    ( ast direcive )
    int8_t S : 8; ///< Litteral List Separator
    Attr &operator|(Attr const &_)
    {
        Z |= _.Z;
        R |= _.R;
        L |= _.L;
        X |= _.X;
        //S = A.S;
        return *this;
    }
    
    Attr &operator+()
    {
        R = 1;
        return *this;
    }
    Attr &operator*()
    {
        Z = 1;
        return *this;
    }
    Attr &operator!()
    {
        X = 1;
        return *this;
    }
    Attr &operator~()
    {
        L = 1;
        return *this;
    }
    void Reset() { Z = R = L = X = S = 0; }
    std::string operator()();
    [[nodiscard]] bool IsOpt() const { return Z != 0; }
    [[nodiscard]] bool IsOneOf() const { return L != 0; }
    [[nodiscard]] bool IsStrict() const { return Z == 0 && L == 0 && R == 0; }
    [[nodiscard]] bool IsRepeat() const { return R != 0; }
    [[nodiscard]] bool Accepted() const { return X != 0; }
    void Accept() { X = 1; }
    void Reject() { X = 0; }
};


struct  Term
{
    mutable Attr a = {0, 0, 0, 0, 0}; ///< default : punctual, strict match

    enum class Type : uint8_t
    {
        //term,
        R = 0,
        S,
        M,
        Nil
    };

    void Accept() { a.Accept(); }
    void Reject() { a.Reject(); }

    Term::Type _type = Term::Type::Nil;

    union Mem {
        Rule *R;
        Lsc::Type::T sem;
        Mnemonic c;
    } _Mem = {nullptr};

    using collection = std::vector<Term>;
    using iterator = collection::iterator;
    using const_iterator = collection::const_iterator;

    // pas le choix... 'y faut un parser....

    Term();
    Term(Rule *r, Attr a_ = {0, 0, 0, 0, 0});
    Term(Lsc::Type::T a_sem, Attr a_ = {0, 0, 0, 0, 0});
    Term(Mnemonic a_code, Attr a_ = {0, 0, 0, 0, 0});

    Term(const std::string &a_lexem);

    Term(Term &&_t) noexcept;
    Term(const Term &_t);

    Term &operator=(Term &&_t);
    Term &operator=(const Term &_t);

    bool operator==(const Term &t) const;
    bool operator==(const TokenData &t) const;
    bool operator!=(const TokenData &t) const;

    operator bool() { return _type != Term::Type::Nil; }
    ~Term();

    Term &operator*()
    {
        *a;
        return *this;
    }
    Term &operator+()
    {
        +a;
        return *this;
    }
    Term &operator!()
    {
        !a;
        return *this;
    }
    Term &operator~()
    {
        ~a;
        return *this;
    }

    std::string operator()() const;

    bool IsRule() const { return _type == Type::R; }
    bool IsSemantic() const { return _type == Type::S; }
    bool IsMnemonic() const { return _type == Type::M; }
    bool IsNull() const { return _type == Type::Nil; }

    static Term Query(const char * C_);
    static Term Query(Lsc::Type::T T_);
    static Term Query(Mnemonic M_);
};


struct  Seq
{

    Attr a = {0, 0, 0, 0, 0}; ///< default : punctual, strict match

    //using data = std::vector<term_list_t>;

    Term::collection terms;

    using collection = std::vector<Seq>;
    using const_iterator = collection::const_iterator;
    using iterator = collection::iterator;
    using stack = std::stack<iterator>;

    Seq() = default;

    Term::const_iterator begin() const { return terms.cbegin(); }

    bool end(Term::const_iterator t) const
    {
        return terms.cend() == t;
    }

    Term next(Term::const_iterator &it) const;

    ~Seq()
    {
        terms.clear();
    }
    Seq &operator<<(Term a_t);

    // Emplace_back:
    Seq &operator<<(Lsc::Type::T a_t);
    Seq &operator<<(Mnemonic a_t);
    Seq &operator<<(Rule *a_t);
};

struct SCRIPTURE_LIB Rule
{

    Seq::collection sequences;
    // ---------------------------------------
    Seq::iterator seq; // Temporary held for building this rule.
    // ---------------------------------------
    //Seq::stack seq_stack;

    using collection = std::map<std::string, Rule *>;
    using iterator = collection::const_iterator;

    Attr a = {0, 0, 0, 0, 0}; /// Volatile attribute infos. ( Copied into the rule's recursion context  )
    Attr inject = {0, 0, 0, 0, 0};

    std::string _id;

    Rule() = default;
    Rule(const std::string &a_id);

    Rule(int) {}
    ~Rule();
    bool empty() const { return sequences.empty() ? true : sequences.begin()->terms.empty(); }
    void inject_attr(Attr a_a) { inject = a_a; }
    Rule &new_sequence();
    Rule &operator|(Rule *_r);
    //Rule& operator |(const char*   _t);
    Rule &operator|(Lsc::Type::T _t);
    Rule &operator|(Mnemonic _t);

    Seq::const_iterator Begin() const { return sequences.cbegin(); }
    bool End(Seq::const_iterator s) const { return s == sequences.cend(); }
};



class  Grammar
{
public:
    Grammar() = default;
    ~Grammar() = default;
    String &text() { return _Text; }
    Return Build();
    void Dump();

private:
    enum state_mac
    {
        st_begin = 0, ///< about to define new rule: cursor on rule id.
        st_init_rule, ///< initialize sequence of terms: cursor on ':'.
        st_seq,       ///< back and forth between st_seq<->st_init_term.
        st_option,    ///< one of ' *+? ' option state.
        st_init_term, ///< query {rule | type semantic | e_code | litteral} : cursor on identifier.
        st_add_seq,   ///< terminate current sequence and start a new sequence on the rule: cursor on ','.
        st_end_rule   ///< terminate rule : cursor on '.'.
    };

    Attr a = {0, 0, 0, 0, 0}; ///< default : punctual, strict match

    state_mac _state = Grammar::st_begin;
    
    [[maybe_unused]] int Init();
    static Rule::collection _Rules;
    Rule                    *_Rule = nullptr;
    static Rule *QueryRule(const std::string &a_id);

    using RuleScanner = Return (Grammar::*)(String::Iterator &);
    String::Word::Collection tokens;
    String                   _Text;

    using Dictionary = std::map<char, Grammar::RuleScanner>;
    static Dictionary TeaGrammarDictionary;

public:
    const Rule *operator[](const std::string &r_id) const
    {
        return _Rules[r_id];
        //Rule* r = _Rules[r_id]; return (const Rule*)r;
    }

    static bool Built() { return _Rules.size() != 0; }

private:
    Grammar::Dictionary::iterator RuleIt;

    //--------------- Rules builders -------------------

    Return ParseIdentifier(String::Iterator &crs);
    Return EnterRuleDef(String::Iterator &crs);
    Return NewSequence(String::Iterator &crs);
    Return EndRule(String::Iterator &crs);
    Return SetRepeat(String::Iterator &crs);
    Return SetOptional(String::Iterator &crs);
    Return EnterLitteral(String::Iterator &crs);
    Return SetOneof(String::Iterator &crs);
    Return SetDirective(String::Iterator &crs);
};

} // namespace teacc