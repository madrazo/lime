<<<<<<< HEAD
package lime.gl;


#if lime_html5
	
	typedef GLShader = js.html.webgl.Shader;

#else //lime_html5

	class GLShader extends GLObject {
		
		public function new (version:Int, id:Dynamic) {
			super (version, id);
		}
		
		override private function getType ():String {
			return "Shader";
		}
		
	}

#end //lime_native

=======
package lime.gl;


#if lime_html5
	
	typedef GLShader = js.html.webgl.Shader;

#else //lime_html5

	class GLShader extends GLObject {
		
		public function new (version:Int, id:Dynamic) {
			super (version, id);
		}
		
		override private function getType ():String {
			return "Shader";
		}
		
	}

#end //lime_native

>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
