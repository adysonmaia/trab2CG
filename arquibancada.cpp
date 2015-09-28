#include "arquibancada.hpp"

Arquibancada::Arquibancada(Point3 p, float largura , float altura, float profundidade)
{
  this->box = new Box(p,largura,0.2*altura,profundidade); //A altura da Caixa tem 20% da altura da Arquibancada
  this->largura = largura;
  this->altura = altura;
  this->p = p;
  this->profundidade = profundidade;
  
  /*material */
  Material *mat;
	
	float *a, *d, *s, *e;
	float shini = 90; 
	a = new float[4];
	d = new float[4];
	s = new float[4];
	e = new float[4];
	
	a[0] = 0.2 ; a[1] = 0.2; a[2] =0.1; a[3] = 1.0;
	d[0] = 0.5 ; d[1] = 0.5; d[2] =0.0; d[3] = 1.0;
	s[0] = 0.3 ; s[1] = 0.3; s[2] =0.0; s[3] = 1.0;
	e[0] = 0.0 ; e[1] = 0.0; e[2] =0.0; e[3] = 1.0;

	mat = new Material (a,d,s,e,shini);
	carregarMaterial(mat);
	
	Material *mat2;
	
	float *a2, *d2, *s2, *e2;
	float shini2 = 10; 
	a2 = new float[4];
	d2 = new float[4];
	s2 = new float[4];
	e2 = new float[4];
	
	a2[0] = 0.1 ; a2[1] = 0.1; a2[2] =0.1; a2[3] = 1.0;
	d2[0] = 0.98 ; d2[1] = 0.85; d2[2] =0.76; d2[3] = 1.0;
	s2[0] = 0.3 ; s2[1] = 0.3; s2[2] =0.3; s2[3] = 1.0;
	e2[0] = 0.0 ; e2[1] = 0.0; e2[2] =0.0; e2[3] = 1.0;

	mat2 = new Material (a2,d2,s2,e2,shini2);
	carregarMaterial(mat2);
}

Arquibancada::~Arquibancada()
{
 delete(this->box);
}

void Arquibancada::desenha()
{
  float x = this->p.x();
  float y = this->p.y();
  float z = this->p.z();
  
  float a = this->altura;
  float l = this->largura;
  float p = this->profundidade;

  glPushMatrix();  //guarda matriz

  /*usa material*/
  
  glTranslatef(x,y,z); 
  this->box->Desenha();
  
  glNormal3f(0,1,0);
  this -> materiais[0] -> usarMaterial();
   glBegin(GL_QUADS);
    glVertex3f(x,y+0.2*a,z + p/2);
    glVertex3f(x+l,y+0.2*a,z + p/2);
    glVertex3f(x+l,a,z - p/2);
    glVertex3f(x,a,z - p/2);
  glEnd();
  
  
  this -> materiais[1] -> usarMaterial();
  glBegin(GL_QUADS);
    glVertex3f(x,y+0.2*a,z - p/2);
    glVertex3f(x+l,y+0.2*a,z - p/2);
    glVertex3f(x+l,a,z - p/2);
    glVertex3f(x,a,z - p/2);

  glEnd();

  glBegin(GL_TRIANGLES);
    glVertex3f(x+l,y+0.2*a,z + p/2);
    glVertex3f(x+l,y+0.2*a,z - p/2);
    glVertex3f(x+l,a,z - p/2);
  glEnd();
 
  glBegin(GL_TRIANGLES);
    glVertex3f(x,y+0.2*a,z + p/2);
    glVertex3f(x,y+0.2*a,z - p/2);
    glVertex3f(x,a,z - p/2);
  glEnd();

  

  glPopMatrix();  //volta matriz
}


