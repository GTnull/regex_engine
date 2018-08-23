#include <iostream>
#include <stack>
#include <string>

#include "dfa.hpp"
#include "edge.hpp"
#include "vertex.hpp"
using namespace std;

template <class T>
LinkStack<T>::LinkStack() {
    top = NULL;
}

template <class T>
LinkStack<T>::~LinkStack() {
    Clear();
}

template <class T>
bool LinkStack<T>::IsEmpty() {
    return (!top);
}

template <class T>
int LinkStack<T>::Length() {
    StackNode<T>* temp = top;
    int len = 0;
    while (temp) {
        temp = temp->next;
        len++;
    }
    return len;
}

template <class T>
void LinkStack<T>::Push(const T& item) {
    top = new StackNode<T>(item, top);
}

template <class T>
T LinkStack<T>::Pop() {
    if (!IsEmpty()) {
        StackNode<T>* temp = top;
        top = top->next;
        T value = temp->data;
        delete temp;
        return value;
    } else {
        cout << "The stack is empty" << endl;
        exit(1);
    }
}

template <class T>
T LinkStack<T>::GetTop() {
    if (!IsEmpty()) {
        return top->data;
    } else {
        cout << "The stack is empty" << endl;
        exit(1);
    }
}

template <class T>
void LinkStack<T>::Clear() {
    StackNode<T>* temp;
    while (top) {
        temp = top;
        top = top->next;
        delete temp;
    }
}

DFA::DFA() {
    regex_ = new char[127];
    regexPost_ = new char[127];
    edgeNum_ = new char[127];
    edgeNumber_ = 0;
    dfaStatesNumber_ = 0;
    nfaStatesNumber_ = 0;

    nfaTable_ = new AdjacentTable();
    dfaTable_ = new AdjacentTable();
}

DFA::~DFA() {
    delete[] regex_;
    delete[] regexPost_;
    delete[] edgeNum_;

    nfaTable_->Clear();
    dfaTable_->Clear();
    delete nfaTable_;
    delete dfaTable_;
}

void DFA::InputRegex() {
    cout << "1. please enter regular expression:" << endl;
    cin.getline(regex_, 127);
}

void DFA::InsertNode() {
    int i = 0, j, len = int(strlen(regex_));
    int length = len;
    len--;

    while (len--) {
        if (((regex_[i] != '(' && regex_[i] != '.' && regex_[i] != '|') ||
             regex_[i] == ')' || regex_[i] == '*') &&
            (regex_[i + 1] != ')' && regex_[i + 1] != '.' &&
             regex_[i + 1] != '|' && regex_[i + 1] != '*')) {
            for (j = length; j > i; j--) {
                regex_[j + 1] = regex_[j];
            }
            regex_[i + 1] = '.';
            length++;
            regex_[length] = '\0';
            i++;
        }
        i++;
    }

    cout << endl;
    cout << "Regular expression:" << endl;
    cout << regex_ << endl;
    cout << "String length: " << length << endl;
}

int DFA::Precedence(char symbol) {
    int priority;
    switch (symbol) {
        case '|':
            priority = 1;
            break;
        case '.':
            priority = 2;
            break;
        case '*':
            priority = 3;
            break;
        default:
            priority = 0;
            break;
    }
    return priority;
}

void DFA::RegextoPost() {
    int i = 0, j = 0;
    char ch, cl;
    strcpy(regexPost_, "\0");
    LinkStack<char>* Value = new LinkStack<char>();
    Value->Clear();
    ch = regex_[i];
    Value->Push('#');
    ch = regex_[i];  // FIXME: ?
    while (ch != '\0') {
        if (ch == '(') {
            Value->Push(ch);
            ch = regex_[++i];
        } else if (ch == ')') {
            while (Value->GetTop() != '(') {
                regexPost_[j++] = Value->Pop();
            }
            Value->Pop();
            ch = regex_[++i];
        } else if ((ch == '|') || (ch == '*') || (ch == '.')) {
            cl = Value->GetTop();
            while (Precedence(cl) >= Precedence(ch)) {
                regexPost_[j++] = cl;
                Value->Pop();
                cl = Value->GetTop();
            }
            Value->Push(ch);
            ch = regex_[++i];
        } else {
            regexPost_[j++] = ch;
            ch = regex_[++i];
        }
    }
    ch = Value->Pop();
    while (ch == '|' || ch == '*' || ch == '.') {
        regexPost_[j++] = ch;
        ch = Value->Pop();
    }
    regexPost_[j] = '\0';
    Value->Clear();
    delete Value;
    cout << endl
         << "3.transform RegePost" << endl
         << regexPost_ << endl
         << "String length : " << strlen(regexPost_);
}

void DFA::GetEdgeNumber() {
    int i = 0, j;
    edgeNumber_ = 0;
    while (regexPost_[i] != '\0') {
        if (regexPost_[i] == '.' || regexPost_[i] == '|' ||
            regexPost_[i] == '*') {
            i++;
            continue;
        }
        for (j = 0; j < edgeNumber_; j++) {
            if (regexPost_[i] == edgeNum_[j]) {
                break;
            }
        }
        if (j == edgeNumber_) {
            edgeNum_[j] = regexPost_[i];
            edgeNumber_++;
        }
        i++;
    }
    edgeNum_[edgeNumber_] = '\0';
    cout << endl;
    cout << "4. get char list" << endl;
    for (i = 0; i < edgeNumber_; i++) {
        cout << edgeNum_[i] << ' ';
    }
    cout << endl << "char numbers: " << edgeNumber_ << endl;
    cout << endl << "----------------------------" << endl;
}

void DFA::Thompson() {
    int i, j;
    char ch;
    int s1, s2;
    LinkStack<int>* States = new LinkStack<int>();
    States->Clear();
    if (strlen(regexPost_) < 1) {
        cout << "no regex expression find" << endl;
        exit(1);
    }
    i = 1, j = 0;
    ch = regexPost_[j];
    while (ch != '\0') {
        if (ch == '.') {
            s2 = States->Pop();
            int ex1 = States->Pop();
            int ex2 = States->Pop();
            s1 = States->Pop();
        }
    }
}