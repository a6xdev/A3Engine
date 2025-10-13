#include "Component.h"

#include "../Engine.h"
#include "../AssetManager.h"

#include "../../scene/GameObject.h"
#include "../../resources/Model.h"
#include "../../resources/Material.h"

ModelRenderer::ModelRenderer(GameObject* owner, std::string r_model, std::string n_material) : Component(owner) {
    m_model = AssetManager::getModelByPath(r_model);
    m_material = AssetManager::getMaterialByName(n_material);
}

void ModelRenderer::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    std::vector<Vertex> vertices = m_model->getVertices();
    std::vector<uint32_t> indices = m_model->getIndices();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    // Pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Tex
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ModelRenderer::process() {
    if (objectOwner->isVisible()) {
        if (m_material) {
            m_material->process();
            m_material->setModelMatrix(objectOwner->getGlobalModelMatrix());
        }

       glBindVertexArray(VAO);
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
       glDrawElements(GL_TRIANGLES, m_model->getIndices().size(), GL_UNSIGNED_INT, 0);
    }
}

void ModelRenderer::shutdown() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    m_model = nullptr;
    m_material = nullptr;
}

Model* ModelRenderer::getModel() {
    return m_model;
}

Material* ModelRenderer::getMaterial() {
    return m_material;
}

void ModelRenderer::setModel(std::string r_path) {
    m_model = AssetManager::getModelByPath(r_path);
}

void ModelRenderer::setMaterial(std::string r_path) {
    m_material = AssetManager::getMaterialByName(r_path);
}