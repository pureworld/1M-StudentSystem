#pragma once
template <typename T>
struct QueueNode {
    QueueNode<T>* next;
    T data;
};

template<typename T>
class CMyQueue {
public:
    CMyQueue() {
        head = NULL;
    }
    ~CMyQueue() {
        if (head != NULL) {
            pop();
        }
    }

    void push(T _data) {
        if (empty()) {
            head = new QueueNode<T>();
            head->data = _data;
            head->next = NULL;
            return;
        }
        QueueNode<T>* pTmp = new QueueNode<T>;
        pTmp->data = _data;
        pTmp->next = head;
        head = pTmp;
        return;
    }

    void pop() {
        if (head->next == NULL) {
            head = NULL;
            return;
        }
        QueueNode<T>* pTmp = new QueueNode<T>();
        pTmp = head;
        while (pTmp->next->next != NULL) {
            pTmp = pTmp->next;
        }
        pTmp->next = NULL;
        return;
    }

    T& front() {
        QueueNode<T>* pTmp = new QueueNode<T>();
        pTmp = head;
        while (pTmp->next != NULL) {
            pTmp = pTmp->next;
        }
        return pTmp->data;
    }

    T& back() {
       return head->data;
    }

    int size() {
        QueueNode<T>* pTmp = new QueueNode<T>();
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
    QueueNode<T>* head;
};
