/** \file *********************************************************************
 *
 * pr_barcode - Passport Reader sample program
 *
 * 2006-2010 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/

/**
 * Image capturing and barcode reading
 *
 * Purpose:
 *		Show how to capture images and to read barcode.
 *
 * Description:
 *
 *		Capture images after successful startup.
 *		Read the barcode, the calculated checksum, and display the result.
 *
 */

#include "prapi.h"
#include "gxsdldr.cpp"

#include "../__lib__.h"
Lib lib;

#ifdef GX_NAMESPACES
using namespace gx;
using namespace pr;
#endif

/**
 * Main Function
 */
int main() {
	const char *ec[]={"Ok","Warning","Error"};

	try {
		/* Opening the PR system */
		lib.FunctionStart("Opening system files");
		PassportReader pr;	/* Object for the PR system */
		lib.FunctionEnd();

		/* Validity check */
		if (!pr.IsValid()) {
			lib.Error("Failed to initialize!");
			return 0;
		}

		/* Connecting to the first device */
		lib.FunctionStart("Connecting to the first device");
		pr.UseDevice(0,PR_UMODE_FULL_CONTROL);
		lib.FunctionEnd();

		while (!lib.KbHit()) {

			prDoc *doc = NULL;

			lib.ProcessStart("Processing document");

			try {

				/* Capturing images */
				lib.FunctionStart("Capturing images");
				pr.Capture();
				lib.FunctionEnd();

				/* Reading barcode */
				lib.FunctionStart("Reading barcode from infra image");
				doc = pr.GetBarcode(0,PR_LIGHT_INFRA,PR_IT_ORIGINAL,0,0);
				lib.FunctionEnd();

				if (!doc->IsValid()) {
					lib.FunctionStart("Reading barcode from white image");
					doc = pr.GetBarcode(0,PR_LIGHT_WHITE,PR_IT_ORIGINAL,0,0);
					lib.FunctionEnd();
				}

				if (!doc->IsValid()) {
					lib.WriteLine("No data found!");
				} else {
					/* Displaying document type */
					lib.WriteLine("Document type: " + lib.itos(doc->Code()) + ", status: " + ec[doc->Status()/100]);

					/* Searching for the barcode and displaying it */
					char text[3000];
					int stext = sizeof(text);
					try {
						/* Try to get ascii data */
						doc->Field(PR_DF_BC1, text, &stext);
					}
					catch (const gxException &) {
						/* Try to get binary data */
						doc->Field(PR_DF_BC1, (void*)text, &stext);
					}
					text[stext] = 0;

					int type = -1;
					int status = doc->FieldStatus(PR_DF_BC1);

					gxVariant* pdoc = doc->ToVariant();
					gxVariant v;
					if(pdoc->GetChild(v, GX_VARIANT_BY_ID, PRV_BARCODE, 0))
					{
						type = v.GetInt();
						v.Dispose();
					}

					/* Converting the data and displaying on the console */
					lib.WriteLine("Barcode type: " + lib.itos(type) + ", status: " + lib.itos(status) +	", length: " + lib.itos(stext));
#ifdef WIN32
					CharToOemBuff(text, text, stext);
#endif
					lib.WriteLine(text);

					/* Saving the barcode image */
					lib.FunctionStart("Save barcode image");
					gxImage* img = doc->FieldImage(PR_DF_BC1);
					if(img->IsValid()) img->Save("barcode.jpg", GX_JPEG);
					if(img) delete img;
					lib.FunctionEnd();

					/* Searching for the fields and displaying them */
					gxVariant fieldlist;
					pdoc->GetChild(fieldlist, GX_VARIANT_BY_ID, PRV_FIELDLIST, 0);
					int nitems = fieldlist.GetNItems();
					for(int i = 0;i < nitems;i++)
					{
						gxVariant field;
						fieldlist.GetItem(field, GX_VARIANT_BY_INDEX, 0, i);
						int field_code = field.GetInt();
						stext = sizeof(text);
						try {
							doc->Field(field_code, text, &stext);
						}
						catch (const gxException &) {
							doc->Field(field_code, (void*)text, &stext);
						}
						text[stext] = 0;
#ifdef WIN32
						CharToOemBuff(text, text, stext);
#endif
						if (text[0]) lib.WriteLine("[" + lib.itos(field_code) + "] \"" + text + "\" [" + ec[doc->FieldStatus(field_code)/100] + "]");
					}
					delete pdoc;
				}
			} catch (gxException e) {
				lib.DisplExcp(e);
			}
			if (doc) delete doc;

			lib.ProcessEnd();
			lib.WaitForSec(3);
		}

		/* Closing the device */
		lib.FunctionStart("Closing the device");
		pr.CloseDevice();
		lib.FunctionEnd();

	} catch (gxException e) {
		lib.DisplExcp(e);
	}

	return lib.PrintStat();
}
