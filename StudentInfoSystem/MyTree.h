#pragma once
#include "MyStack.h"
#include "MyString.h"

#define DELETED 0
#define FILLED 1

template<typename Tkey, typename Tvalue>
struct TreeNode {
    TreeNode* m_pLeft;
    TreeNode* m_pRight;
    TreeNode* m_pParent;
    TreeNode* m_pNext;
    int m_nSign;
    int m_nHeight;
    Tkey m_Key;
    Tvalue m_Value;

    TreeNode() {
        m_pLeft = NULL;
        m_pRight = NULL;
        m_pParent = NULL;
        m_pNext = NULL;
        m_nSign = FILLED;
        m_nHeight = 0;
    }
    TreeNode(Tkey key, Tvalue value) {
        m_pLeft = NULL;
        m_pRight = NULL;
        m_pParent = NULL;
        m_pNext = NULL;
        m_nSign = FILLED;
        m_nHeight = 0;
        m_Key = key;
        m_Value = value;
    }
};

template<typename Tkey, typename Tvalue>
class CMyTree {
public:
    CMyTree() {
        m_pRoot = NULL;
        m_nNodeSize = 0;
        m_nSize = 0;
    }
    ~CMyTree() {
        (*this).Clear();
    }

    bool InsertNode(Tkey key, Tvalue value);

    bool DeleteNode(Tkey key, Tvalue value);

    TreeNode<Tkey, Tvalue>* Find(Tkey key);
    TreeNode<Tkey, Tvalue>* Find(Tkey key, Tvalue value);
    bool Clear();

    void OutputFile(CMyString);

private:
    void Balance(TreeNode<Tkey, Tvalue>* pNode);
    bool Destroy(TreeNode<Tkey, Tvalue>* pNode);
    void RightRotate(TreeNode<Tkey, Tvalue>* pNode);
    void LeftRotate(TreeNode<Tkey, Tvalue>* pNode);

    int  GetHeight(TreeNode<Tkey, Tvalue>* pNode) {
            return (pNode == NULL)? 0 : pNode->m_nHeight;
    }

    TreeNode<Tkey, Tvalue>* m_pRoot;
    int m_nNodeSize;    //树节点数量
    int m_nSize;        //<key,value>数量，若key有重复可能比树节点多
};

template<typename Tkey, typename Tvalue>
bool CMyTree<Tkey, Tvalue>::InsertNode(Tkey key, Tvalue value) {
    TreeNode<Tkey, Tvalue>* pNode = new TreeNode<Tkey, Tvalue>(key, value);
    if (m_pRoot == NULL) {
        m_pRoot = pNode;
        m_nNodeSize++;
        m_nSize++;
        return true;
    }

    TreeNode<Tkey, Tvalue>* pCur = m_pRoot;
    while (true) {
        if (pCur->m_Key == key) {
            //相同键则挂链表
            while (true) {
                if (pCur->m_pNext == NULL) {
                    pCur->m_pNext = pNode;
                    break;
                } else {
                    pCur = pCur->m_pNext;
                }
            }
            pNode->m_pParent = pCur;
            m_nSize++;
            break;

        } else if (key < pCur->m_Key) {
            if (pCur->m_pLeft == NULL) {
                pCur->m_pLeft = pNode;
                m_nNodeSize++;
            } else {
                pCur = pCur->m_pLeft;
                continue;
            }
        } else {//key > pCur->m_Key
            if (pCur->m_pRight == NULL) {
                pCur->m_pRight = pNode;
                m_nNodeSize++;
            } else {
                pCur = pCur->m_pRight;
                continue;
            }
        }

        pNode->m_pParent = pCur;
        m_nSize++;

        Balance(pNode);

        return true;
    }

    return false;
}

template<typename Tkey, typename Tvalue>
bool CMyTree<Tkey, Tvalue>::DeleteNode(Tkey key, Tvalue value) {
    TreeNode<Tkey, Tvalue>* pFindNode = Find(key);
    TreeNode<Tkey, Tvalue>* pFind = Find(key, value);
    if (pFind == NULL) {
        return false;
    }
    //要删的节点在链表中
    //为链表头
    if ((pFind == pFindNode) && pFind->m_pNext != NULL) {
        TreeNode<Tkey, Tvalue>* pParent = pFind->m_pParent;
        TreeNode<Tkey, Tvalue>* pNext = pFind->m_pNext;
        if (pFind == pParent->m_pLeft) {
            pParent->m_pLeft = pNext;
        } else if (pFind == pParent->m_pRight) {
            pParent->m_pRight = pNext;
        }
        pNext->m_pParent = pParent;
        pNext->m_pLeft = pFind->m_pLeft;
        pNext->m_pRight = pFind->m_pRight;
        m_nSize--;
        return true;
    }
    //为链表尾
    if ((pFind != pFindNode) && pFind->m_pNext == NULL) {
        pFind->m_pParent->m_pNext = NULL;
        m_nSize--;
        return true;
    }
    //链表中间
    if (pFind != pFindNode) {
        pFind->m_pParent->m_pNext = pFind->m_pNext;
        m_nSize--;
        return true;
    }

    //要删的节点只有节点，链表为空
    //只有根节点
    if (m_pRoot->m_Key == key && m_nNodeSize == 1) {
        m_pRoot = NULL;
        m_nSize--;
        m_nNodeSize--;
        return true;
    }

    //删除叶子节点
    if (pFind->m_pLeft == NULL && pFind->m_pRight == NULL) {
        TreeNode<Tkey, Tvalue>* pParent = pFind->m_pParent;
        if (pFind == pParent->m_pLeft) {
            pParent->m_pLeft = NULL;
        } else {// pFind == pParent->m_pRight
            pParent->m_pRight = NULL;
        }
    } else
        //删除两个孩子的节点
        if (pFind->m_pLeft != NULL && pFind->m_pRight != NULL) {
            //找左边最大值 交换后删除
            TreeNode<Tkey, Tvalue>* pTmp = pFind->m_pLeft;
            while (pTmp->m_pRight) {
                pTmp = pTmp->m_pRight;
            }

            TreeNode<Tkey, Tvalue>* pParent = pTmp->m_pParent;

            pFind->m_Key = pTmp->m_Key;
            pFind->m_Value = pTmp->m_Value;

            if (pTmp == pParent->m_pLeft) {
                pParent->m_pLeft = pTmp->m_pLeft;
                if (pParent->m_pLeft != NULL) {
                    pParent->m_pLeft->m_pParent = pParent;
                }
            } else if (pTmp == pParent->m_pRight) {
                pParent->m_pRight = pTmp->m_pLeft;
                if (pParent->m_pRight != NULL) {
                    pParent->m_pRight->m_pParent = pParent;
                }
            }
        } else
            //删除一个孩子的节点
            if (pFind->m_pLeft != NULL) {
                TreeNode<Tkey, Tvalue>* pParent = pFind->m_pParent;
                if (pParent == NULL) {
                    m_pRoot = pFind->m_pLeft;
                    m_pRoot->m_pParent = NULL;
                } else if (pFind == pParent->m_pLeft) {
                    pParent->m_pLeft = pFind->m_pLeft;
                    pParent->m_pLeft->m_pParent = pParent;
                } else {// pFind == pParent->m_pRight
                    pParent->m_pRight = pFind->m_pLeft;
                    pParent->m_pRight->m_pParent = pParent;
                }
            } else {// pFind->m_pRight != NULL
                TreeNode<Tkey, Tvalue>* pParent = pFind->m_pParent;
                if (pParent == NULL) {
                    m_pRoot = pFind->m_pRight;
                    m_pRoot->m_pParent = NULL;
                } else if (pFind == pParent->m_pLeft) {
                    pParent->m_pLeft = pFind->m_pRight;
                    pParent->m_pLeft->m_pParent = pParent;
                } else {// pFind == pParent->m_pRight
                    pParent->m_pRight = pFind->m_pRight;
                    pParent->m_pRight->m_pParent = pParent;
                }
            }

            Balance(pFind->m_pParent);
            m_nNodeSize--;
            m_nSize--;

            return true;
}

template<typename Tkey, typename Tvalue>
TreeNode<Tkey, Tvalue>* CMyTree<Tkey, Tvalue>::Find(Tkey key) {
    if (m_pRoot == NULL) {
        return NULL;
    }

    TreeNode<Tkey, Tvalue>* pCur = m_pRoot;
    while (true) {
        if (key == pCur->m_Key) {
            return pCur;
        } else if (key < pCur->m_Key) {
            if (pCur->m_pLeft == NULL) {
                break;
            }
            pCur = pCur->m_pLeft;
        } else {
            if (pCur->m_pRight == NULL) {
                break;
            }
            pCur = pCur->m_pRight;
        }
    }

    return NULL;
}

template<typename Tkey, typename Tvalue>
TreeNode<Tkey, Tvalue>* CMyTree<Tkey, Tvalue>::Find(Tkey key, Tvalue value) {
    TreeNode<Tkey, Tvalue>* pCur = Find(key);
    if (pCur == NULL) {
        return NULL;
    }
    while (pCur != NULL) {
        if (pCur->m_Value == value) {
            return pCur;
        } else {
            pCur = pCur->m_pNext;
        }
    }
    return NULL;
}

template<typename Tkey, typename Tvalue>
bool CMyTree<Tkey, Tvalue>::Clear() {
    return Destroy(m_pRoot);
}

template<typename Tkey, typename Tvalue>
bool CMyTree<Tkey, Tvalue>::Destroy(TreeNode<Tkey, Tvalue>* pNode) {
    if (pNode) {
        Destroy(pNode->m_pLeft);
        Destroy(pNode->m_pRight);
        delete pNode;
        pNode = NULL;
    }
    return true;
}

template<typename Tkey, typename Tvalue>
void CMyTree<Tkey, Tvalue>::Balance(TreeNode<Tkey, Tvalue>* pNode) { 
    while (pNode != NULL){
        int nLeftH = GetHeight(pNode->m_pLeft);
        int nRightH = GetHeight(pNode->m_pRight);
        pNode->m_nHeight = max(nLeftH, nRightH) + 1;

        int nBf = nLeftH - nRightH;

        TreeNode<Tkey, Tvalue>* pK1 = NULL;
        TreeNode<Tkey, Tvalue>* pK2 = NULL;
        TreeNode<Tkey, Tvalue>* pK3 = NULL;

        if (nBf >= 2 ||  nBf <= -2) {
            pK1 = pNode;
            if (nBf > 0) {
                pK2 = pK1->m_pLeft;
            } else {
                pK2 = pK1->m_pRight;
            }

            if (GetHeight(pK2->m_pLeft) - GetHeight(pK2->m_pRight) > 0) {
                pK3 = pK2->m_pLeft;
            } else {
                pK3 = pK2->m_pRight;
            }

            //四种情况
            if (pK2 == pK1->m_pLeft && pK3 == pK2->m_pLeft) {
                RightRotate(pK1);
            } else if (pK2 == pK1->m_pRight && pK3 == pK2->m_pRight) {
                LeftRotate(pK1);
            } else if (pK2 == pK1->m_pRight && pK3 == pK2->m_pLeft) {
                RightRotate(pK2);
                LeftRotate(pK1);
            } else if (pK2 == pK1->m_pLeft && pK3 == pK2->m_pRight) {
                LeftRotate(pK2);
                RightRotate(pK1);
            }
        }

        pNode = pNode->m_pParent;
    }

    return;
}

template<typename Tkey, typename Tvalue>
void CMyTree<Tkey, Tvalue>::RightRotate(TreeNode<Tkey, Tvalue>* pNode) {
    TreeNode<Tkey, Tvalue>* pG = pNode->m_pParent;
    TreeNode<Tkey, Tvalue>* pK = pNode->m_pLeft;
    TreeNode<Tkey, Tvalue>* pA = pK->m_pLeft;
    TreeNode<Tkey, Tvalue>* pB = pK->m_pRight;
    TreeNode<Tkey, Tvalue>* pC = pNode->m_pRight;

    if (pG == NULL) {
        m_pRoot = pNode->m_pLeft;
    } else {
        if (pG->m_pLeft == pNode) {
            pG->m_pLeft = pK;
        } else {
            pG->m_pRight = pK;
        }
    }

    pNode->m_pLeft = pB;
    pNode->m_pParent = pK;

    pK->m_pParent = pG;
    pK->m_pRight = pNode;

    if (pB != NULL) {
        pB->m_pParent = pNode;
    }

    pNode->m_nHeight = max(GetHeight(pB), GetHeight(pC)) + 1;
    pK->m_nHeight = max(GetHeight(pA), GetHeight(pNode)) + 1;
}

template<typename Tkey, typename Tvalue>
void CMyTree<Tkey, Tvalue>::LeftRotate(TreeNode<Tkey, Tvalue>* pNode) {
    TreeNode<Tkey, Tvalue>* pG = pNode->m_pParent;
    TreeNode<Tkey, Tvalue>* pK = pNode->m_pRight;
    TreeNode<Tkey, Tvalue>* pA = pK->m_pLeft;
    TreeNode<Tkey, Tvalue>* pB = pK->m_pRight;
    TreeNode<Tkey, Tvalue>* pC = pNode->m_pLeft;

    if (pG == NULL) {
        m_pRoot = pK;
    } else {
        if (pG->m_pLeft == pNode) {
            pG->m_pLeft = pK;
        } else {
            pG->m_pRight = pK;
        }
    }

    pNode->m_pRight = pA;
    pNode->m_pParent = pK;

    pK->m_pParent = pG;
    pK->m_pLeft = pNode;

    if (pA != NULL) {
        pA->m_pParent = pNode;
    }

    pNode->m_nHeight = max(GetHeight(pA), GetHeight(pC)) + 1;
    pK->m_nHeight = max(GetHeight(pB), GetHeight(pNode)) + 1;
}

template<typename Tkey, typename Tvalue>
void CMyTree<Tkey, Tvalue>::OutputFile(CMyString path) {
    ofstream out(path.GetStr(), ios::out | ios::binary);
    //FILE* file = fopen(path.GetStr(), "rb+");
    TreeNode<Tkey, Tvalue>* pCur = m_pRoot;
    CMyStack<TreeNode<Tkey, Tvalue>*> s;
    if (out.is_open()) {
        while (1) {
            if (pCur != NULL) {
                s.push(pCur);
                while (pCur->m_pLeft != NULL) {
                    s.push(pCur->m_pLeft);
                    pCur = pCur->m_pLeft;
                }
            }

            pCur = s.top();
            s.pop();

            TreeNode<Tkey, Tvalue>* pToFile = pCur;
            
            while (pToFile != NULL) {
                out << pToFile->m_Value << endl;
                pToFile = pToFile->m_pNext;
            }

            if (pCur->m_pRight == NULL && s.empty()) {
                return;
            }

            pCur = pCur->m_pRight;
        }
    }
}
