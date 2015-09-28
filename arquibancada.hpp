#ifndef ARQUIBANCADA_HPP
#define ARQUIBANCADA_HPP

#include "box.hpp"
#include "point.hpp"
#include "objeto.hpp"


class Arquibancada : public Objeto
{
  private:
  float altura;
  float largura;
  float profundidade;
  Box   *box; 
  Point3 p; 
  

  public:
  Arquibancada(Point3 , float , float ,float);
  ~Arquibancada();
  void desenha();

};

#endif /*ARQUIBANCADA_HPP*/



