#include "box.hpp"

Box::Box(Point3 po,float largura,float altura,float profundidade)
{
	//int i;
	this->altura = altura;
        this->largura = largura;
	this->profundidade = profundidade;
	
        this->p = po;
	
	float x = this->p.x();
	float y = this->p.y();
	float z = this->p.z();
	 
        float a = altura;
        float p = profundidade;
	float l	= largura;
 
	 topo[0][0] = x;
	 topo[0][1] = y+a;
	 topo[0][2] = z;
	 topo[1][0] = x+l;
	 topo[1][1] = y+a;
	 topo[1][2] = z;
	 topo[2][0] = x+l;
	 topo[2][1] = y+a;
	 topo[2][2] = z+p;
	 topo[3][0] = x;
	 topo[3][1] = y+a;
	 topo[3][2] = z+p;
	 
	 base[0][0] = x;
	 base[0][1] = y;
	 base[0][2] = z;
	 base[1][0] = x+l;
	 base[1][1] = y;
	 base[1][2] = z;
	 base[2][0] = x+l;
	 base[2][1] = y;
	 base[2][2] = z+p;
	 base[3][0] = x;
	 base[3][1] = y;
	 base[3][2] = z+p;
	 
	 frente[0][0] = x;
	 frente[0][1] = y;
	 frente[0][2] = z;
	 frente[1][0] = x+l;
	 frente[1][1] = y;
	 frente[1][2] = z;
	 frente[2][0] = x+l;
	 frente[2][1] = y+a;
	 frente[2][2] = z;
	 frente[3][0] = x;
	 frente[3][1] = y+a;
	 frente[3][2] = z;
	 
	 fundo[0][0] = x;
	 fundo[0][1] = y;
	 fundo[0][2] = z+p;
	 fundo[1][0] = x+l;
	 fundo[1][1] = y;
	 fundo[1][2] = z+p;
	 fundo[2][0] = x+l;
	 fundo[2][1] = y+a;
	 fundo[2][2] = z+p;
	 fundo[3][0] = x;
	 fundo[3][1] = y+a;
	 fundo[3][2] = z+p;
	 
	 esquerda[0][0] = x;
	 esquerda[0][1] = y;
	 esquerda[0][2] = z;
	 esquerda[1][0] = x;
	 esquerda[1][1] = y;
	 esquerda[1][2] = z+p;
	 esquerda[2][0] = x;
	 esquerda[2][1] = y+a;
	 esquerda[2][2] = z+p;
	 esquerda[3][0] = x;
	 esquerda[3][1] = y+a;
	 esquerda[3][2] = z;
	 
	 direita[0][0] = x+l;
	 direita[0][1] = y;
	 direita[0][2] = z;
	 direita[1][0] = x+l;
	 direita[1][1] = y;
	 direita[1][2] = z+p;
	 direita[2][0] = x+l;
	 direita[2][1] = y+a;
	 direita[2][2] = z+p;
	 direita[3][0] = x+l;
	 direita[3][1] = y+a;
	 direita[3][2] = z;
	 
}

Box::~Box()
{
	
}

void Box::Desenha()
{
	float x = this->p.x();
	float y = this->p.y();
	float z = this->p.z();
	//float t = this->size; 
	
	
	glPushMatrix();
	glTranslatef(x,y,z);
	glBegin(GL_QUADS);
	  //========== frente do cubo ================
		glVertex3fv(frente[0]);
		glVertex3fv(frente[1]);
		glVertex3fv(frente[2]);
		glVertex3fv(frente[3]);
	  //========== frente do cubo ================
	glEnd();
	glBegin(GL_QUADS);
	  //========== fundo do cubo ================
		glVertex3fv(fundo[0]);
		glVertex3fv(fundo[1]);
		glVertex3fv(fundo[2]);
		glVertex3fv(fundo[3]);
	  //========== fundo do cubo ================
	glEnd();
	glBegin(GL_QUADS);
	  //========== lateral esquerda do cubo ================
		glVertex3fv(esquerda[0]);
		glVertex3fv(esquerda[1]);
		glVertex3fv(esquerda[2]);
		glVertex3fv(esquerda[3]);
	  //========== lateral esquerda do cubo ================
	glEnd();
	glBegin(GL_QUADS);
	  //========== lateral direita do cubo ================
		glVertex3fv(direita[0]);
		glVertex3fv(direita[1]);
		glVertex3fv(direita[2]);
		glVertex3fv(direita[3]);
	  //========== lateral direita do cubo ================
	glEnd();
	
	glBegin(GL_QUADS);
	
	  //========== topo do cubo ================
	    glVertex3fv(topo[0]);
	    glVertex3fv(topo[1]);
	    glVertex3fv(topo[2]);
	    glVertex3fv(topo[3]);
	  //========== topo do cubo ================
	glEnd();
	glBegin(GL_QUADS);
	
	  //========== base do cubo ================
	    glVertex3fv(base[0]);
	    glVertex3fv(base[1]);
	    glVertex3fv(base[2]);
	    glVertex3fv(base[3]);
	  //========== base do cubo ================
	glEnd();
	glPopMatrix();
	
}





