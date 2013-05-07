#include <iostream>
#include "ogreApplication.h"

using namespace std;


int main(int argc, char **argv) {
	ogreApplication* ogre = new ogreApplication();
	return ogre->run();
};
