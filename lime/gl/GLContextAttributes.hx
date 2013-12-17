<<<<<<< HEAD
package lime.gl;

#if lime_html5

    typedef GLContextAttributes = js.html.webgl.ContextAttributes;

#else

    typedef GLContextAttributes = {
        
        alpha:Bool, 
        depth:Bool,
        stencil:Bool,
        antialias:Bool,
        premultipliedAlpha:Bool,
        preserveDrawingBuffer:Bool,
        
    };

=======
package lime.gl;

#if lime_html5

    typedef GLContextAttributes = js.html.webgl.ContextAttributes;

#else

    typedef GLContextAttributes = {
        
        alpha:Bool, 
        depth:Bool,
        stencil:Bool,
        antialias:Bool,
        premultipliedAlpha:Bool,
        preserveDrawingBuffer:Bool,
        
    };

>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
#end //lime_html5