using namespace std;

#include "SceneManager.h"

int main() {
	SceneManager scene = SceneManager();

	scene.initialize();

	scene.run();

	scene.finish();

	return 0;
}
