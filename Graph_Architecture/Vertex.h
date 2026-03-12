//
// Created by luca eaton on 3/11/26.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
class Edge;
using namespace std;

class Vertex {
private:
    size_t id_;
    double lat_;
    double lon_;
public:
    Vertex();
    Vertex(long long i, double la, double lo);
};



#endif //VECTOR_H
