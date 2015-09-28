#include "trave.hpp"

Trave::Trave(Point3 posicaoIni,float largura, float altura)
{

  this->posicaoIni = posicaoIni;
  this->largura = largura;
  this->altura  = altura;
  this->raio = 6.0;
  
  /*material */
  Material *mat;
	
	float *a, *d, *s, *e;
	float shini = 500; 
	a = new float[4];
	d = new float[4];
	s = new float[4];
	e = new float[4];
	
	a[0] = 0.2 ; a[1] = 0.2; a[2] =0.1; a[3] = 1.0;
	d[0] = 0.5 ; d[1] = 0.5; d[2] =0.5; d[3] = 1.0;
	s[0] = 0.3 ; s[1] = 0.3; s[2] =0.3; s[3] = 1.0;
	e[0] = 0.0 ; e[1] = 0.0; e[2] =0.0; e[3] = 1.0;

	mat = new Material (a,d,s,e,shini);
	carregarMaterial(mat);

}
Trave::~Trave()
{

}

float Trave::getAltura()
{
  return this->altura;
}

float Trave::getLargura()
{
  return this->largura;
}
 
void Trave::desenha()
{
  
  glPushMatrix();

	/*usa material*/
  this -> materiais[0] -> usarMaterial();
  float x = this->posicaoIni.x();
  float y = this->posicaoIni.y();
  float z = this->posicaoIni.z();
  glTranslatef(x,y,z);
  glRotatef(-90.0,1.0,0.0,0.0);
  
  gluCylinder(obj,this->raio, this->raio, this->altura,10,10);
  glPopMatrix();
  glPushMatrix();
   y = this->altura;

   glTranslatef(x,y,z);
   gluSphere(obj,this->raio,10,10);

   glRotatef(-180.0,0.0,1.0,0.0);
   gluCylinder(obj,this->raio, this->raio, this->largura,10,10);

  glPopMatrix();
  glPushMatrix();

  x = this->posicaoIni.x();
  y = this->posicaoIni.y();
  z = this->posicaoIni.z() - this->largura;
  glTranslatef(x,y,z);
  glRotatef(-90.0,1.0,0.0,0.0);
  gluCylinder(obj,this->raio, this->raio, this->altura,10,10);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(x,this->altura,z);
  gluSphere(obj,this->raio,10,10);
  glPopMatrix();
}




