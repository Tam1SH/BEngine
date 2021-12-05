#include "KEY_CODE.as"
namespace Input { 

	bool isKeyPressed(KEY_CODE key) {
		return input.__isKeyPressed(key);
	}
}
void Start()
{
	GameObject obj;
	print("EBAL");
}
void Update()
{
	if(Input::isKeyPressed(KEY_Q)) {
		print("I LOVE YOU");
	}
	//Input input;
	//GameObject obj1;
	//if(input.isKeyPressed(KEY_CODE.KEY_0)){
	//	print("A");
	//}
	//obj1.Create();
}