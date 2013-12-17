<<<<<<< HEAD
package shaders;


class VertexShader {

	
	public static var source = "
		
		attribute vec3 position;
		attribute vec2 surfacePosAttrib;
		varying vec2 surfacePosition;
		
		void main() {
			
			surfacePosition = surfacePosAttrib;
			gl_Position = vec4( position, 1.0 );
			
		}
		
	";
	
	
=======
package shaders;


class VertexShader {

	
	public static var source = "
		
		attribute vec3 position;
		attribute vec2 surfacePosAttrib;
		varying vec2 surfacePosition;
		
		void main() {
			
			surfacePosition = surfacePosAttrib;
			gl_Position = vec4( position, 1.0 );
			
		}
		
	";
	
	
>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
}