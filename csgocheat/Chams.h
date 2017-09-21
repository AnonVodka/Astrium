#pragma once

#include "singleton.h"

class IMatRenderContext;
struct DrawModelState_t;
struct ModelRenderInfo_t;
class matrix3x4_t;
class IMaterial;
class Color;

class Chams
	: public Singleton<Chams>
{
	friend class Singleton<Chams>;

	Chams();
	~Chams();

public:
	void OnDrawModelExecute(void* ctx, void* state, const ModelRenderInfo_t& info, matrix3x4_t* matrix);

private:
	void OverrideMaterial(bool ignoreZ, bool flat, bool wireframe, bool glass, const Color& rgba);
	void OverrideMaterialTP(bool ignoreZ, bool flat, bool wireframe, bool glass);

	IMaterial* materialRegular = nullptr;
	IMaterial* materialRegularIgnoreZ = nullptr;
	IMaterial* materialFlatIgnoreZ = nullptr;
	IMaterial* materialFlat = nullptr;
};