#include "app.h"
#include "assets.h"
#include "map.h"
#include "maplayertiled.h"
#include "maplayermetadata.h"
#include "collisionobject.h"

App::App()
{
	pSystem->AddListener(this);
	pInput->AddKeyboardListener(this);

	cConfig.SetRendererDeviceType(Seed::RendererDeviceOpenGL14);
	//cConfig.SetVideoMode(Seed::Video_iPhonePortrait);
	cConfig.SetVideoMode(Seed::Video_800x600);
	cConfig.SetFrameRate(Seed::FrameRateLockAt60);
	//cConfig.SetPlatformSimulation(Seed::SimulateIOS3G);
	//cConfig.bDebugSprite = TRUE;
	cConfig.SetApplicationTitle("Scroller Test");
	cConfig.SetApplicationDescription("Tiled Scroller Test");
}

App::~App()
{
	pInput->RemoveKeyboardListener(this);
	pSystem->RemoveListener(this);
}

BOOL App::Initialize()
{
	IGameApp::Initialize();

	/* ------- Rendering Initialization ------- */
	cScene.SetPriority(0);
	cSceneStatic.SetPriority(20000);

	cRenderer.Add(&cScene);
	cRenderer.Add(&cSceneStatic);

	cViewport.SetRenderer(&cRenderer);
	pViewManager->Add(&cViewport);
	pRendererManager->Add(&cRenderer);

	pSceneManager->Add(&cScene);
	pSceneManager->Add(&cSceneStatic);

	pScene = &cScene;
	pSceneStatic = &cSceneStatic;
	/* ------- Rendering Initialization ------- */

	pMap = New(Map);
	pMap->SetWidth(1.0f);
	pMap->SetHeight(1.0f);
	pMap->Load(MAP_TESTE);
	//pLayerBg = pMap->GetLayerByName("Bottom")->AsTiled();
	pLayerBg = pMap->GetLayerAt(0)->AsTiled();
	if (pLayerBg)
	{
		pLayerBg->SetTileSet(SPT_TILESET_TILESET);
	}

	pLayerBg2 = NULL;
	pLayerBg2 = pMap->GetLayerAt(1)->AsMetadata();

	cScene.Add(pMap);

	pPlayer = new CollisionObject();
	pPlayer->SetPosition(0.0f, 0.0f);
	pPlayer->SetWidth(64.0f);
	pPlayer->SetHeight(64.0f);
	pPlayer->SetPriority(100);
	cScene.Add(pPlayer);

	/*
	u32 layerId = pMap->AddLayerTiled();
	pLayerBg = pMap->GetLayerAt(layerId)->AsTiled();
	if (pLayerBg)
	{
		pLayerBg->SetTileSet(SPT_TILEMAP);
		pLayerBg->Initialize(100, 100);
		pLayerBg->SetView(10, 15);
		pLayerBg->SetWrap(TRUE);
		cScene.Add(pLayerBg);
	}
	*/

	return TRUE;
}

static u32 vel = 1;
static Point2i dir(0, 1);
static Point2i inc(0, 1);
static Point2i pos(0, 0);
static f32 elapsed = 0;
BOOL App::Update(f32 dt)
{
	elapsed += dt;

	{
		inc = dir * vel;
		pos = pLayerBg->ViewAt(pos);

		// pos volta corrigido aqui se necessario.
		if (pLayerBg2)
		{
			pos = pLayerBg2->ViewAt(pos);
		}

		//pos += inc;
		elapsed = 0;
	}

	return TRUE;
}

void App::MovePlayer()
{
	Rect4f hitArea;
	IMetadataObject *obj = NULL;

	pPlayer->SetPosition(static_cast<f32>(pos.x), static_cast<f32>(pos.y));

	if (pLayerBg2->CheckHit(pPlayer->GetBoundingBox(), hitArea, &obj))
	{
		Log("COLLISION with object %s type \"%s\" - overlap area [%f, %f, %f, %f].\n", obj->GetName(), obj->GetType(), hitArea.x, hitArea.y, hitArea.width, hitArea.height);
	}
}

BOOL App::Shutdown()
{
	Delete(pMap);

	pLayerBg = NULL;
	pLayerBg2 = NULL;
	pMap = NULL;

	return IGameApp::Shutdown();
}

BOOL App::Reset()
{
	return TRUE;
}

BOOL App::HasError() const
{
	return FALSE;
}

void App::OnSystemShutdown(const EventSystem *ev)
{
	pSystem->Shutdown();
}

void App::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	switch (k.GetValue())
	{
		case Seed::KeyEscape:
		{
			pSystem->Shutdown();
		}
		break;

		case Seed::KeyUp:
		{
			dir.x = 0;
			dir.y = -1;
			vel = (vel ? vel : 10);
		}
		break;

		case Seed::KeyDown:
		{
			dir.x = 0;
			dir.y = 1;
			vel = (vel ? vel : 10);
		}
		break;

		case Seed::KeyLeft:
		{
			dir.x = -1;
			dir.y = 0;
			vel = (vel ? vel : 10);
		}
		break;

		case Seed::KeyRight:
		{
			dir.x = 1;
			dir.y = 0;
			vel = (vel ? vel : 10);
		}
		break;

		case 'a':
		case Seed::KeyA:
		{
			vel += 10;
		}
		break;

		case 'z':
		case Seed::KeyZ:
		{
			vel -= 10;
		}
		break;

		case Seed::KeySpace:
		{
			vel = 0;
		}
		break;

		default:
		{
		}
		break;
	}

	pos += inc;

	this->MovePlayer();
}

void App::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
}
