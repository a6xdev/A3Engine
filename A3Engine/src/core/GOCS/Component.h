#pragma once

#include <string>
#include <vector>

class GameObject;
class Model;
class Material;

struct Component {
	GameObject*	objectOwner	= nullptr;

	Component(GameObject* owner);

	virtual void	init()					{};
	virtual void	process()				{};
	virtual void	shutdown()				{};

	GameObject*		getObjectOwner()		{ return objectOwner; };
};

struct ModelRenderer : Component {
	Model* m_model;
	Material* m_material;
	unsigned int VAO, VBO, EBO;

	ModelRenderer(GameObject* owner, std::string r_model, std::string n_material);

	void			init() override;
	void			process() override;
	void			shutdown() override;

	Model*			getModel();
	Material*		getMaterial();

	void			setModel(std::string r_path);
	void			setMaterial(std::string r_path);
};