#ifndef __APP_H__
#define __APP_H__

#include <Seed.h>
using namespace Seed;

extern ISceneNode *pScene;
extern ISceneNode *pSceneStatic;

#define GRID_ROW	17
#define GRID_COL	12
#define GRID_SIZE	(GRID_ROW * GRID_COL)

class Map;
class MapLayerTiled;
class MapLayerMetadata;
class CollisionObject;

class App : public IGameApp, public IEventSystemListener, public IEventInputKeyboardListener
{
	public:
		App();
		~App();

		virtual BOOL Initialize();
		virtual BOOL Update(f32 dt);
		virtual BOOL Reset();
		virtual BOOL Shutdown();
		virtual BOOL HasError() const;

		void MovePlayer();

		// IEventSystemListener
		virtual void OnSystemShutdown(const EventSystem *ev);

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardRelease(const EventInputKeyboard *ev);
		virtual void OnInputKeyboardPress(const EventInputKeyboard *ev);

	private:
		SEED_DISABLE_COPY(App);

	protected:
		SceneNode<1024> cScene;
		SceneNode<128> cSceneStatic;
		Array<int, 10> cArray;
		Viewport	cViewport;
		Renderer	cRenderer;

		Map *pMap;
		MapLayerTiled *pLayerBg;
		MapLayerMetadata *pLayerBg2;
		CollisionObject *pPlayer;
};

#endif // __APP_H__

