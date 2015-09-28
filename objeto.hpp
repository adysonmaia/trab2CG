#ifndef OBJETO_HPP_
#define OBJETO_HPP_

#include <QtOpenGL>
#include <QList>
#include <OpenGL/glu.h>
//#include <GL/glu.h>

class Objeto;
class TreeNode;
class Material;

class TreeNode {
  float *m;
  TreeNode *irmao;
  TreeNode *filho;
  Objeto *obj;
public: 
  TreeNode(float *matriz, TreeNode *irmao, TreeNode *filho, Objeto *objeto);
  ~TreeNode();
  void desenha();
  TreeNode* getFilho();
  void setFilho(TreeNode *filho);
  TreeNode* getIrmao();
  void setIrmao(TreeNode *irmao);
  void setMatriz(float *matriz);
};

class Objeto {
protected:
	GLUquadricObj *obj;
	QList <Material*> materiais;
public:
  Objeto();
  virtual ~Objeto() {};
  virtual void desenha() =0;
  void carregarMaterial(Material *mat);  
};

class Material {
  float *ambiente;
  float *difusa;
  float *specular;
  float *emissao;
  float shininess;
public:
  Material(float *a, float *d, float *s, float *e, float shininess);
  ~Material();
  void usarMaterial();  
};


#endif //OBJETO_HPP_
