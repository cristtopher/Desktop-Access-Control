/** \file *********************************************************************
 *
 * pr_mrz - Passport Reader sample program
 *
 * 2006-2010 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/

/**
 * Simple image capturing and processing
 *
 * Purpose:
 *		Shows how to capture image and to read MRZ data.
 *
 * Description:
 *
 *		Capture images after successful startup.
 *		Read the MRZ data, the calculated checksum, and display the result.
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

			lib.ProcessStart("MRZ");

			prDoc * doc = NULL;

			try {
				/* Capturing images */
				lib.FunctionStart("Capturing images");
				pr.Capture();
				lib.FunctionEnd();

				/* Getting the MRZ data */
				lib.FunctionStart("Reading MRZ");
				doc = pr.GetMrz(0,PR_LIGHT_INFRA,PR_IT_ORIGINAL);
				lib.FunctionEnd();

				if (!doc->IsValid()) {
					lib.WriteLine("No MRZ data found!");
				} else {
					/* Searching for MRZ fields and displaying them */
					text = doc->FieldA(PR_DF_MRZ1);
					if (text != "") lib.WriteLine("MRZ1 \"" + text + "\" [" + ec[doc->FieldStatus(PR_DF_MRZ1)/100] + "]");

					text = doc->FieldA(PR_DF_MRZ2);
					if (text != "") lib.WriteLine("MRZ2 \"" + text + "\" [" + ec[doc->FieldStatus(PR_DF_MRZ2)/100] + "]");

					text = doc->FieldA(PR_DF_MRZ3);
					if (text != "") lib.WriteLine("MRZ3 \"" + text + "\" [" + ec[doc->FieldStatus(PR_DF_MRZ3)/100] + "]");
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
