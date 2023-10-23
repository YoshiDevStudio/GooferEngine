#include "Entity.h"
namespace Goofer
{
	Entity::Entity()
	{
		children = new Array<Entity*>();
		childrenNames = new Array<std::string>();
		childCount = 0;
	}
	Entity::~Entity()
	{
		delete children;
		delete childrenNames;
	}
	void Entity::Init()
	{
		
	}

	void Entity::Start()
	{

	}

	void Entity::Update()
	{

	}

	void Entity::AddChild(Entity*& ent)
	{
		if (ent == nullptr)
			return;
		if(ent->parent != nullptr)
			ent->parent->RemoveChild(ent);

		childrenMap.emplace(ent->GetName(), ent);
		children->PushBack(ent);
		childrenNames->PushBack(ent->GetName());
		ent->parent = this;

		childCount++;
	}

	void Entity::RemoveChild(Entity*& ent)
	{
		if (ent == nullptr || this == nullptr)
			return;
		LOG("this is not nullptr")
		//erroring because it is trying to remove an item that is not being stored
		if (childrenMap.find(ent->GetName()) == childrenMap.end() || !children->Has(ent) || !childrenNames->Has(ent->GetName()))
			return;
		childrenMap.erase(childrenMap.find(ent->GetName()));
		children->Remove(ent);
		childrenNames->Remove(ent->GetName());

		childCount--;
	}

	Entity* Entity::GetEntity(std::string name)
	{
		std::map<std::string, Entity*> map = childrenMap;
		std::size_t slashIndex = name.find("/");
		Entity* lastChildEntity = this;

		//names starting with / will be an absolute path starting from the root node
		if (slashIndex == 0)
		{
			LOG("searching from root");
			return GetRoot()->GetEntity(name.substr(1));
		}
		
		//if a ../ was found go back into the parent and continue from there
		std::size_t backIndex = name.find("../");
		if (backIndex != std::string::npos)
		{
			LOG(name.substr(backIndex + 3));
			return lastChildEntity->parent->GetEntity(name.substr(backIndex + 3));
		}
		
		//if a slash was found in the path
		while(slashIndex != std::string::npos)
		{
			if (slashIndex == 0)
			{
				//Set lastChildEntity to the last child Entity*
				std::string currentEntityName = name.substr(1);
				lastChildEntity = lastChildEntity->childrenMap[currentEntityName];
				break;
			}
			//set lastChildEntity to the next child in the list
			std::string currentEntityName = name.substr(0, slashIndex);
			if (lastChildEntity->childrenMap.find(currentEntityName) == childrenMap.end())
			{
				LOG_ERROR("Could not find Child with given name: " + currentEntityName + " from: " + lastChildEntity->GetName());
				return nullptr;
			}
			lastChildEntity = lastChildEntity->childrenMap[currentEntityName];
			//remove last childs name from name and find next slash
			name = name.substr(slashIndex);
			slashIndex = name.find("/");
		}
		return lastChildEntity;
		
	}

	Entity* Entity::GetChildByIndex(int i)
	{
		Array<Entity*> arr = *children;
		return arr[i];
	}
	Array<Entity*> Entity::GetChildren()
	{
		return *children;
	}
	void Entity::SetParent(Entity* parentEntity)
	{
		if (parentEntity->parent != nullptr)
		{
			parentEntity->parent->RemoveChild(entity);
		}
		parentEntity->AddChild(entity);
		parent = parentEntity;
	}
	void Entity::SetName(std::string entityName)
	{
		name = entityName;
	}
	std::string Entity::GetName()
	{
		if(this != nullptr)
			return name;
		else
		{
			LOG_ERROR("Unable to get Entity name");
			return "";
		}
	}
	Entity* Entity::GetRoot()
	{
		Entity* entity = this;
		while (entity->parent != nullptr)
		{
			entity = entity->parent;
		}
		return entity;
	}
}
