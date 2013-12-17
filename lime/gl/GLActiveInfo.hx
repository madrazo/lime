<<<<<<< HEAD
package lime.gl;

#if lime_html5

    typedef GLActiveInfo = js.html.webgl.ActiveInfo;

#else

	typedef GLActiveInfo = {
		
		size : Int,
		type : Int,
		name : String,
		
	};

=======
package lime.gl;

#if lime_html5

    typedef GLActiveInfo = js.html.webgl.ActiveInfo;

#else

	typedef GLActiveInfo = {
		
		size : Int,
		type : Int,
		name : String,
		
	};

>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
#end //lime_html5