#ifndef POINT_HPP_
#define POINT_HPP_

class Point3;

class Point3
{
private:
	float X,Y,Z; /// coordenadas do ponto
public:

	/**
	 * construtor padrao, todas as coordenadas sao setadas para 0
	 */
	Point3();
	
	/**
	 * construtor que recebe as 3 coordenadas
	 * \param X coordenada X
	 * \param Y coordenada Y
	 * \param Z coordenada Z
	 */
	Point3(float X,float Y,float Z);
	
	/**
	 * muda o valor de X
	 * \param X nova coordenada de X
	 */
	void setX(float X);
	
	/**
	 * muda o valor de Y
	 * \param X nova coordenada de Y
	 */
	void setY(float Y);
	
	/**
	 * muda o valor de Z
	 * \param X nova coordenada de Z
	 */
	void setZ(float Z);
	
	/**
	 * retona X
	 */
	float x() const;
	
	/**
	 * retona Y
	 */
	float y() const;
	
	/**
	 * retona Z
	 */
	float z() const;
	
	/** multiplica as coordenadas de um ponto por um dado fator e retorna a referencia para esse ponto
	 * \param fator fator de multiplicacao
	 * \return Point3 retorna a referencia do ponto
	 */
	Point3 & operator*=(float fator);
	
	/**
	 * soma as coordenadas correspondetes e retorna uma referencia para o ponto
	 * \param point ponto para somar com o atual
	 * \return Point3 retorna a referencia do ponto
	 */
	Point3 & operator+= (const Point3 & point);
	
	/**
	 * subtrai as coordenadas correspondetes e retorna uma referencia para o ponto
	 * \param point point ponto para subtrair com o atual
	 * \return Point3 retorna a referencia do ponto
	 */
	//Vector3 & operator-=(const Point3 & point);
	
	/** divide as coordenadas de um ponto por um dado fator e retorna a referencia para esse ponto
	 * \param divisor fator de divisao
	 * \return Point3 retorna a referencia do ponto
	 */
	Point3 & operator/=(float divisor);
	
	/**
	 * \return true se os pontos sao iguais
	 * \return false caso contrario
	 */
	bool operator==(const Point3 & point) const;
	
	/**
	 * \return true se todas as coordenadas dos pontos sao diferentes
	 * \return false caso contrario
	 */
	bool operator!=(const Point3 & point) const;
		
	Point3 & operator=(const Point3 & point);
};

#endif /*POINT_HPP_*/





