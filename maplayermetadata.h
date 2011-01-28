#ifndef __MAPLAYERMETADATA_H__
#define __MAPLAYERMETADATA_H__

#include "imaplayer.h"

#define MAX_METAOBJECTS 128

class IMetadataObject;

class MapLayerMetadata : public IMapLayer
{
	public:
		MapLayerMetadata();
		virtual ~MapLayerMetadata();

		virtual void Initialize(u32 tileSize, u32 count, const LayerObjectHeader *data);
		virtual void Reset();

		virtual Point2i ViewAt(Point2i pos);
		virtual BOOL CheckHit(const Rect4f &area, Rect4f &overlap, IMetadataObject **objOut) const;

		/// Called to instantiate each metadata object.
		/*! For each object in a metadata layer, this method will be called to construct
			a customized metadata object. You should override this method to instantiate your
			own custom objects. When overriding this method, do not call the base method, as
			it will instantiate a new object and may leak.

			\param entry a struct of Layer Object basic information.
			\return An instance of a custom object from IMetadataObject type.
		*/
		virtual IMetadataObject *CreateObject(const LayerObjectHeader *entry);

		// IMapLayer
		MapLayerMetadata *AsMetadata();

		// ISceneObject
		virtual void Update(f32 delta);
		virtual void Render();

	private:
		SceneNode<MAX_METAOBJECTS> cScene;
		IMetadataObject **pObjects;
		u32 iObjects;
		u32 iTileSize;
};

#endif // __MAPLAYERMETADATA_H__
