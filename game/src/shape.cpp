#include "../include/shape.hpp"

void shape::draw(glm::mat4 mModel)
{
    GLuint matrixLocation = glGetUniformLocation(this->mShader->getShaderProgram(), "matrixModel");
    glBindVertexArray(this->mVao);
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr((mModel * this->matrix4x4)));
    glUseProgram(this->mShader->getShaderProgram());
    glBindBuffer(GL_ARRAY_BUFFER, this->mVbo);
    glDrawArrays(GL_TRIANGLES, 0, this->Mesh.size() * 3);
}

void shape::configureVbo()
{
    glGenBuffers(1, &this->mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->mVbo);
    glBufferData(GL_ARRAY_BUFFER, this->Mesh.size() * sizeof(triangle), this->Mesh.data(), this->mDrawType);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

std::vector<triangle> shape::loadShapeFromFile(const char* nameCase, const char* nameFile)
{
    loadObjFile obj = loadObjFile(nameCase, nameFile);
    return (obj.getMesh());
}

shape::shape(const char* name, const char* caseToLoad, const char* fileToLoad, shader* mShader, unsigned int drawtype)
{
    this->name = name;
    this->mDrawType = drawtype;
    this->mShader = mShader;

    this->Mesh = this->loadShapeFromFile(caseToLoad, fileToLoad);


    glGenVertexArrays(1, &this->mVao);
	glBindVertexArray(this->mVao);
	this->configureVbo();
}

shape::~shape() { }