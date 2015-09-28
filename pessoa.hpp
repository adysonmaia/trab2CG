#ifndef PESSOA_HPP_
#define PESSOA_HPP_

#include <iostream>
#include "objeto.hpp"
#include <math.h>

using namespace std;

class MembroCorpo : public Objeto {
protected:
	float altura;
	float raio;
public:
	MembroCorpo(float h, float r) : altura(h), raio(r) {};
	virtual ~MembroCorpo() {};
};

class Braco : public MembroCorpo {
	float anguloAnteBraco[3];
	float anguloBraco;
public:
	Braco(float altura, float raio, Material *matAnteBraco, Material *matBraco);
	~Braco() {};
	void desenha();
	
	float* getAnguloAnteBraco();
	void setAnguloAnteBraco(float angulo1, float angulo2, float angulo3);
	
	float getAnguloBraco();
	void setAnguloBraco(float angulo);
};


class Perna : public MembroCorpo {
	float anguloCoxa[2];
	float anguloPerna;
public:
	Perna(float altura, float raio, Material *matCoxa, Material *matPerna);
	~Perna() {};
	void desenha();
	
	float* getAnguloCoxa();
	void setAnguloCoxa(float angulo1, float angulo2);
	
	float getAnguloPerna();
	void setAnguloPerna(float angulo);
};



class Tronco : public MembroCorpo {
public:
	Tronco(float altura, float raio, Material *tronco, Material *bacia);
	~Tronco() {};
	void desenha();
};


class Cabeca : public MembroCorpo {
public:
	Cabeca(float altura, float raio, Material *mat);
	~Cabeca() {};
	void desenha();
};

class Pessoa : public Objeto {
	Perna *pernas[2];
	Braco *bracos[2];
	Tronco *tronco;
	Cabeca *cabeca;
	
	TreeNode *arv;
	float centro[3];
	float angulo[3];
public:
	Pessoa (float altura, float larguraCabeca, float *posicao, 
	        Material *pele, Material *camisa, Material *calcao, Material *meiao);
	~Pessoa ();
	void desenha();
		
	void setAnguloCorpo(float anguloX, float anguloY, float anguloZ);
	void setPosicaoCorpo(float posX, float posY, float posZ);
	
	void setAnguloBraco(int lado, float angulo);
	void setAnguloAnteBraco(int lado, float angulo1, float angulo2, float angulo3 );
	
	void setAnguloCoxa(int lado, float angulo1, float angulo2);
	void setAnguloPerna(int lado, float angulo);
};

#endif //PESSOA_HPP_
