/** \file *********************************************************************
 *
 * pr_recognize - Passport Reader sample program
 *
 * 2006-2010 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/

/**
 * Advanced image capturing and processing
 *
 * Purpose:
 *		Show how to capture and recognize images.
 *
 * Description:
 *
 *		Capture images after successful startup.
 *		Read the recognized field data, the calculated checksum, and display the result.
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
 * Main function
 */
int main() {
	string text;
	string ec[]={"Ok","Warning","Error"};

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

		/* Using the device */
		while (!lib.KbHit()) {

			lib.ProcessStart("Processing document");

			prDoc * doc = NULL;

			try {
				/* Capturing images */
				lib.FunctionStart("Capturing images");
				pr.Capture();
				lib.FunctionEnd();

				/* Getting document data */
				lib.FunctionStart("Recognizing.");
				doc = pr.Recognize(0);
				lib.FunctionEnd();

				if (!doc->IsValid()) {
					lib.WriteLine("No data found.");
				} else {
					/* Displaying document type */
					lib.WriteLine("Document type: " + lib.itos(doc->Code()) + ", status: " + ec[doc->Status()/100]);

					/* Reading some fixed fields and displaying them */
					text = doc->FieldA(PR_DF_NAME);
					if (text != "") lib.WriteLine("NAME \"" + text + "\" [" + ec[doc->FieldStatus(PR_DF_NAME)/100] + "]");

					text = doc->FieldA(PR_DF_DOCUMENT_NUMBER);
					if (text != "") lib.WriteLine("DOCUMENT NUMBER \"" + text + "\" [" + ec[doc->FieldStatus(PR_DF_DOCUMENT_NUMBER)/100] + "]");

					text = doc->FieldA(PR_DF_EXPIRY_DATE);
					if (text != "") lib.WriteLine("EXPIRY DATE \"" + text + "\" [" + ec[doc->FieldStatus(PR_DF_EXPIRY_DATE)/100] + "]");

					/* Searching for the fields and displaying them */
					gxVariant* pdoc = doc->ToVariant();
					gxVariant fieldlist;
					pdoc->GetChild(fieldlist, GX_VARIANT_BY_ID, PRV_FIELDLIST, 0);
					int nitems = fieldlist.GetNItems();
					for(int i = 0;i < nitems;i++)
					{
						gxVariant field;
						fieldlist.GetItem(field, GX_VARIANT_BY_INDEX, 0, i);
						int field_code = field.GetInt();
						text = doc->FieldA(field_code);
						if (text != "") lib.WriteLine("[" + lib.itos(field_code) + "] \"" + text + "\" [" + ec[doc->FieldStatus(field_code)/100] + "]");

						if(field_code >= PR_DF_FORMATTED) continue;
						try
						{
							gxImage* img = doc->FieldImage(field_code);
							if(img->IsValid()) img->Save(lib.itos(field_code) + ".jpg", GX_JPEG);
							if(img) delete img;
						} catch (gxException e) {
							lib.DisplExcp(e);
						}
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
