#pragma once

#ifndef NULL
#define NULL 0
#endif

template <typename T>
struct StackNode {
    StackNode<T>* next;
    T data;
};

template <typename T>
class CMyStack {
public:
    CMyStack() {
        head = NULL;
    }

    ~CMyStack(){
        while(head != NULL) {
            pop();
        }
    }
    
    void push(T _data) {
        if (head == NULL) {
            head = new StackNode<T>;
            head->data = _data;
            head->next = NULL;
            return;
        }
        StackNode<T>* pTmp = new StackNode<T>;
        pTmp->data = _data;
        pTmp->next = head;
        head = pTmp;
        return;
    }

    void pop() {
        head = head->next;
    }

    T& top() {
        return head->data;
    }

    int size() {
        StackNode<T>* pTmp = new StackNode<T>;
        pTmp = head;
        int nCnt = 0;
        while (pTmp != NULL) {
            pTmp = pTmp->next;
            nCnt++;
        }
        return nCnt;
    }

    bool empty() {
        return head == NULL;
    }
private:
    StackNode<T>* head;
};

