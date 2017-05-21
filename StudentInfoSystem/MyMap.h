#pragma once

#define DELETED 0
#define FILLED 1

template<typename Tkey, typename Tvalue>
struct MapNode {
    MapNode* m_pLeft;
    MapNode* m_pRight;
    MapNode* m_pParent;
    int m_nSign;
    int m_nBf;
    Tkey m_Key;
    Tvalue m_Value;

    MapNode() {
        m_pLeft = NULL;
        m_pRight = NULL;
        m_pParent = NULL;
        m_nSign = FILLED;
        m_nBf = 0;
    }
    MapNode(Tkey key, Tvalue value) {
        m_pLeft = NULL;
        m_pRight = NULL;
        m_pParent = NULL;
        m_nSign = FILLED;
        m_nBf = 0;
        m_Key = key;
        m_Value = value;
    }
};

template<typename Tkey, typename Tvalue>
class CMyMap {
public:
    CMyMap() {
        m_pRoot = NULL;
    }
    ~CMyMap() {
        (*this).Clear();
    }
    bool InsertNode(Tkey key, Tvalue, value);
    bool DeleteNode(Tkey key);
    bool Find(Tkey key);

    bool Clear();

    Tvalue& operator[](Tkey key);

private:
    MapNode<Tkey, Tvalue>* m_pRoot;
};

template<typename Tkey, typename Tvalue>
bool CMyMap<Tkey, Tvalue>::InsertNode(Tkey key, Tvalue, value) {
    MapNode* pNode = new MapNode(key, value);
    if (m_pRoot == NULL) {
        m_pRoot = pNode;
        return true;
    }

    while (1) {
        if (m_pRoot->m_Key == key) {

        } else if (m_pRoot->m_Key < key) {

        } else {//m_pRoot->m_Key > key

        }
    }
}