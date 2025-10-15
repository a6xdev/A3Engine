#include "Component.h"

#include "../Engine.h"
#include "../AssetManager.h"

#include "../../scene/GameObject.h"
#include "../../resources/Model.h"
#include "../../resources/Material.h"

ModelRenderer::ModelRenderer(GameObject* owner, std::string r_model, std::string n_material) : Component(owner) {
    m_model = AssetManager::getModelByPath(r_model);

    for (int i = 0; i < m_model->GLTFNodes.size(); i++) {
        auto* GLTFNode = m_model->GLTFNodes[i];
        if (GLTFNode->hasMaterial()) {
            // They already load your own texture
            return;
        }
        else {
            GLTFNode->m_material = AssetManager::getMaterialByName(n_material);
        }
    }
}

void ModelRenderer::init() {
    for (int i = 0; i < m_model->GLTFNodes.size(); i++) {
        auto* GLTFNode = m_model->GLTFNodes[i];

        glGenVertexArrays(1, &GLTFNode->VAO);
        glGenBuffers(1, &GLTFNode->VBO);
        glGenBuffers(1, &GLTFNode->EBO);
        glBindVertexArray(GLTFNode->VAO);

        std::vector<Vertex> vertices = GLTFNode->getVertices();
        std::vector<uint32_t> indices = GLTFNode->getIndices();

        glBindBuffer(GL_ARRAY_BUFFER, GLTFNode->VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GLTFNode->EBO);
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
}

void ModelRenderer::process() {
    for (int i = 0; i < m_model->GLTFNodes.size(); i++) {
        auto* GLTFNode = m_model->GLTFNodes[i];

        if (objectOwner->isVisible()) {
            if (GLTFNode->m_material && not GLTFNode->m_material->isLoaded()) { GLTFNode->m_material->load(); }

            if (GLTFNode->m_material) {
                GLTFNode->m_material->setModelMatrix(objectOwner->getGlobalModelMatrix() * GLTFNode->getNodeMatrix());
                GLTFNode->m_material->process();
            }

            glBindVertexArray(GLTFNode->VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GLTFNode->EBO);
            glDrawElements(GL_TRIANGLES, GLTFNode->getIndices().size(), GL_UNSIGNED_INT, 0);
        }
        else {
            if (GLTFNode->m_material && GLTFNode->m_material->isLoaded()) {
                GLTFNode->m_material->unload();
            }
        }
    }
}

void ModelRenderer::shutdown() {
    for (int i = 0; i < m_model->GLTFNodes.size(); i++) {
        auto* GLTFNode = m_model->GLTFNodes[i];
        GLTFNode->m_material = nullptr;

        glDeleteVertexArrays(1, &GLTFNode->VAO);
        glDeleteBuffers(1, &GLTFNode->VBO);
        glDeleteBuffers(1, &GLTFNode->EBO);
    }

    m_model = nullptr;
}

Model* ModelRenderer::getModel() {
    return m_model;
}

void ModelRenderer::setModel(std::string r_path) {
    m_model = AssetManager::getModelByPath(r_path);
}
