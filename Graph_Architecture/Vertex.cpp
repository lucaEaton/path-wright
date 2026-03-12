//
// Created by luca eaton on 3/11/26.
//

#include "Vertex.h"

Vertex::Vertex() : id_(0ll), lat_(0.0), lon_(0.0) {}
Vertex::Vertex(const long long i, const double la, const double lo) : id_(i), lat_(la), lon_(lo) {};