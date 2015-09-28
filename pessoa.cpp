#include "pessoa.hpp"

/* ------------- */

Braco :: Braco(float altura, float raio, Material *matAnteBraco, Material *matBraco)
       : MembroCorpo(altura,raio)
{
	anguloAnteBraco[0] = 0;
	anguloAnteBraco[1] = 0;
	anguloAnteBraco[2] = 0;
	anguloBraco        = 0;
  
  carregarMaterial(matAnteBraco);	
  carregarMaterial(matBraco);

}

float* Braco :: getAnguloAnteBraco() {
	return this->anguloAnteBraco;
}

void Braco :: setAnguloAnteBraco(float angulo1, float angulo2, float angulo3) {
	float max[] = {200,180,180};
	float min[] = {0,0,-180};
	
	if (angulo1 > max[0])	angulo1 = max[0];
        if (angulo1 < min[0])	angulo1 = min[0];
		
        if (angulo2 > max[1])	angulo2 = max[1];
        if (angulo2 < min[1])	angulo2 = min[1];
  
        if (angulo3 > max[2])	angulo3 = max[2];
        if (angulo3 < min[2])	angulo3 = min[2];
		
	this -> anguloAnteBraco[0] = angulo1;
	this -> anguloAnteBraco[1] = angulo2;
	this -> anguloAnteBraco[2] = angulo3;
}

float Braco :: getAnguloBraco() {
	return this->anguloBraco;
}

void Braco :: setAnguloBraco(float angulo) {
  float max = 100, min = 0;		

	if (angulo < min)
		angulo = min;
	if (angulo > max)
		angulo = max;
		
	this -> anguloBraco = -angulo;
}

void Braco :: desenha() {

	glPushMatrix();
  	glRotatef(-90.0, 1.0, 0.0, 0.0);
  	
  	//Desenha o antebraço
  	glRotatef(anguloAnteBraco[0], 1.0, 0.0, 0.0);
  	glRotatef(anguloAnteBraco[1], 0.0, 1.0, 0.0);
  	glRotatef(anguloAnteBraco[2], 0.0, 0.0, 1.0);
    
    materiais[0]->usarMaterial();
    gluSphere(this->obj,this->raio,10,10);
    gluCylinder(this->obj,this->raio, this->raio, this->altura*2/5 ,10,10);
  	
  	//Desenha o braço
  	
  	glTranslatef(0.0,0.0,this->altura*2/5);
  	glRotatef(anguloBraco, 0.0, 1.0, 0.0);
  	gluSphere(this->obj,this->raio,10,10);
  	materiais[1]->usarMaterial();
  	gluCylinder(this->obj,this->raio, this->raio, this->altura*3/5,10,10);
  		
  	glTranslatef(0.0,0.0,this->altura*3/5);
  	gluSphere(this->obj,this->raio,10,10);
  	
  glPopMatrix();
}


/*-------------- */
Perna :: Perna(float altura, float raio, Material *matCoxa, Material *matPerna)
       : MembroCorpo(altura,raio) {
	anguloCoxa[0]  = 0;
	anguloCoxa[1]  = 0;
	anguloPerna    = 0;
	
	carregarMaterial(matCoxa);	
	carregarMaterial(matPerna);
}

float* Perna :: getAnguloCoxa() {
	return this->anguloCoxa;
}

void Perna :: setAnguloCoxa(float angulo1, float angulo2) {
	float max[] = {120, 45}, min[] = {-100, -30};
	
	if (angulo1 > max[0])	angulo1 = max[0];
  if (angulo1 < min[0])	angulo1 = min[0];
  
  if (angulo2 > max[1])	angulo2 = max[1];
  if (angulo2 < min[1])	angulo2 = min[1];
	
	this -> anguloCoxa[0] = angulo1;
	this -> anguloCoxa[1] = angulo2;
}

float Perna :: getAnguloPerna() {
	return this->anguloPerna;
}

void Perna :: setAnguloPerna(float angulo) {
	float max = 60, min = 0;
	
	if (angulo > max)
		angulo = max;
	if (angulo < min)
		angulo = min;
	this -> anguloPerna = angulo;
}

void Perna :: desenha() {
	float proporsao = 0.5;
	
	glPushMatrix();
  	glRotatef(90.0, 1.0, 0.0, 0.0);	
  	
  	//Desenha a coxa
  	glRotatef(anguloCoxa[0], 1.0, 0.0, 0.0);
  	glRotatef(anguloCoxa[1], 0.0, 1.0, 0.0);
    
    materiais[0]->usarMaterial();
    gluSphere(this->obj,this->raio,10,10);
    gluCylinder(this->obj,this->raio, this->raio, this->altura*proporsao ,10,10);
  	
  	//Desenha a perna
  	glPushMatrix();
  		materiais[1]->usarMaterial();
  		glTranslatef(0.0,0.0,this->altura*proporsao);
  		glRotatef(anguloPerna, 1.0, 0.0, 0.0);  		
  		gluSphere(this->obj,this->raio,10,10);
  		gluCylinder(this->obj,this->raio, this->raio, this->altura*(1-proporsao),10,10);
  		
  		glTranslatef(0.0,0.0,this->altura*(1-proporsao) );
  		gluSphere(this->obj,this->raio,10,10);
  	glPopMatrix();
  	
  glPopMatrix();
}

/* ------------- */
Tronco :: Tronco(float altura, float raio, Material *tronco, Material *bacia)
        : MembroCorpo(altura,raio) 
{	
	carregarMaterial(tronco);
	carregarMaterial(bacia);	
}


void Tronco :: desenha() {
	float raioBase = this -> raio*0.9;
	float raioTop  = this -> raio;
	float proporsao = 0.3;
	
	glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		
		materiais[1]->usarMaterial();
		gluCylinder(this->obj,raioBase, raioBase, this->altura*proporsao ,80,80);
		gluSphere(this->obj,raioBase,10,10); 
	  
		glTranslatef(0.0,0.0,this->altura*proporsao);
		materiais[0]->usarMaterial();
		gluCylinder(this->obj,raioBase, raioTop, this->altura*(1-proporsao) ,80,80);
	  
	  glTranslatef(0.0,0.0,this->altura*(1-proporsao));
		glScalef(1.0, 1.0, 0.5);
		materiais[0]->usarMaterial();
		gluSphere(this->obj,raioTop,10,10);
		
	glPopMatrix();
}

/* ------------- */

Cabeca :: Cabeca(float altura, float raio, Material *mat)
        : MembroCorpo(altura,raio) 
{ 
	carregarMaterial(mat);
}

void Cabeca :: desenha(){
	glPushMatrix();
  	glRotatef(-90.0, 1.0, 0.0, 0.0);
  	glTranslatef(0.0, 0.0,0.5*this->altura);
   	materiais[0]->usarMaterial();
   	gluSphere(this->obj,this->altura,100,100);
  glPopMatrix();
}

/* ------------- */
Pessoa :: Pessoa (float altura, float larguraCabeca, float *posicao, 
	        Material *pele, Material *camisa, Material *calcao, Material *meiao) 
{
	this -> angulo[0] = this -> angulo[1] = this -> angulo[2] = 0;
	
	float hCabeca = altura/8;
	float hTronco = 3*hCabeca;
	float hBraco  = 3*hCabeca;
	float hPerna  = 4*hCabeca;
	
	float wCabeca = larguraCabeca;
	float wTronco = wCabeca*1.5;
	float wBraco  = wCabeca/2;
	float wPerna  = wCabeca*2/3;	
	
	cabeca    = new Cabeca (hCabeca , wCabeca, pele);
  tronco    = new Tronco (hTronco , wTronco, camisa , calcao);
  pernas[0] = new Perna  (hPerna  , wPerna , calcao , meiao);
  pernas[1] = new Perna  (hPerna  , wPerna , calcao , meiao);
  bracos[0] = new Braco  (hBraco  , wBraco , camisa , pele);
  bracos[1] = new Braco  (hBraco  , wBraco , camisa , pele);
  
  for (int i=0; i< 3; i++){
  	centro[i] = posicao[i];
  }
 
  float *m;
  m = new float[16];
  
  glLoadIdentity();
  glPushMatrix();
  	glTranslatef(centro[0],centro[1], centro[2]);
  	glGetFloatv(GL_MODELVIEW_MATRIX,m);
  	arv = new TreeNode(m , NULL, NULL, tronco);
  glPopMatrix();
  
  glPushMatrix();
  	glTranslatef(wTronco,-wTronco, 0.0);
  	m = new float[16];
  	glGetFloatv(GL_MODELVIEW_MATRIX,m);
  	arv -> setFilho( new TreeNode(m , NULL, NULL, pernas[0]));
  glPopMatrix();
  
  glPushMatrix();
  	glScalef(-1.0,1.0,1.0);
  	glTranslatef(wTronco,-wTronco, 0.0);
  	m = new float[16];
  	glGetFloatv(GL_MODELVIEW_MATRIX,m);
  	arv -> getFilho() -> setIrmao ( new TreeNode(m , NULL, NULL, pernas[1]));
  glPopMatrix();
  
  glPushMatrix();
  	glTranslatef(wTronco + wBraco,hTronco, 0.0);
  	m = new float[16];
  	glGetFloatv(GL_MODELVIEW_MATRIX,m);
  	arv -> getFilho() -> getIrmao() -> setIrmao ( new TreeNode(m , NULL, NULL, bracos[0]));
  glPopMatrix();
  
  glPushMatrix();
  	glScalef(-1.0,1.0,1.0);
  	glTranslatef(wTronco + wBraco,hTronco, 0.0);
  	m = new float[16];
  	glGetFloatv(GL_MODELVIEW_MATRIX,m);
  	arv -> getFilho() -> getIrmao() -> getIrmao() -> setIrmao ( new TreeNode(m , NULL, NULL, bracos[1]));
  glPopMatrix();
  
  
  glPushMatrix();
  	glTranslatef(0,hTronco + wTronco, 0.0);
  	m = new float[16];
  	glGetFloatv(GL_MODELVIEW_MATRIX,m);
  	arv -> getFilho() -> getIrmao() -> getIrmao() -> getIrmao() -> setIrmao ( new TreeNode(m , NULL, NULL, cabeca) );
  glPopMatrix();
  /**/

}

Pessoa :: ~Pessoa (){
//	delete[] pernas;
//	delete[] bracos;
	delete tronco;
	delete cabeca;
	delete arv;
}

		
void Pessoa :: setAnguloCorpo(float anguloX, float anguloY, float anguloZ) {
	this -> angulo[0] = anguloX;
	this -> angulo[1] = anguloY;
	this -> angulo[2] = anguloZ;
}

void Pessoa :: setPosicaoCorpo(float posX, float posY, float posZ) {
	this -> centro[0] = posX;
	this -> centro[1] = posY;
	this -> centro[2] = posZ;
}
	
void Pessoa :: setAnguloBraco(int lado, float angulo) {
	lado = (lado < 2 && lado > -1) ? lado : 0;
	this -> bracos[lado] -> setAnguloBraco(angulo);
}

void Pessoa :: setAnguloAnteBraco(int lado, float angulo1, float angulo2, float angulo3 ) {
	lado = (lado < 2 && lado > -1) ? lado : 0;
	this -> bracos[lado] -> setAnguloAnteBraco(angulo1,angulo2,angulo3);
}
	
void Pessoa :: setAnguloCoxa(int lado, float angulo1, float angulo2) {
	lado = (lado < 2 && lado > -1) ? lado : 0;
	this -> pernas[lado] -> setAnguloCoxa(angulo1,angulo2);
}

void Pessoa :: setAnguloPerna(int lado, float angulo) {
	lado = (lado < 2 && lado > -1) ? lado : 0;
	this -> pernas[lado] -> setAnguloPerna(angulo);
}

void Pessoa :: desenha() {
	
  glPushMatrix();
  	
  	glLoadIdentity();
  	glTranslatef(centro[0],centro[1], centro[2]);
  	glRotatef(angulo[0], 1.0, 0.0, 0.0);
  	glRotatef(angulo[1], 0.0, 1.0, 0.0);
  	glRotatef(angulo[2], 0.0, 0.0, 1.0);
  	
  	float *m = new float[16];
  	glGetFloatv(GL_MODELVIEW_MATRIX,m);
  	arv-> setMatriz(m);
  	
  glPopMatrix();
	arv -> desenha();
}



