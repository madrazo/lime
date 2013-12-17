#include "renderer/opengl/OpenGLTexture.h"


namespace lime {
	
	
	bool gFullNPO2Support = false;
	bool gPartialNPO2Support = false;
	
	
	bool NonPO2Supported (bool inNotRepeating) {
		
		static bool tried = false;
		
		//OpenGL 2.0 introduced non PO2 as standard, in 2004 - safe to assume it exists on PC
		#ifdef FORCE_NON_PO2
		return true;
		#endif
		
		if (!tried) {
			
			tried = true;
			const char* extensions = (char*)glGetString (GL_EXTENSIONS);
			
			gFullNPO2Support = strstr (extensions, "ARB_texture_non_power_of_two") != 0;
			
			if (!gFullNPO2Support) {
				
				gPartialNPO2Support = strstr (extensions, "GL_APPLE_texture_2D_limited_npot") != 0;
				
			}
			
			//printf("Full non-PO2 support : %d\n", gFullNPO2Support);
			//printf("Partial non-PO2 support : %d\n", gPartialNPO2Support);
			
		}
		
		return (gFullNPO2Support || (gPartialNPO2Support && inNotRepeating));
		
	}
	
	
	void RGBX_to_RGB565 (uint8 *outDest, const uint8 *inSrc, int inPixels) {
		
		unsigned short *dest = (unsigned short *)outDest;
		const uint8 *src = inSrc;
		for (int x = 0; x < inPixels; x++) {
			
			*dest++ = ((src[0] << 8) & 0xf800) | ((src[1] << 3) & 0x07e0) | ((src[2] >> 3));
			src += 4;
			
		}
		
	}
	
	
	void RGBA_to_RGBA4444 (uint8 *outDest, const uint8 *inSrc, int inPixels) {
		
		unsigned short *dest = (unsigned short *)outDest;
		const uint8 *src = inSrc;
		for (int x = 0; x < inPixels; x++) {
			
			*dest++ = ((src[0] << 8) & 0xf000) | ((src[1] << 4) & 0x0f00) | ((src[2]) & 0x00f0) | ((src[3] >> 4));
			src += 4;
			
		}
		
	}
	
//#if HX_WINDOWS
#if 1
	#define GL_PALETTE8_RGBA8_OES 0x1000
	#define GL_PALETTE4_RGBA8_OES 0x1001
	
	static GLenum uncompress_image(int l, int tl, GLenum internalformat,
                               GLsizei width, GLsizei height,
                               GLsizei imageSize, const GLvoid *data, 
                               GLenum *newformat, GLvoid **newdata_)
	{
		GLubyte *newdata;
		const GLubyte *palette;
		const GLubyte *imagedata;
		int is_alpha;
		int i;
		int total;
		int skip;

		total = 0;
		for (i = 0; i <= tl; i++)
			{
				total += (width >> i) * (height >> i);
			}

		skip = 0;
		for (i = 0; i < l; i++)
		{
			skip += width * height;
			width /= 2;
			height /= 2;
		}

		/* TODO: different levels should be tested! */
	#if 0
		printf("level %d/%d total %d skip %d\n", l, tl, total, skip);
	#endif

		palette = (const GLubyte *) data;

		switch (internalformat)
		{
		default:
			return GL_INVALID_ENUM;
		/*case GL_PALETTE4_RGB8_OES:
			if (imageSize != 16*3 + total / 2)
				return GL_INVALID_VALUE;
			imagedata = palette + 16 * 3 + skip / 2;
			is_alpha = 0;
			break;
	
		case GL_PALETTE4_R5_G6_B5_OES:
			if (imageSize != 16*2 + total / 2)
				return GL_INVALID_VALUE;
			imagedata = palette + 16 * 2 + skip / 2;
			is_alpha = 0;
			break;
		
		case GL_PALETTE8_RGB8_OES:
			if (imageSize != 256*3 + total)
				return GL_INVALID_VALUE;
			imagedata = palette + 256 * 3 + skip;
			is_alpha = 0;
			break;
	
		case GL_PALETTE8_R5_G6_B5_OES:
			if (imageSize != 256*2 + total)
				return GL_INVALID_VALUE;
			imagedata = palette + 256 * 2 + skip;
			is_alpha = 0;
			break;
			*/
		case GL_PALETTE4_RGBA8_OES:
			if (imageSize != 16*4 + total / 2)
				return GL_INVALID_VALUE;
			imagedata = palette + 16 * 4 + skip / 2;
			is_alpha = 1;
			break;
			/*
		case GL_PALETTE4_RGBA4_OES:
			if (imageSize != 16*2 + total / 2)
				return GL_INVALID_VALUE;
			imagedata = palette + 16 * 2 + skip / 2;
			is_alpha = 1;
			break;
		
		case GL_PALETTE4_RGB5_A1_OES:
			if (imageSize != 16*2 + total / 2)
				return GL_INVALID_VALUE;
			imagedata = palette + 16 * 2 + skip / 2;
			is_alpha = 1;
			break;
			*/
		case GL_PALETTE8_RGBA8_OES:
			if (imageSize != 256*4 + total)
				return GL_INVALID_VALUE;
			imagedata = palette + 256 * 4 + skip;
			is_alpha = 1;
			break;
			/*
		case GL_PALETTE8_RGBA4_OES:
			if (imageSize != 256*2 + total)
				return GL_INVALID_VALUE;
			imagedata = palette + 256 * 2 + skip;
			is_alpha = 1;
			break;
		case GL_PALETTE8_RGB5_A1_OES:
			if (imageSize != 256*2 + total)
				return GL_INVALID_VALUE;
			imagedata = palette + 256 * 2 + skip;
			is_alpha = 1;
			break;*/
		}


		newdata = (GLubyte*)malloc(width * height * (3 + is_alpha));
		if (newdata == NULL)
			return GL_OUT_OF_MEMORY;

		for (i = 0; (int) i < width * height; i++)
		{
			int r, g, b, a = 0;
			int index;

			switch (internalformat)
			{
			default:
				free(newdata);
				return GL_INVALID_ENUM;
			//case GL_PALETTE4_RGB8_OES:
			case GL_PALETTE4_RGBA8_OES:
			//case GL_PALETTE4_R5_G6_B5_OES:
			//case GL_PALETTE4_RGBA4_OES:
			//case GL_PALETTE4_RGB5_A1_OES:
				if (i & 1)
					index = imagedata[i / 2] & 15;
				else
					index = imagedata[i / 2] >> 4;
				break;
			//case GL_PALETTE8_RGB8_OES:
			case GL_PALETTE8_RGBA8_OES:
			//case GL_PALETTE8_R5_G6_B5_OES:
			//case GL_PALETTE8_RGBA4_OES:
			//case GL_PALETTE8_RGB5_A1_OES:
				index = imagedata[i];
				break;
			}

			switch (internalformat)
			{
			default:
				free(newdata);
				return GL_INVALID_ENUM;
			/*case GL_PALETTE4_RGB8_OES:
			case GL_PALETTE8_RGB8_OES:
				r = palette[index*3];
				g = palette[index*3+1];
				b = palette[index*3+2];
				break;*/
			case GL_PALETTE4_RGBA8_OES:
			case GL_PALETTE8_RGBA8_OES:
				r = palette[index*4];
				g = palette[index*4+1];
				b = palette[index*4+2];
				a = palette[index*4+3];
				break;
			/*case GL_PALETTE4_R5_G6_B5_OES:
			case GL_PALETTE8_R5_G6_B5_OES:
				r = palette[index*2+1] >> 3;
				r = (r << 3) | (r >> 2);
				g = ((palette[index*2+1] & 7) << 3) | (palette[index*2] >> 5);
				g = (g << 2) | (g >> 4);
				b = palette[index*2] & 0x1F;
				b = (b << 3) | (b >> 2);
				break;*/
			/*case GL_PALETTE4_RGBA4_OES:
			case GL_PALETTE8_RGBA4_OES:
				r = palette[index*2+1] >> 4;
				r |= (r << 4) | r;
				g = palette[index*2+1] & 0xF;
				g |= (g << 4) | g;
				b = palette[index*2] >> 4;
				b |= (b << 4) | b;
				a = palette[index*2] & 0xF;
				a |= (a << 4) | a;
				break;*/
			/*case GL_PALETTE4_RGB5_A1_OES:
			case GL_PALETTE8_RGB5_A1_OES:
				r = palette[index*2+1] >> 3;
				r = (r << 3) | (r >> 2);
				g = ((palette[index*2+1] & 7) << 2) | (palette[index*2] >> 6);
				g = (g << 3) | (g >> 2);
				b = (palette[index*2] >> 1) & 0x1F;
				b = (b << 3) | (b >> 2);
				a = (palette[index*2] & 1) ? 255 : 0;
				break;*/
			}

			if (is_alpha)
			{
				newdata[i*4+0] = r;
				newdata[i*4+1] = g;
				newdata[i*4+2] = b;
				newdata[i*4+3] = a;
			}
			else
			{
				newdata[i*3+0] = r;
				newdata[i*3+1] = g;
				newdata[i*3+2] = b;
			}
		}

		*newformat = is_alpha ? GL_RGBA : GL_RGB;
		*newdata_ = newdata;

		return GL_NO_ERROR;
	}

#endif	
	
	OpenGLTexture::OpenGLTexture (Surface *inSurface, unsigned int inFlags) {
		
		mPixelWidth = inSurface->Width ();
		mPixelHeight = inSurface->Height ();
		mDirtyRect = Rect (0, 0);
		mContextVersion = gTextureContextVersion;
		
		bool non_po2 = NonPO2Supported (true && (inFlags & SURF_FLAGS_NOT_REPEAT_IF_NON_PO2));
		//printf("Using non-power-of-2 texture %d\n",non_po2);
		
		int w = non_po2 ? mPixelWidth : UpToPower2 (mPixelWidth);
		int h = non_po2 ? mPixelHeight : UpToPower2 (mPixelHeight);
		mCanRepeat = IsPower2 (w) && IsPower2 (h);
		
		//__android_log_print(ANDROID_LOG_ERROR, "lime",	"NewTexure %d %d", w, h);
		
		mTextureWidth = w;
		mTextureHeight = h;
		bool copy_required = inSurface->GetBase () && (w != mPixelWidth || h != mPixelHeight);
		
		Surface *load = inSurface;
		
		uint8 *buffer = 0;
		PixelFormat fmt = inSurface->Format ();
		GLuint store_format = (fmt == pfAlpha ? GL_ALPHA : GL_RGBA);
		int pixels = GL_UNSIGNED_BYTE;
		int gpuFormat = inSurface->GPUFormat ();
		bool compressed = fmt==pfIDX8 || fmt==pfIDX4 ? true: false;
		
		//if (inSurface) {
			//inSurface->multiplyAlpha();
		//}
		
		if (!inSurface->GetBase ()) {
			
			if (gpuFormat != fmt)
				switch (gpuFormat) {
					
					case pfARGB4444: pixels = GL_UNSIGNED_SHORT_4_4_4_4; break;
					case pfRGB565: pixels = GL_UNSIGNED_SHORT_5_6_5; break;
					default: pixels = gpuFormat;
					
				}
			
		} else if (gpuFormat == pfARGB4444) {
			
			pixels = GL_UNSIGNED_SHORT_4_4_4_4;
			buffer = (uint8 *)malloc (mTextureWidth * mTextureHeight * 2);
			for (int y = 0; y < mPixelHeight; y++)
				RGBA_to_RGBA4444 (buffer + y * mTextureWidth * 2, inSurface->Row (y), mPixelWidth);
			
		} else if ( gpuFormat == pfRGB565) {
			
			pixels = GL_UNSIGNED_SHORT_5_6_5;
			buffer = (uint8 *)malloc (mTextureWidth * mTextureHeight * 2);
			for (int y = 0; y < mPixelHeight; y++)
				RGBX_to_RGB565 (buffer + y * mTextureWidth * 2, inSurface->Row (y), mPixelWidth);
			
		} else if (w != mPixelWidth || h != mPixelHeight) {
			
			int pw = (inSurface->Format () == pfAlpha ? 1 : 4);
			buffer = (uint8 *)malloc (pw * mTextureWidth * mTextureHeight);
			for (int y = 0; y < mPixelHeight; y++) {
				
				const uint8 *src = inSurface->Row (y);
				uint8 *b = buffer + (mTextureWidth * pw * y);
				memcpy (b, src, mPixelWidth * pw);
				if (w > mPixelWidth)
					memcpy (b + (mPixelWidth * pw), buffer + (mPixelWidth - 1) * pw, pw);
				
			}
			
			if (h != mPixelHeight) {
				
				uint8 *b = buffer + (mTextureWidth * pw * mPixelHeight);
				uint8 *b0 = b - (mTextureWidth * pw);
				memcpy (b, b0, (mPixelWidth + (w != mPixelWidth)) * pw);
				
			}
			
		} else {
			
			buffer = (uint8 *)inSurface->Row (0);
			
		}
		
		/*#ifdef LIME_PREMULTIPLIED_ALPHA
		if (store_format != GL_ALPHA) {
			
			for (int i = 0; i < mTextureWidth * mTextureHeight * 4; i += 4) {
				
				float a = buffer[i + 3] / 255.0;
				buffer[i] = int(buffer[i] * a);
				buffer[i + 1] = int(buffer[i + 1] * a);
				buffer[i + 2] = int(buffer[i + 2] * a);
				
			}
			
		}
		#endif*/
		
		glGenTextures (1, &mTextureID);
		// __android_log_print(ANDROID_LOG_ERROR, "lime", "CreateTexture %d (%dx%d)",
		//	mTextureID, mPixelWidth, mPixelHeight);
		glBindTexture (GL_TEXTURE_2D, mTextureID);
		mRepeat = mCanRepeat;
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mRepeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mRepeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
		
		if(compressed){
			int a_palette_size = (fmt==pfIDX8? 256:16)*4;
			int a_image_size = (fmt==pfIDX8? (w*h):(w*h+1)/2);
			int a_size = a_palette_size+a_image_size;

			/*TODO these pointers in the correct place*/
			unsigned char* a_data = (unsigned char*) malloc(a_size);
			memcpy( a_data, (void *) inSurface->getClut(), a_palette_size );
			memcpy( a_data + a_palette_size, buffer, a_image_size );


		//#ifdef HX_WINDOWS
		#if 1
		
/*		

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			//glBind..
			glEnable(GL_COLOR_TABLE);
			glColorTableEXT(GL_TEXTURE_2D, GL_RGBA8, a_palette_size, GL_RGBA, GL_UNSIGNED_BYTE, inSurface->getClut());
			//GLenum err = glGetError();
			//fprintf(stderr, "%s:%d glGetError() = 0x%04x", __FILE__, __LINE__, err);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_COLOR_INDEX8_EXT, w, h, 0, GL_COLOR_INDEX, GL_UNSIGNED_BYTE, inSurface->Row(0));
			//GLenum err2= glGetError();
			
*/
			GLenum newformat;
			GLvoid *newdata;
			GLenum err;

			err = uncompress_image(0/*-i*/, 0/*-level*/, (fmt==pfIDX8? GL_PALETTE8_RGBA8_OES:GL_PALETTE4_RGBA8_OES), w, h,
		                       a_size, a_data,
		                       &newformat, &newdata);
			if (err != GL_NO_ERROR)		   
			  return;
			glTexImage2D (GL_TEXTURE_2D, 0, newformat, w, h, 0, newformat, GL_UNSIGNED_BYTE, newdata);
			free(newdata);

		#else
		
			glCompressedTexImage2D( GL_TEXTURE_2D,
			                            0,
			                            //#if ANDROID
			                            (fmt==pfIDX8 ? 0x00008b96 : GL_PALETTE4_RGBA8_OES),
			                            //#else
			                            //(fmt==pfIDX8 ? GL_PALETTE8_RGBA8_OES : GL_PALETTE4_RGBA8_OES),
			                            //#endif
			                            w,
			                            h,
			                            0,
			                            a_size,
			                            a_data
			                            );

			GLenum  err = glGetError();
			__android_log_print(ANDROID_LOG_ERROR, "lime", "CreateTexture %d (%dx%d) err %d",
			mTextureID, mPixelWidth, mPixelHeight,(int)err);

		#endif

			free(a_data);
		}else{
			glTexImage2D (GL_TEXTURE_2D, 0, store_format, w, h, 0, store_format, pixels, buffer);
		}
		if (buffer && buffer != inSurface->Row (0))
			free (buffer);
		
		mSmooth = true;
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		// TODO: Need replacement call for GLES2?
		#ifdef GPH
		glTexEnvx (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		#endif
		
		#ifndef LIME_FORCE_GLES2
		glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		#endif
		
		//int err = glGetError();
		//printf ("GL texture error: %i", err);
		
	}
	
	
	OpenGLTexture::~OpenGLTexture () {
		
		if (mTextureID && mContextVersion == gTextureContextVersion && HardwareContext::current) {
			
			//__android_log_print(ANDROID_LOG_ERROR, "lime", "DeleteTexture %d (%dx%d)",
			//mTextureID, mPixelWidth, mPixelHeight);
			HardwareContext::current->DestroyNativeTexture ((void *)(size_t)mTextureID);
			
		}
		
	}
	
	
	void OpenGLTexture::Bind (class Surface *inSurface, int inSlot) {
		
		if (inSlot >= 0 && &glActiveTexture) {
			
			glActiveTexture (GL_TEXTURE0 + inSlot);
			
		}
		
		glBindTexture (GL_TEXTURE_2D, mTextureID);
		if (gTextureContextVersion != mContextVersion) {
			
			mContextVersion = gTextureContextVersion;
			mDirtyRect = Rect (inSurface->Width (), inSurface->Height ());
			
		}
		
		if (inSurface->GetBase () && mDirtyRect.HasPixels ()) {
			
			//__android_log_print(ANDROID_LOG_INFO, "lime", "UpdateDirtyRect! %d %d",
			//mPixelWidth, mPixelHeight);
			
			PixelFormat fmt = inSurface->Format ();
			GLuint store_format = (fmt == pfAlpha ? GL_ALPHA : GL_RGBA);
			glGetError ();
			const uint8 *p0 = inSurface->Row (mDirtyRect.y) + (mDirtyRect.x * inSurface->BytesPP ());
			
			#if defined(LIME_GLES)
			// TODO: pixel transform & copy rect
			for (int y = 0; y < mDirtyRect.h; y++) {
				
				glTexSubImage2D (GL_TEXTURE_2D, 0, mDirtyRect.x, mDirtyRect.y + y, mDirtyRect.w, 1, store_format, GL_UNSIGNED_BYTE, p0 + (y * inSurface->GetStride ()));
				
			}
			#else
			glPixelStorei (GL_UNPACK_ROW_LENGTH, inSurface->Width ());
			glTexSubImage2D (GL_TEXTURE_2D, 0, mDirtyRect.x, mDirtyRect.y, mDirtyRect.w, mDirtyRect.h, store_format, GL_UNSIGNED_BYTE, p0);
			glPixelStorei (GL_UNPACK_ROW_LENGTH, 0);
			#endif
			
			int err = glGetError ();
			if (err != GL_NO_ERROR)
				ELOG ("GL Error: %d", err);
			mDirtyRect = Rect ();
			
		}
		
	}
	
	
	void OpenGLTexture::BindFlags (bool inRepeat, bool inSmooth) {
		
		if (!mCanRepeat) inRepeat = false;
		if (mRepeat != inRepeat) {
			
			mRepeat = inRepeat;
			if (mRepeat) {
				
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				
			} else {
				
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				
			}
			
		}
		
		if (mSmooth != inSmooth) {
			
			mSmooth = inSmooth;
			if (mSmooth) {
				
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				
			} else {
				
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				
			}
			
		}
		
	}
	
	
	UserPoint OpenGLTexture::PixelToTex (const UserPoint &inPixels) {
		
		return UserPoint (inPixels.x / mTextureWidth, inPixels.y / mTextureHeight);
		
	}
	
	
	UserPoint OpenGLTexture::TexToPaddedTex (const UserPoint &inTex) {
		
		return UserPoint (inTex.x * mPixelWidth / mTextureWidth, inTex.y * mPixelHeight / mTextureHeight);
		
	}
	
	
}
