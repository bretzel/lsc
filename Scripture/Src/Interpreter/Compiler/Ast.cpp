//
// Created by slussier on 21-01-02.
//

#include <Lsc/Scripture/Interpreter/Compiler/Ast.h>



namespace Lsc::Ast
{
/*
         a = 32 * (2+3) / 4;
                    =           =               =              =              =            =              =               = <---+           =
                   / \         / \             / \            / \            / \          / \            / \             / \    |          / \
                  a  [/]      a   *  <- (     a   *          a   *          a   *        a   *          a   *           a   * <-|         a   /
                     /  \        /               / \            / \            / \          / \            / \             / \  |            / \
                    *    4 ;    32              32  ( <- 2     32  (          32  (        32 ( <--+      32  ) <- /      32  + /           *   4;
                   / \                                            /              /           /     |         /               / \           / \
                  32  +                                          2 <- +         + <- 3      +      |        +               2   3         32  +
                     / \                                                       /           / \     +       / \                               / \
                    2   3                                                     2           2   3 <- )      2   3                             2   3
                    
// Arithmetic Binary Tree: associative building logic table:
Node::InputTable      Node::_InputTable = {

    {{Lsc::Type::binary,   Lsc::Type::leftpar},   &xio::tree_set_right},
    {{Lsc::Type::leftpar,  Lsc::Type::leaf},      &xio::tree_set_left},
    {{Lsc::Type::leftpar,  Lsc::Type::prefix},    &xio::tree_set_left},
    {{Lsc::Type::leftpar,  Lsc::Type::binary},    &xio::tree_set_left},
    {{Lsc::Type::prefix,   Lsc::Type::leftpar},   &xio::tree_set_right},
    {{Lsc::Type::closepar,  Lsc::Type::leaf},     &xio::tree_rpar_input_leaf},
    {{Lsc::Type::closepar,  Lsc::Type::binary},   &xio::tree_close_par},
    {{Lsc::Type::closepar,  Lsc::Type::postfix},  &xio::tree_close_par},
    {{Lsc::Type::closepar,  Lsc::Type::closepar}, &xio::tree_rpar_rpar},

    {{Lsc::Type::prefix,   Lsc::Type::closepar},  &xio::tree_input_rpar},
    {{Lsc::Type::leaf,     Lsc::Type::closepar},  &xio::tree_input_rpar},
    {{Lsc::Type::leaf,     Lsc::Type::postfix},   &xio::tree_set_right_to_op},
    {{Lsc::Type::leaf,     Lsc::Type::assign},    &xio::tree_input_binary},


    {{Lsc::Type::postfix,  Lsc::Type::closepar},  &xio::tree_input_rpar},
    {{Lsc::Type::leftpar,  Lsc::Type::binary},    &xio::tree_set_left},
    {{Lsc::Type::leaf,     Lsc::Type::binary},    &xio::tree_input_binary},
    {{Lsc::Type::binary,   Lsc::Type::binary},    &xio::tree_input_binary},
    {{Lsc::Type::binary,   Lsc::Type::leaf},      &xio::tree_set_right},
    {{Lsc::Type::prefix,   Lsc::Type::binary},    &xio::tree_input_binary},
    {{Lsc::Type::binary,   Lsc::Type::prefix},    &xio::tree_set_right},
    {{Lsc::Type::prefix,   Lsc::Type::leaf},      &xio::tree_set_right},
    {{Lsc::Type::prefix,   Lsc::Type::number},    &xio::tree_set_right},
    {{Lsc::Type::sign,     Lsc::Type::id},        &xio::tree_set_right},
    {{Lsc::Type::sign,     Lsc::Type::number},    &xio::tree_set_right},
    {{Lsc::Type::sign,     Lsc::Type::leaf},      &xio::tree_set_right},
    {{Lsc::Type::postfix,  Lsc::Type::binary},    &xio::tree_input_binary},

    {{Lsc::Type::assign,   Lsc::Type::binary},    &xio::tree_set_right},
    {{Lsc::Type::assign,   Lsc::Type::leaf},      &xio::tree_set_right},
    {{Lsc::Type::assign,   Lsc::Type::prefix},    &xio::tree_set_right},
    {{Lsc::Type::assign,   Lsc::Type::postfix},   &xio::tree_set_right}

};
 */

Return Node::Input(TokenData *Token_, Node::Maker Maker_)
{
/*
    inptr_fn_t pfn = nullptr;
    for(auto key : xio::tree_input_assoc_table)
    {
        if((key.first.first & t0->s) && (a_token->s & key.first.second))
        {
            logdebugfn << logger::White
                     << "'" << logger::Yellow
                     << t0->attribute()
                     << logger::White  << "' - Key:"
                     << logger::Yellow << lexer::type::to_s(key.first.first)
                     << logger::White  << " <=> "
                     << logger::Blue  << __FUNCTION__
                     << logger::White  << ":'"
                     << logger::Yellow << a_token->attribute()
                     << logger::White  << "' - Key:"
                     << logger::Yellow << lexer::type::to_s(key.first.second)
                     << logger::White  << ":"
                     << Ends;

            pfn = key.second;
            break;
        }
    }
    if (pfn)
        return (this->*pfn)(invoke_maker(a_token));

    return
        {(
             utils::notification::push(utils::notification::type::error),
                 ":(debug): syntax error, unexpected token:",
                 a_token->attribute(),
                 "\n",
                 a_token->mark()
         )};
*/
}
}