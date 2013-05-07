#include "ogreApplication.h"
#include "frameListener.h"

ogreApplication::ogreApplication() {
	mOgre = new Root( "plugins.cfg", "ogre.cfg", "ogre.log" );
	loadConfig();
	loadResources();

	mWindow = mOgre->initialise( true,"Application" );
	createScene();
	initialise();
	//mOgre->startRendering();
}

ogreApplication::~ogreApplication() {
	delete mOgre;
}

bool ogreApplication::loadConfig() {
	if ( !mOgre->restoreConfig() ) {
		if ( !mOgre->showConfigDialog() )	{
			return 1;
		}
	}
	return 0;
}

void ogreApplication::loadResources() {
	//инициализация ресурсов
	//загрузка путей к ресурсам из конфиг-файла
	ConfigFile cf;
	cf.load("resources.cfg");

	ConfigFile::SectionIterator seci = cf.getSectionIterator();

	String secName, typeName, archName;
	while ( seci.hasMoreElements() ) {
		secName = seci.peekNextKey();
		ConfigFile::SettingsMultiMap *settings = seci.getNext();
		ConfigFile::SettingsMultiMap::iterator i;
		for ( i = settings->begin(); i != settings->end(); ++i ) {
			typeName = i->first;
			archName = i->second;
			ResourceGroupManager::getSingleton().addResourceLocation( archName, typeName, secName );
		}
	}
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void ogreApplication::initialise() {
	mViewport = mWindow->addViewport( mCamera );
	mViewport->setBackgroundColour( ColourValue( 0.0f, 0.0f, 0.0f ) );
	mCamera->setAspectRatio( Real( mViewport->getActualWidth() ) / Real( mViewport->getActualHeight() ) );

	mFrameLst = new frameListener( mWindow );
	mOgre->addFrameListener( mFrameLst );
}

int ogreApplication::run() {
	mOgre->startRendering();
	return 0;
}

void ogreApplication::createScene() {
	mSceneManager = mOgre->createSceneManager( ST_GENERIC,"sceneManager" );
	mSceneManager->setAmbientLight( ColourValue( 1, 1, 1 ) );
	mCamera = mSceneManager->createCamera( "Camera" );
	mCamera->setPosition( Vector3( 0.0f, 0.0f, 500.0f ) );
	mCamera->lookAt( Vector3( 0.0f, 0.0f, 0.0f ) );
	mCamera->setNearClipDistance( 5.0f );
	mCamera->setFarClipDistance( 5000.0f );

    LogManager::getSingletonPtr()->logMessage( "*** Initializing CEGUI ***" );
	myRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");


	Entity *ent1 = mSceneManager->createEntity( "Robot1", "robot.mesh" );
	SceneNode* node1 = mSceneManager->getRootSceneNode()->createChildSceneNode( "Robot1Node", Vector3( 0, -30, 100 ) );
	node1->yaw( Radian( Degree( -90 ) ) );
	node1->attachObject( ent1 );
    
    //CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    //CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
    
    CEGUI::Window *guiRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout("TextDemo.layout"); 
    CEGUI::System::getSingleton().setGUISheet(guiRoot);
}
