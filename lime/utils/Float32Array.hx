<<<<<<< HEAD
package lime.utils;

#if lime_html5
        
    typedef Float32Array = js.html.Float32Array;

#else

    import lime.geometry.Matrix3D;


    class Float32Array extends ArrayBufferView implements ArrayAccess<Float> {
        
        static public inline var SBYTES_PER_ELEMENT = 4;
        
        public var BYTES_PER_ELEMENT (default, null):Int;
        public var length (default, null):Int;
        
        public function new (bufferOrArray:Dynamic, start:Int = 0, length:Null<Int> = null) {
            
            BYTES_PER_ELEMENT = 4;

            if (Std.is (bufferOrArray, Int)) {
                
                super (Std.int (bufferOrArray) * BYTES_PER_ELEMENT);
                this.length = bufferOrArray;
                
            } else if (Std.is (bufferOrArray, Array)) {

                var floats:Array<Float> = bufferOrArray;
                
                if (length != null) {
                    
                    this.length = length;
                    
                } else {
                    
                    this.length = floats.length - start;
                    
                }
                
                super (this.length << 2);
                
                #if !cpp
                buffer.position = 0;
                #end
                
                for (i in 0...this.length) {
                    
                    #if cpp
                    untyped __global__.__hxcpp_memory_set_float (bytes, (i << 2), floats[i]);
                    #else
                    buffer.writeFloat (floats[i + start]);
                    #end
                    
                }
                
            } else {

                super (bufferOrArray, start, length << 2 );
                
                if ((byteLength & 0x03) > 0) {
                    
                    throw("Invalid array size");
                    
                }
                
                this.length = byteLength >> 2;
                
                if ((this.length << 2) != byteLength) {
                    
                    throw "Invalid length multiple";
                    
                }
            }
        }
        
            
        public function clear() {
            length = 0;
        }
        
        public static function fromMatrix (matrix:Matrix3D):Float32Array {
            return new Float32Array (matrix.rawData);
        }
        
        @:noCompletion @:keep inline public function __get (index:Int):Float { return getFloat32 (index << 2); }
        @:noCompletion @:keep inline public function __set (index:Int, value:Float):Void { setFloat32 (index << 2, value); }
        
        
    }

#end //lime_native
=======
package lime.utils;

#if lime_html5
        
    typedef Float32Array = js.html.Float32Array;

#else

    import lime.geometry.Matrix3D;


    class Float32Array extends ArrayBufferView implements ArrayAccess<Float> {
        
        static public inline var SBYTES_PER_ELEMENT = 4;
        
        public var BYTES_PER_ELEMENT (default, null):Int;
        public var length (default, null):Int;
        
        public function new (bufferOrArray:Dynamic, start:Int = 0, length:Null<Int> = null) {
            
            BYTES_PER_ELEMENT = 4;

            if (Std.is (bufferOrArray, Int)) {
                
                super (Std.int (bufferOrArray) * BYTES_PER_ELEMENT);
                this.length = bufferOrArray;
                
            } else if (Std.is (bufferOrArray, Array)) {

                var floats:Array<Float> = bufferOrArray;
                
                if (length != null) {
                    
                    this.length = length;
                    
                } else {
                    
                    this.length = floats.length - start;
                    
                }
                
                super (this.length << 2);
                
                #if !cpp
                buffer.position = 0;
                #end
                
                for (i in 0...this.length) {
                    
                    #if cpp
                    untyped __global__.__hxcpp_memory_set_float (bytes, (i << 2), floats[i]);
                    #else
                    buffer.writeFloat (floats[i + start]);
                    #end
                    
                }
                
            } else {

                super (bufferOrArray, start, length << 2 );
                
                if ((byteLength & 0x03) > 0) {
                    
                    throw("Invalid array size");
                    
                }
                
                this.length = byteLength >> 2;
                
                if ((this.length << 2) != byteLength) {
                    
                    throw "Invalid length multiple";
                    
                }
            }
        }
        
            
        public function clear() {
            length = 0;
        }
        
        public static function fromMatrix (matrix:Matrix3D):Float32Array {
            return new Float32Array (matrix.rawData);
        }
        
        @:noCompletion @:keep inline public function __get (index:Int):Float { return getFloat32 (index << 2); }
        @:noCompletion @:keep inline public function __set (index:Int, value:Float):Void { setFloat32 (index << 2, value); }
        
        
    }

#end //lime_native
>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
