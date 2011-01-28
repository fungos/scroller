#include "maplayermetadata.h"
#include "imetadataobject.h"
#include "collisionobject.h"
#include "triggerobject.h"
#include "spawnerobject.h"

MapLayerMetadata::MapLayerMetadata()
	: pObjects(NULL)
	, iObjects(0)
	, iTileSize(0)
{
}

MapLayerMetadata::~MapLayerMetadata()
{
	this->Reset();
}

void MapLayerMetadata::Reset()
{
	for (u32 i = 0; i < iObjects; i++)
	{
		Delete(pObjects[i]);
	}

	pMemoryManager->Free(pObjects);
	pObjects = NULL;
	iObjects = 0;
}

void MapLayerMetadata::Initialize(u32 tileSize, u32 count, const LayerObjectHeader *data)
{
	iTileSize = tileSize;
	iObjects = count;
	pObjects = (IMetadataObject **)pMemoryManager->Alloc(sizeof(IMetadataObject *) * iObjects);
	for (u32 i = 0; i < iObjects; i++)
	{
		pObjects[i] = this->CreateObject(&data[i]);
	}
}

IMetadataObject *MapLayerMetadata::CreateObject(const LayerObjectHeader *entry)
{
	const char *type = _S(entry->iTypeId);
	IMetadataObject *obj = NULL;

	if (STRCMP(type, "collision") == 0)
	{
		obj = New(CollisionObject());
	}
	else if (STRCMP(type, "trigger") == 0)
	{
		obj = New(TriggerObject());
	}
	else if (STRCMP(type, "spawner") == 0)
	{
		obj = New(SpawnerObject());
	}

	obj->SetNameId(entry->iNameId);
	obj->SetTypeId(entry->iTypeId);
	obj->LoadProperties(entry->iPropertiesId);
	obj->SetPosition(entry->fPosX * iTileSize, entry->fPosY * iTileSize);
	obj->SetWidth(entry->fWidth * iTileSize);
	obj->SetHeight(entry->fHeight * iTileSize);

	cScene.Add(obj);

	return obj;
}

Point2i MapLayerMetadata::ViewAt(Point2i pos)
{
	cScene.SetPosition(-pos.x / static_cast<f32>(pScreen->GetWidth()), -pos.y / static_cast<f32>(pScreen->GetHeight()));

	return pos;
}

BOOL MapLayerMetadata::CheckHit(const Rect4f &area, Rect4f &overlap, IMetadataObject **objOut) const
{
	for (u32 i = 0; i < iObjects; i++)
	{
		IMetadataObject *obj = pObjects[i];
		if (obj->CheckHit(area, overlap))
		{
			*objOut = obj;
			return TRUE;
		}
	}

	return FALSE;
}

void MapLayerMetadata::Update(f32 dt)
{
	cScene.Update(dt);
}

void MapLayerMetadata::Render()
{
	for (u32 i = 0; i < iObjects; i++)
	{
		IMetadataObject *obj = pObjects[i];
		obj->Render();
	}
}

MapLayerMetadata *MapLayerMetadata::AsMetadata()
{
	return this;
}
