#ifndef ADJ_H_
#define ADJ_H_

#include "vertex.hpp"

class AdjacentTable {
   public:
    AdjacentTable()
        : numOfEdge_(0), numOfVertexs_(1), startVertex_(new Vertex()){};
    ~AdjacentTable();

    int GetValueByPos(int pos) const;
    int GetPosByValue(int value) const;
    char GetWeightByPos(int v1, int v2) const;
    char GetWeightByValue(int value1, int value2) const;
    void SetValue(int value, int pos);
    void InsertVertex(int value);
    void InsertEdgeByPos(int v1, int v2, char weight);
    void RemoveAllEdges(void);
    void Clear(void);
    int* Closure(int* T);
    int* Move(int* T, char ch);
    void OutputNFA(void);

    int GetNumOfVertexs() { return numOfVertexs_; }
    int GetNumOfEdges() { return numOfEdge_; }
    Vertex* GetStartVertex() { return startVertex_; }

    void SetStartVertex(Vertex* startVertex) { startVertex_ = startVertex; }

   private:
    int numOfVertexs_;
    int numOfEdge_;
    Vertex* startVertex_;
};

#endif