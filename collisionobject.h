#ifndef __COLLISIONOBJECT_H__
#define __COLLISIONOBJECT_H__

#include "main.h"
#include "imetadataobject.h"

class CollisionObject : public IMetadataObject
{
	public:
		CollisionObject();
		virtual ~CollisionObject();

		// ISceneObject
		virtual void Update(f32 delta);
		virtual void Render();
};

#endif // __COLLISIONOBJECT_H__
