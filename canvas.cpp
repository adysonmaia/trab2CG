#include <cmath>
#include <iostream>
using namespace std;

#include "canvas.hpp"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

Canvas::Canvas(QWidget *parent)
    : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    
    /*Definindo como o focu se comporta nesse widget*/
    setFocusPolicy(Qt::StrongFocus);

    /*Altura da Viewport*/
    AlturaViewport = 70;    

    /*Inicializando posição da câmera*/
    CameraX = 1200.0;
    CameraY = 150.0;
    CameraZ = 150.0;

    /*Inicializando a Posição para onde a câmera está apontada*/
    distanciaObs = 100;
    anguloXZ = 95.0;
    anguloXY = -15.0;

    /*Ângulo da Projeção*/
    angle = 90.0;

    /*Largura das Barras de Velocidade e Ângulo*/
    this->largBarra = 30.0;
    /*Variação das Barras*/
    this->variacao  = -30.0;   
    /*Flag usada na animação da Barra*/
    this->aumentar  = true;
    /*Quantas vezes o usuário apertou 'C'*/
    this->qtdC = 0;
    /*Tempo de Animação da Bola*/   
    this->tempoAtual = 0.0;
        
    /*Inicializando fator de soma do chute*/
    pontB[0] = 0.0;
    pontB[1] = 0.0;  
    pontB[2] = 0.0;
   
    /*Evento de Tempo para a Barra*/
    tempoBarra = new QTimeLine(1000, this);
    tempoBarra->setFrameRange(0,100);
    tempoBarra->setCurveShape( QTimeLine::LinearCurve );
    tempoBarra->setLoopCount(0); //loop infinito
    connect(tempoBarra, SIGNAL(frameChanged(int)), this, SLOT(animaBarra())); 
     
    /*Inicializando angulo da Perna do Pele*/
    anguloP  = 0.0;
    
    /*variável que diz quando a perna do pele devera subir*/
    this->subir = true;

    /*Inicializando ângulos do Chute*/
    this->anguloChuteV = M_PI/4; 
    this->anguloChuteH = M_PI/2.0; 
    this->vInicialBola = 0.0;
    this->gol = false;
    
    /*Criando um Evento de Tempo para a Animação da Bola*/
    /*Cada Frame demora 1000mseg, ou seja, 1seg*/
    tempo = new QTimeLine(1000, this);
    /*Número de Frames*/
    tempo->setFrameRange(0,100);
    //loop infinito
    tempo->setLoopCount(0); 
    /*Definindo o padrão da curva de animação*/
    /*LinearCurve significa que o tempo é incrementado constantemente*/
    tempo->setCurveShape( QTimeLine::LinearCurve );
    
    connect(tempo, SIGNAL(frameChanged(int)), this, SLOT(animaPele())); 
    connect(tempo, SIGNAL(frameChanged(int)), this, SLOT(anima())); 
    
    /*Propriedade do Evento de Movimento do Mouse*/
    /*False: faz com que o botão precise ser pressionado para o evento ser ativado*/
    setMouseTracking( false );
    

}

void Canvas :: incrementaAnguloXZ(float incremento) {
	anguloXZ += incremento;
	if (anguloXZ < -360 )	anguloXZ = 0;
	if (anguloXZ >  360 )	anguloXZ = 0;
}

void Canvas :: incrementaPosicaoCameraXZ(float incremento) {
	float maxX = 1500, maxZ = 1000;
	float minX = 0, minZ = 0;
	
	CameraX += incremento*cos(anguloXZ*(M_PI/180));
	CameraZ += incremento*sin(anguloXZ*(M_PI/180));
	
	if (CameraX < minX) CameraX = minX;
	if (CameraZ < minZ) CameraZ = minZ;
	
	if (CameraX > maxX) CameraX = maxX;
	if (CameraZ > maxZ) CameraZ = maxZ;
	
}

void Canvas :: incrementaAnguloYX(float incremento) {
	float max = 60, min = -60;     
	anguloXY += incremento;

	if (anguloXY >= max ) anguloXY = max;
	if (anguloXY <= min ) anguloXY = min;    
}

void Canvas :: incrementaAlturaCamera(float incremento) {
	float min = 50.0, max = 600.0;
	
	CameraY += incremento;
  if (CameraY < min) CameraY = min;
  if (CameraY > max) CameraY = max;  
}

void Canvas :: inicializaCenario() {
  Material *matBlusa, *matCalcao, *matPele, *matMeiao;
	
	float *aBlusa, *dBlusa, *sBlusa, *eBlusa;
	float shiniBlusa = 100; 
	aBlusa = new float[4];
	dBlusa = new float[4];
	sBlusa = new float[4];
	eBlusa = new float[4];
	
	aBlusa[0] = 0.5 ; aBlusa[1] = 0.5; aBlusa[2] =0.1; aBlusa[3] = 1.0;
	dBlusa[0] = 1.0 ; dBlusa[1] = 1.0; dBlusa[2] =0.0; dBlusa[3] = 1.0;
	sBlusa[0] = 1.0 ; sBlusa[1] = 1.0; sBlusa[2] =0.0; sBlusa[3] = 1.0;
	eBlusa[0] = 0.0 ; eBlusa[1] = 0.0; eBlusa[2] =0.0; eBlusa[3] = 1.0;

	matBlusa = new Material (aBlusa,dBlusa,sBlusa,eBlusa,shiniBlusa);		
		
	float *aCalcao, *dCalcao, *sCalcao, *eCalcao;
	float shiniCalcao = 100; 
	aCalcao = new float[4];
	dCalcao = new float[4];
	sCalcao = new float[4];
	eCalcao = new float[4];
	
	aCalcao[0] = 0.2 ; aCalcao[1] = 0.2; aCalcao[2] =0.5; aCalcao[3] = 1.0;
	dCalcao[0] = 0.0 ; dCalcao[1] = 0.0; dCalcao[2] =1.0; dCalcao[3] = 1.0;
	sCalcao[0] = 0.5 ; sCalcao[1] = 0.5; sCalcao[2] =0.5; sCalcao[3] = 1.0;
	eCalcao[0] = 0.0 ; eCalcao[1] = 0.0; eCalcao[2] =0.0; eCalcao[3] = 1.0;

	matCalcao = new Material (aCalcao,dCalcao,sCalcao,eCalcao,shiniCalcao);	
	
	float *aPele, *dPele, *sPele, *ePele;
	float shiniPele = 100; 
	aPele = new float[4];
	dPele = new float[4];
	sPele = new float[4];
	ePele = new float[4];
	
	aPele[0] = 0.1 ; aPele[1] = 0.1; aPele[2] =0.1; aPele[3] = 1.0;
	dPele[0] = 0.2 ; dPele[1] = 0.2; dPele[2] =0.2; dPele[3] = 1.0;
	sPele[0] = 0.52 ; sPele[1] = 0.35; sPele[2] =0.30; sPele[3] = 1.0;
	ePele[0] = 0.0 ; ePele[1] = 0.0; ePele[2] =0.0; ePele[3] = 1.0;
	
	matPele = new Material (aPele,dPele,sPele,ePele,shiniPele);
	
	float *aMeiao, *dMeiao, *sMeiao, *eMeiao;
	float shiniMeiao = 300; 
	aMeiao = new float[4];
	dMeiao = new float[4];
	sMeiao = new float[4];
	eMeiao = new float[4];
	
	aMeiao[0] = 0.2 ; aMeiao[1] = 0.2; aMeiao[2] =0.2; aMeiao[3] = 1.0;
	dMeiao[0] = 1.0;  dMeiao[1] = 1.0; dMeiao[2] =1.0; dMeiao[3] = 1.0;
	sMeiao[0] = 0.5 ; sMeiao[1] = 0.5; sMeiao[2] =0.5; sMeiao[3] = 1.0;
	eMeiao[0] = 0.0 ; eMeiao[1] = 0.0; eMeiao[2] =0.0; eMeiao[3] = 1.0;
	
	matMeiao = new Material (aMeiao,dMeiao,sMeiao,eMeiao,shiniMeiao);
	
	float pelePos[3] = { 738.0, 29.0, 495.0 };  
	
	/*angulos de movimento do pele*/
	angAntebracos[0][0] = 200.0; angAntebracos[0][1] = 30.0; angAntebracos[0][2] = -90.0;
	angAntebracos[1][0] = 180.0; angAntebracos[1][1] = 30.0; angAntebracos[1][2] = -90.0;
	angBracos[0] = 90.0; angBracos[1] = 30.0;
  
  angCoxas[0][0] = 0.0; angCoxas[0][1] = 0.0;
  angCoxas[1][0] = 0.0; angCoxas[1][1] = 0.0;
  angPernas[0] = 0.0; angPernas[1] = 0.0;
  
  /*Criando Pele*/
  pele = new Pessoa(45.0,3.0,pelePos, matPele, matBlusa, matCalcao, matMeiao);
  /*Criando Campo*/
  campo = new Campo(1500.0,1000.0,200.0,80.0);
  /*criando a bola*/
  bola = new Bola(5.0);

  /*Criando Arquibancadas*/
  arquibancada =  new Arquibancada(Point3(0.0,0.0,-150),1500,300,300);
  arquibancada2 = new Arquibancada(Point3(0.0,0.0,-150),1000,300,300);
  arquibancada3 = new Arquibancada(Point3(0.0,0.0,-150),1500,300,300);
  arquibancada4 = new Arquibancada(Point3(0.0,0.0,-150),1000,300,300);

}


void Canvas::initializeGL()
{

    qglClearColor(Qt::white);
    inicializaCenario();
    
    GLfloat light_ambient[]=  {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]=  {0.5, 0.5, 0.5, 1.0};
    GLfloat light_specular[]= {1.0, 1.0, 1.0, 1.0};
    
    GLfloat light_position[]={750.0, 500.0, 500.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    //glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

    /*Habilitando um bocado de coisa*/
  
    // habilita o uso de iluminação
    glEnable(GL_LIGHTING); 
    //habilita a luz 0
    glEnable(GL_LIGHT0);
    //habilita a definição da cor do material a partir da cor corrente
    //glEnable(GL_COLOR_MATERIAL);
        
    //habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    
    /*glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);*/
    
    glEnable(GL_TEXTURE_2D);
    
    glShadeModel(GL_SMOOTH);
                                  
    //gerando textura
    glGenTextures(1, this->texture_id);    // 1 = uma textura;
   
    //carregando imagem da textura                                        
    this->texture_id[0] = bindTexture(QImage(":/imagens/campinho.png"));

    // Define a textura corrente
    glBindTexture( GL_TEXTURE_2D, this->texture_id[0] );
 
}

void Canvas::resizeGL(int width, int height)
{
    //glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*Previne divisão por zero*/
    if(height == 0) height = 1;

    this->largura = width;
    this->altura = height;

    GLfloat x = GLfloat(width) / height;
    
    //Projeção em Perspectiva
    gluPerspective(this->angle,x,0.1,3000.0);
          //  angle,aspect,near,far 
}

void Canvas::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

void Canvas::draw()
{
    
    /*=====================Primeira Viewport==============================*/
    /*Onde fica o desenho das Barras de Velocidade e de Ângulo*/
    glViewport(0, 0, this->largura, this->AlturaViewport);
      
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(  -40.0,-0.0,25.0,
                0.0,0.0,25.0,
                0.0,1.0,0.0 ); 

    glPushMatrix();  
   
    /*Transaladando o eixo da Primeira Viewport*/   
    glTranslatef(0.0,-20.0,-25.0);   
   
    /*Texto a ser desenhado na Tela*/
    QFont velFont("SansSerif", 10);
    QString velText("Forca: ");

    /*Cor da Fonte*/
    qglColor(Qt::blue);
    /*Renderizando Texto*/ 
    renderText(0.0, 35.0, 0.0, velText, velFont);

    /* mostra se fez gol */
    if(this->gol)
    {
    	qglColor(Qt::red);
    	QFont velFontGol("SansSerif", 30);
    	QString velGol("GOOOOOL!!!!!");
    	renderText(200.0,0.0,0.0,velGol,velFontGol);
    }
    glLineWidth(2.0); 

    /*Criando Caixa*/
    glBegin(GL_LINE_LOOP);
        qglColor(Qt::black); 
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.0,this->largBarra);
        glVertex3f(0.0,25.0,this->largBarra); 
        glVertex3f(0.0,25.0,0.0);               
    glEnd();

    glLineWidth(1.0);  

    /*Criando Preenchimento*/
    glBegin(GL_QUADS);
        qglColor(Qt::red); 
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.0,this->largBarra + this->variacao);
        glVertex3f(0.0,25.0,this->largBarra + this->variacao); 
        glVertex3f(0.0,25.0,0.0); 
    glEnd();

   glPopMatrix();
    
    /*=========================Segunda Viewport============================*/
    /*Onde fica o desenho do campo*/
    glViewport(0, this->AlturaViewport, this->largura, this->altura); 

    //Mudando posicao da camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
          
    float AtX, AtY, AtZ;
   
    AtX = cos(anguloXZ*(M_PI/180))*distanciaObs + CameraX;
    AtZ = sin(anguloXZ*(M_PI/180))*distanciaObs + CameraZ;
    AtY = CameraY + tan(anguloXY*(M_PI/180) )*distanciaObs;
    	
    gluLookAt(  CameraX,CameraY,CameraZ,
                AtX,AtY,AtZ,
                0.0,1.0,0.0 );
   
    /*Desenhando Campo*/
    campo->desenha();
   
    /*Desenhando arquibancadas*/
    arquibancada->desenha();
   
    glPushMatrix();
    glRotatef(90.0,0.0,1.0,0.0);
    glTranslatef(-1000.0,0.0,0.0);
    arquibancada2->desenha();
    glPopMatrix();
   
    glPushMatrix();
    glRotatef(180.0,0.0,1.0,0.0);
    glTranslatef(-1500.0,0.0,-1000.0);
    arquibancada3->desenha();
    glPopMatrix();
  
    glPushMatrix();
    glRotatef(270.0,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,-1500.0);
    arquibancada4->desenha();
    glPopMatrix();

    /*Desenhando Pele*/
    //qglColor(Qt::black);
    pele->setAnguloCorpo(0.0,90.0,0.0);
    
    pele->setAnguloAnteBraco(0, angAntebracos[0][0], angAntebracos[0][1], angAntebracos[0][2]);
    pele->setAnguloAnteBraco(1, angAntebracos[1][0], angAntebracos[1][1], angAntebracos[1][2]);
    pele->setAnguloBraco(0,angBracos[0]);
    pele->setAnguloBraco(1,angBracos[1]);
    pele->setAnguloCoxa(1,angCoxas[0][0], angCoxas[0][1]);
    pele->setAnguloCoxa(1,angCoxas[1][0], angCoxas[1][1]);
    pele->setAnguloPerna(1,angPernas[1]);
    pele->setAnguloPerna(0,angPernas[0]);
    pele->desenha();
   
    /*Desenhando Retas de Mudança ângulo do chute*/
    if(this->qtdC == 1)
    {
        glPushMatrix();

        glLineWidth(5.0);
  
        glTranslatef(755.0,0.0,500.0);

        glRotatef(this->anguloChuteV * 53.0,0.0,0.0,1.0);
        //glRotatef(this->anguloChuteH * 53.0,0.0,1.0,0.0);

        /*Mudança na Vertical e Na Horizontal*/
        glBegin(GL_LINES);
          qglColor(Qt::red); 
          glVertex3f(4.0,4.0,0.0);
          glVertex3f(50.0,4.0,0.0);
        glEnd();
 
        glLineWidth(1.0);

        
        glPopMatrix();
    }  
   

    /*Bola*/
    glPushMatrix(); //armazenando matrix de transformação atual
    
    /*Posicao da Bola*/
    glTranslatef(750.0 + pontB[0],7.0 + pontB[1],500.0 + pontB[2]);

    /*Desenhando a Bola*/
    bola -> desenha();
    
    glPopMatrix(); //Voltando matrix original
    
    glFlush();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

/*Evento do movimento do mouse*/
void Canvas::mouseMoveEvent(QMouseEvent *event)
{
   float dx = event->x() - lastPos.x();
   float dy = event->y() - lastPos.y();
    
   if(event->buttons() & Qt::LeftButton)
   {  	
   	incrementaAnguloXZ(dx/10);     
   	incrementaPosicaoCameraXZ(dy);
   }
   else if(event->buttons() & Qt::RightButton)
   {     
     incrementaAnguloYX(dy/10);     
   }
    
   updateGL(); 
   lastPos = event->pos();
}

/*Evento da Rodinha do Mouse, usado para movimentar a camera no eixo Y*/
void Canvas::wheelEvent(QWheelEvent *event)
{
     event->setAccepted(true);
     int numDegrees = event->delta() / 8;
     int numSteps = numDegrees ;
     
     incrementaAlturaCamera(numSteps);  
     updateGL();     
}


/*Evento do Teclado, quando uma tecla é pressionada*/
void Canvas::keyPressEvent(QKeyEvent * event) 
{
   float delta;
      
   switch (event->key())
   {
     case (Qt::Key_C): //C - chuta
       this->qtdC += 1; 
       this->configuraAnimacoes();  //Configurando as animações
       break;
     case (Qt::Key_P): //P - pausa
       this->tempo->setPaused(true); //pausando contador de tempo
       break;
     case (Qt::Key_R): //R - continua
       this->tempo->resume(); //resumindo contador de tempo
       break;
     case (Qt::Key_Up):
     	 delta = 20.0;
     	 incrementaPosicaoCameraXZ(delta);
   		 updateGL();
     	 break;
     case (Qt::Key_Down):
     	 delta = -20.0;
     	 incrementaPosicaoCameraXZ(delta);
   		 updateGL();
     	 break;
     case (Qt::Key_Left):
     	 delta = -10.0;
     	 incrementaAnguloXZ(delta);
     	 updateGL();
     	 break;
     case (Qt::Key_Right):
     	 delta = 10.0;
     	 incrementaAnguloXZ(delta);
     	 updateGL();
     	 break;
     case (Qt::Key_PageUp):
     	 delta = 10;
     	 incrementaAlturaCamera(delta);
     	 updateGL();
     	break;
     case (Qt::Key_PageDown):
     	 delta = -10;
     	 incrementaAlturaCamera(delta);
     	 updateGL();
     	 break;
     case (Qt::Key_Home):
     	 delta = 10;
     	 incrementaAnguloYX(delta);
     	 updateGL();
     	 break;
     case (Qt::Key_End):
     	 delta = -10;
     	 incrementaAnguloYX(delta);
     	 updateGL();
     	 break;
     case (Qt::Key_I):
         this->mudaAnguloChuteV(true);
         break;
     case (Qt::Key_K):
         this->mudaAnguloChuteV(false);
         break;
     case (Qt::Key_J):
         this->mudaAnguloChuteH(true);
         break;
     case (Qt::Key_L):
         this->mudaAnguloChuteH(false);
         break;
   }

}

/*Método que Simula um Lançamento Obliquo de um Objeto*/
void Canvas::chute()
{
     float vx,vy,vz;
     float x = 0.0,y = 0.0,z = 0.0;
     float angV = this->anguloChuteV;
     float angH = this->anguloChuteH;
     float count = this->tempoAtual;     
        
     vx = this->vInicialBola * cos(angV); //definindo velocidade no eixo x
     vy = this->vInicialBola * sin(angV); //definindo velocidade no eixo y
     vz = vx * cos(angH); //definindo velocidade no eixo z    

     x = x + (vx * count); //valor da componente x  do deslocamento em cada instante
     
     vy = vy - (GRAVIDADE * count); //valor da componente y da velocidade em cada instante 
     //valor da componente y do deslocamento em cada instante
     y = y + (vy * count) - (0.5 * GRAVIDADE * count * count); 
     z = z + (vz * count); //valor da componente z do deslocamento em cada instante       
   
     if(this->vInicialBola <= 0.0) this->tempo->stop();
     
     /*Engine de Colisões : ) */
     if( y <= 0.0 ) //colidiu com o chão
     {
        y = 0.0;                               
        //this->vInicialBola -= 0.8 * this->vInicialBola; //atrito (2.0 é a massa da bola)
        if (this->vInicialBola < 0.01){
          this->vInicialBola = 0.0;
          this->tempo->stop();
        }
         
     }
     if( x >= 895.0 ) //colidiu com arquibancada da frente
     {
        x = 895.0;
        if(y > 0.0) y -= ( (GRAVIDADE * count * count)/2.0 ) / 10.0;
        if(y <= 0.0)
        {  
          y = 0.0;
          this->tempo->stop();  
        }
        
     }

     if( x <= -895.0 ) //colidiu com arquibancada de trás
     {
        x = -895.0;
        if(y > 0.0) y -= ( (GRAVIDADE * count * count)/2.0 ) / 10.0;
        if(y <= 0.0)
        {  
          y = 0.0;
          this->tempo->stop();  
        }
     }

     /*Fim das Colisões*/

     /*Armazenando os Pontos atuais*/
     this->pontB[0] = x;
     this->pontB[1] = y;
     this->pontB[2] = z;
     
     if(this->campo->Gol(Point3(x,y,z))) this->gol = true;
 
     updateGL(); 
     
} 

/*Método que determina quais animações serão chamadas*/
void Canvas::configuraAnimacoes()
{
    
     if(this->qtdC == 1) //apertou 'C' pela primeira vez
     {
        this->reinicializa(); //reinicializando variáveis
        this->tempoBarra->start(); //iniciando animação da barra de velocidade
     }
     else //apertou 'C' pela segunda vez
     {
        this->qtdC = 0; //reinicializando o numero de vezes que pressionou 'C'
        this->tempoBarra->stop(); //parando animação da barra de velocidade
        
        //cálculo da velocidade em função do comprimento da barra
        this->vInicialBola = (this->variacao + 30.0) * 10.0;        

        this->tempo->start(); //iniciando contador de tempo
     }

}


/*Método de Animação da Bola*/
void Canvas::anima()
{
    /*Obtendo o valor do tempo atual do cronômetro definido*/
    //tempoAtual = this->tempo->currentTime() / 100.0; 
    this->tempoAtual += 0.3;

    this->chute(); //chute
}

/*Método de Animação do Pele*/
void Canvas::animaPele()
{
   
   /*Movimentando a perna do pele*/   
   if(this->angPernas[1] < 90.0 && this->subir) this->angPernas[1] += 60.0;
   else
   { 
       
       this->subir = false;
       this->angPernas[1] -= 60.0;
       this->angCoxas[1][0] = -90.0;        
   } 

   updateGL();
}

/*Animação da Barra de Velocidade*/
void Canvas::animaBarra()
{
    /*Aumenta a Barra*/    
    if(variacao < 0 && this->aumentar)
    {
       this->variacao += 1.0;  
        
    }
    else if(variacao > -this->largBarra) //Diminui a Barra
    {
       this->aumentar = false;
       this->variacao -= 1.0;
     
    }
    else this->aumentar = true; 

    updateGL();
    
}


/*Reinicializa valores*/
void Canvas::reinicializa()
{
    this->pontB[0] = 0.0;
    this->pontB[1] = 0.0;  
    this->pontB[2] = 0.0;
    this->angPernas[1]  = 0.0;
    this->angCoxas[1][0] = 0.0;  
    this->subir    = true;
    this->variacao = -30.0;
    this->tempoAtual = 0.0;
    this->gol = false;
     
}

/*Muda ângulo do chute no eixo vertical*/
void Canvas::mudaAnguloChuteV(bool positivo)
{
     if(this->qtdC == 1)
     {
          if(positivo)           
          {
              if(this->anguloChuteV < M_PI/2.0) this->anguloChuteV += M_PI/18; //10 graus 
          }
          else
          {
              if(this->anguloChuteV > M_PI/40.0) this->anguloChuteV -= M_PI/18; //10 graus 
          }   
    }

    updateGL();
   
}

/*Muda ângulo do chute no eixo horizontal*/
void Canvas::mudaAnguloChuteH(bool positivo)
{
     if(this->qtdC == 1)
     {
         if(positivo)           
         {
                 /*if(this->anguloChuteH < M_PI) 
                 this->anguloChuteH += M_PI/18; //10 graus */
         }
         else
         {
                 /*if(this->anguloChuteH > 0.0) 
                 this->anguloChuteH -= M_PI/18; //10 graus */
         }
           
     }
    
     //updateGL();
}











