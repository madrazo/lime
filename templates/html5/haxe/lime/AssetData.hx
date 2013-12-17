<<<<<<< HEAD
package lime;


import lime.utils.Assets;


class AssetData {

	private static var initialized:Bool = false;

	public static var className = new Map <String, Dynamic> ();
	public static var library = new Map <String, LibraryType> ();
	public static var path = new Map <String, String> ();
	public static var type = new Map <String, AssetType> ();
	
	public static function initialize():Void {
		
		if (!initialized) {
			
			::if (assets != null)::::foreach assets::::if (type == "font")::className.set ("::id::", nme.lime_::flatName::);::else::path.set ("::id::", "::resourceName::");::end::
			type.set ("::id::", Reflect.field (AssetType, "::type::".toUpperCase ()));
			::end::::end::
			::if (libraries != null)::::foreach libraries::library.set ("::name::", Reflect.field (LibraryType, "::type::".toUpperCase ()));
			::end::::end::
			initialized = true;
			
		} //initialized
		
	} //initialize
	
	
} //AssetData


::foreach assets::::if (type == "font")::class lime_::flatName:: extends flash.text.Font { }::end::
=======
package lime;


import lime.utils.Assets;


class AssetData {

	private static var initialized:Bool = false;

	public static var className = new Map <String, Dynamic> ();
	public static var library = new Map <String, LibraryType> ();
	public static var path = new Map <String, String> ();
	public static var type = new Map <String, AssetType> ();
	
	public static function initialize():Void {
		
		if (!initialized) {
			
			::if (assets != null)::::foreach assets::::if (type == "font")::className.set ("::id::", nme.lime_::flatName::);::else::path.set ("::id::", "::resourceName::");::end::
			type.set ("::id::", Reflect.field (AssetType, "::type::".toUpperCase ()));
			::end::::end::
			::if (libraries != null)::::foreach libraries::library.set ("::name::", Reflect.field (LibraryType, "::type::".toUpperCase ()));
			::end::::end::
			initialized = true;
			
		} //initialized
		
	} //initialize
	
	
} //AssetData


::foreach assets::::if (type == "font")::class lime_::flatName:: extends flash.text.Font { }::end::
>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
::end::