#ifndef __CANVAS_HPP__
#define __CANVAS_HPP__

//#include <GL/glu.h>
#include <OpenGL/glu.h>
#include <cmath>
#include "objeto.hpp"
#include "trave.hpp"
#include "point.hpp"

class Campo : public Objeto
{
	public:
		/*Conatrutor do Campo*/
		Campo(float Largura,float Altura,float TraveLarg,float alturaTrave);
		~Campo(); /*Destrutor do Campo*/
		void desenha(); /*Método Virtual Desenha*/
		// se a ponto estiver dentro do gol retorna true
		bool Gol(Point3);
	
	private:
		
		//Campo
		float Largura;     //Largura do Campo
		float Altura;      //Altura do Campo
		float TraveLarg;   //Largura da Trave
		float alturaTrave; //Altura da Trave       
		Trave *trave;      //Trave 1 
		Trave *trave2;     //Trave 2
				
};

class Bola : public Objeto
{
		float raio;
	public:
		Bola(float raio);
		~Bola() {};
		void desenha();
};

#endif

