#include "ogreApplication.h"
#include "frameListener.h"

ogreApplication::ogreApplication() {
	mOgre = new Root( "plugins.cfg", "ogre.cfg", "ogre.log" );
	loadConfig();
	loadResources();

	mWindow = mOgre->initialise( true, "Application" );
	createScene();
	initialise();
	//mOgre->startRendering();
    
    parsek = 3.08567758e+16;
    ligthYear = 9.46073047e+15;
    milkyWayDiameter = 100000 * ligthYear;
    AE = 149597871000.0;
    solSystemDiameter = AE * 110;
    cout << "Size of Ogre::Real: " << sizeof(Ogre::Real) << " size of parsek: " << sizeof(double) << endl;
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

	mFrameLst = new frameListener( mWindow, mCamera );
	mOgre->addFrameListener( mFrameLst );
}

int ogreApplication::run() {
	mOgre->startRendering();
	return 0;
}

void ogreApplication::createScene() {
	mSceneManager = mOgre->createSceneManager( ST_GENERIC, "ExteriorSceneManager" );
	mSceneManager->setAmbientLight( ColourValue( 1, 1, 1 ) );
	createCamera();

    initCEGUI();

    //mSceneManager->setWorldGeometry("terrain.cfg");
    
    /*
	Entity *robotEntity = mSceneManager->createEntity( "Robot1", "robot.mesh" );
	SceneNode* robotNode = mSceneManager->getRootSceneNode()->createChildSceneNode( "Robot1Node", Vector3( 0, -30, 100 ) );
	robotNode->yaw( Radian( Degree( -90 ) ) );
	robotNode->attachObject( robotEntity );
    */
    
    Real solDiameter = 1.392E9;
    Entity *starEntity = mSceneManager->createEntity( "Star1", "Star.mesh" );
    starEntity->setMaterialName("StarColor");
	SceneNode* starNode = mSceneManager->getRootSceneNode()->createChildSceneNode( "Star1Node", Vector3( solDiameter * 10, 0, 0 ) );
	starNode->yaw( Radian( Degree( -90 ) ) );
	starNode->attachObject( starEntity );
    starNode->scale(solDiameter, solDiameter, solDiameter);

    /*
    Ogre::Material starMaterial  = MaterialManager::getSingleton().create("StarColor", "General", true);
    Ogre::Technique* starTechnique = starMaterial->getTechnique(0);
	Ogre::Pass* starPass = starTechnique->getPass(0);
    */
    
    Real planetDiameter = 6371000;
    Entity *planetEntity = mSceneManager->createEntity( "Planet1", "Planet.mesh" );
    
	SceneNode* planetNode = mSceneManager->getRootSceneNode()->createChildSceneNode( "Planet1Node", Vector3( planetDiameter * 20, 0, 0 ) );
	planetNode->yaw( Radian( Degree( -90 ) ) );
	planetNode->attachObject( planetEntity );
    planetNode->scale(planetDiameter, planetDiameter, planetDiameter);
    
    //Ogre::MaterialPtr planetMaterial  = MaterialManager::getSingleton().create("Planet", "General", true);
    //planetMaterial->load();
    /*
    Ogre::Technique* planetTechnique = planetMaterial->getTechnique(0);
	Ogre::Pass* planetPass = planetTechnique->getPass(0);
    Ogre::TextureUnitState* planetTextureUnit = planetPass->createTextureUnitState();
	planetTextureUnit->setTextureName("rockbeach05.dds", Ogre::TEX_TYPE_2D);
	planetTextureUnit->setTextureCoordSet(0);
    
    */
    //planetEntity->setMaterialName("Planet");
    //planetEntity->setMaterial(planetMaterial);


    //Entity *shipEntity = mSceneManager->createEntity( "PlayerShip", "RZR-002.mesh" );
    //mCameraNode->attachObject(shipEntity);
}

void ogreApplication::initCEGUI() {
    LogManager::getSingletonPtr()->logMessage( "*** Initializing CEGUI ***" );
	myRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
    
    // Demo layout
    //CEGUI::Window *guiRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout("TextDemo.layout"); 
    //CEGUI::System::getSingleton().setGUISheet(guiRoot);
}

void ogreApplication::createCamera(void) {
    mCameraNode = mSceneManager->getRootSceneNode()->createChildSceneNode( "CameraNode", Vector3( 0.0f, 0.0f, 500.0f ) );
    mCamera = mSceneManager->createCamera( "Camera" );
	//mCamera->setPosition( Vector3( 0.0f, 0.0f, 500.0f ) );
	mCamera->lookAt( Vector3( 0.0f, 0.0f, 0.0f ) );
	mCamera->setNearClipDistance( 5.0f );
	mCamera->setFarClipDistance( solSystemDiameter );
    mCameraNode->attachObject(mCamera);
    //mCamera->setFarClipDistance( 100000.0f );
}
