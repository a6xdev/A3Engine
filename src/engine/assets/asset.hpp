#pragma once

#include "../Core.hpp"

class A3_API Asset {
public:
	enum AssetType {
		TEXTURE_2D,
		SHADER
	};

	Asset() {};
	~Asset() {};

	virtual void Load() {}; // Load on GPU
	virtual void Unload() {}; // Unload on GPU
	virtual void HotReload() {}; // Reload the Asset

	AssetType GetAssetType() const { return m_assetType; }
	bool IsLoaded() const { return m_isLoaded; }
protected:
	AssetType m_assetType;
	unsigned int m_assetUID = 0;
	std::string m_assetPath = "";

	bool m_isLoaded = false;
};

// TEXTURE2D
class A3_API Texture2D : public Asset {
public:
	Texture2D(unsigned int uid, std::string path, bool loadInstantly = true);
	~Texture2D();

	void Load() override;
	void Unload() override;
	void HotReload() override;

	void bind(unsigned int slot = 0);
};