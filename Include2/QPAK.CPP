#include "qpak.h"

int qpak_ExtractFile (const char *pakFile, const char *lumpName, char *outFile)
{
	FILE *file = fopen (pakFile, "rb");
	if (!file)
		return 0;

	int ident, dirofs, dirlen;

	fread (&ident, sizeof (int), 1, file);
	if (ident != (int) (('K' << 24) + ('C' << 16) + ('A' << 8) + 'P'))
	{
		fclose (file);
		return 0;
	}

	fread (&dirofs, sizeof (int), 1, file);
	fread (&dirlen, sizeof (int), 1, file);

	fseek (file, dirofs, SEEK_SET);
	int numLumps = dirlen / 64;

	for (int i = 0; i < numLumps; i++)
	{
		char name[56];
		int filepos, filelen;

		fread (name, 56, 1, file);
		fread (&filepos, sizeof (int), 1, file);
		fread (&filelen, sizeof (int), 1, file);

		if (stricmp(name, lumpName)==0)
		{
			FILE *out = fopen (outFile, "wb");
			if (!out)
			{
				fclose (file);
				return 0;
			}

			fseek (file, filepos, SEEK_SET);

			while (filelen--)
				fputc (fgetc (file), out);

			fclose (out);
			fclose (file);

			return 1;
		}
	}

	fclose (file);

	return 0;
}

int qpak_GetFilePos(const char *pakFile, const char *lumpName, int *pos,int *size)
{
	FILE *file = fopen (pakFile, "rb");
	if (!file)
		return 0;

	int ident, dirofs, dirlen;

	fread (&ident, sizeof (int), 1, file);
	if (ident != (int) (('K' << 24) + ('C' << 16) + ('A' << 8) + 'P'))
	{
		fclose (file);
		return 0;
	}

	fread (&dirofs, sizeof (int), 1, file);
	fread (&dirlen, sizeof (int), 1, file);

	fseek (file, dirofs, SEEK_SET);
	int numLumps = dirlen / 64;

	for (int i = 0; i < numLumps; i++)
	{
		char name[56];
		int filepos, filelen;

		fread (name, 56, 1, file);
		fread (&filepos, sizeof (int), 1, file);
		fread (&filelen, sizeof (int), 1, file);

		if (stricmp(name, lumpName)==0)
		{
			*pos=filepos;
			*size=filelen;

			fclose (file);
			return 1;
		}
	}

	fclose (file);

	return 0;
}