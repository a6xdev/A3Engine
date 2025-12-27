#include "asset.hpp"
#include <stb/stb_image.h>

Texture2D::Texture2D(unsigned int uid, std::string path, bool loadInstantly) {
	m_assetUID = uid;
	m_assetPath = path;
	m_assetType = AssetType::TEXTURE_2D;

	if (loadInstantly) { Load(); }
}

Texture2D::~Texture2D() {
	Unload();
}

void Texture2D::Load() {
	glGenTextures(1, &m_assetUID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int w, h, ch;
	unsigned char* data = stbi_load(m_assetPath.c_str(), &w, &h, &ch, 0);

	if (data) {
		GLenum format = (ch == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		std::cout << "TEXTURE2D::TEXTURE_LOADED: " << m_assetPath << std::endl;
	}
	else {
		std::cout << "TEXTURE2D::ERROR_LOAD_TEXTURE: " << m_assetPath << std::endl;
	}

	m_isLoaded = true;
}

void Texture2D::Unload() {
	glDeleteTextures(1, &m_assetUID);
	m_isLoaded = false;
}

void Texture2D::HotReload() {
	Unload();
	Load();
}

void Texture2D::bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_assetUID);
}