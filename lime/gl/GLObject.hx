<<<<<<< HEAD
package lime.gl;


#if lime_html5

	typedef GLObject = Dynamic;
	
#else //lime_html5

	class GLObject {
		
		public var id (default, null):Dynamic;
		public var invalidated (get, null):Bool;
		public var valid (get, null):Bool;
		
		private var version:Int;
		
		private function new (version:Int, id:Dynamic) {
			
			this.version = version;
			this.id = id;
			
		}
		
		private function getType ():String {
			return "GLObject";
		}
		
		public function invalidate ():Void {
			id = null;
		}
		
		public function isValid ():Bool {
			return id != null && version == GL.version;
		}
		
		public function isInvalid ():Bool {
			return !isValid ();
		}
		
		public function toString ():String {
			return getType () + "(" + id + ")";
		}
		
		// Getters & Setters
		
		private function get_invalidated ():Bool {
			return isInvalid ();
		}
		
		private function get_valid ():Bool {
			return isValid ();
		}
		
	}

#end //lime_native
=======
package lime.gl;


#if lime_html5

	typedef GLObject = Dynamic;
	
#else //lime_html5

	class GLObject {
		
		public var id (default, null):Dynamic;
		public var invalidated (get, null):Bool;
		public var valid (get, null):Bool;
		
		private var version:Int;
		
		private function new (version:Int, id:Dynamic) {
			
			this.version = version;
			this.id = id;
			
		}
		
		private function getType ():String {
			return "GLObject";
		}
		
		public function invalidate ():Void {
			id = null;
		}
		
		public function isValid ():Bool {
			return id != null && version == GL.version;
		}
		
		public function isInvalid ():Bool {
			return !isValid ();
		}
		
		public function toString ():String {
			return getType () + "(" + id + ")";
		}
		
		// Getters & Setters
		
		private function get_invalidated ():Bool {
			return isInvalid ();
		}
		
		private function get_valid ():Bool {
			return isValid ();
		}
		
	}

#end //lime_native
>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
