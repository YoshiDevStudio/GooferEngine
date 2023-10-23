#pragma once
#include <string>
#include <vector>
#include <map>

#include "Core.h"
#include "Array.h"
namespace Goofer
{
	class Entity
	{
	public:
		Entity();
		~Entity();

		virtual void Init();
		virtual void Start();
		virtual void Update();

		void AddChild(Entity*& ent);
		void RemoveChild(Entity*& ent);
		Entity* GetEntity(std::string name);
		Entity* GetChildByIndex(int i);
		Array<Entity*> GetChildren();

		void SetParent(Entity* parentEntity);
		void SetName(std::string entityName);
		std::string GetName();

		Entity* GetRoot();

		int childCount = 0;
		std::string name = "Entity";
		Entity* entity = this;
		Entity* parent = nullptr;

	private:
		Array<Entity*>* children;
		Array<std::string>* childrenNames;
		std::map<std::string, Entity*> childrenMap;
	};
}

