#include "WindowLinux.h"

#include <cstdio>
#include <cstdlib>

WindowLinux::WindowLinux()
	: WindowBaseClass()
{
  RenderComponentLinux* l_renderComponentLinux = new RenderComponentLinux();
  
  // Attempt to init the window
  if(! this->Init( l_renderComponentLinux ) )
  {
    printf( this->GetErrorMessage().c_str() );
    exit(1);
  }
  
  // Attempt to init the graphical rendering system
  if( !l_renderComponentLinux->Init() )
  {
    printf( l_renderComponentLinux->GetErrorMessage().c_str() );
    exit(1);
  }
  
	// TODO set-up callbacks. we can also do a keyboard and mouse input callback, and various others
	//glfwSetWindowSizeCallback( ResizeCallback ); // register callback for reshape (if set earlier won't be called until an actual resize)
  
	m_renderComponentInterface = l_renderComponentLinux;
	m_gameInterface->Initialize( m_renderComponentInterface );
}

WindowLinux::~WindowLinux()
{
	delete m_gameInterface;
}

bool WindowLinux::Init( RenderComponentLinux *p_renderComponentLinux )
{
  // Init the GLFW for creation of the window
	if( !glfwInit() )
		return this->SetError( std::string( "ERROR: GLFW init\n" ) );
    
	// Get a list of supported video modes
	GLFWvidmode l_list[ 20 ];
	int l_numModes = glfwGetVideoModes( l_list, 20 );

	if( l_numModes < 1 )
		return this->SetError( std::string( "No desktop modes available!" ) );

  // The following code is for debugging purposes, to see the available window modes
	/*printf("Supported modes:\n");
	for (int i = 0; i < numModes; i++)
	{
		printf("\t %dx%d (%d, %d, %d)\n", list[i].Width, list[i].Height, list[i].RedBits, list[i].GreenBits, list[i].BlueBits);
	}*/

	// Pick the highest mode available
	int l_currentMode = l_numModes - 1;

  // The window creation requires hints to know the version of OpenGL to attempt to create
  p_renderComponentLinux->SetHints();

  // Attempt to open the window
	if( !glfwOpenWindow(
        l_list[ l_currentMode ].Width,
        l_list[ l_currentMode ].Height,
        l_list[ l_currentMode ].RedBits,
        l_list[ l_currentMode ].GreenBits,
        l_list[ l_currentMode ].BlueBits,
        0,
        0,
        0,
        GLFW_WINDOW
        // GLFW_FULLSCREEN
      )
    )
	{
		glfwTerminate();
		return this->SetError( std::string( "ERROR: creating load window\n" ) );
	}
  
  m_oldTime = glfwGetTime();
  
  return true;
}

void WindowLinux::Run()
{
  while( glfwGetWindowParam(GLFW_OPENED) ) //3.x.x: !glfwWindowShouldClose(window)
  {
    this->Update();
    
    glfwPollEvents();
  }
}

void WindowLinux::Update()
{
	// Fix update variables
  double l_newTime       = glfwGetTime();
	double l_deltaTime     = l_newTime - m_oldTime;
  m_oldTime              = l_newTime;
  
  int l_mousePositionX, l_mousePositionY;
  glfwGetMousePos( &l_mousePositionX, &l_mousePositionY );

	WindowBaseClass::Update(l_deltaTime, l_mousePositionX, l_mousePositionY);
  
  glfwSleep( 1. / 60. - l_deltaTime - .01 ); // Limit UPS
}

void WindowLinux::Render()
{
	WindowBaseClass::Render();
  
  BoundingBox l_bb;
  l_bb.farTopLeftX = 0;
  l_bb.farTopLeftY = 0;
  l_bb.width = 0;
  l_bb.height = 0;
  
  ((RenderComponentLinux*)m_renderComponentInterface)->RenderObject( l_bb, ENEMY1 );
  ((RenderComponentLinux*)m_renderComponentInterface)->Render();
}

std::string WindowLinux::GetErrorMessage( )
{
  return this->m_errorMessage;
}

// Set the error message and return false to be returned further on for the error management
bool WindowLinux::SetError( std::string p_errorMessage )
{
  this->m_errorMessage = p_errorMessage;
  
  return false;
}