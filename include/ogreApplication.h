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
        void initCEGUI();
		int run();
		void createScene();
        void createCamera();

		Root* mOgre;
		SceneManager* mSceneManager;
		Camera* mCamera;
		Viewport* mViewport;
		RenderWindow* mWindow;
		frameListener* mFrameLst;
        
        CEGUI::OgreRenderer* myRenderer;
};
