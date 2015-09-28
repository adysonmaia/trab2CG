#include "campo.hpp"

/*Construtor do Campo*/
Campo::Campo(float Largura,float Altura,float TraveLarg, float alturaTrave)
{
	this->Largura = Largura;
	this->Altura  = Altura;
	this->TraveLarg = TraveLarg;
	this->alturaTrave = alturaTrave;
  this->trave =  new Trave(Point3(0.0,0.0,600.0),this->TraveLarg,this->alturaTrave);
  this->trave2 = new Trave(Point3(this->Largura,0.0,600.0),this->TraveLarg,this->alturaTrave);	
 
	/*material */
  Material *mat;
	
	float *a, *d, *s, *e;
	float shini = 100; 
	a = new float[4];
	d = new float[4];
	s = new float[4];
	e = new float[4];
	
	a[0] = 0.2 ; a[1] = 0.2; a[2] =0.1; a[3] = 1.0;
	d[0] = 0.0 ; d[1] = 0.5; d[2] =0.0; d[3] = 1.0;
	s[0] = 0.0 ; s[1] = 0.3; s[2] =0.0; s[3] = 1.0;
	e[0] = 0.0 ; e[1] = 0.0; e[2] =0.0; e[3] = 1.0;

	mat = new Material (a,d,s,e,shini);
	carregarMaterial(mat);
	
	Material *mat2;
	
	float *a2, *d2, *s2, *e2;
	float shini2 = 50; 
	a2 = new float[4];	d2 = new float[4];
	s2 = new float[4];	e2 = new float[4];
	
	a2[0] = 0.5 ; a2[1] = 0.5; a2[2] =0.5; a2[3] = 1.0;
	d2[0] = 0.0 ; d2[1] = 0.0; d2[2] =0.0; d2[3] = 1.0;
	s2[0] = 0.0 ; s2[1] = 0.0; s2[2] =0.0; s2[3] = 1.0;
	e2[0] = 0.0 ; e2[1] = 0.0; e2[2] =0.0; e2[3] = 1.0;

	mat2 = new Material (a2,d2,s2,e2,shini2);
	carregarMaterial(mat2);

}

/*Destrutor do Campo*/
Campo::~Campo()
{

}

/*Método usado para desenhar do Campo*/
void Campo::desenha()
{
   
   glPushMatrix();
   
    /*Pontos Usados no Campo*/
    GLfloat P1[3] = { 0.0, 0.0, 0.0 };
    GLfloat P2[3] = { Largura, 0.0, 0.0 };
    GLfloat P3[3] = { Largura, 0.0, Altura };
    GLfloat P4[3] = { 0.0, 0.0, Altura };

    float fator = 4;
    GLfloat P5[3] = { -fator*Largura, 0.0, 0.0 };
    GLfloat P6[3] = { -fator*Largura, 0.0, -fator*Altura };
    GLfloat P7[3] = { fator*Largura, 0.0, -fator*Altura };    
    GLfloat P8[3] = { fator*Largura, 0.0, 0.0 };
     
    GLfloat P9[3] = { -fator*Largura, 0.0, Altura };
    GLfloat P10[3] = { -fator*Largura, 0.0, fator*Altura };
    GLfloat P11[3] = { fator*Largura, 0.0, fator*Altura };    
    GLfloat P12[3] = { fator*Largura, 0.0, Altura };
    
    GLfloat P13[3] = { -fator*Largura, 0.0, 0.0 };
    GLfloat P14[3] = { -fator*Largura, 0.0, Altura };
    GLfloat P15[3] = { 0.0, 0.0, Altura };    
    GLfloat P16[3] = { 0.0, 0.0, 0.0 };

    GLfloat P17[3] = { fator*Largura, 0.0, 0.0 };
    GLfloat P18[3] = { fator*Largura, 0.0, Altura };    
    GLfloat P19[3] = { Largura, 0.0, Altura };
    GLfloat P20[3] = { Largura, 0.0, 0.0 };
    
   
    /*chao*/
     /*usa material*/
    
    glNormal3f(0,1,0);

    glPushMatrix();
    this -> materiais[1] -> usarMaterial(); 
    glBegin(GL_QUADS);
    	glVertex3fv(P5);      glVertex3fv(P6);
      glVertex3fv(P7);      glVertex3fv(P8);
      
      glVertex3fv(P9);      glVertex3fv(P10);
      glVertex3fv(P11);     glVertex3fv(P12);
      
      glVertex3fv(P13);      glVertex3fv(P14);
      glVertex3fv(P15);     glVertex3fv(P16);
    
      glVertex3fv(P13);      glVertex3fv(P14);
      glVertex3fv(P15);     glVertex3fv(P16);
      
      glVertex3fv(P17);      glVertex3fv(P18);
      glVertex3fv(P19);     glVertex3fv(P20);
    glEnd();
    glPopMatrix();

    glNormal3f(0,1,0);
    this -> materiais[0] -> usarMaterial(); 
    /*Solo do Campo*/
    /*Parte de Cima*/
    glBegin(GL_QUADS);
     glColor3f(0.0,1.0,0.0);
     glTexCoord2f(0.0f, 0.0f); glVertex3fv(P4);
     glTexCoord2f(0.0f, 1.0f); glVertex3fv(P3);
     glTexCoord2f(1.0f, 1.0f); glVertex3fv(P2);
     glTexCoord2f(1.0f, 0.0f); glVertex3fv(P1);
    glEnd();

    /*Solo do Campo*/
    /*Parte de Baixo*/
    glBegin(GL_QUADS);
     glColor3f(0.0,1.0,0.0);
     glTexCoord2f(1.0f, 0.0f); glVertex3fv(P1);
     glTexCoord2f(1.0f, 1.0f); glVertex3fv(P2);
     glTexCoord2f(0.0f, 1.0f); glVertex3fv(P3);
     glTexCoord2f(0.0f, 0.0f); glVertex3fv(P4);
    glEnd(); 
    
   

   glPopMatrix();

   this->trave->desenha();
   this->trave2->desenha();

}

Bola :: Bola (float r) : raio(r) 
{
	/*material */
  Material *mat;
	
	float *a, *d, *s, *e;
	float shini = 200; 
	a = new float[4];
	d = new float[4];
	s = new float[4];
	e = new float[4];
	
	a[0] = 0.2 ; a[1] = 0.2; a[2] =0.2; a[3] = 1.0;
	d[0] = 1.0 ; d[1] = 1.0; d[2] =1.0; d[3] = 1.0;
	s[0] = 0.5 ; s[1] = 0.5; s[2] =0.5; s[3] = 1.0;
	e[0] = 0.0 ; e[1] = 0.0; e[2] =0.0; e[3] = 1.0;

	mat = new Material (a,d,s,e,shini);
	carregarMaterial(mat);

}

void Bola :: desenha(){
	/*usa material*/
  this -> materiais[0] -> usarMaterial();
	
	/*Desenhando a Bola*/
	gluSphere(this->obj, this->raio, 200, 200); 
}

bool Campo::Gol(Point3 p)
{
	float x = p.x();
	float y = p.y();
	float z = p.z();	  
	/*if((x >= 725.0) && (y >= 0.0 && y<= this->alturaTrave-30) && z ) return true;
	//else return false;*/
	return false;
}


