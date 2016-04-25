/** \file *********************************************************************
 *
 * pr_capture_adv - Passport Reader sample program
 *
 * 2006-2010 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/

/**
 * Advanced image capturing
 *
 * Purpose:
 *		Show how to capture image using advanced features.
 *
 * Description:
 *		Capture images after successful startup. Set the event function, and handle the events
 *		during the capture process. At the end save the original and the document image.
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
 * Displays event messages
 */
void GXAPI evfunc(int event, int param1, int param2, void *uparam)
{
	switch (event) {
		case PR_EV_UVLEDWARMING:
			lib.WriteLine("<Event> UV tube warming started");
			break;
		case PR_EV_PAGECAPTURED:
			lib.WriteLine("<Event> Page captured: page = " + lib.itos(param1) + ", error_code = " + lib.itos(param2));
			break;
		case PR_EV_IMAGECAPTURED:
			lib.WriteLine("<Event> Image captured: page = " + lib.itos(param1) + ", light = " + lib.itos(param2));
			break;
		case PR_EV_CAPTURESTARTED:
			lib.WriteLine("<Event> Capture started: page = " + lib.itos(param1));
			break;
		case PR_EV_NOIMAGEINFO:
			lib.WriteLine("<Event> No image info: page = " + lib.itos(param1) + ", light = " + lib.itos(param2));
			break;
		case PR_EV_DOCFRAMEFOUND:
			lib.WriteLine("<Event> Document frame found: page = " + lib.itos(param1));
			break;
		default:
			lib.WriteLine("<Event> General event(" + lib.itos(event) + "): p1 = " + lib.itos(param1) + ", p2 = " + lib.itos(param2));
			break;
	}
}

/**
 * Main Function
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

		/* Getting the device list */
		lib.FunctionStart("Getting device list");
		vector<string> devlist = pr.GetDeviceListA();
		lib.FunctionEnd();

		if (!devlist.size()) {
			lib.WriteLine("No device found!");
			return 0;
		} else {
			lib.WriteLine(lib.itos(devlist.size()) + " device(s) found!");
		}

		/* Connecting to the first device */
		lib.FunctionStart("Connecting to the first device " + devlist[0]);
		pr.UseDevice(devlist[0], PR_UMODE_FULL_CONTROL);
		lib.FunctionEnd();

		/* Warming UV tubes */
		try {
			lib.FunctionStart("Warming UV tubes");
			pr.SetProperty("freerun_mode", PR_FRMODE_UVLEDWARMING);
			lib.FunctionEnd();
		} catch (gxException e) {
			lib.DisplExcp(e);
		}

		/* Setting all the lights for the first page */
		try {
			lib.FunctionStart("Setting lights");
			vector<int> pages;
			pages.push_back(0xFF);
			pr.SetPageLight(pages);
			lib.FunctionEnd();
		} catch (gxException e) {
			lib.DisplExcp(e);
		}

		/* Setting event function */
		try {
			lib.FunctionStart("Setting event function");
			pr.SetProperty("event_types", PR_ET_LED | PR_ET_CAPTURE);
			pr.SetEventFunction(evfunc, NULL);
			lib.FunctionEnd();
		} catch (gxException e) {
			lib.DisplExcp(e);
		}

		while (!lib.KbHit()) {

			lib.ProcessStart("Processing document");

			/* Capturing images */
			lib.FunctionStart("Capturing images");
			pr.Capture();
			lib.FunctionEnd();

			/* Saving to file */
			try {
				lib.FunctionStart("Saving original image");
				pr.SaveImage(0,PR_LIGHT_WHITE,PR_IT_ORIGINAL,"original.jpg",GX_JPEG);
				lib.FunctionEnd();
			} catch (gxException e) {
				lib.DisplExcp(e);
			}

			try {
				lib.FunctionStart("Saving document image");
				pr.SaveImage(0,PR_LIGHT_WHITE,PR_IT_DOCUMENT,"document.jpg",GX_JPEG);
				lib.FunctionEnd();
			} catch (gxException e) {
				lib.DisplExcp(e);
			}

			lib.ProcessEnd();
			lib.WaitForSec(3);
		}

		/* Turning off the lights */
		try {
			lib.FunctionStart("Turning off the lights");
			pr.SetProperty("freerun_mode", PR_FRMODE_NULL);
			lib.FunctionEnd();
		} catch (gxException e) {
			lib.DisplExcp(e);
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
