/** \file *********************************************************************
 *
 * pr_capture_simple - Passport Reader sample program
 *
 * 2006-2010 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/

/**
 * Simple image capturing
 *
 * Purpose:
 *		Show how to capture image.
 *
 * Description:
 *		Capture images after successful startup.
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
		while (!lib.KbHit()) {

			lib.ProcessStart("Processing document");
			/* Capturing images */
			lib.FunctionStart("Capturing images");
			pr.Capture();
			lib.FunctionEnd();

			/* Saving to file */
			lib.FunctionStart("Saving image");
			pr.SaveImage(0,PR_LIGHT_WHITE,PR_IT_ORIGINAL,"white.bmp",GX_BMP);
			lib.FunctionEnd();

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
