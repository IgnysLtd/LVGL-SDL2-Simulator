/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include "stdbool.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static SDL_TimerID timerID = 0;
static bool quit = false;


static void keyboard_event(SDL_KeyboardEvent * key)
{
	printf("key: %d\n", key->keysym.sym);
	switch (key->keysym.scancode)
	{
	    case SDL_SCANCODE_ESCAPE:
		    quit = true;
		    break;
	        default:
		break;
	}
}

static void mouse_event(SDL_MouseButtonEvent * button)
{
    printf("*****\nSTART Mouse Event\n*****\n");

    if (SDL_PRESSED == button->state)
    {
        printf("Button Pressed\n");
    }
    else if (SDL_RELEASED == button->state)
    {
        printf("Button Released\n");
    }
    else
    {
        printf("Button State not known!");
        return;
    }


    printf("Type: %u\n",      button->type);
    printf("timestamp: %u\n", button->timestamp);
    printf("windowID: %u\n",  button->windowID);

    printf("which: %u\n",     button->which);
    printf("button: %u\n",    button->button);
    printf("clicks: %u\n",    button->clicks);
    printf("coordinate x: %d\ncoordinate y:%d\n", (int32_t)button->x, (int32_t)button->y);
    
    printf("*****\nEND Mouse Event\n*****\n\n\n");

}

static Uint32 callback( Uint32 interval, void* param )
{
	(void) interval;
	(void) param;
    //Print callback message
    printf( "Render callback\n");
    //MODULE_DISPLAY_update();
    if (timerID)
    {
    	SDL_RemoveTimer(timerID);
    }
    timerID = 0;
    return 0;
}

static void event_process( void )
{
    SDL_Event e;
	while( SDL_PollEvent( &e ) != 0 )
	{
		switch (e.type)
		{
		    case SDL_QUIT:
		    	quit = true;
		    	return;
		    case SDL_KEYDOWN:
		    	keyboard_event(&e.key);
		    	return;
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
                mouse_event(&e.button);
                return;
		    case SDL_USEREVENT:
		    	//uint32_t delay = MODULE_DISPLAY_lv_tasks();
		    	//if (delay != 0xFFFFFFFF)
		    	//{
		    		if (timerID != 0)
		    		{
		    			SDL_RemoveTimer(timerID);
		    		}
		    		timerID = SDL_AddTimer( 5000, callback, NULL);
		    	//}
            default:
		    	return;
		}
	}
}



int main( int argc, char* args[] )
{ 
	//The window we'll be rendering to
    printf("Starting the Application\n");
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );
            
            //Hack to get window to stay up
            
            while( quit == false )
            {
                event_process();
			    fflush(stdout);
            }
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );
    SDL_RemoveTimer( timerID );
	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
