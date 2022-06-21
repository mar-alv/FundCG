#include "SceneManager.h"

using namespace std;

int main() {
	SceneManager scene = SceneManager();

	scene.initialize();
	scene.run();
	scene.finish();

	return 0;
}
