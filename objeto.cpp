#include "objeto.hpp"

TreeNode :: TreeNode(float *matriz, TreeNode *irmao, TreeNode *filho, Objeto *objeto) {
	this -> m = matriz;
	this -> irmao = irmao;
	this -> filho = filho;
	this -> obj = objeto;
}

TreeNode :: ~TreeNode() {
	delete[] m;
	delete filho;
	delete irmao;
}

void TreeNode :: desenha() {
	glPushMatrix();
  	glMultMatrixf(this->m);
  	this->obj->desenha();
  	if(this->filho) this->filho->desenha();
  glPopMatrix();
  if(this->irmao) this->irmao->desenha();

}

TreeNode* TreeNode :: getFilho() {
	return this->filho;
}

void TreeNode :: setFilho(TreeNode *filho){
	this -> filho = filho;
}

TreeNode* TreeNode :: getIrmao() {
	return this->irmao;
}

void TreeNode :: setIrmao(TreeNode *irmao){
	this -> irmao = irmao;
}

void TreeNode :: setMatriz(float *matriz){
	delete[] m;
	this -> m = matriz;
}

Objeto :: Objeto() {
	this->obj=gluNewQuadric();
	gluQuadricDrawStyle(this->obj, GLU_FILL);
}

void Objeto :: carregarMaterial(Material *mat) {
  materiais << mat; 
}

Material :: Material(float *a, float *d, float *s, float *e, float shini) {
  ambiente  = a;
  difusa    = d;
  specular  = s;
  emissao   = e;
  shininess = shini;
}

Material :: ~Material() {
  delete ambiente;
  delete difusa;
  delete specular;
  delete emissao;
}

void Material :: usarMaterial () {
  GLenum face = GL_FRONT;
  
  glMaterialfv(face, GL_AMBIENT   ,ambiente);
  glMaterialfv(face, GL_DIFFUSE   ,difusa);
  glMaterialfv(face, GL_SPECULAR  ,specular);
  glMaterialfv(face, GL_EMISSION  ,emissao);
  glMaterialf(face, GL_SHININESS  ,shininess);
}

