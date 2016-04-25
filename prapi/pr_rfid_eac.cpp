/** \file *********************************************************************
 *
 * pr_rfid_eac - Passport Reader sample program
 *
 * 2006-2010 (c) ARH Inc. (http://www.arhungary.hu)
 ******************************************************************************/

/**
 * RFID handling example
 *
 * Purpose:
 *		Show how to read data from an EAC RFID chip.
 *
 * Description:
 *
 *		Activate the Basic Access Control mechanism in case of BAC protected documents.
 *		Execute Passive, Active, Chip, Terminal Authentication. Reads all files from the RFID chip.
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

/* The load_certificates helper function, loading the certificate files */
int load_certificates(PassportReader &pr)
{
	vector<string>::size_type i;
	/* Loading certificates */
	vector<string> list = lib.FileList("../../../data/certs", "*.cer");
	for (i=0; i<list.size(); i++) {
		try {
			lib.FunctionStart("Loading sample certificate: " + list[i]);
			pr.LoadCertFile(list[i], "");
			lib.FunctionEnd();
		} catch (gxException e) {
			lib.DisplExcp(e);
		}
	}

	/* Loading CV certificates */
	list = lib.FileList("../../../data/certs", "*.cvcert");
	for (i=0; i<list.size(); i++) {
		try {
			lib.FunctionStart("Loading sample CV certificate: " + list[i]);
			string pk = list[i].substr(0,list[i].length()-6) + "pkcs8";
			pr.LoadCertFile(list[i], lib.IsFile(pk) ? pk.c_str() : "");
			lib.FunctionEnd();
		} catch (gxException e) {
			lib.DisplExcp(e);
		}
	}
	return 0;
}

/* The make_bac helper function, reading MRZ from the document and using it to make BAC */
int make_bac(PassportReader &pr, string & card)
{
	/* Setting only infra light for capture */
	try {
		lib.FunctionStart("\t- Setting infra light");
		vector<int> pages;
		pages.push_back(pr.LightMask(PR_LIGHT_INFRA,0));
		pr.SetPageLight(pages);
		lib.FunctionEnd();

		lib.FunctionStart("\t- Capturing images");
		pr.Capture();
		lib.FunctionEnd();

		lib.FunctionStart("\t- Reading MRZ");
		prDoc* doc = pr.GetMrz(0, PR_LIGHT_INFRA, PR_IT_ORIGINAL);
		lib.FunctionEnd();

		if (!doc->IsValid()) {
			if (doc) {delete doc; doc = NULL;}
			gxSystem::SetError(GX_ENOENT,L"No MRZ data found!");
			throw;
		}

		vector<string> mrz;
		mrz.push_back(doc->FieldA(PR_DF_MRZ1));
		mrz.push_back(doc->FieldA(PR_DF_MRZ2));
		mrz.push_back(doc->FieldA(PR_DF_MRZ3));
		if (doc) {delete doc; doc = NULL;}

		lib.FunctionStart("\t- Making BAC");
		pr.MakeBAC(card, mrz);
		lib.FunctionEnd();
	} catch (gxException e) {
		return lib.DisplExcp(e);
	}
	return 0;
}

/* The get_rfid_files helper function, reading RFID dir from the resolved EF_COM document */
int get_rfid_files(prDoc* doc)
{
	gxVariant* pdoc = doc->ToVariant();
	if(pdoc == NULL) return 0;
	int ret = 0;
	gxVariant v;
	char path[64];
	gx_snprintf(path, sizeof(path), "C,D=%i/L,V=%i/C,D=%i", PRV_FIELDLIST, PR_DF_RFID_FIELDS|PR_DFE_DOCUMENT_DESCRIPTOR, PRV_RFIDDIR);
	if(pdoc->GetItemByPath(v, path))
	{
		ret = v.GetInt();
		v.Dispose();
	}
	delete pdoc;
	return ret;
}

/* The resolve_dg1 helper function, parsing EF_DG1 and displaying MRZ information */
int resolve_dg1(PassportReader &pr, void * data, int size)
{
	int error_code = 0;
	prDoc* doc = NULL;
	try {
		lib.FunctionStart("\t- Resolving DG1");
		doc = pr.ResolveRfidData(data, size);
		if (!doc->IsValid()) lib.Error("No MRZ data found!");
		else {
			lib.FunctionEnd();
			lib.WriteLine("\t- MRZ data:");
			string mrz = doc->FieldA(PR_DF_RFID_MRZ);
			lib.WriteLine("\t\t" + mrz.substr(0, 44));
			lib.WriteLine("\t\t" + mrz.substr(44, 87));
		}
	} catch (gxException e) {
		error_code = lib.DisplExcp(e);
	}
	if (doc) { delete doc; doc = NULL; }
	return error_code;
}

/* The resolve_dg2 helper function, parsing EF_DG2 and saving the face image */
int resolve_dg2(PassportReader &pr, void * data, int size)
{
	int error_code = 0;
	gxImage * img = NULL;
	prDoc* doc = NULL;
	try {
		lib.FunctionStart("\t- Resolving");
		doc = pr.ResolveRfidData(data, size);
		if (!doc->IsValid()) lib.Error("No image data found!");
		else {
			lib.FunctionEnd();
			lib.FunctionStart("\t- Saving image");
			img = doc->FieldImage(PR_DF_RFID_FACE);
			if (!img->IsValid()) lib.Error("No image found!");
			else {
				img->Save("face.jpg", GX_JPEG);
				lib.FunctionEnd();
			}
		}
	} catch (gxException e) {
		error_code = lib.DisplExcp(e);
	}
	if (img) delete img;
	if (doc) { delete doc; doc = NULL; }
	return error_code;
}

/**
 * Main function
 */
int main() {
	vector<string> cardlist;
	void * data = NULL;
	int size = 0;
	unsigned int rfid_files = 0;
	string fn;
	size_t i;
	prDoc * doc = NULL;

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

		/* Loading certificates */
		lib.WriteLine("Loading certificates");
		load_certificates(pr);

		while (!lib.KbHit()) {

			lib.ProcessStart("RFID");

			try {

				/* Searching for RFID cards */
				lib.FunctionStart("Searching for RFID cards ...");
				cardlist = pr.GetRfidCardListA();
				lib.FunctionEnd();

				if(cardlist.size() == 0)
				{
					lib.WriteLine("No card found");
				}
				else
				{
					/* Connecting to the first chip */
					lib.FunctionStart("Connecting to the RFID chip");
					pr.ConnectRfidCard(cardlist[0]);
					lib.FunctionEnd();
					lib.WriteLine("Serial no.: " + cardlist[0]);

					/* Initializing chip reading */
					lib.FunctionStart("Initializing chip reading");
					try {
						lib.FunctionStart("Initializing chip reading");
						pr.GetRfidFile(cardlist[0].c_str(), PR_RFID_EF_COM, &data, &size);
						lib.FunctionEnd();
					} catch (gxException e) {
						lib.DisplExcp(e);
						if (e.GetErrorCode() != GX_EACCES) throw;
						make_bac(pr, cardlist[0]);
						lib.FunctionStart("Initializing chip reading");
						pr.GetRfidFile(cardlist[0].c_str(), PR_RFID_EF_COM, &data, &size);
						lib.FunctionEnd();
					}

					/* Getting available files */
					lib.FunctionStart("\t- Available files");
					doc = pr.ResolveRfidData(data, size);
					rfid_files = 0;
					if (doc->IsValid()) {
						rfid_files = get_rfid_files(doc);
						for (i=PR_RFID_EF_DG1; i<=PR_RFID_EF_DG16; i++)
							if (((1<<i) & rfid_files)) lib.Write("DG" + lib.itos(i) + " ");
					}
					if (doc) { delete doc; doc = NULL; }
					if (data) {gx_globalfree(data); data = NULL; size = 0;}
					lib.FunctionEnd();

					/* Making Chip Authentication */
					if ((1 << PR_RFID_EF_DG14) & rfid_files) {
						try {
							lib.FunctionStart("\t- Making Chip Authentication");
							pr.MakeChipAuth(cardlist[0]);
							lib.FunctionEnd();
						} catch (gxException e) {
							lib.DisplExcp(e);
						}
					}

					/* Making Passive Authentication */
					try {
						lib.FunctionStart("\t- Making Passive Authentication");
						pr.MakePassiveAuth(cardlist[0]);
						lib.FunctionEnd();
					} catch (gxException e) {
						lib.DisplExcp(e);
					}

					/* Making Active Authentication */
					if ((1 << PR_RFID_EF_DG15) & rfid_files) {
						try {
							lib.FunctionStart("\t- Making Active Authentication");
							pr.MakeActiveAuth(cardlist[0]);
							lib.FunctionEnd();
						} catch (gxException e) {
							lib.DisplExcp(e);
						}
					}

					/* Making Terminal Authentication */
					if ((1 << PR_RFID_EF_DG14) & rfid_files) {
						try {
							lib.FunctionStart("\t- Making Terminal Authentication");
							pr.MakeTerminalAuth(cardlist[0]);
							lib.FunctionEnd();
						} catch (gxException e) {
							lib.DisplExcp(e);
						}
					}

					/* Reading available files, checking hash, saving and resolving them */
					for (i=PR_RFID_EF_COM; i<=PR_RFID_EF_SOD; i++) {
						if (!((1<<i) & rfid_files)) continue;

						switch (i) {
						case PR_RFID_EF_COM: fn = "EF_COM"; break;
						case PR_RFID_EF_CVCA: fn = "EF_CVCA"; break;
						case PR_RFID_EF_SOD: fn = "EF_SOD"; break;
						default: fn = "EF_DG" + lib.itos(i); break;
						}

						try {
							lib.FunctionStart("Reading " + fn);
							pr.GetRfidFile(cardlist[0].c_str(), i, &data, &size);
							lib.FunctionEnd();
						} catch (gxException e) {
							lib.DisplExcp(e);
							continue;
						}

						try {
							if ((i>=PR_RFID_EF_DG1) && (i<=PR_RFID_EF_DG16)) {
								lib.FunctionStart("\t- Checking hash");
								pr.CheckRfidFileHash(cardlist[0], i);
								lib.FunctionEnd();
							}
						} catch (gxException e) {
							lib.DisplExcp(e);
						}

						lib.FunctionStart("\t- Saving " + fn);
						if (!lib.Save(fn + ".dat", data, size)) lib.Error("File write error!");
						else lib.FunctionEnd();

						if (i == PR_RFID_EF_DG1) resolve_dg1(pr, data, size);
						if (i == PR_RFID_EF_DG2) resolve_dg2(pr, data, size);

						if (data) {gx_globalfree(data); data = NULL; size = 0;}
					}

					/* Disconnecting from the chip */
					lib.FunctionStart("Disconnecting from the RFID chip");
					pr.DisconnectRfidCard(cardlist[0]);
					lib.FunctionEnd();
				}
			} catch (gxException e) {
				lib.DisplExcp(e);
			}

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
