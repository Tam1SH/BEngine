#include "KEY_CODE.as"
namespace Input { 

	bool isKeyPressed(KEY_CODE key) {
		return input.__isKeyPressed(key);
	}
}
///namespace Camera { 
	//Camera MainCamera() {
	//	return __mainCamera;
	//}
//}
GameObject@ obj1;
array<GameObject@> objects;
void Start()
{
	GameObject obj(Vector3(0,40,0));

	@obj1 = @obj;

	print("EBAL");
}
void Update()
{
	GameObject obj(Vector3(0,40,0));

	if(Input::isKeyPressed(KEY_Q)) {
		print("I LOVE YOU");
	}
	if(Input::isKeyPressed(KEY_Z)) {
		GameObject obj(Vector3(0,40,0));
		objects.insertLast(obj);
	}
	if(Input::isKeyPressed(KEY_T)) {
		if(objects.length() != 0)
			objects.removeLast();
	}
	//Input input;
	//GameObject obj1;
	//if(input.isKeyPressed(KEY_CODE.KEY_0)){
	//	print("A");
	//}
	//obj1.Create();
}