
#include <iostream>

#include "lib/graphics.hpp"

#ifdef __APPLE__
#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFString.h>
#include <OpenGl/OpenGL.h>
// function provides some Mac OS X specific source code to load files from the resources of the application bundle.
char * resPath(char **argv, char* name, char* type ) 
{
   static char resource[1024];
   
   CFURLRef cfBundleURL = CFBundleCopyResourceURL( CFBundleGetMainBundle(),    
									   CFStringCreateWithCString(kCFAllocatorDefault,
														  name, 
														  kCFStringEncodingISOLatin1), 
									   CFStringCreateWithCString(kCFAllocatorDefault, 
														  type, 
														  kCFStringEncodingISOLatin1), 
									   NULL );
   
   
   CFStringGetCString( CFURLCopyPath(cfBundleURL),
				  resource,
				  1023,
				  kCFStringEncodingISOLatin1);
   
   return resource;
}
#pragma comment(lib, "libMacOSX.a")
#endif


int main(int argc, char* argv[]){
	Graphical::Engine graphics;
	graphics.setup();
	while(!graphics.exitRequested()){
		graphics.render();
	}
	graphics.closeup();
	return 0;
}
