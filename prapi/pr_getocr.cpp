/** \file *********************************************************************
 *
 * pr_getocr - Passport Reader sample program
 *
 * 2006-2010 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/

/**
 * Image capturing and OCR
 *
 * Purpose:
 *		Shows how to capture image and to call OCR.
 *
 * Description:
 *
 *		Capture images after successful startup.
 *		Call OCR and display the result.
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

				/* Call OCR */
				lib.FunctionStart("Call OCR");

				gxPG4 r1 = {100*16, 1200*16, 1900*16, 1200*16, 1900*16, 1400*16, 100*16, 1400*16};	/* x1, y1, x2, y2, x3, y3, x4, y4 */
				int height = 2500;
				int spacewidth = 50;
				int spacetype = 0;
				int justification = 0;
				char font[] = "General";

				gxVariant params, vd;
				params.CreateEmptyList(PRV_OCRPARAMS);

				vd.Create(PRV_IMAGEFRAME,r1);
				params.AddItem(GX_VARIANT_APPEND,0,0,vd);
				vd.Create(PRV_CHARHEIGHT,height);
				params.AddItem(GX_VARIANT_APPEND,0,0,vd);
				vd.Create(PRV_SPACEWIDTH,spacewidth);
				params.AddItem(GX_VARIANT_APPEND,0,0,vd);
				vd.Create(PRV_SPACETYPE,spacetype);
				params.AddItem(GX_VARIANT_APPEND,0,0,vd);
				vd.Create(PRV_JUSTIFICATION,justification);
				params.AddItem(GX_VARIANT_APPEND,0,0,vd);
				vd.Create(PRV_FONTTYPE,font);
				params.AddItem(GX_VARIANT_APPEND,0,0,vd);

				doc = pr.GetOcr(0,PR_LIGHT_INFRA,PR_IT_ORIGINAL,&params);
				lib.FunctionEnd();

				if (!doc->IsValid()) {
					lib.WriteLine("No OCR data found.");
				} else {

					/* Reading and displaying OCR data */
					try {
						string text;
						int len = 100;
						char path[100];

						gxVariant* pdoc = doc->ToVariant();
						gx_snprintf(path,sizeof(path),"C,D=%i/L,D=%i/C,D=%i",PRV_OCRROWLIST,PRV_OCRROW,PRV_FIELDVALUE);
						gxVariant ocr;
						pdoc->GetItemByPath(ocr, path);
						text = ocr.GetASCII(len);
						lib.WriteLine("OCR \"" + text + "\"");
						delete pdoc;
					} catch (gxException e) {
						lib.DisplExcp(e);
					}
				}

			} catch (gxException e) {
				lib.DisplExcp(e);
			}

			if(doc) delete doc;
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
