#ifndef TRAVE_HPP
#define TRAVE_HPP

#include "point.hpp"
#include "objeto.hpp"

class Trave : public Objeto
{

private:

  float largura;
  float altura;
  Point3 posicaoIni;
  float raio;

public:
  // recebe posicao inicial, largura e altura da trave
  Trave(Point3,float,float);
  ~Trave();
  float getAltura();
  float getLargura();
  void desenha();


};



#endif /*TRAVE_HPPP*/





