
//кто-нибудь мне бл€ть объ€снит откуда в встроенных скриптах на v8 есть бл€ть какие-то другие объекты?
//ясно.  ороче эта хуйн€ сломаетс€ тогда, когда € буду переносить это на другую ось
//--------------------------------------------------------
//					STATIC VARIABLES
//--------------------------------------------------------
class RunService {

	constructor() {
		this.instance = __LOCAL_SCRIPT__._RunService;
	}
	Connect(Function) {
		this.instance.Connect(Function);
	}

}
export let runService = new RunService();
//--------------------------------------------------------
//					DYNAMIC VARIABLES
//--------------------------------------------------------

export class Transform {
	constructor(position, scale, rotation) {
		this.instance = new BEbraEngine.Transform();
	}
}
export class Vector3 {
	constructor(x, y, z) {
		this.__instance = BEbraEngine.Vector3(x, y, z);
	}
	subtract(other) {
		this.__instance.x += other.instance.x;
		this.__instance.y += other.instance.y;
		this.__instance.z += other.instance.z;
	}
	multiply(other) {
		let c = new Vector3(0, 0, 0);
		c.x = (this.__instance.y * other.instance.z) - (this.__instance.z * other.instance.y);
		c.y = (this.__instance.z * other.instance.x) - (this.__instance.x * other.instance.z);
		c.z = (this.__instance.x * other.instance.y) - (this.__instance.y * other.instance.x);
		return c;
	}
	minus(other) {
		this.__instance.x -= other.instance.x;
		this.__instance.y -= other.instance.y;
		this.__instance.z -= other.instance.z;
		return this;
	}
	multiply_scalar(scalar) {
		this.__instance.x *= scalar;
		this.__instance.y *= scalar;
		this.__instance.z *= scalar;
		return this;
	}
	normalize() {
		let length = 1.0 / Math.sqrt(this.x * this.x + this.y * this.y + this.z * this.z);
		return this.multiply_scalar(length);
	}
	ToString() {
		return "X: " + this.__instance.x + " Y: " + this.__instance.y + " Z: " + this.__instance.y;
	}


}

export class GameObject {
	constructor(position) {
		this.gameObject = new BEbraEngine.GameObject(position.instance);
	}
	Destroy() {
		this.gameObject.Destroy()
	}
	GetComponent(name) {

	}
}
