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

	ModelRenderer(GameObject* owner, std::string r_model, std::string n_material);

	void			init() override;
	void			process() override;
	void			shutdown() override;

	Model*			getModel();

	void			setModel(std::string r_path);
};