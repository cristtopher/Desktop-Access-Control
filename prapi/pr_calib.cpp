/** \file *********************************************************************
 *
 * pr_calib - Passport Reader sample program
 *
 * 2006-2010 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/

/**
 * Calibration example
 *
 * Purpose:
 *		Show how to calibrate the device.
 *
 * Description:
 *		Connect to the device, put the calibration image onto the document window.
 *		Type 'yes' to calibrate the device or 'no' to cancel.
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

		lib.WriteLine("The device is " + string(pr.IsCalibrated(0)?"":"not ") + "calibrated.");
		lib.WriteLine("Put the calibration image on the document window.");

		string s = "";
		while (s != "no")	{
			s = lib.ReadLine("Do you want to (re)calibrate? (yes/no) ");

			if (s == "no") break;
			if (s != "yes") {
				lib.WriteLine(" !!! Type 'yes' or 'no' please!");
				continue;
			}

			try {
				lib.FunctionStart("Calibrating device");
				pr.Calibrate(0);
				lib.FunctionEnd();
			} catch (gxException e) {
				lib.DisplExcp(e);
			}
		}

		/* Overall result */
		lib.WriteLine("The device is " + string(pr.IsCalibrated(0)?"":"not ") + "calibrated.");

		/* Closing the device */
		lib.FunctionStart("Closing the device");
		pr.CloseDevice();
		lib.FunctionEnd();

	} catch (gxException e) {
		lib.DisplExcp(e);
		return 0;
	}

	return 1;
}
