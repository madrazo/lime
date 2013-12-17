<<<<<<< HEAD
package lime.gl;

#if lime_html5

	typedef GLBuffer = js.html.webgl.Buffer;
	
#else

	class GLBuffer extends GLObject {
		public function new (version:Int, id:Dynamic) {
			super (version, id);
		}
		override function getType ():String {
			return "Buffer";
		}
	}

=======
package lime.gl;

#if lime_html5

	typedef GLBuffer = js.html.webgl.Buffer;
	
#else

	class GLBuffer extends GLObject {
		public function new (version:Int, id:Dynamic) {
			super (version, id);
		}
		override function getType ():String {
			return "Buffer";
		}
	}

>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
#end //lime_html5