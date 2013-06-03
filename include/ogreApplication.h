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
        
    protected:
        Ogre::Real parsek; //= 3.08567758E16;
        Ogre::Real ligthYear; //= 9.46073047E15;
        Ogre::Real milkyWayDiameter; // = 100000 * ligthYear;
        Ogre::Real AE;
        Ogre::Real solSystemDiameter;
        Ogre::SceneNode* mCameraNode;
};
