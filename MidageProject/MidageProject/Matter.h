#pragma once
#include "GameObject.h"

enum Matter_Kind {
	MATTER_DEFAULT,
	TREE
};

enum Matter_Type {
	TREE_NEEDLED_HIGH,
	TREE_NEEDLED_MIDDLE,
	TREE_NEEDLED_LOW,
	TREE_ROOT
};

class Matter : public GameObject
{
private:
	Matter_Kind matterKind;

public:
	Matter();
	~Matter();

	virtual HRESULT Init(D2D_POINT_2L id, D2D_POINT_2L frame, Matter_Kind matterKind, int type, GameObject_Kind kind = MATTER);
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	virtual HRESULT PaletteInit(D2D_POINT_2F pos, D2D_POINT_2L frame, Matter_Kind matterKind, int type, GameObject_Kind kind = MATTER);
	virtual void PaletteUpdate(void) override;
	virtual void PaletteRender(void) override;

	void SetName(int type)override;
	Matter_Kind GetMatterKind(void) { return matterKind; }
};

