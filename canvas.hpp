#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QWidget>
#include <QtOpenGL>
#include <QTimeLine>
#include "campo.hpp"
#include "pessoa.hpp"
#include "arquibancada.hpp"
#include <iostream>

#define MAX_TEXTURES 5
#define GRAVIDADE 9.80

using namespace std;
class Canvas : public QGLWidget
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = 0);

private slots:
    void anima();
    void animaPele();
    void animaBarra();
    void reinicializa();
    
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    
    void inicializaCenario();
    
    /* funcoes do mouse e teclado */
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent * event);     
    
    /* animacao */
    void chute();
    void configuraAnimacoes();    
    void mudaAnguloChuteV(bool positivo);
    void mudaAnguloChuteH(bool positivo);    

    //funcoes da camera
    void incrementaAnguloXZ(float incremento);
    void incrementaAnguloYX(float incremento);
    void incrementaAlturaCamera(float incremento);
    void incrementaPosicaoCameraXZ(float incremento);
    

private:
    void draw();
    Pessoa *pele; //ponteiro para a classe pessoa, bonequinho do pelé
    Campo  *campo; //ponteiro para a classe Campo
    Bola *bola; //a bola
    /*Arquibancadas*/
    Arquibancada *arquibancada;
    Arquibancada *arquibancada2;
    Arquibancada *arquibancada3;
    Arquibancada *arquibancada4;
    
    GLuint texture_id[MAX_TEXTURES]; // vetor com os números das texturas  
    QTimeLine *tempo; //Evento de Tempo da Bola
    QTimeLine *tempoBarra; //Evento de Tempo da Barra
    
    //Camera
    float CameraX, CameraY, CameraZ; //posicao da camera
    float anguloXZ;        //angulo que a camera faz no plano xz
    float anguloXY;        //angulo que a camera faz no plano xy;
    float distanciaObs;    //distancia entre a camera e o ponto onde ela olha
   
    float angle; //ângulo da projeção
    QPoint lastPos; 
    

    float pontB[3]; //posição da bola na hora do chute
    float anguloP; //angulo da Perna do Pele
    bool subir; //flag que diz quando a perna do pelé deve subir
    int qtdC;   //armazena quantas vezes o usuario pressionou 'C'

    int largura; //largura da janela
    int altura;  //altura da janela
    int AlturaViewport ; //altura da Viewport
    float largBarra; //Largura das Barras
    float variacao;  //variacao da animação das barras
    bool aumentar;   //flag usada na animacao da barra
    float tempoAtual; //tempo da animação da bola 
    
    float anguloChuteV; //ângulo do chute na Vertical
    float anguloChuteH; //ângulo do chute na Horizontal
    float vInicialBola;
        
    //angulos do pele para animacao
    float angAntebracos[2][3];
    float angBracos[2];
    float angCoxas[2][2];
    float angPernas[2];
    
    // diz se foi gol
    bool gol;
 
};

#endif

