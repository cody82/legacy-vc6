/////////////////////////////////////////////////////////////////////////////////////
// TEXTURE class
/////////////////////////////////////////////////////////////////////////////////////
class TEXTURE
{
private:
	IDirectDrawSurface *MemorySurface;  // System memory surface
	IDirectDrawSurface *DeviceSurface;  // Video memory texture
	IDirectDrawPalette *Palette;
	D3DTEXTUREHANDLE    Handle;

public:
	TEXTURE()
	{
		MemorySurface = 0;
		DeviceSurface = 0;
		Palette = 0;
		Handle = 0;
	}

	D3DTEXTUREHANDLE    GetHandle()  { return Handle; }
	IDirectDrawSurface* GetSurface() { return MemorySurface; }
	IDirectDrawPalette* GetPalette() { return Palette; }

	BOOL Load(IDirect3DDevice2 *Device, char *BitmapName);
	BOOL Copy(HBITMAP Bitmap);

	BOOL LoadAlpha(IDirect3DDevice2 *Device);
	BOOL CreateDefaultAlpha(void);

	void Release(void);
	BOOL Restore(void);
};
