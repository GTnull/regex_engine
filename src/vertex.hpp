#ifndef VERTEX_H_
#define VERTEX_H_

#include "edge.hpp"

class Vertex {
   public:
    Vertex() : number_(-1), next_(nullptr), out_(nullptr){};
    Vertex(int num) : number_(num), next_(nullptr), out_(nullptr){};

    ~Vertex() {}
    Edge* GetOutPtr() { return out_; }
    Vertex* GetNextPtr() { return next_; }
    int GetNumber() { return number_; }

    void SetOut(Edge* out) { out_ = out; }
    void SetNumber(int num) { number_ = num; }
    void SetNext(Vertex* next) { next_ = next; }

   private:
    int number_;
    Vertex* next_;
    Edge* out_;
};

#endif