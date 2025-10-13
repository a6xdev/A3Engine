#include "../../pch.h"
#include "Texture.h"
#include "../common/UniqueID.h"
#include "../core/Engine.h"
#include "../core/AssetManager.h"

Texture::Texture(std::string r_name, std::string r_path, unsigned int t_slot) {
	m_resourceID = UniqueID::getNext();
	m_resourceName = r_name;
	m_resourcePath = r_path;
	m_slot = t_slot;
	AssetManager::registerResource(this);
}

void Texture::load() {
	glGenTextures(1, &m_resourceID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int w, h, ch;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(m_resourcePath.c_str(), &w, &h, &ch, 0);

	if (data) {
		GLenum format = (ch == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}

	m_loaded = true;
};

void Texture::unload() {
	glDeleteTextures(1, &m_resourceID);
	m_loaded = false;
};

void Texture::hotReload() {
	unload();
	load();
}

void Texture::bind() {
	glActiveTexture(GL_TEXTURE0 + m_slot);
	glBindTexture(GL_TEXTURE_2D, m_resourceID);
}