#include <Ogre.h>
#include <OgreErrorDialog.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "frameListener.h"

using namespace Ogre;
using namespace std;

class ogreApplication {
	public:
		ogreApplication();
		~ogreApplication();
		bool loadConfig();
		void loadResources();
		void initialise();
		int run();
		void createScene();
		Root* mOgre;
		//EventProcessor* m_EventProcessor;
		SceneManager* mSceneManager;
		Camera* mCamera;
		Viewport* mViewport;
		RenderWindow* mWindow;
		frameListener* mFrameLst;
        
        CEGUI::OgreRenderer* myRenderer;
};
