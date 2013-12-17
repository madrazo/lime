<<<<<<< HEAD
package lime.gl;

#if lime_html5

	typedef GLRenderbuffer = js.html.webgl.Renderbuffer;

#else //lime_html5

	class GLRenderbuffer extends GLObject {
		
		public function new (version:Int, id:Dynamic) {
			super (version, id);
		}
		
		override private function getType ():String {
			return "Renderbuffer";
		}
		
	}

#end //lime_native

=======
package lime.gl;

#if lime_html5

	typedef GLRenderbuffer = js.html.webgl.Renderbuffer;

#else //lime_html5

	class GLRenderbuffer extends GLObject {
		
		public function new (version:Int, id:Dynamic) {
			super (version, id);
		}
		
		override private function getType ():String {
			return "Renderbuffer";
		}
		
	}

#end //lime_native

>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
