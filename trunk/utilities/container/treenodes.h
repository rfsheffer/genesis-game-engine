//
//  util_treenodes.h
//  Common tree node elements
//
//  Created by Ryan Sheffer on 11/15/2013.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_TREE_NODE
#define UTIL_TREE_NODE

#ifdef _WIN
#pragma once
#endif

namespace Utility
{
    //--------------------------------------------------------------------------
    /**
     * A Binary Tree Node. It contains a left path, and a right path.
     */
    template<class T>
    class BinaryTreeNode
    {
    public:
        BinaryTreeNode(BinaryTreeNode *pLeftElm = NULL,
                       BinaryTreeNode *pRightElm = NULL)
        {
            m_pLeft = pLeftElm;
            m_pRight = pRightElm;
        }
        
        T   m_elm;
        
        /** The element at the left */
        BinaryTreeNode   *m_pLeft;
        
        /** The element at the right */
        BinaryTreeNode   *m_pRight;
    };
} // namespace Utility

#endif // UTIL_TREE_NODE
