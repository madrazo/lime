<<<<<<< HEAD
package lime.gl;

#if lime_html5 

    typedef GLUniformLocation = js.html.webgl.UniformLocation;
    
#else //lime_html5

    typedef GLUniformLocation = Dynamic;

#end //lime_native

=======
package lime.gl;

#if lime_html5 

    typedef GLUniformLocation = js.html.webgl.UniformLocation;
    
#else //lime_html5

    typedef GLUniformLocation = Dynamic;

#end //lime_native

>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
