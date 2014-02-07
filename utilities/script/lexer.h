//
//  Lexer.h
//  lexandparse
//
//  Created by Ryan Sheffer on 2013-01-17.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef LEXER_H
#define LEXER_H

namespace ScriptParse
{
    // Defines how many ASCII characters are usable
#define MAX_NUM_ASCII_CHARACTERS        128
    
    // Maximums for strings
#define MAX_NUM_VARIABLES               16
#define MAX_NUM_OPERATORS               16
    
    //--------------------------------------------------------------------------
    // Base Token
    //--------------------------------------------------------------------------
    struct iLexToken
    {
        enum token_type
        {
            TOKEN_TYPE_VARIABLE,
            TOKEN_TYPE_OPERATOR,
            
            NUM_TOKEN_TYPES
        };
        
        token_type          tokenType;
    };
    
    //--------------------------------------------------------------------------
    // Variable Token
    //--------------------------------------------------------------------------
    struct LexTokenVariable : public iLexToken
    {
        enum variable_type
        {
            VAR_INT,
            VAR_FLOAT,
            
            NUM_VAR_TYPES
        };
        
        variable_type       varType;
        
        //temp
        float         val;
    };
    
    //--------------------------------------------------------------------------
    // Operator Token
    //--------------------------------------------------------------------------
    struct LexTokenOperator : public iLexToken
    {
        enum operator_type
        {
            // Level 6
            OPERATOR_SUBTRACTION,
            OPERATOR_ADDITION,
            
            // Level 5
            OPERATOR_DIVISION,
            OPERATOR_MODULO,
            OPERATOR_MULTIPLICATION,
            
            // Level 2
            OPERATOR_RIGHT_BRACKET,
            OPERATOR_LEFT_BRACKET,
            
            NUM_OPERATOR_TYPES
        };
        
        operator_type       opType;
        char                letter;
    };
    
    //--------------------------------------------------------------------------
    // Lexigraphical Analysis of a script
    //--------------------------------------------------------------------------
    class CScriptLexer
    {
    public:
        
        enum lexer_error_codes
        {
            LEX_ERR_NONE,
            LEX_ERR_NO_L_OP,
            LEX_ERR_NO_R_OP,
        };
        
        CScriptLexer();
        
        void                    Analyze(const char *pString);
        
        inline unsigned int     GetNumTokens(void) const { return m_iNumTokens; }
        
        inline iLexToken        **GetTokens(void){ return m_pTokens; }
        
        unsigned int            m_iErrCode;
        
    private:
        
        void                    PushVariable(const char *pszVariable, bool bFloatingPoint);
        inline void             PushOperator(const char *pOperator);
        
        unsigned int            m_iNumTokens;
        iLexToken               *m_pTokens[MAX_NUM_VARIABLES + MAX_NUM_OPERATORS];
        
        unsigned int            m_iCurVariable;
        LexTokenVariable        m_tokenVariables[MAX_NUM_VARIABLES];
        
        unsigned int            m_iCurOperator;
        LexTokenOperator        m_tokenOperators[MAX_NUM_OPERATORS];
        
        LexTokenOperator::operator_type    m_operatorTable[MAX_NUM_ASCII_CHARACTERS];
    };
    
    //--------------------------------------------------------------------------
    // Purpose: Pushes an operator onto the token stack
    //--------------------------------------------------------------------------
    inline void CScriptLexer::PushOperator(const char *pOperator)
    {
        m_tokenOperators[m_iCurOperator].tokenType = iLexToken::TOKEN_TYPE_OPERATOR;
        m_tokenOperators[m_iCurOperator].opType = m_operatorTable[*pOperator];
        m_tokenOperators[m_iCurOperator].letter = *pOperator;
        m_pTokens[m_iNumTokens++] = &m_tokenOperators[m_iCurOperator];
        ++m_iCurOperator;
    }
    
#define MAX_OPERATOR_STACK      10
    
    //--------------------------------------------------------------------------
    // Parses a lexigraphically sorted list of tokens, and outputs a list of
    // tokens in reverse polish notation.
    //--------------------------------------------------------------------------
    class CScriptParse
    {
    public:
        CScriptParse();
        
        void                    Parse(iLexToken **pTokens, unsigned int numTokens);
        
        inline iLexToken        **GetOutput(void){ return m_pOutput; }
        inline unsigned int     GetNumOutput(void) const { return m_uiNumInOutput; }
        
        void                    PrintOutput(void);
        
    private:
        
        inline void             AddTokenToOutput(iLexToken *pToken)
        {
            m_pOutput[m_uiNumInOutput++] = pToken;
        }
        
        void                    AddTokenToOperatorStack(iLexToken *pToken);
        
        unsigned int            m_uiNumOnOperatorStack;
        LexTokenOperator        *m_pOperatorStack[MAX_OPERATOR_STACK];
        
        unsigned int            m_uiNumInOutput;
        iLexToken               *m_pOutput[MAX_NUM_VARIABLES + MAX_NUM_OPERATORS];
        
        unsigned int            m_uiOpLevels[LexTokenOperator::NUM_OPERATOR_TYPES];
    };
    
    //--------------------------------------------------------------------------
    // Evaluates a Postfix expression
    //--------------------------------------------------------------------------
    class CPostfixEvaluate
    {
    public:
        
        CPostfixEvaluate();
        
        float           Evaluate(iLexToken **pTokens, unsigned int numTokens);
        
    private:
        
        inline void             EvaluateOperator(iLexToken *pToken);
        
        inline void             PushToVariableStack(LexTokenVariable *pToken)
        {
            //printf("push %f to stack\n", pToken->val);
            m_pVariableStack[m_uiNumOnVariableStack++] = pToken;
        }
        
        inline LexTokenVariable *PopVariableStack(void)
        {
            //printf("pop %f from stack\n", m_pVariableStack[m_uiNumOnVariableStack - 1]->val);
            return m_pVariableStack[--m_uiNumOnVariableStack];
        }
        
        unsigned int            m_uiNumOnVariableStack;
        LexTokenVariable        *m_pVariableStack[MAX_NUM_VARIABLES];
        
        float                   m_flOutput;
    };
    
} // ScriptParse

#endif // LEXER_H
