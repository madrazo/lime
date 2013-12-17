<<<<<<< HEAD
package lime.gl;


#if lime_html5
	
	typedef GLFramebuffer = js.html.webgl.Framebuffer;

#else

	class GLFramebuffer extends GLObject {
		
		public function new (version:Int, id:Dynamic) {
			super (version, id);
		}
		
		override function getType ():String {
			return "Framebuffer";
		}
		
	} //GLFramebuffer


=======
package lime.gl;


#if lime_html5
	
	typedef GLFramebuffer = js.html.webgl.Framebuffer;

#else

	class GLFramebuffer extends GLObject {
		
		public function new (version:Int, id:Dynamic) {
			super (version, id);
		}
		
		override function getType ():String {
			return "Framebuffer";
		}
		
	} //GLFramebuffer


>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
#end //lime_html5