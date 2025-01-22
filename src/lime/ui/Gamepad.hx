package lime.ui;

import lime._internal.backend.native.NativeCFFI;
import lime.app.Event;
import lime.system.CFFI;

using StringTools;

#if !lime_debug
@:fileXml('tags="haxe,release"')
@:noDebug
#end

private typedef GamepadExtraInfoT = {
	path:String,
	serial:String,
	usb: {
		vendor:Int,
		product:Int,
		version:Int,
		firmware:Int,
	},
	guid: {
		vendor:Int,
		product:Int,
		version:Int,
		crc16:Int,
	},
}

@:forward
abstract GamepadExtraInfo(GamepadExtraInfoT) from Dynamic {
	@:to inline function toString():String {
		var result = '---GamepadExtraInfo---';
		result += '\n\tPath: ${this.path}';
		if(this.serial != null) {
			result += '\n\tSerial: ${this.serial}';
		}
		result += '\n\tUSB -> Vendor: 0x${this.usb.vendor.hex().lpad("0", 4)} Product: 0x${this.usb.product.hex().lpad("0", 4)} Version: 0x${this.usb.version.hex().lpad("0", 4)} Firmware: 0x${this.usb.firmware.hex().lpad("0", 4)}';
		result += '\n\tGUID -> Vendor: 0x${this.guid.vendor.hex().lpad("0", 4)} Product: 0x${this.guid.product.hex().lpad("0", 4)} Version: 0x${this.guid.version.hex().lpad("0", 4)} CRC16: 0x${this.guid.crc16.hex().lpad("0", 4)}';
		result += '\n----------------------';
		return result;
	}
}

@:access(lime._internal.backend.native.NativeCFFI)
@:access(lime.ui.Joystick)
class Gamepad
{
	public static var devices = new Map<Int, Gamepad>();
	public static var onConnect = new Event<Gamepad->Void>();

	public var connected(default, null):Bool;
	public var guid(get, never):String;
	public var id(default, null):Int;
	public var name(get, never):String;
	public var type(get, never):GamepadType;
	public var extraInfo(get, never):GamepadExtraInfo;
	public var steamInputHandle(get, never):String;
	public var onAxisMove = new Event<GamepadAxis->Float->Void>();
	public var onButtonDown = new Event<GamepadButton->Void>();
	public var onButtonUp = new Event<GamepadButton->Void>();
	public var onDisconnect = new Event<Void->Void>();
	public var onSteamInputHandleChanged = new Event<Gamepad->Void>();

	public function new(id:Int)
	{
		this.id = id;
		connected = true;
	}

	public static function addMappings(mappings:Array<String>):Void
	{
		#if (lime_cffi && !macro)
		#if hl
		var _mappings = new hl.NativeArray<String>(mappings.length);
		for (i in 0...mappings.length)
			_mappings[i] = mappings[i];
		var mappings = _mappings;
		#end
		NativeCFFI.lime_gamepad_add_mappings(mappings);
		#end
	}

	@:noCompletion private static function __connect(id:Int):Void
	{
		if (!devices.exists(id))
		{
			var gamepad = new Gamepad(id);
			devices.set(id, gamepad);
			onConnect.dispatch(gamepad);
		}
	}

	@:noCompletion private static function __disconnect(id:Int):Void
	{
		var gamepad = devices.get(id);
		if (gamepad != null) gamepad.connected = false;
		devices.remove(id);
		if (gamepad != null) gamepad.onDisconnect.dispatch();
	}

	// Get & Set Methods
	@:noCompletion private inline function get_guid():String
	{
		#if (lime_cffi && !macro)
		return CFFI.stringValue(NativeCFFI.lime_gamepad_get_device_guid(this.id));
		#elseif (js && html5)
		var devices = Joystick.__getDeviceData();
		return devices[this.id].id;
		#else
		return null;
		#end
	}

	@:noCompletion private inline function get_name():String
	{
		#if (lime_cffi && !macro)
		return CFFI.stringValue(NativeCFFI.lime_gamepad_get_device_name(this.id));
		#elseif (js && html5)
		var devices = Joystick.__getDeviceData();
		return devices[this.id].id;
		#else
		return null;
		#end
	}

	@:noCompletion private inline function get_extraInfo():GamepadExtraInfo
		{
			#if (lime_cffi && !macro)
			return NativeCFFI.lime_gamepad_get_device_extra_info(this.id);
			#else
			return {
				vendor: 0,
				product: 0,
				product_version: 0,
				firmware_version: 0,
				serial: null,
				path: null,
				guid_info: {
					vendor: 0,
					product: 0,
					version: 0,
					crc16: 0,
				},
			};
			#end
		}

	@:noCompletion private inline function get_type():GamepadType
	{
		#if (lime_cffi && !macro)
		return NativeCFFI.lime_gamepad_get_type(this.id);
		#else
		return UNKNOWN;
		#end
	}

	@:noCompletion private inline function get_steamInputHandle():String
	{
		#if (lime_cffi && !macro)
		return CFFI.stringValue(NativeCFFI.lime_gamepad_get_device_steam_input_handle(this.id));
		#else
		return null;
		#end
	}
}
