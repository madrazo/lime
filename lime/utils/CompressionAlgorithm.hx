<<<<<<< HEAD
package lime.utils;
#if (lime_native || lime_html5)
// #if (cpp || neko)

enum CompressionAlgorithm {
    DEFLATE;
    ZLIB;
    LZMA;
    GZIP;
} 

#else
typedef CompressionAlgorithm = flash.utils.CompressionAlgorithm;
=======
package lime.utils;
#if (lime_native || lime_html5)
// #if (cpp || neko)

enum CompressionAlgorithm {
    DEFLATE;
    ZLIB;
    LZMA;
    GZIP;
} 

#else
typedef CompressionAlgorithm = flash.utils.CompressionAlgorithm;
>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
#end