#include "NavMesh.hpp"

NavMesh::NavMesh(std::vector<Vector3d> vertices, std::vector<unsigned int> indexes){

    for (size_t i = 0; i < indexes.size(); i+=3)
    {
        Vector3d v1 = vertices[indexes[i]];
        Vector3d v2 = vertices[indexes[i+1]];
        Vector3d v3 = vertices[indexes[i+2]];

        Triangle triangle = Triangle(v1, v2, v3);
        triangles.push_back(triangle);
    }
    

}

NavMesh::NavMesh(){

}

NavMesh::~NavMesh(){}

void NavMesh::debug(){
    for (size_t i = 0; i < triangles.size(); i++)
    {
        std::cout<<"TRIAGLE: "<<i<<"\n";
        std::cout<<"V1: " << triangles[i]._v1.getVectorX() <<", " << triangles[i]._v1.getVectorY() <<", "<< triangles[i]._v1.getVectorY() <<"\n";
        std::cout<<"V2: " << triangles[i]._v2.getVectorX() <<", " << triangles[i]._v2.getVectorY() <<", "<< triangles[i]._v2.getVectorY() <<"\n";
        std::cout<<"V3: " << triangles[i]._v3.getVectorX() <<", " << triangles[i]._v3.getVectorY() <<", "<< triangles[i]._v3.getVectorY() <<"\n";
    }
    
}