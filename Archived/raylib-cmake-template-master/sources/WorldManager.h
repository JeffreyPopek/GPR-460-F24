#pragma once

#include "ComponentPool.h"
#include "StackAllocator.h"
#include "GameObject.h"

#include <chrono>
#include <fstream>
#include <filesystem>
#include <stdlib.h>
#include <unordered_map>

const std::string WORLD_FILE_PATH = "../../../";
const std::string WORLD_FILE_NAME = "level.txt";
const int MAX_COMMENT_LENGTH = 256;
const char COMMENT_SYMBOL = '#';
const int POOL_SIZE = 20;
const int MAX_COMPONENTS = 20;


class WorldManager
{
public:
	// Instance Helpers
	static void CreateInstance();
	static void DestroyInstance();
	static WorldManager* GetInstance();

	// Loop
	void GameLoop();

private:

	#pragma region Functions

	// Constructor and Destructor
	WorldManager();
	~WorldManager();

	// Loop Other
	void UpdateGameObjects();
	void Render();

	// Level Serialization
	std::unordered_map<int, GameObject*> m_World;
	int GetComponentValuesFromStream(std::string stream);
	void LoadLevel();

	// GameObject Helpers
	void AddComponent(GameObject* gameobject, ComponentTypes type);
	GameObject* NewGameObject();
	void SpawnPlayer(NewTransform* transform);

	// GameObject ID
	int GetNewObjectID();

	// Component Pool
	NewTransform* AddToTransformPool();
	NewTransform* AddToTransformPool(float x, float y);

	CollisionColorChanger* AddToCollisionColorChangerPool();
	CollisionColorChanger* AddToCollisionColorChangerPool(Color newColor, Color defaultColor);

	PlayerController* AddToPlayerControllerPool();

	RectangleCollider* AddToColliderPool();

	RectangleRenderer* AddToRendererPool();
	RectangleRenderer* AddToRendererPool(float width, float height, float leftX, float leftY, Color color);
	RectangleRenderer* AddToRendererPool(Vector2 size, Vector2 left, Color color);

	#pragma endregion

	#pragma region VARIABLES

	// Static Instance
	static WorldManager* gs_WorldManager;

	// Collision Vars
	RectangleCollider* m_ActiveCollisions;
	size_t m_Collisions;

	// GameObject ID
	int m_ObjectIDIndex;

	// Component Pools & Lists
	ComponentPool<NewTransform> m_TransformComponentPool;
	std::vector<NewTransform*> m_TransformComponentList;

	ComponentPool<PlayerController> m_PlayerControllerPool;
	std::vector<PlayerController*> m_PlayerControllerList;

	ComponentPool<RectangleCollider> m_ColliderPool;
	std::vector<RectangleCollider*> m_ColliderList;

	ComponentPool<RectangleRenderer> m_RendererPool;
	std::vector<RectangleRenderer*> m_RendererList;

	ComponentPool<CollisionColorChanger> m_ColliderColorChangerPool;
	std::vector<CollisionColorChanger*> m_ColliderColorChangerList;

	// Debug
	int* m_Frames;

	#pragma endregion
};