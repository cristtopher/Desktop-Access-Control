/** \file *********************************************************************
 *
 * pr_motdet - Passport Reader sample program
 *
 * 2006-2010 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/

/**
 * Device controlling example
 *
 * Purpose:
 *		Show how to control the device.
 *
 * Description:
 *		Test the power of the device after successful startup.
 *
 *		Enable motion detection and check the state of the start button and the motion detection, and display it
 *		on the console. The display leds are controlled by the result of the tests.
 *
 *		Press a key to break the testing loop.
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
	vector<string> statxt(6);
	statxt[0] = "No document detected.";
	statxt[1] = "Document is moving.";
	statxt[2] = "Take out the document!";
	statxt[3] = "";
	statxt[4] = "Ready for reading.";
	statxt[5] = "Button is pressed.";

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

		/* Testing power switch */
		try {
			lib.FunctionStart("Testing power switch");
			int state = pr.TestPowerState();
			if ((state & PR_PWR_MASK) == PR_PWR_OFF)
				lib.WriteLine("Power is off! Please turn power on!");

			while ((state & PR_PWR_MASK) == PR_PWR_OFF) {
				try {
					state = pr.TestPowerState();
				} catch (gxException e) {
					lib.DisplExcp(e);
				}
				lib.Wait(300);
			}
			lib.FunctionEnd();
		} catch (gxException e) {
			lib.DisplExcp(e);
		}

		/* Enabling motion detection */
		try {
			lib.FunctionStart("Enabling motion detection");
			pr.SetProperty("freerun_mode",PR_FRMODE_TESTDOCUMENT);
			lib.FunctionEnd();
		} catch (gxException e) {
			lib.DisplExcp(e);
		}

		while (!lib.KbHit()) {
			try {
				/* Testing the start button */
				int state = pr.TestButton(PR_KEY_START);
				if (state == PR_KEY_PRESSED) state = 5;
				else {
					/* If the start button is not pressed testing the document detection */
					state = pr.TestDocument(0);

					/* Turning the display leds depending on the status */
					int color = PR_SLC_OFF;
					switch(state) {
						case PR_TD_OUT:		color = PR_SLC_GREEN; break;
						case PR_TD_MOVE:	color = PR_SLC_ANY; break;
						case PR_TD_NOMOVE:	color = PR_SLC_RED; break;
					}
					pr.SetStatusLed(0xFF, color);
				}
				lib.Write("State of the device: " + statxt[state] + "        \r");
				lib.Wait(200);
				if ((state == PR_TD_IN) || (state == 5)) lib.Wait(800);
			} catch (gxException e) {
				lib.DisplExcp(e);
			}
		}
		lib.WriteLine("");

		/* Turning off the lights */
		try {
			lib.FunctionStart("Turning off the lights");
			pr.SetProperty("freerun_mode", PR_FRMODE_NULL);
			lib.FunctionEnd();
		} catch (gxException e) {
			lib.DisplExcp(e);
		}

		/* Turning off the display leds */
		try {
			lib.FunctionStart("Turning off the display leds");
			pr.SetStatusLed(0xFF, PR_SLC_OFF);
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
		return 0;
	}

	return 1;
}
