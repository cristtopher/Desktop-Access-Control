#ifndef PRTYPES_INCL
#define PRTYPES_INCL
/*******************************************************************************
 * PR TYPES 2004-2015 (c) ARH Inc.
 * 2015.04.17 v2.1.5.25
 ******************************************************************************/
#ifdef GX_DOTNET
	#using "gxdotnet7.dll"
#endif
#include "gxtypes.h"
/******************************************************************************/
/**
  \file prtypes.h
  <b>Passport Reader Api module constants</b>

  The  Passport Reader  is a  travel  document  reader  and  analyser  system by
  <b>ARH Inc.</b>,  which bases  on the GX system.  The  prtypes.h  contains the
  descriptions of constants of the api module.

*/
/******************************************************************************/
#ifdef GX_NAMESPACES
	namespace pr {
#endif

#ifdef GX_DOTNET
	#pragma managed
#endif

/** Device connection modes in the prapi */

GX_ENUM PR_USAGEMODE {
	PR_UMODE_DISCONNECT		= 0,	/**< Disconnect the actually used device */
	PR_UMODE_NORMAL_USE		= 1,	/**< Connect the device with restricted abilities */
	PR_UMODE_FULL_CONTROL	= 2		/**< Connect the device with all the abilities */
};

/**
  Device freerun light controlling modes. Not all of the modes can be used at the same time.
  The system can override the control settings.
*/

GX_ENUM PR_FREERUNMODE {
	PR_FRMODE_NULL			= 0x0000,	/**< Disable freerun activity */
	PR_FRMODE_PREVIEWLIGHT	= 0x0001,	/**< Direct controlled lights for real-time preview image capturing */
	PR_FRMODE_UVLEDWARMING	= 0x0002,	/**< UV tube warming control */
	PR_FRMODE_TESTDOCUMENT	= 0x0004	/**< Lights controlled by the HW/SW object motion detection algorithm */
};

/**
  Device motion detection methods. Not all of the modes can be set for the different
  types of devices. See the device descriptions for more information.
*/

GX_ENUM PR_TESTDOCMODE {
	PR_TDM_COMBINED				= 0,	/**< Combined software and hardware test (one detection per document) */
	PR_TDM_COMBINEDMOVEABLE		= 1,	/**< Combined software and hardware test (documents can be redetected after moving) */
	PR_TDM_FORCEDSOFTWARE		= 2,	/**< Only software methods are used for detection */
	PR_TDM_DELAYEDHARDWARE		= 3		/**< Only hardware devices are used for detection */
};

/** Used object windows of the PR system */

GX_ENUM PR_WINDOW_ID {
	PR_OW_MASK			= 0xff000000,	/**< Mask for object window operation */
	PR_OW_DEFAULT		= 0x00000000,	/**< Default object window */
	PR_OW_1ST			= 0x01000000,	/**< First object window */
	PR_OW_2ND			= 0x02000000,	/**< Second object window */
};

/** Options for page light setup */

GX_ENUM PR_PAGELIGHT_PROP {
	PR_CAPTURE_CONTINUOUS	= 0x10000000,	/**< Images of the capture will be embedded into the previous page */
	PR_APPEND_PAGELIGHTS	= 0x20000000,	/**< The actual page/light list will be appended with the current set */
};

/** Used light settings of the PR system */

GX_ENUM PR_LIGHT {
	PR_LIGHT_OFF		=  0,		/**< Undefined light / Light Off */
	PR_LIGHT_WHITE		=  1,		/**< Visible light */
	PR_LIGHT_INFRA		=  2,		/**< Infra-red light */
	PR_LIGHT_UV			=  3,		/**< Ultra-violet light */
	PR_LIGHT_COAXIAL	=  4,		/**< Visible coaxial light */
	PR_LIGHT_KINEGRAM	=  5,		/**< Kinegram image */
	PR_LIGHT_PHOTO		=  6,		/**< Photo image */
	PR_LIGHT_BLUE		= 16,		/**< Blue light */
	PR_LIGHT_RED		= 17,		/**< Red light */
	PR_LIGHT_CLEANUV	= 19,		/**< Enhanced UV image */
	PR_LIGHT_CLEANOVD	= 21,		/**< Differential OVD image */
};

/** Result of the document (motion) detector module */

GX_ENUM PR_TESTDOC {
	PR_TD_OUT		= 0,		/**< Document is out of the object test area */
	PR_TD_MOVE		= 1,		/**< Document is moving on the object window */
	PR_TD_NOMOVE	= 2,		/**< Document is not moving on the object window (after capturing or moving) */
	PR_TD_IN		= 4			/**< Document is on the object window, ready to capture */
};

/** The barcode module currently can read only the following barcode types */

GX_ENUM PR_BCTYPE {
	PR_BCTYPE_EAN8			= 1,	/**< 8 char article numbering code */
	PR_BCTYPE_EAN13			= 2,	/**< 13 char article numbering code */
	PR_BCTYPE_CODE39		= 3,	/**< General text code */
	PR_BCTYPE_CODE128		= 4,	/**< General text code */
	PR_BCTYPE_PDF417		= 5,	/**< 2D binary / text code */
	PR_BCTYPE_INTER25		= 6,	/**< General number code */
	PR_BCTYPE_DATAMATRIX	= 7,	/**< 2D binary / text code */
	PR_BCTYPE_QR			= 8,	/**< 2D binary / text code */
	PR_BCTYPE_AZTEC			= 9,	/**< 2D binary / text code */
	PR_BCTYPE_UPU			= 10,	/**< Universal Postal Union code */
};

/** Image types of the prapi functions (get-, save-, drawimage) */

GX_ENUM PR_IMAGE_TYPE {
	PR_IT_ORIGINAL = 0,	/**< Captured image of the device window */
	PR_IT_DOCUMENT,		/**< Resampled image of the document */
	PR_IT_PREVIEW,		/**< Low resolution real-time captured image */
	PR_IT_FINGER,		/**< Captured finger image */
};

/** The event types and the events of the prapi module */

GX_ENUM PR_EVENT {
	PR_ET_LED				= 1,	/**< Led events */
	PR_ET_CAPTURE			= 2,	/**< Capture events */
	PR_ET_IO				= 4,	/**< Input events */
	PR_ET_RFID				= 8,	/**< RFID events */

	PR_EV_UVLEDWARMING		=   1,	/**< UV tube warming started (Led event) */

	PR_EV_PAGECAPTURED		= 101,	/**< All images of the page captured (Capture event) */
	PR_EV_IMAGECAPTURED		= 102,	/**< Image captured (Capture event) */
	PR_EV_CAPTURESTARTED	= 103,	/**< Capture started (Capture event) */
	PR_EV_NOIMAGEINFO		= 104,	/**< No image captured because it contains no information (Capture event) */
	PR_EV_DOCFRAMEFOUND		= 105,	/**< Document frame found (Capture event) */
	PR_EV_FGCAP				= 106,	/**< Fingers captured (Capture event) */
	PR_EV_PREVIEWCAPTURED	= 107,	/**< Preview captured (Capture event) */

	PR_EV_MOTIONDETECTION	= 201,	/**< Motion detection state changed (Input event) */
	PR_EV_BUTTON			= 202,	/**< Button state changed (Input event) */
	PR_EV_POWER				= 203,	/**< Power state or battery level changed (Input event) */
	PR_EV_CONNECTION		= 204,	/**< Device list changes (Input event), occures when no device is used and a new device is connected or the used device is disconnected */
	PR_EV_DEVICE_UPDATE		= 205,	/**< Firmware or calib file transfer events (Input event)  */

	PR_EV_RFAUTH_BEGIN		= 301,	/**< RFID authentication begins (RFID event) */
	PR_EV_RFAUTH_WAIT4INPUT	= 302,	/**< RFID authentication is waiting for input (RFID event) */
	PR_EV_RFAUTH_DONE		= 303,	/**< RFID authentication done (RFID event) */
	PR_EV_RFFILE_BEGIN		= 304,	/**< RFID file transfer begins (RFID event) */
	PR_EV_RFFILE_DONE		= 305,	/**< RFID file transfer done (RFID event) */
	PR_EV_RFFILE_CHECKED	= 306,	/**< RFID file hash checked (RFID event) */

};

/** The window messages of the PR system. */

GX_ENUM PR_WND_MESSAGE {
	PR_WM_UVLEDWARMING		= 0,	/**< Window message type for led warming event */
	PR_WM_PAGECAPTURED		= 1,	/**< Window message type for page captured event */
	PR_WM_IMAGECAPTURED		= 2,	/**< Window message type for image captured event */
	PR_WM_CAPTURESTARTED	= 3,	/**< Window message type for capture started event */
	PR_WM_NOIMAGEINFO		= 4,	/**< Window message type for image info state event in advanced image capture processing */
	PR_WM_PREVIEWCAPTURED	= 5,	/**< Window message type for preview captured event */
	PR_WM_MOTIONDETECTION	= 6,	/**< Window message type for motion detection state changed event */
	PR_WM_BUTTON			= 7,	/**< Window message type for button state changed event */
	PR_WM_POWER				= 8,	/**< Window message type for power state or battery level changed event */
	PR_WM_CONNECTION		= 9,	/**< Window message type for device list changes, occures when no device is used and a new device is connected or the used device is disconnected */
	PR_WM_DOCFRAMEFOUND		= 10,	/**< Window message type for document frame found event */
	PR_WM_FGCAP				= 11,	/**< Window message type for fingers captured event */
	PR_WM_RFAUTH_BEGIN		= 12,	/**< Window message type for RFID authentication begins event */
	PR_WM_RFAUTH_WAIT4INPUT	= 13,	/**< Window message type for RFID authentication is waiting for input event */
	PR_WM_RFAUTH_DONE		= 14,	/**< Window message type for RFID authentication done event */
	PR_WM_RFFILE_BEGIN		= 15,	/**< Window message type for RFID file transfer begins event */
	PR_WM_RFFILE_DONE		= 16,	/**< Window message type for RFID file transfer done event */
	PR_WM_RFFILE_CHECKED	= 17,	/**< Window message type for RFID file hash checked event */
	PR_WM_DEVICE_UPDATE		= 18,	/**< Window message type for firmware or calib file transfer event */

	PR_WM_LAST_VALUE		= 31,	/**< The end of the reserved space for future window message types */
};

/** File formats for document saving functions. */

GX_ENUM PR_DOCFILEFORMATS {
	PR_DFF_XML				= 1,	/**< XML file format */
	PR_DFF_ZIPPED			= 2,	/**< Zipped file format, i.e. XML descriptor and binary image files packed in one zip file */
	PR_DFF_AUTH				= 3,	/**< Authentication reference data format */
};

/** File IDs contained in rfid chips */

GX_ENUM PR_RFID_FILES {
	PR_RFID_EF_COM			= 0,	/**< EF.COM */
	PR_RFID_EF_DG1			= 1,	/**< EF.DG1 */
	PR_RFID_EF_DG2			= 2,	/**< EF.DG2 */
	PR_RFID_EF_DG3			= 3,	/**< EF.DG3 */
	PR_RFID_EF_DG4			= 4,	/**< EF.DG4 */
	PR_RFID_EF_DG5			= 5,	/**< EF.DG5 */
	PR_RFID_EF_DG6			= 6,	/**< EF.DG6 */
	PR_RFID_EF_DG7			= 7,	/**< EF.DG7 */
	PR_RFID_EF_DG8			= 8,	/**< EF.DG8 */
	PR_RFID_EF_DG9			= 9,	/**< EF.DG9 */
	PR_RFID_EF_DG10			= 10,	/**< EF.DG10 */
	PR_RFID_EF_DG11			= 11,	/**< EF.DG11 */
	PR_RFID_EF_DG12			= 12,	/**< EF.DG12 */
	PR_RFID_EF_DG13			= 13,	/**< EF.DG13 */
	PR_RFID_EF_DG14			= 14,	/**< EF.DG14 */
	PR_RFID_EF_DG15			= 15,	/**< EF.DG15 */
	PR_RFID_EF_DG16			= 16,	/**< EF.DG16 */
	PR_RFID_EF_CARD_ACCESS	= 28,	/**< EF.CardAccess */
	PR_RFID_EF_CARD_SECURITY= 29,	/**< EF.CardSecurity */
	PR_RFID_EF_CVCA			= 30,	/**< EF.CVCA */
	PR_RFID_EF_SOD			= 31,	/**< EF.SOD */
	PR_RFID_CF_DS			= 32,	/**< Document Signer certificate file */
	PR_RFID_CF_CSCA			= 33,	/**< Country Signing CA certificate file */
	PR_RFID_EF_ALL			= -1,	/**< All files available on the chip */
	PR_RFID_EF_SEL			= -2,	/**< Files selected by the rfid/selected_files property */

	PR_RFID_GENERAL_DATA			= 1000,
	PR_RFID_PERSONAL_DETAILS		= 1001,
	PR_RFID_ISSUER_DETAILS			= 1002,
	PR_RFID_PORTRAIT				= 1003,
	PR_RFID_SIGNATURE				= 1004,
	PR_RFID_FACE					= 1005,
	PR_RFID_FINGER					= 1006,
	PR_RFID_IRIS					= 1007,
	PR_RFID_OTHER_BIOMETRIC_DATA	= 1008,
	PR_RFID_DOMESTIC_DATA			= 1009,
	PR_RFID_AA_DATA					= 1010,
	PR_RFID_ANY_FACE				= 1011,
	PR_RFID_TOCFILE					= 1012,
	PR_RFID_EAP_DATA				= 1013,
};

/** Memory addressing options for rfid storage cards. */

GX_ENUM PR_RFID_MEMOPTS {
	PR_RFID_MEMORY_ADDRESS		= 0x40000000,		/**< the lower 16 bit of the rf file id is a memory address. */
	PR_RFID_BLOCK_ADDRESS		= 0x20000000,		/**< the lower 16 bit of the rf file id is a block address. */
	PR_RFID_SECTOR_ADDRESS		= 0x60000000,		/**< the lower 16 bit of the rf file id is a sector address. */
};

/** Authentication codes */

GX_ENUM PR_AUTH_PROC
{
	PR_NO_AUTH_PROCESS		= 0,	/**< No current authentication */
	PR_PASSIVE_AUTH			= 1,	/**< Passive authentication */
	PR_TERMINAL_AUTH		= 2,	/**< Terminal authentication */
	PR_PACE					= 3,	/**< Password Authenticated Connection Establishment */
	PR_BAC					= 4,	/**< Basic Access Control */
	PR_CHIP_AUTH			= 5,	/**< Chip authentication */
	PR_ACTIVE_AUTH			= 6,	/**< Active authentication */
	PR_SELECT_APPLICATION	= 7,	/**< Select application */
	PR_BAP					= 8,	/**< Basic Access Protection */
	PR_BLOCK_AUTH			= 9,	/**< Block authentication */
	PR_INIT_TERMINAL_AUTH	= 10,	/**< Terminal authentication 1st part */
	PR_COMPLETE_TERMINAL_AUTH = 11,	/**< Terminal authentication 2nd part */
	PR_STORAGE_CARD_AUTH	= 12,	/**< Storage card authentication */
};

/** Requested authentication level for automatic RF reading */

GX_ENUM PR_REQ_AUTH
{
	PR_REQ_MIN_AUTH				= 1,	/**< Minimal authentication */
	PR_REQ_OPT_AUTH				= 2,	/**< Optimal authentication */
	PR_REQ_MAX_AUTH				= 3,	/**< Maximal authentication */
};

/** Application types */

GX_ENUM PR_APP_TYPE
{
	PR_APP_NONE 		= 0,
	PR_APP_EPASSPORT	= 1,
	PR_APP_EID			= 2,
	PR_APP_ESIGN		= 3,
	PR_APP_ISODL		= 4,
	PR_APP_NFC			= 5,
	PR_APP_EDL			= 6,
};

/** Password codes for Password Authenticated Connection Establishment (PACE) */

GX_ENUM PR_PACE_PASSWORD
{
	PR_PACE_PW_MRZ = 1,				/**< Password from MRZ */
	PR_PACE_PW_CAN = 2,				/**< Password from Card Access Number */
	PR_PACE_PW_PIN = 3,				/**< Password from Personal Identification Number */
	PR_PACE_PW_PUK = 4,				/**< Password from PIN Unblock Key */
};

/** Certificate selection flag */

GX_ENUM PR_CERTIFICATE_SELECTION
{
	PR_SEL_CERT_EXPIRED = 0x100,	/**< Select expired certificates */
	PR_SEL_CERT_REVOKED = 0x200,	/**< Select revoked certificates */
};

/** Power state codes of devices */

GX_ENUM PR_POWER_STATE {
	PR_PWR_MASK				= 0x000f,	/**< Mask for power data */

	PR_PWR_UNKNOWN			= 0x0000,	/**< The power state is unknown (cannot be tested) */
	PR_PWR_OFF				= 0x0001,	/**< The power is off */
	PR_PWR_ON				= 0x0002,	/**< The power is on */
	PR_PWR_DATA				= 0x0003,	/**< The power is on data wire */

	PR_BATTERY_MASK			= 0x00f0,	/**< Mask for battery data */

	PR_BATTERY_UNAVAILABLE	= 0x0000,	/**< The battery is unavailbe */
	PR_BATTERY_AVAILABLE	= 0x0010,	/**< The battery is availbe */
	PR_BATTERY_UNKNOWN		= 0x0020,	/**< The state of the battery is unavailbe */
};

/** Usable status led colors. Both led types and led states are enumerated. */

GX_ENUM PR_STATUS_LED_COLOR {
	PR_SLC_OFF		= 0x00,		/**< Led state: turn off */
	PR_SLC_OG		= 0x02,		/**< The led type is a two color green/orange. Set to this value is not permitted. */
	PR_SLC_ORG		= 0x03,		/**< The led type is a three color red/green/orange. Set to this value is not permitted. */
	PR_SLC_SYSTEM	= 0x10,		/**< Led type. The led is controlled by the system only. Set to this value is not permitted. */
	PR_SLC_GREEN	= 0x81,		/**< State/type. The color of the led is green */
	PR_SLC_RED		= 0x82,		/**< State/type. The color of the led is red */
	PR_SLC_ORANGE	= 0x83,		/**< State/type. The color of the led is orange */
	PR_SLC_BLUE		= 0x84,		/**< State/type. The color of the led is blue */
	PR_SLC_AUTO		= 0xac,		/**< Led state: turn on automatic control */
	PR_SLC_ANY		= 0xff,		/**< Led state: turn on any of the available lights */
};

/** Id of the buzzer */

GX_ENUM PR_BUZZER {
	PR_SLC_BUZZER	= 0xc0,		/**< Buzzer */
};

/** Button state codes of PR devices */

GX_ENUM PR_KEY_STATE {
	PR_KEY_UNKNOWN		= 0,	/**< The state or presence of the button is unknown (cannot be tested) */
	PR_KEY_PRESSED		= 1,	/**< The state of the button is pressed */
	PR_KEY_RELEASED		= 2,	/**< The state of the button is released */
	PR_KEY_NOKEY		= 3		/**< The button does not exist on the device */
};

/** Button codes of PR devices */

GX_ENUM PR_KEY_CODE {
	PR_KEY_POWER	= 0x10101,	/**< Code of the power button */
	PR_KEY_START	= 0x10110,	/**< Code of the start button */
};

/** Hardware part types */

GX_ENUM PR_HWTYPE {
	PR_HW_IO,					/**< Device */
	PR_HW_SCANNER,				/**< Scanner */
	PR_HW_RFIDREADER,			/**< Rfid reader */
	PR_HW_CONTACTREADER,		/**< Contact smart card reader */
	PR_HW_MAGNETICREADER,		/**< Magnetic stripe reader */
};

/** Variant IDs used. */

GX_ENUM PR_VAR_ID {

	PRV_ROOT			= 0,					/**< The root of the document structure */

	PRV_PAGELIST		= PRV_ROOT | 1,			/**< Reserved for internal use */
	PRV_TASKLIST		= PRV_ROOT | 2,			/**< Reserved for internal use */
	PRV_PERSONINFO		= PRV_ROOT | 3,			/**< Reserved for internal use */
	PRV_DOCINFO			= PRV_ROOT | 4,			/**< Reserved for internal use */

	PRV_DOCUMENT		= 0xD0000000,			/**< Document type, see \ref PR_DOCUMENT */
	PRV_FIELDLIST		= PRV_DOCUMENT | 1,		/**< List of fields */
	PRV_FIELD			= PRV_DOCUMENT | 2,		/**< Field id, see \ref PR_DOCFIELD */
	PRV_FIELDVALUE		= PRV_DOCUMENT | 3,		/**< Field data */
	PRV_CHECKSUM		= PRV_DOCUMENT | 4,		/**< Field checksum */
	PRV_CONFIDENCE		= PRV_DOCUMENT | 5,		/**< Confidence value */
	PRV_WINDOWFRAME		= PRV_DOCUMENT | 6,		/**< Frame by window coordinates (in um) */
	PRV_WINDOWFULLFRAME	= PRV_DOCUMENT | 7,		/**< Nominal frame by window coordinates (in um) */
	PRV_ACCORDANCE		= PRV_DOCUMENT | 8,		/**< Accordance to reference data */
	PRV_FMTVALUE		= PRV_DOCUMENT | 9,		/**< Formatted field data */
	PRV_STDVALUE		= PRV_DOCUMENT | 10,	/**< Standardized field data */
	PRV_CORRECTION		= PRV_DOCUMENT | 11,	/**< Data correction value */
	PRV_FIELDCOMPARES	= PRV_DOCUMENT | 12,	/**< Array of field compare data */
	PRV_CHKDETAILS		= PRV_DOCUMENT | 13,	/**< Array of field checking details */

	PRV_IMAGE			= 0xD0100000,			/**< Image */
	PRV_IMAGELIST		= PRV_IMAGE | 1,		/**< List of images */
	PRV_IMAGEFRAME		= PRV_IMAGE | 2,		/**< Frame by image coordinates (1/16 pixel) */
	PRV_SAMPLE			= PRV_IMAGE | 3,		/**< Sample image */

	PRV_DEVICE_INFO		= 0xD0200000,			/**< The root of the device info structure */
	PRV_DEVICE_ID		= PRV_DEVICE_INFO | 1,	/**< Device id string */
	PRV_LIGHT			= PRV_DEVICE_INFO | 2,	/**< Light value, see \ref PR_LIGHT */
	PRV_CAPTIME			= PRV_DEVICE_INFO | 3,	/**< Date and time of capture */
	PRV_PAGE			= PRV_DEVICE_INFO | 4,	/**< Page id */
	PRV_TRAFO			= PRV_DEVICE_INFO | 5,	/**< Coordinate transformation structure */
	PRV_CAMERA			= PRV_DEVICE_INFO | 6,	/**< Camera id */
	PRV_MODE			= PRV_DEVICE_INFO | 8,	/**< Capture mode */
	PRV_HWTYPE			= PRV_DEVICE_INFO | 9,	/**< Hardware part type */
	PRV_STATLEDLIST		= PRV_DEVICE_INFO | 10,	/**< List of status led colors */
	PRV_KEYBOARD		= PRV_DEVICE_INFO | 11,	/**< List of available key code values */
	PRV_POWER			= PRV_DEVICE_INFO | 12,	/**< Power capability */
	PRV_VERSION			= PRV_DEVICE_INFO | 13,	/**< HW/FW/SW/etc. version */
	PRV_WINDOWLIST		= PRV_DEVICE_INFO | 14,	/**< Window list */
	PRV_CAPABILITY		= PRV_DEVICE_INFO | 15,	/**< Subdevice capability */

	PRV_BARCODE			= 0xD0300000,			/**< Barcode type, see \ref PR_BCTYPE */
	PRV_BARCODEVALUE	= PRV_BARCODE | 1,		/**< Barcode data */
	PRV_BARCODELIST		= PRV_BARCODE | 2,		/**< Barcode list */

	PRV_OCR				= 0xD0400000,			/**< Reserved for internal use */
	PRV_OCRROWLIST		= PRV_OCR | 1,			/**< List of OCR rows */
	PRV_OCRROW			= PRV_OCR | 2,			/**< OCR row */
	PRV_OCRCHAR			= PRV_OCR | 3,			/**< OCR character */

	PRV_OQCA			= PRV_OCR | 0x00080000,	/**< Alert bits for quality assurance, see \ref PR_OCR_QUALITY_ALERT */
	PRV_OQC_ROTATION	= PRV_OQCA | 1,			/**< Rotation value for quality assurance */
	PRV_OQC_HEIGHT		= PRV_OQCA | 2,			/**< Height value for quality assurance */
	PRV_OQC_WIDTH		= PRV_OQCA | 3,			/**< Width value for quality assurance */
	PRV_OQC_HANGOUT		= PRV_OQCA | 4,			/**< Hangout value for quality assurance */
	PRV_OQC_DISTANCE	= PRV_OQCA | 5,			/**< Distance value for quality assurance */
	PRV_OQC_CONTRAST	= PRV_OQCA | 6,			/**< Contrast value for quality assurance */
	PRV_OQC_SHAPE		= PRV_OQCA | 7,			/**< Shape confidence for quality assurance */

	PRV_RFID			= 0xD0500000,			/**< Reserved for internal use */
	PRV_RFIDDIR			= PRV_RFID | 1,			/**< Data group presence map for RFID */
	PRV_RFIDFILELIST	= PRV_RFID | 2,			/**< List of RFID binaries */
	PRV_RFIDFILE		= PRV_RFID | 3,			/**< RFID file id */
	PRV_RFIDFILEDATA	= PRV_RFID | 4,			/**< Binary data of an RFID file */
	PRV_CERTID_LIST		= PRV_RFID | 5,			/**< List of Certificate Ids */
	PRV_DGLIST			= PRV_RFID | 6,			/**< Data group list */
	PRV_AUTHLIST		= PRV_RFID | 7,			/**< List of Authentication results */

	PRV_CARD			= 0xD0600000,			/**< Card Id */
	PRV_CARDTYPE		= PRV_CARD | 1,			/**< Type of a card */
	PRV_CARDATR			= PRV_CARD | 2,			/**< ATR of a card */
	PRV_CARDPOS			= PRV_CARD | 3,			/**< Card position */
	PRV_MEMORY_SIZE		= PRV_CARD | 4,			/**< Size of the memory area in bytes */
	PRV_MEMORY_BLOCK	= PRV_CARD | 5,			/**< Size of one block of memory area in bytes */
	PRV_CARDCAP			= PRV_CARD | 6,			/**< Card capability data */
	PRV_CHIPTYPE		= PRV_CARD | 7,			/**< Chip type data */

	PRV_COMMON			= 0xD0700000,			/**< RFU */
	PRV_PROCTIME		= PRV_COMMON | 1,		/**< Date and time of process execution */
	PRV_PROCPERIOD		= PRV_COMMON | 2,		/**< Duration of process execution */
	PRV_WARNLIST		= PRV_COMMON | 3,		/**< List of warning messages */
	PRV_TASK			= PRV_COMMON | 4,		/**< Call code of a GX task */

	PRV_FINGER			= 0xD0800000,			/**< Finger position, see \ref PR_FINGER_POSITION */
	PRV_FINGER_TYPE		= PRV_FINGER | 1,		/**< Finger impression type, see \ref PR_FINGER_IMPRESSION_TYPE */
	PRV_NIST_QUALITY	= PRV_FINGER | 2,		/**< NIST image quality value */
	PRV_FINGER_DRYWET	= PRV_FINGER | 3,		/**< Finger dry/wet level */
	PRV_FINGER_FRACTION	= PRV_FINGER | 4,		/**< Finger fraction level */
};

/** Variant ids used in special OCR operations. */

GX_ENUM PR_VAR_ID_OCR_PARAMS {

	PRV_OCRPARAMS		= 0xD0490000,			/**< Parameter list for OCR function */

	PRV_CHARHEIGHT		= PRV_OCRPARAMS | 1,	/**< Character height parameter (in um) */
	PRV_SPACEWIDTH		= PRV_OCRPARAMS | 2,	/**< Space width in percent of character height */
	PRV_JUSTIFICATION	= PRV_OCRPARAMS | 3,	/**< Justification of text in the field (0 - left, 1 - right, 2 - center) */
	PRV_SPACETYPE		= PRV_OCRPARAMS | 4,	/**< Type of space (0 - edges, 1 - centers) */
	PRV_FONTTYPE		= PRV_OCRPARAMS | 5,	/**< Type name of font 'string' */
};

/** OCR quality check flags. */

GX_ENUM PR_OCR_QUALITY_ALERT {

	PR_OQA_CHARPOSITION		= 1,			/**< Character position error alert bit for quality assurance */
	PR_OQA_CHARDISTANCE		= 2,			/**< Character distance error alert bit for quality assurance */
	PR_OQA_CHARSIZE			= 4,			/**< Character size error alert bit for quality assurance */
	PR_OQA_CHARROTATION		= 8,			/**< Character rotation error alert bit for quality assurance */
	PR_OQA_CONTRAST			= 0x10,			/**< Contrast error alert bit for quality assurance */
	PR_OQA_SPARE			= 0x20,			/**< Spare character in the row error alert bit for quality assurance */
	PR_OQA_ERZ				= 0x40,			/**< Hangout from the Effective Reading Zone error alert bit for quality assurance */
	PR_OQA_ROWPOSITION		= 0x100,		/**< Row position error alert bit for quality assurance */
	PR_OQA_ROWDISTANCE		= 0x200,		/**< Row distance error alert bit for quality assurance */
	PR_OQA_ROWSIZE			= 0x400,		/**< Row size error alert bit for quality assurance */
	PR_OQA_ROWROTATION		= 0x800,		/**< Row rotation error alert bit for quality assurance */
	PR_OQA_SHAPE			= 0x1000,		/**< Shape confidence error alert bit for quality assurance */
};

/** Variant ids for warnings of the Passive Authentication. */

GX_ENUM PR_VAR_ID_PA_WARNINGS {

	PRV_PA_WARNLIST						= 0xD0590000,			/**< List of Passive authentication warnings */

	PRV_PA_WARN_UNKNOWN_DG				= PRV_PA_WARNLIST | 1,
	PRV_PA_WARN_DG_MISSING 				= PRV_PA_WARNLIST | 2,
	PRV_PA_WARN_DG_HASH_MISSING			= PRV_PA_WARNLIST | 3,
	PRV_PA_WARN_COM_FORMAT 				= PRV_PA_WARNLIST | 4,
	PRV_PA_WARN_HASH_CHECK 				= PRV_PA_WARNLIST | 5,
	PRV_PA_WARN_COM_MISSING				= PRV_PA_WARNLIST | 6,

	PRV_PA_WARN_DS_NOTFOUND				= PRV_PA_WARNLIST | 7,
	PRV_PA_WARN_DS_DATE_INVALID			= PRV_PA_WARNLIST | 8,
	PRV_PA_WARN_DS_DATE_RANGE			= PRV_PA_WARNLIST | 9,
	PRV_PA_WARN_DS_REVOKED				= PRV_PA_WARNLIST | 10,
	PRV_PA_WARN_DS_EXPIRED				= PRV_PA_WARNLIST | 11,
	PRV_PA_WARN_DS_WRONG_SIGNATURE		= PRV_PA_WARNLIST | 12,

	PRV_PA_WARN_AUTHKEYID_FORMAT		= PRV_PA_WARNLIST | 13,
	PRV_PA_WARN_AUTHKEYID_MISSING		= PRV_PA_WARNLIST | 14,

	PRV_PA_WARN_CS_NOTFOUND				= PRV_PA_WARNLIST | 15,
	PRV_PA_WARN_CS_EXPIRED				= PRV_PA_WARNLIST | 16,
	PRV_PA_WARN_CS_REVOKED				= PRV_PA_WARNLIST | 17,
	PRV_PA_WARN_CS_WRONG_SIGNATURE		= PRV_PA_WARNLIST | 18,

	PRV_PA_WARN_SOD_MISSING				= PRV_PA_WARNLIST | 19,
	PRV_PA_WARN_SOD_FORMAT 				= PRV_PA_WARNLIST | 20,
	PRV_PA_WARN_SOD_SIGNATURE_MISSING	= PRV_PA_WARNLIST | 21,
	PRV_PA_WARN_SOD_HASH_CHECK			= PRV_PA_WARNLIST | 22,
	PRV_PA_WARN_SOD_HASH_NOTFOUND		= PRV_PA_WARNLIST | 23,
	PRV_PA_WARN_SOD_WRONG_SIGNATURE		= PRV_PA_WARNLIST | 24,
	PRV_PA_WARN_SOD_SIGNEDDATA_MISSING	= PRV_PA_WARNLIST | 25,

	PRV_PA_WARN_CHAIN_DIFFERENT_ISSUER	= PRV_PA_WARNLIST | 26,
};

/** Detailed checking states. */

GX_ENUM PR_VAR_CHECKINGS {

	PRV_CHK_MISSING						= 0xD0080003,	/**< Mandatory entity is missing. */

	PRV_CHK_SELFCHK_OK					= 0xD0080010,	/**< Self checking is succeeded. */
	PRV_CHK_SELFCHK_INVALID				= 0xD0080012,	/**< Self checking is prohibited by invalid data format. */
	PRV_CHK_SELFCHK_FALIED				= 0xD0080013,	/**< Self checking is falied. */

	PRV_CHK_FORMAT_OK					= 0xD0080020,	/**< Format test is succeeded. */
	PRV_CHK_FORMAT_INVALID				= 0xD0080023,	/**< Format test is falied. */

	PRV_CHK_DATE_OK						= 0xD0080030,	/**< Date is not expired. */
	PRV_CHK_DATE_INVALID				= 0xD0080032,	/**< Date in the past is greater than current date. */
	PRV_CHK_DATE_EXPIRED				= 0xD0080033,	/**< Date is expired. */

	PRV_CHK_REVOKED						= 0xD0080043,	/**< Data validity has been revoked. */
};

/** Finger storage IDs. */

GX_ENUM PR_FINGER_POSITION {
	PR_FG_UNKNOWN		= 0,			/**< Unknown finger */
	PR_FG_RIGHT_THUMB	= 1,			/**< Right thumb */
	PR_FG_RIGHT_INDEX	= 2,			/**< Right index finger */
	PR_FG_RIGHT_MIDDLE	= 3,			/**< Right middle finger */
	PR_FG_RIGHT_RING	= 4,			/**< Right ring finger */
	PR_FG_RIGHT_LITTLE	= 5,			/**< Right little finger */
	PR_FG_LEFT_THUMB	= 6,			/**< Left thumb */
	PR_FG_LEFT_INDEX	= 7,			/**< Left index finger */
	PR_FG_LEFT_MIDDLE	= 8,			/**< Left middle finger */
	PR_FG_LEFT_RING		= 9,			/**< Left ring finger */
	PR_FG_LEFT_LITTLE	= 10,			/**< Left little finger */

	PR_FG_PLAIN_RIGHT_THUMB		= 11,	/**< Plain right thumb */
	PR_FG_PLAIN_LEFT_THUMB		= 12,	/**< Plain left thumb */
	PR_FG_PLAIN_RIGHT_4FINGERS	= 13,	/**< Plain right four fingers */
	PR_FG_PLAIN_LEFT_4FINGERS	= 14,	/**< Plain left four fingers */
	PR_FG_PLAIN_THUMBS			= 15,	/**< Plain two thumbs together */
};

/** The capturing mode of the finger capture process. */

GX_ENUM PR_FINGER_IMPRESSION_TYPE {
	PR_FG_SCAN_LIVE			= 0,		/**< Live scan plain */
	PR_FG_SCAN_ROLLED		= 1,		/**< Live scan rolled */
	PR_FG_SCAN_ACCUMULATED	= 0x1000,	/**< Accumulated live scan */
};

/** Elements of the self test. */

GX_ENUM PR_SELFTEST_ELEMENTS
{
	PRV_SELFTESTLIST		= 0x57000000,				/**< List of selftest results */
	PRV_ST_OVERALL_RESULT	= PRV_SELFTESTLIST + 1,		/**< Overall result */
	PRV_ST_DEVICE_COMM		= PRV_SELFTESTLIST + 2,		/**< Device accessible */
	PRV_ST_RFID_COMM		= PRV_SELFTESTLIST + 3,		/**< Rfid subdevice accessible */
	PRV_ST_CALIBRATED		= PRV_SELFTESTLIST + 4,		/**< Calibration state */
	PRV_ST_SENSOR_COMM		= PRV_SELFTESTLIST + 5,		/**< Sensors accessible */
	PRV_ST_SENSOR_BUS		= PRV_SELFTESTLIST + 6,		/**< Sensor pin test */
	PRV_ST_LIGHT_SWITCH		= PRV_SELFTESTLIST + 7,		/**< Light switch test */
	PRV_ST_LIGHT_BLOWOUT	= PRV_SELFTESTLIST + 8,		/**< Lights test */
	PRV_ST_NNC				= PRV_SELFTESTLIST + 9,		/**< Nnc test */
	PRV_ST_THERMOMETER		= PRV_SELFTESTLIST + 10,	/**< Thermometer test */
};

/** Result of the self test. */

GX_ENUM PR_SELFTEST_RESULT
{
	PR_ST_RESULT_OK			= 0, /**< Test succeeded */
	PR_ST_RESULT_SKIPPED	= 1, /**< Test skipped */
	PR_ST_RESULT_UNKNOWN	= 2, /**< Test result indeterminate */
	PR_ST_RESULT_FAILED		= 3, /**< Test failed */
};

/******************************************************************************/
#ifdef GX_NAMESPACES
	}
#endif
/******************************************************************************/
#endif//PRTYPES_INCL
