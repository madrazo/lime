<<<<<<< HEAD
package lime.utils;
// #if (cpp || neko)
#if (lime_native || lime_html5)

interface IDataInput 
{
   public var bytesAvailable(get_bytesAvailable, null):Int;
   public var endian(get_endian, set_endian):String;

   public function readBoolean():Bool;
   public function readByte():Int;
   public function readBytes(outData:ByteArray, inOffset:Int = 0, inLen:Int = 0):Void;
   public function readDouble():Float;
   public function readFloat():Float;
   public function readInt():Int;

   // not implemented ...
   //var objectEncoding : UInt;
   //public function readMultiByte(length : Int, charSet:String):String;
   //public function readObject():Dynamic;
   public function readShort():Int;
   public function readUnsignedByte():Int;
   public function readUnsignedInt():Int;
   public function readUnsignedShort():Int;
   public function readUTF():String;
   public function readUTFBytes(inLen:Int):String;

   private function get_bytesAvailable():Int;
   private function get_endian():String;
   private function set_endian(s:String):String;
}

#else
typedef IDataInput = flash.utils.IDataInput;
=======
package lime.utils;
// #if (cpp || neko)
#if (lime_native || lime_html5)

interface IDataInput 
{
   public var bytesAvailable(get_bytesAvailable, null):Int;
   public var endian(get_endian, set_endian):String;

   public function readBoolean():Bool;
   public function readByte():Int;
   public function readBytes(outData:ByteArray, inOffset:Int = 0, inLen:Int = 0):Void;
   public function readDouble():Float;
   public function readFloat():Float;
   public function readInt():Int;

   // not implemented ...
   //var objectEncoding : UInt;
   //public function readMultiByte(length : Int, charSet:String):String;
   //public function readObject():Dynamic;
   public function readShort():Int;
   public function readUnsignedByte():Int;
   public function readUnsignedInt():Int;
   public function readUnsignedShort():Int;
   public function readUTF():String;
   public function readUTFBytes(inLen:Int):String;

   private function get_bytesAvailable():Int;
   private function get_endian():String;
   private function set_endian(s:String):String;
}

#else
typedef IDataInput = flash.utils.IDataInput;
>>>>>>> 8e074ccffa5957d0db223fb47adf40965717c8c7
#end