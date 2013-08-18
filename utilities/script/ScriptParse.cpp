//
//  Lexer.cpp
//  lexandparse
//
//  Created by Ryan Sheffer on 2013-01-17.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "ScriptParse.h"
#include "ASCIITable.h"

namespace ScriptParse
{
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    CScriptLexer::CScriptLexer() :  m_iNumTokens(0),
    m_iErrCode(0),
    m_iCurVariable(0),
    m_iCurOperator(0)
    {
        // Initialize the operator table for referencing later.
        for(int i = 0; i < MAX_NUM_ASCII_CHARACTERS; ++i)
        {
            switch(i)
            {
                case '(':
                    m_operatorTable[i] = LexTokenOperator::OPERATOR_LEFT_BRACKET;
                    continue;
                case ')':
                    m_operatorTable[i] = LexTokenOperator::OPERATOR_RIGHT_BRACKET;
                    continue;
                case '/':
                    m_operatorTable[i] = LexTokenOperator::OPERATOR_DIVISION;
                    continue;
                case '%':
                    m_operatorTable[i] = LexTokenOperator::OPERATOR_MODULO;
                    continue;
                case '*':
                    m_operatorTable[i] = LexTokenOperator::OPERATOR_MULTIPLICATION;
                    continue;
                case '+':
                    m_operatorTable[i] = LexTokenOperator::OPERATOR_ADDITION;
                    continue;
                case '-':
                    m_operatorTable[i] = LexTokenOperator::OPERATOR_SUBTRACTION;
                    continue;
            }
            
            m_operatorTable[i] = LexTokenOperator::NUM_OPERATOR_TYPES;
        }
    }
    
    //--------------------------------------------------------------------------
    // Purpose: Analyzes the passed in string of characters and builds a list of
    // tokens.
    //--------------------------------------------------------------------------
    void CScriptLexer::Analyze(const char *pString)
    {
        int iVarIndex = 0;
        char szVar[32];
        bool bFloatingPoint = false;
        
        while(*pString != ASCII_NULL)
        {
            if(*pString != ASCII_SPACE) // Skip Spaces
            {
                if(m_operatorTable[*pString] == LexTokenOperator::NUM_OPERATOR_TYPES)
                {
                    if(*pString == '.')
                    {
                        bFloatingPoint = true;
                    }
                    
                    // Variable Character
                    szVar[iVarIndex++] = *pString;
                }
                else
                {
                    // Operator Character
                    if(iVarIndex == 0)
                    {
                        m_iErrCode = LEX_ERR_NO_L_OP;
                        break;
                    }
                    
                    // Push the Variable onto the token stack, then the operator
                    if(iVarIndex != 0)
                    {
                        szVar[iVarIndex] = ASCII_NULL;
                        PushVariable(szVar, bFloatingPoint);
                        iVarIndex = 0;
                        bFloatingPoint = false;
                    }
                    
                    PushOperator(pString);
                }
            }
            
            ++pString;
        }
        
        if(iVarIndex != 0)
        {
            szVar[iVarIndex] = ASCII_NULL;
            PushVariable(szVar, bFloatingPoint);
        }
        else
        {
            m_iErrCode = LEX_ERR_NO_R_OP;
        }
    }
    
    //--------------------------------------------------------------------------
    // Purpose: Pushes a variable onto the token stack
    //--------------------------------------------------------------------------
    void CScriptLexer::PushVariable(const char *pszVariable, bool bFloatingPoint)
    {
        // TODO: Determine the variable type
        m_tokenVariables[m_iCurVariable].tokenType = iLexToken::TOKEN_TYPE_VARIABLE;
        m_tokenVariables[m_iCurVariable].varType = LexTokenVariable::VAR_INT;
        
        if(bFloatingPoint)
        {
            m_tokenVariables[m_iCurVariable].val = atof(pszVariable);
        }
        else
        {
            m_tokenVariables[m_iCurVariable].val = atoi(pszVariable);
        }
        
        m_pTokens[m_iNumTokens++] = &m_tokenVariables[m_iCurVariable];
        ++m_iCurVariable;
    }
    
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    CScriptParse::CScriptParse() : m_uiNumOnOperatorStack(0),
                                    m_uiNumInOutput(0)
    {
        
        // UPDATE THIS IF MORE OPERATORS ARE ADDED!
        // Numbers from:
        // http://en.cppreference.com/w/cpp/language/operator_precedence
        
        m_uiOpLevels[LexTokenOperator::OPERATOR_SUBTRACTION] = 6;
        m_uiOpLevels[LexTokenOperator::OPERATOR_ADDITION] = 6;
        
        m_uiOpLevels[LexTokenOperator::OPERATOR_DIVISION] = 5;
        m_uiOpLevels[LexTokenOperator::OPERATOR_MODULO] = 5;
        m_uiOpLevels[LexTokenOperator::OPERATOR_MULTIPLICATION] = 5;
        
        m_uiOpLevels[LexTokenOperator::OPERATOR_RIGHT_BRACKET] = 2;
        m_uiOpLevels[LexTokenOperator::OPERATOR_LEFT_BRACKET] = 2;
    }
    
    //--------------------------------------------------------------------------
    // Purpose: Parses a Lexigraphically sorted list of tokens into reverse polish
    // notation.
    //--------------------------------------------------------------------------
    void CScriptParse::Parse(iLexToken **pTokens, unsigned int numTokens)
    {
        iLexToken *pCurToken;
        
        for(unsigned int i = 0; i < numTokens; ++i)
        {
            pCurToken = pTokens[i];
            
            // If it's a variable, put it on the output right away
            if(pCurToken->tokenType == iLexToken::TOKEN_TYPE_VARIABLE)
            {
                AddTokenToOutput(pCurToken);
                //printf("Adding Variable to OUT\n");
                continue;
            }
            else if(pCurToken->tokenType == iLexToken::TOKEN_TYPE_OPERATOR)
            {
                AddTokenToOperatorStack(pCurToken);
                continue;
            }
        }
        
        // Put the last of the operators on the outputs
        for(int i = m_uiNumOnOperatorStack - 1; i >= 0; --i)
        {
            AddTokenToOutput(m_pOperatorStack[i]);
            //printf("Adding Operator to OUT\n");
        }
    }
    
#   define OPLEVEL(opType)    m_uiOpLevels[opType]
    
    //--------------------------------------------------------------------------
    // Purpose: Adds the operator to the stack. If the operator being added has
    // less presedence than the operator on the top of the operator stack, then
    // the operator on the top of the stack gets put onto the output.
    //--------------------------------------------------------------------------
    void CScriptParse::AddTokenToOperatorStack(iLexToken *pToken)
    {
        LexTokenOperator *pOpToken = static_cast<LexTokenOperator*>(pToken);
        
        // Determine which operators should be popped off the stack before adding
        // the new operator.
        while(m_uiNumOnOperatorStack != 0)
        {
            if(OPLEVEL(pOpToken->opType) >=
               OPLEVEL(m_pOperatorStack[m_uiNumOnOperatorStack - 1]->opType))
            {
                AddTokenToOutput(m_pOperatorStack[--m_uiNumOnOperatorStack]);
                //printf("Adding Operator to OUT\n");
            }
            else
            {
                break;
            }
        }
        
        // Add the new operator to the stack
        m_pOperatorStack[m_uiNumOnOperatorStack++] = pOpToken;
    }
    
    //--------------------------------------------------------------------------
    // Purpose: Outputs the postfix to the standard output
    //--------------------------------------------------------------------------
    void CScriptParse::PrintOutput(void)
    {
        printf("Postfix Out:");
        
        iLexToken *pCurToken;
        
        for(unsigned int i = 0; i < m_uiNumInOutput; ++i)
        {
            pCurToken = m_pOutput[i];
            
            if(pCurToken->tokenType == iLexToken::TOKEN_TYPE_VARIABLE)
            {
                LexTokenVariable *pVar = static_cast<LexTokenVariable *>(pCurToken);
                
                printf(" %f ", pVar->val);
            }
            else if(pCurToken->tokenType == iLexToken::TOKEN_TYPE_OPERATOR)
            {
                LexTokenOperator *pOp = static_cast<LexTokenOperator *>(pCurToken);
                
                printf(" %c ", pOp->letter);
            }
        }
        
        printf("\n");
    }
    
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
    CPostfixEvaluate::CPostfixEvaluate() : m_uiNumOnVariableStack(0),
                                            m_flOutput(0.0f)
    {
        
    }
    
    //--------------------------------------------------------------------------
    // Purpose: Evaluates a Postfix expression stack and outputs the answer
    //--------------------------------------------------------------------------
    float CPostfixEvaluate::Evaluate(iLexToken **pTokens, unsigned int numTokens)
    {
        iLexToken *pCurToken;
        
        for(unsigned int i = 0; i < numTokens; ++i)
        {
            pCurToken = pTokens[i];
            
            // If it's a variable, put it on the output right away
            if(pCurToken->tokenType == iLexToken::TOKEN_TYPE_VARIABLE)
            {
                PushToVariableStack(static_cast<LexTokenVariable *>(pCurToken));
                continue;
            }
            else if(pCurToken->tokenType == iLexToken::TOKEN_TYPE_OPERATOR)
            {
                EvaluateOperator(pCurToken);
                continue;
            }
        }
        
        // Push the last operator
        return m_pVariableStack[--m_uiNumOnVariableStack]->val;
    }
    
    //--------------------------------------------------------------------------
    // Purpose: Operators. Add more as needed.
    //--------------------------------------------------------------------------
    float TokenSubtract(LexTokenVariable *pV1, LexTokenVariable *pV2)
    {
        return pV1->val - pV2->val;
    }
    
    float TokenAdd(LexTokenVariable *pV1, LexTokenVariable *pV2)
    {
        return pV1->val + pV2->val;
    }
    
    float TokenMultiply(LexTokenVariable *pV1, LexTokenVariable *pV2)
    {
        return pV1->val * pV2->val;
    }
    
    float TokenModulo(LexTokenVariable *pV1, LexTokenVariable *pV2)
    {
        return (int)pV1->val % (int)pV2->val;
    }
    
    float TokenDivide(LexTokenVariable *pV1, LexTokenVariable *pV2)
    {
        return pV1->val / pV2->val;
    }
    
    float (*fEvalFunc[])(LexTokenVariable *, LexTokenVariable *) =
    {TokenSubtract, TokenAdd, TokenDivide, TokenModulo, TokenMultiply};
    
    //--------------------------------------------------------------------------
    // Purpose: Evaluates an operator token with the last two variables on the
    // variable stack.
    //--------------------------------------------------------------------------
    inline void CPostfixEvaluate::EvaluateOperator(iLexToken *pToken)
    {
        LexTokenOperator *pOpToken = static_cast<LexTokenOperator*>(pToken);
        
        LexTokenVariable *pV1 = PopVariableStack();
        LexTokenVariable *pV2 = PopVariableStack();
        
        float output = fEvalFunc[pOpToken->opType](pV2, pV1);
        
        // Reuse one of the variables to pop back onto the stack
        pV2->val = output;
        PushToVariableStack(pV2);
    }
}