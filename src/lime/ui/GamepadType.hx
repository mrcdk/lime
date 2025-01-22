package lime.ui;

#if (haxe_ver >= 4.0) enum #else @:enum #end abstract GamepadType(Int) from Int to Int from UInt to UInt
{
	var UNKNOWN = 0;
	var XBOX360;
	var XBOXONE;
	var PS3;
	var PS4;
	var NINTENDO_SWITCH_PRO;
	var VIRTUAL;
	var PS5;
	var AMAZON_LUNA;
	var GOOGLE_STADIA;
	var NVIDIA_SHIELD;
	var NINTENDO_SWITCH_JOYCON_LEFT;
	var NINTENDO_SWITCH_JOYCON_RIGHT;
	var NINTENDO_SWITCH_JOYCON_PAIR;
	var MAX;

	public inline function toString():String
	{
		return switch (this) {
			case UNKNOWN: "UNKNOWN";
			case XBOX360: "XBOX360";
			case XBOXONE: "XBOXONE";
			case PS3: "PS3";
			case PS4: "PS4";
			case NINTENDO_SWITCH_PRO: "NINTENDO SWITCH PRO";
			case VIRTUAL: "VIRTUAL";
			case PS5: "PS5";
			case AMAZON_LUNA: "AMAZON LUNA";
			case GOOGLE_STADIA: "GOOGLE STADIA";
			case NVIDIA_SHIELD: "NVIDIA SHIELD";
			case NINTENDO_SWITCH_JOYCON_LEFT: "NINTENDO SWITCH JOYCON LEFT";
			case NINTENDO_SWITCH_JOYCON_RIGHT: "NINTENDO SWITCH JOYCON RIGHT";
			case NINTENDO_SWITCH_JOYCON_PAIR: "NINTENDO SWITCH JOYCON PAIR";
			case MAX: "MAX";
			default: "UNKNOWN (" + this + ")";
		}
	}
}
