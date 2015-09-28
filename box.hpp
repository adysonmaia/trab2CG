#ifndef BOX_HPP
#define BOX_HPP


class Box;


#include <iostream>
using namespace std;
#include <QtOpenGL>
#include "point.hpp"

class Box
{
	
private:
  float color[3];
  
protected:
	
  // tamanho da aresta do cubo
  float largura;
  float altura;
  float profundidade;
  // ponto de referencia do cubo
  Point3 p;
  
  float topo[4][3];
  float base[4][3];
  float fundo[4][3];
  float frente[4][3];
  float esquerda[4][3];
  float direita[4][3];
  
public:
  Box(Point3,float,float,float);
  virtual ~Box();
  // muda o ponto de referencia
  virtual void Desenha();
  
};

#endif /*BOX_HPP*/



