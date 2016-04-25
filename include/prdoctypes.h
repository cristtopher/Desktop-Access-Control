#ifndef PRDOCTYPES_INCL
#define PRDOCTYPES_INCL
/*******************************************************************************
 * PR DOCTYPES 2004-2015 (c) ARH Inc.
 * 2015.03.18 v2.1.5.25
 ******************************************************************************/
#ifdef GX_DOTNET
	#using "gxdotnet7.dll"
#endif
#include "gxtypes.h"
/******************************************************************************/
#ifdef GX_NAMESPACES
	#include "gxsd.h"
	namespace pr {
	using namespace gx;
#endif

#ifdef GX_DOTNET
	#pragma managed
#endif

/**
  \file prdoctypes.h
  <b>Passport Reader Document module constants</b>

  The  Passport Reader  is a  travel  document  reader  and  analyser  system by
  <b>ARH Inc.</b>, which bases on the GX system. The prdoctypes.h  contains  the
  descriptions  of the constants of the document analyser module.
*/

/** Field status values */

//Status Values
GX_ENUM PR_CHKERR {
	PR_CHKERR_OK				= 0,		/**< No error detected */
	PR_CHKERR_NO_CHECKSUM		= 1,		/**< There is no checksum for this field */

//warnings
	PR_CHKERR_WARNING			= 100,		/**< \b Warning \b Level \b codes */

	PR_CHKERR_DATA_INTEGRITY	= 101,		/**< Data integrity failed */
	PR_CHKERR_OCR_WARNING		= 102,		/**< Recognition module warning */

//errors
	PR_CHKERR_ERROR				= 200,		/**< \b Error \b Level \b codes */

	PR_CHKERR_ILLEGAL_CHAR		= 201,		/**< Illegal character in field */
	PR_CHKERR_ILLEGAL_CHECKSUM	= 202,		/**< Illegal checksum in field */
	PR_CHKERR_CHECKSUM			= 203		/**< Checksum mismatch error */
};

/** Document Code Values */

//Document Code Values
GX_ENUM PR_DOCUMENT {

	PR_DOC_UNKNOWN			= 0,	/**< Unknown document */

	PR_DOC_PASSPORT			= 1,	/**< ICAO standard Passport (MRP) */
	PR_DOC_IDCARD			= 2,	/**< ICAO standard 2 row Travel Document (TD-2) */
	PR_DOC_IDCARD2			= 3,	/**< ICAO standard 3 row Travel Document (TD-1) */
	PR_DOC_VISA				= 4,	/**< ICAO standard visa (MRV-A) (MRV-B) */
	PR_DOC_IDFRA			= 5,	/**< French ID card (special MRZ) */
	PR_DOC_IDCARDPRE		= 6,	/**< pre ICAO standard 3 row Travel Document */
	PR_DOC_IDSVK1B			= 7,	/**< Slovak ID card */
	PR_DOC_DLAAMVA			= 8,	/**< AAMVA standard driving license */
	PR_DOC_IDBEL3B			= 9,	/**< Belgian ID */
	PR_DOC_DLCHEB			= 10,	/**< Swiss driving license */
	PR_DOC_IDCIV			= 11,	/**< ID of Cote d'Ivoire */
	PR_DOC_FTCARD			= 12,	/**< Financial Transaction Card */
	PR_DOC_BPIATA			= 13,	/**< IATA boarding pass */
	PR_DOC_IDCARDO2			= 14,	/**< ICAO Travel Document (TD-1, front page, named) */
	PR_DOC_IDCARDO3			= 15,	/**< ICAO Travel Document (TD-1, front page, typed) */
	PR_DOC_IDLC				= 16,	/**< ISO standard driving licence */
	PR_DOC_MAIL				= 17,	/**< Mail item */
	PR_DOC_EMRTD			= 18,	/**< ICAO standard electronic document (Passport/ID) */
	PR_DOC_EID				= 19,	/**< EID */
	PR_DOC_ESIGN			= 20,	/**< ESign */
	PR_DOC_NFC				= 21,	/**< NFC */
	PR_DOC_EDL				= 22,	/**< European standard driving license */

//hungarian module
	PR_DOC_ACHUN			= 101,	/**< Hungarian address card - front */
	PR_DOC_PNOCARD_HUN		= 102,	/**< Hungarian address card - back */
	PR_DOC_DLHUNF			= 103,	/**< Hungarian driving license - front */
	PR_DOC_DLHUNB			= 104,	/**< Hungarian driving license - back */
	PR_DOC_IDHUNF			= 105,	/**< Hungarian ID card - front */
	PR_DOC_IDHUNB			= 106,	/**< Hungarian ID card - back */
	PR_DOC_IDHUNO			= 107,	/**< Hungarian paper-based old ID book inside cover */
	PR_DOC_DLHEUF			= 108,	/**< Hungarian driving license (EU) - front */
	PR_DOC_DLHEUB			= 109,	/**< Hungarian driving license (EU) - back */
	PR_DOC_PPHUN			= 110,	/**< Hungarian passport */
	PR_DOC_E111HUNB			= 111,	/**< Hungarian 5 row E-111 card - back */
	PR_DOC_HICHUNO			= 112,	/**< Hungarian paper-based old health insurance card (type 1) */
	PR_DOC_E111HUNB2		= 113,	/**< Hungarian 4 row E-111 card - back */
	PR_DOC_HICHUNO2			= 114,	/**< Hungarian paper-based old health insurance card (type 2) */
	PR_DOC_HICHUNO3			= 115,	/**< Hungarian paper-based old health insurance card (type 3) */
	PR_DOC_PPHUN1			= 116,	/**< New hungarian passport */
	PR_DOC_PNOCARD_HUN1		= 117,	/**< New hungarian address card - back */
	PR_DOC_PPHUN2			= 118,	/**< New hungarian passport, type 2 */
	PR_DOC_IDHUN2F			= 119,	/**< Hungarian ID card - front */
	PR_DOC_IDHUN2B			= 120,	/**< Hungarian ID card - back */
	PR_DOC_PNOCARD_HUN2		= 121,	/**< Hungarian address card - back */
	PR_DOC_DLHUN2F			= 122,	/**< Hungarian driving license - front */
	PR_DOC_DLHUN2B			= 123,	/**< Hungarian driving license - back */

//spanish module
	PR_DOC_IDESPF			= 201,	/**< Spanish ID card - front */
	PR_DOC_IDESPB			= 202,	/**< Spanish ID card - back */
	PR_DOC_IDESPBO			= 203,	/**< Spanish ID card - back (old, 2 MRZ lines) */
	PR_DOC_IDESPFORF1		= 204,	/**< Spanish ID card for foreigners - front */
	PR_DOC_IDESPFORB1		= 205,	/**< Spanish ID card for foreigners - back */
	PR_DOC_IDESPFORF2		= 206,	/**< Spanish ID card for foreigners - front */
	PR_DOC_IDESPFORB2		= 207,	/**< Spanish ID card for foreigners - back */
	PR_DOC_IDESPF2			= 208,	/**< New Spanish ID card - front */
	PR_DOC_IDESPB2			= 209,	/**< New Spanish ID card - back */
	PR_DOC_DLESPF			= 210,	/**< Spanish driving license - front */

//hungarian cheque module
	PR_DOC_POSTAL_CHEQUE	= 301,	/**< Hungarian postal cheque */

//european health insurance cards
	PR_DOC_E111_5RF			= 401,	/**< E-111 card 5 row - front */
	PR_DOC_E111_4RF			= 402,	/**< E-111 card 4 row - front */

//passports
	PR_DOC_PPIND			= 501,	/**< Indonesian passport */
	PR_DOC_PPSGP_P			= 502,	/**< Singaporean passport type 1 */
	PR_DOC_PPSGP_PA			= 503,	/**< Singaporean passport type 2 */
	PR_DOC_PPSGP_BIO		= 504,	/**< Singaporean passport type 3 */
	PR_DOC_IDSGPF1			= 505,	/**< Singaporean ID card - front */

//albanian module
	PR_DOC_ALB_DLF			= 601,	/**< Albanian driving licence - front */

//mexican credential
	PR_DOC_MEX_CREDF		= 701,	/**< Mexican credential - front */
	PR_DOC_MEX_CREDB		= 702,	/**< Mexican credential - back */
	PR_DOC_MEX_CRED1F		= 703,	/**< Mexican credential, type 1 - front */
	PR_DOC_MEX_CRED2F		= 704,	/**< Mexican credential, type 2 - front */
	PR_DOC_MEX_CRED0F		= 705,	/**< Mexican credential, old - front */

//Hong Kong and Chinese cards
	PR_DOC_IDHKG			= 801,	/**< Hong Kong identity card */
	PR_DOC_IDCHN			= 802,	/**< Chinese identity card */
	PR_DOC_HKMP				= 803,	/**< Hong Kong Macau Permit */
	PR_DOC_HKIDC			= 804,	/**< Hong Kong Immigration Department Card */
	PR_DOC_IDHKGO			= 805,	/**< Old Hong Kong identity card */
	PR_DOC_CHNKE			= 806,	/**< Two Way Permit in transit to and from Taiwan */
	PR_DOC_CHNOWP			= 807,	/**< One Way Permit */
	PR_DOC_CHNHVP			= 808,	/**< Home visit permit for Hong Kong Macau */
	PR_DOC_MOADC			= 809,	/**< Macau Arrival/Departure card */
	PR_DOC_CHNPP			= 810,	/**< Chinese Passport*/
	PR_DOC_MCSIDC			= 811,	/**< Macau smart id card */
	PR_DOC_CHNEEP			= 812,	/**< Exit and entry permit*/
	PR_DOC_CHNPP1			= 813,	/**< Chinese Passport, 2007*/
	PR_DOC_HKGMTP1			= 814,	/**< Mainland Travel Permit for Taiwan residences type 1*/
	PR_DOC_HKGMTP2			= 815,	/**< Mainland Travel Permit for Taiwan residences type 2*/
	PR_DOC_CHNPP0			= 816, 	/**< Chinese Passport, 2008*/
	PR_DOC_CHNPS			= 817,	/**< People's Republic of Chinese Passport, 2007*/
	PR_DOC_CHNPT			= 818,	/**< People's Republic of Chinese, Travel Document, 2005*/
	PR_DOC_MCSIDCF			= 819,	/**< Macau smart id card - front*/
	PR_DOC_CHNHRP			= 820,	/**< Home Return Permit */
	PR_DOC_IDMACF821		= 821,	/**< Macau ID card - front */
	PR_DOC_IDMACB822		= 822,	/**< Macau ID card - back */

//South African module
	PR_DOC_IDRSA1			= 901,	/**< South African paper-based ID book, type 1 */
	PR_DOC_IDRSA2			= 902,	/**< South African paper-based ID book, type 2 */

//Dutch driving licenses
	PR_DOC_DLNLDF			= 1001,	/**< Dutch driving license - front */
	PR_DOC_DLNLDB			= 1002,	/**< Dutch driving license - back */
	PR_DOC_DLNLDO			= 1003,	/**< Dutch driving license - old */
	PR_DOC_IDNLDF			= 1004,	/**< Dutch identity card - front */
	PR_DOC_IDNLDB			= 1005,	/**< Dutch identity card - back */
	PR_DOC_NDLNLDF			= 1006,	/**< New dutch driving license - front */
	PR_DOC_NDLNLDB			= 1007,	/**< New dutch driving license - back */
	PR_DOC_DLNLDO2			= 1008,	/**< Dutch driving license - old, type2 */

//Australian driving licenses
	PR_DOC_DLAUSWAF			= 1101,	/**< Western australian driving license - front */
	PR_DOC_DLAUSNSW1 		= 1102,	/**< New South Wales (Australia) driving license - type 1*/
	PR_DOC_DLAUSNSW2 		= 1103,	/**< New South Wales (Australia) driving license - type 2*/
	PR_DOC_DLAUSVF			= 1104,	/**< Victoria (Australia) driving license - front */
	PR_DOC_PAAUSWAF			= 1105,	/**< Western australian proof of age card - front */
	PR_DOC_DLAUSVPF			= 1106,	/**< Victoria (Australia) probationary driving license - front */
	PR_DOC_DLAUSV1F			= 1107,	/**< Victoria (Australia) old style driving license - front */
	PR_DOC_DLAUSV1PF		= 1108,	/**< Victoria (Australia) old style probationary driving license - front */
	PR_DOC_PCAUSNSW			= 1109,	/**< New South Wales (Australia) photo card */
	PR_DOC_DLAUSNT1			= 1110,	/**< Northern Territories (Australia) driving licence, type 1 */
	PR_DOC_DLAUSNT2			= 1111,	/**< Northern Territories (Australia) driving licence, type 2 */
	PR_DOC_DLAUSNT1P		= 1112,	/**< Northern Territories (Australia) provisional driving licence */
	PR_DOC_DLAUSSA			= 1113,	/**< South Australia, driving license*/
	PR_DOC_PAAUSSA			= 1114,	/**< South Australia, proof of age card*/
	PR_DOC_PAAUSQL			= 1115,	/**< Queensland (Australia) proof of age card */
	PR_DOC_DLAUSQL1			= 1116,	/**< Queensland (Australia) driving licence, type 1 */
	PR_DOC_DLAUSQL2			= 1117,	/**< Queensland (Australia) driving licence, type 2 */
	PR_DOC_DLAUSQL3			= 1118,	/**< Queensland (Australia) driving licence, type 3 */
	PR_DOC_DLAUSWA1F		= 1119,	/**< Western australian new driving license - front */
	PR_DOC_DLAUSWA1PF		= 1120,	/**< Western australian new provisional driving license - front */
	PR_DOC_PAAUSVF			= 1121,	/**< Victoria (Australia) proof of age card - front */
	PR_DOC_KPAUS			= 1122,	/**< Australian keypass card - front */
	PR_DOC_DLAUSACTF		= 1123,	/**< Australian Capital Territory driving license - front */
	PR_DOC_PAAUSACTF		= 1124,	/**< Australian Capital Territory proof of age card - front */
	PR_DOC_DLAUSQL4			= 1125,	/**< Queensland (Australia) new driving licence */
	PR_DOC_PAAUSQL2			= 1126,	/**< Queensland (Australia) new proof of age card */
	PR_DOC_PAAUSSA1			= 1161,	/**< South Australia, new proof of age card*/
	PR_DOC_DLAUSSA1			= 1171,	/**< South Australia, new driving license*/
	PR_DOC_DLAUSWA2F		= 1173,	/**< Western australian new driving license - front */
	PR_DOC_DLAUSWA2PF		= 1175,	/**< Western australian new provisional driving license - front */

//Poland
	PR_DOC_POLIDF1			= 1201,	/**< Poland ID card - front */
	PR_DOC_POLIDB1			= 1202,	/**< Poland ID card - back */
	PR_DOC_POLDLF1			= 1203,	/**< Poland driving license */
	PR_DOC_POLDLFO			= 1204,	/**< Poland driving license old */
	PR_DOC_POLSTCD			= 1205,	/**< Poland student card */

//Slovak documents
	PR_DOC_SLOIDOF1			= 1301,	/**< Slovak old ID card - front */
	PR_DOC_SLOIDOB1			= 1302,	/**< Slovak old ID card - back */
	PR_DOC_SLOIDF1			= 1303,	/**< Slovak ID card - front */
	PR_DOC_SLOIDFO			= 1304,	/**< Slovak ID card - back */

//Croatian documents
	PR_DOC_HRVIDF1			= 1401,	/**< Croatian old ID card - front */
	PR_DOC_HRVIDB1			= 1402,	/**< Croatian old ID card - back */
	PR_DOC_HRVIDF2			= 1403,	/**< Croatian ID card - front */
	PR_DOC_HRVIDB2			= 1404,	/**< Croatian ID card - back */

//Saudi Arabia
	PR_DOC_DLSAU			= 1501,	/**< Kingdom of Saudi Arabia Driving Licence*/
	PR_DOC_RPSAU			= 1502,	/**< Kingdom of Saudi Arabia Residence Permit*/
	PR_DOC_LCUAE			= 1503,	/**< United Arab Emirates Labour card - front */
	PR_DOC_RPUAE			= 1504,	/**< United Arab Emirates Residence Permit */
	PR_DOC_RPSAU2		    = 1505,	/**< Kingdom of Saudi Arabia Residence Permit, type 2*/

//United Kingdom
	PR_DOC_DLGBR1F			= 1601,	/**< British driving licence, type 1 - front */
	PR_DOC_DLGBR2F			= 1602,	/**< British driving licence, type 2 - front */
	PR_DOC_DLPGBR1F			= 1603,	/**< British provisional driving licence - front */

//Other documents
	PR_DOC_CZEPPD			= 2001,	/**< Czech Passport Diplomatic*/
	PR_DOC_GERPPD			= 2002,	/**< German Passport Diplomatic*/
	PR_DOC_UKPP				= 2003,	/**< United Kingdom Passport*/
	PR_DOC_NLDPP			= 2004,	/**< Dutch Passport*/
	PR_DOC_NLDPPD			= 2005,	/**< Dutch Passport Diplomatic*/
	PR_DOC_PORPP			= 2006,	/**< Portugal Passport*/
	PR_DOC_SWEPPE			= 2007,	/**< Sweden Passport Emergency*/
	PR_DOC_SWEPP			= 2008,	/**< Sweden Passport*/
	PR_DOC_UKTD				= 2009,	/**< United Kingdom Travel Document*/
	PR_DOC_FINPPS			= 2010,	/**< Finland Passport Service*/
	PR_DOC_FINPP			= 2011,	/**< Finland Passport*/
	PR_DOC_FINPPD			= 2012,	/**< Finland Passport Diplomatic*/
	PR_DOC_FRAPP			= 2013,	/**< France Passport*/
	PR_DOC_FRAPPO			= 2014,	/**< France Passport Service*/
	PR_DOC_RUSPPS			= 2015,	/**< Russian Federation Passport Service*/
	PR_DOC_RUSPPD			= 2016,	/**< Russian Federation Passport Diplomatic*/
	PR_DOC_TWNPP			= 2017,	/**< Taiwan Passport*/
	PR_DOC_PAKPP			= 2018,	/**< Pakistan Passport*/
	PR_DOC_AUSPP			= 2019,	/**< Australian Passport*/
	PR_DOC_CZEPP0			= 2020,	/**< Czech Passport (old)*/
	PR_DOC_DNKPP			= 2021,	/**< Denmark Passport*/
	PR_DOC_ITAPP			= 2022,	/**< Italian Passport*/
	PR_DOC_JPNPP1			= 2023,	/**< Japan Passport*/
	PR_DOC_KORPP			= 2024,	/**< Republic of Korea Passport*/
	PR_DOC_NORPP1			= 2026,	/**< Norway Passport*/
	PR_DOC_POLPPS			= 2027,	/**< Poland Passport Service*/
	PR_DOC_USAPP			= 2028,	/**< United States of America Passport*/
	PR_DOC_AUTPP			= 2029,	/**< Austria Passport*/
	PR_DOC_BELPP			= 2030,	/**< Belgium Passport*/
	PR_DOC_SVKPPD			= 2031,	/**< Slovakia Passport Diplomatic*/
	PR_DOC_GERPP			= 2032,	/**< German Passport*/
	PR_DOC_BGRPP			= 2033,	/**< Bulgaria Passport (old)*/
	PR_DOC_ESTPP			= 2034,	/**< Estonia Passport (old)*/
	PR_DOC_SVNPP			= 2035,	/**< Slovenia Passport*/
	PR_DOC_ESPPP			= 2036,	/**< Spanish Passport*/
	PR_DOC_IRLPP			= 2037,	/**< Ireland Passport*/
	PR_DOC_GRCPP			= 2038,	/**< Greece Passport*/
	PR_DOC_LTUPP			= 2039,	/**< Lithuania Passport*/
	PR_DOC_LUXPP			= 2040,	/**< Luxembourg Passport*/
	PR_DOC_LVAPP			= 2041,	/**< Latvia Passport*/
	PR_DOC_MLTPP1			= 2042,	/**< Malta Passport*/
	PR_DOC_ROUPP1			= 2043,	/**< Romania Passport*/
	PR_DOC_POLPP1			= 2044,	/**< Poland Passport*/
	PR_DOC_RUSPP			= 2045,	/**< Russian Passport*/
	PR_DOC_CZEPPA			= 2047,	/**< Czech Alien's Passport*/
	PR_DOC_ARHPP			= 2049,	/**< ARH sample passport*/
	PR_DOC_EGYPP			= 2050,	/**< Egyptian Passport*/
	PR_DOC_MYSPP			= 2051,	/**< Malaysia Passport*/
	PR_DOC_OMNPP			= 2052,	/**< Sultanate of Oman Passport*/
	PR_DOC_QATPP1			= 2053,	/**< Qatar Passport*/
	PR_DOC_SAUPPP			= 2054,	/**< Saudi Arabia Passport Special*/
	PR_DOC_ANDPP			= 2055,	/**< Andorra Passport*/
	PR_DOC_ALBPP			= 2056,	/**< Albania Passport*/
	PR_DOC_BIHPPD			= 2057,	/**< Bosnia and Herzegovina Passport Diplomatic*/
	PR_DOC_BLRPP			= 2058,	/**< Belarus Passport*/
	PR_DOC_CHEPP1			= 2059,	/**< Switzerland Passport*/
	PR_DOC_CYPPP1			= 2060,	/**< Cyprus Passport*/
	PR_DOC_BIHPPS			= 2061,	/**< Bosnia and Herzegovina Passport Service*/
	PR_DOC_DNKPPFI			= 2062,	/**< Denmark/Faroe Islands Passport*/
	PR_DOC_HRVPPS			= 2063,	/**< Republic of Croatia Passport Service*/
	PR_DOC_DNKPPT			= 2064,	/**< Denmark Travel Document*/
	PR_DOC_ISLPP1			= 2065,	/**< Iceland Passport*/
	PR_DOC_LVAPPS			= 2066,	/**< Latvia Passport Service*/
	PR_DOC_MDVPP			= 2067,	/**< Republic of Maldives Passport*/
	PR_DOC_MKDPP			= 2068,	/**< Republic of Macedonia Passport*/
	PR_DOC_MLAPP			= 2069,	/**< Republic of Moldova Passport*/
	PR_DOC_MKDPPS			= 2070,	/**< Republic of Macedonia Passport Service*/
	PR_DOC_POLPPD			= 2071,	/**< Republic of Poland Passport Diplomatic*/
	PR_DOC_MNEPP			= 2072,	/**< Montenegro Passport*/
	PR_DOC_MNEPPD			= 2073,	/**< Montenegro Passport Diplomatic*/
	PR_DOC_SMRPP1			= 2074,	/**< Republic of San Marino Passport*/
	PR_DOC_SRBPPD			= 2075,	/**< Republic of Serbia Passport Diplomatic*/
	PR_DOC_SRBPP			= 2076,	/**< Republic of Serbia Passport*/
	PR_DOC_SVKPPS			= 2077,	/**< Slovakia Passport Service*/
	PR_DOC_THAPP			= 2078,	/**< Thailand Passport*/
	PR_DOC_TWNPP0			= 2079,	/**< Taiwan Passport*/
	PR_DOC_ZAFPP			= 2080,	/**< Republic of South Africa Passport, 2009*/
	PR_DOC_ARGPP			= 2081,	/**< Argentina Passport*/
	PR_DOC_BRAPP1			= 2082,	/**< Brazil Passport*/
	PR_DOC_VNMPP			= 2083,	/**< Vietnam Passport*/
	PR_DOC_CANPP			= 2084,	/**< Canada Passport*/
	PR_DOC_UKRPP			= 2085,	/**< Ukraine Passport*/
	PR_DOC_GEOPP1			= 2086,	/**< Georgia Passport*/
	PR_DOC_IDNPP			= 2087,	/**< Indonesia Passport*/
	PR_DOC_PRYPP			= 2088,	/**< Paraguay Passport*/
	PR_DOC_ISRPP			= 2089,	/**< State of Israel Passport*/
	PR_DOC_IRQPPS			= 2090,	/**< Iraq Passport Service*/
	PR_DOC_PHLPP			= 2091,	/**< Republic of the Philippines Passport Diplomatic/Service*/
	PR_DOC_NZLPP			= 2092,	/**< New Zealand Passport*/
	PR_DOC_NGAPPD			= 2093,	/**< Federal Republic of Nigeria Passport Diplomatic*/
	PR_DOC_IRNPPD			= 2094,	/**< Islamic Republic of Iran Passport Diplomatic*/
	PR_DOC_KENPP			= 2095,	/**< Republic of Kenya Passport*/
	PR_DOC_KORPPS			= 2096,	/**< Republic of Korea Passport Offical*/
	PR_DOC_MEXPP			= 2097,	/**< Mexico Passport*/
	PR_DOC_LBNPP			= 2098,	/**< Republic of Lebanon Passport*/
	PR_DOC_BGRPP1			= 2099,	/**< Republic of Bulgaria Passport*/
	PR_DOC_CZEPP1			= 2100,	/**< Czech Republic Passport*/
	PR_DOC_ESTPP1			= 2101,	/**< Estonia Passport*/
	PR_DOC_GERVS			= 2102,	/**< German Visa*/
	PR_DOC_TUNPPDS			= 2103,	/**< Tunisia Passport Diplomatic or Service*/
	PR_DOC_TUNPP			= 2104,	/**< Tunisia Passport*/
	PR_DOC_MARPP			= 2106,	/**< Kingdom of Morocco Passport*/
	PR_DOC_CHNPP2			= 2107,	/**< People's Republic of China Passport*/
	PR_DOC_CHNPP3			= 2108,	/**< Macao Special Adminstrative Region People's Republic of China Passport*/
	PR_DOC_TURPP			= 2109,	/**< Republic of Turkey Passport*/
	PR_DOC_PHLPP1			= 2110,	/**< Republic of the Philippines Passport*/
	PR_DOC_ZAFPD			= 2111,	/**< Republic of South Africa Passport, Diplomatic 2009*/
	PR_DOC_ZAFPP1			= 2112,	/**< Republic of South Africa Passport 1996*/
	PR_DOC_ZAFPO			= 2114,	/**< Republic of South Africa Passport, Offical 1996*/
	PR_DOC_ZAFPE			= 2115,	/**< Republic of South Africa Passport, Offical 2009*/
	PR_DOC_ZAFPT1			= 2116,	/**< Republic of South Africa Travel Document, 2009*/
	PR_DOC_ZAFPC			= 2119,	/**< Republic of South Africa Child Passport,*/
	PR_DOC_ZAFPT			= 2120,	/**< Republic of South Africa Travel Document, 1996*/
	PR_DOC_BELVS			= 2122,	/**< Belgium Visa, 2010*/
	PR_DOC_NLDVS			= 2125,	/**< Dutch Visa, 2006*/
	PR_DOC_INDPP			= 2126,	/**< Republic of India Passport, 2006*/
	PR_DOC_ALBPD			= 2127,	/**< Republic of Albania Diplomatic Passport*/
	PR_DOC_ALBPS			= 2128,	/**< Republic of Albania Service Passport*/
	PR_DOC_BFAPD			= 2129,	/**< Burkina Faso Diplomatic Passport*/
	PR_DOC_BFAPP			= 2130,	/**< Burkina Faso Passport, 1998*/
	PR_DOC_BFAPP1			= 2131,	/**< Burkina Faso Passport, 2008*/
	PR_DOC_BFAPS			= 2132,	/**< Burkina Faso Service Passport*/
	PR_DOC_CIVPP			= 2133,	/**< Republic of Cote d'Ivoie Passport*/
	PR_DOC_CODPD			= 2134,	/**< Democratic Republic of Congo Diplomatic Passport*/
	PR_DOC_CODPP			= 2135,	/**< Democratic Republic of Congo Passport*/
	PR_DOC_CODPS			= 2136,	/**< Democratic Republic of Congo Service Passport*/
	PR_DOC_CODPP1			= 2137,	/**< Republic of Congo Ordinary Passport, 2008*/
	PR_DOC_GMBPP			= 2138,	/**< Republic of the Gambia Passport*/
	PR_DOC_LBRPD			= 2139,	/**< Republic of Liberia Diplomatic Passport*/
	PR_DOC_LBRPP			= 2140,	/**< Republic of Liberia Passport*/
	PR_DOC_LBRPS			= 2141,	/**< Republic of Liberia Service Passport*/
	PR_DOC_NLDPP1			= 2142,	/**< Kingdom of the Netherlands Passport, 2001*/
	PR_DOC_PANPP			= 2143,	/**< Republic of Panama Passport*/
	PR_DOC_PEPP				= 2144,	/**< Republic of Peru Passport, 2003*/
	PR_DOC_PEPP1			= 2145,	/**< Republic of Peru Passport, 2008*/
	PR_DOC_SMRPP2			= 2148,	/**< Republic of San Marino Passport 2009*/
	PR_DOC_HRVPD2			= 2149,	/**< Republic of Croatia Diplomatic Passport*/
	PR_DOC_HRVPP1			= 2150,	/**< Republic of Croatia Passport*/
	PR_DOC_INDPP1			= 2151,	/**< Republic of India Passport, 2009*/
	PR_DOC_LBRPO			= 2152,	/**< Republic of Liberia Official Passport*/
	PR_DOC_IRNPP1			= 2153,	/**< Islamic Republic of Iran Passport, 2004*/
	PR_DOC_FRAVS			= 2154,	/**< France Visa*/
	PR_DOC_GHAPP			= 2155,	/**< Republic of Ghana Passport*/
	PR_DOC_HKGPP1			= 2156,	/**< Hong Kong Administrative Region, Peoples Republic of China Passport*/
	PR_DOC_PAKPP1			= 2158,	/**< Islamic Republic of Pakistan Passport, 2005*/
	PR_DOC_RUSPP1			= 2159,	/**< Russian Passport, 2009*/
	PR_DOC_LKAPP			= 2160,	/**< Sri Lankan Passport, 2009*/
	PR_DOC_LKAPP1			= 2161,	/**< Sri Lankan Passport, 2003*/
	PR_DOC_CHNPP4			= 2162,	/**< Macao Special Adminstrative Region of the People's Republic of China Passport*/
	PR_DOC_THAPP1			= 2164,	/**< Thailand Passport, 2005*/
	PR_DOC_IRNPS			= 2165,	/**< Islamic Republic of Iran Service Passport, 2007*/
	PR_DOC_IRNPP			= 2166,	/**< Islamic Republic of Iran Passport, 2007*/
	PR_DOC_NLDPP2			= 2167,	/**< Kingdom of the Netherlands Passport, 2009*/
	PR_DOC_AUTVS			= 2168,	/**< Austria Visa, 2004*/
	PR_DOC_CZEVS			= 2169,	/**< Czech Visa, 2007*/
	PR_DOC_ESPVS			= 2170,	/**< Spanish Visa, 2007*/
	PR_DOC_FINVS			= 2171,	/**< Finland Visa, 2006*/
	PR_DOC_FRAVS1			= 2172,	/**< France Visa, 2005*/
	PR_DOC_GBRVS			= 2173,	/**< United Kingdom Visa,2005*/
	PR_DOC_GRCVS			= 2174,	/**< Greece Visa, 2007*/
	PR_DOC_HUNVS			= 2175,	/**< Hungarian Visa, 2004*/
	PR_DOC_ITAVS			= 2176,	/**< Italian Visa, 2005*/
	PR_DOC_LTUVS			= 2177,	/**< Lithuania Visa, 2009*/
	PR_DOC_SWEVS			= 2178,	/**< Sweden Visa, 2006*/
	PR_DOC_MLTVS			= 2179,	/**< Malta Visa, 2011*/
	PR_DOC_NORVS			= 2180,	/**< Norway Visa, 2005*/
	PR_DOC_POLVS			= 2181,	/**< Poland Visa, 2007*/
	PR_DOC_SVKVS			= 2182,	/**< Slovakia Visa,2005*/
	PR_DOC_IRNPD			= 2184,	/**< Islamic Republic of Iran Passport, 2007b*/
	PR_DOC_LIEPD1			= 2445, /**< Liechtenstein Diplomatic Passport, 2000A*/
	PR_DOC_LIEPP			= 2447, /**< Liechtenstein Passport, 2006A*/
	PR_DOC_PHLPP2			= 2567, /**< Republic Of The Philippines Passport, 2007A*/
	PR_DOC_SVNPP1			= 2625, /**< Republica Slovenija Passport, 2000A*/
	PR_DOC_SYRPP			= 2699, /**< Syrian Arab Republic Passport, 2008*/
	PR_DOC_SURPP			= 2700, /**< Surinam Republic Passport, 2008*/
	PR_DOC_LIEPP1			= 2701, /**< Liechtenstein Passport Passport, 2000*/
	PR_DOC_IDROUF2706		= 2706, /**< Romania, ID card, 2001 - front*/
	PR_DOC_IDCZEF2707		= 2707, /**< Czech Republic, ID card, 2005 - front*/

	PR_DOC_IDDEUF2710		= 2710,	/**< German ID card - front*/
	PR_DOC_IDDEUF2714		= 2714,	/**< German ID card - front*/
	PR_DOC_DLAUTF			= 2716,	/**< Austrian driving licence - front*/
	PR_DOC_IDFRAF2718		= 2718,	/**< French ID card, 1994 - front*/
	PR_DOC_IDFRAB2719		= 2719,	/**< French ID card, 1994 - back*/
	PR_DOC_IDCZEF2759		= 2759, /**< Czech Republic, ID card, 2000 - front*/
	PR_DOC_DLTHAF2805		= 2805,	/**< Thailand, life time driving licence for private car - front*/
	PR_DOC_DLTHAF2806		= 2806,	/**< Thailand, driving licence for private motorcycle - front*/
	PR_DOC_DLTHAF2807		= 2807,	/**< Thailand, driving licence for private car - front*/
	PR_DOC_IDCZEF2874		= 2874, /**< Czech Republic, ID card, 2012 - front*/
	PR_DOC_IDDEUF2879		= 2879,	/**< German ID card, 2010 - front */

	PR_DOC_IDNLDF3058		= 3058,	/**< Netherlands, ID card, 2011 - front*/
	PR_DOC_RPNLDF3059		= 3059,	/**< Netherlands, residence permit, 2011 - front*/
	PR_DOC_IDROUF3088		= 3088, /**< Romania, ID card, 2009 - front*/
	PR_DOC_IDNLDB3180		= 3180,	/**< Netherlands, ID card, 2011 - back*/
	PR_DOC_RPNLDF3182		= 3182,	/**< Netherlands, residence permit, 2011 - back*/
	PR_DOC_DLUSAFLF3200		= 3200,	/**< USA, Florida, driving licence - front*/
	PR_DOC_DLUSACAF3201		= 3201,	/**< USA, California, driving licence - front*/
	PR_DOC_DLUSAORF3202		= 3202,	/**< USA, Oregon, driving licence - front*/
	PR_DOC_DLUSAFLF3203		= 3203,	/**< USA, Florida, driving licence - front*/
	PR_DOC_RPDEUF3204		= 3204,	/**< German residence permit, 2011 - front */
	PR_DOC_PPOTHA3206		= 3206,	/**< Thailand, Passport */
	PR_DOC_RPFRAF3207		= 3207,	/**< French residence permit - front */
	PR_DOC_RPFRAB3208		= 3208,	/**< French residence permit - back */

	PR_DOC_DLSAUF3241		= 3241,	/**< Saudi Arabian Driving Licence - front */
	PR_DOC_IDIDNF3254		= 3254,	/**< Indonesian ID card - front (type 1) */
	PR_DOC_IDIDNF3255		= 3255,	/**< Indonesian ID card - front (type 1) */
	PR_DOC_IDDEUB3266		= 3266,	/**< German ID card - back*/
	PR_DOC_PPNLD3289		= 3289,	/**< Netherlands, passport, 2011*/
	PR_DOC_IDMYSF3300		= 3300,	/**< Malaysia, ID card - front (type 1) */
	PR_DOC_DLITAF3358		= 3358,	/**< Italy, driving licence - front */
	PR_DOC_IDSGPF3362		= 3362,	/**< Singaporean ID card - front */
	PR_DOC_DLSGPF3363		= 3363,	/**< Singaporean driving licence - front */
	PR_DOC_IDSGPF3364		= 3364,	/**< Singaporean ID card - front */
	PR_DOC_IDMYSF3367		= 3367,	/**< Malaysia, ID card - front (type 2) */
	PR_DOC_IDTHAF3369		= 3369,	/**< Thailand, ID card, 2005 - front*/
	PR_DOC_IDSAUB3371		= 3371,	/**< Saudi Arabian ID card - back */
	PR_DOC_IDSAUF3377		= 3377,	/**< Saudi Arabian ID card - front */
	PR_DOC_IDDEUF3457		= 3457,	/**< German ID card - front*/
	PR_DOC_DLIDNF3462		= 3462,	/**< Indonesian driving licence - front */
	PR_DOC_DLITAB3463		= 3463,	/**< Italy, driving licence - back */
	PR_DOC_DLITAF3499		= 3499,	/**< Italy, driving licence, 2013 - front */
	PR_DOC_DLITAB3500		= 3500,	/**< Italy, driving licence, 2013 - back */
	PR_DOC_DLCZEF3501		= 3501, /**< Czech Republic, driving licence, 2004 - front*/
	PR_DOC_IDSGPF3536		= 3536,	/**< Singaporean ID card - front */
	PR_DOC_IDSGPF3537		= 3537,	/**< Singaporean ID card - front */
	PR_DOC_IDSGPF3538		= 3538,	/**< Singaporean ID card - front */
	PR_DOC_IDSGPF3539		= 3539,	/**< Singaporean ID card - front */
	PR_DOC_SPSGPF3540		= 3540,	/**< Singaporean S pass card - front */
	PR_DOC_EPSGPF3541		= 3541,	/**< Singaporean employment pass card - front */
	PR_DOC_WPSGPF3542		= 3542,	/**< Singaporean work permit card - front */
	PR_DOC_IDSGPF3543		= 3543,	/**< Singapore Armed Forces Identity Card - front */
};


/** Field Code Values */

//Field Code Values
GX_ENUM PR_DOCFIELD {

	PR_DF_UNKNOWN				= 0,	/**< Unknown document field */

	PR_DF_BLOCK					= 1000,	/**< size of a data source block */
	PR_DF_PARTS					=  100,	/**< area of the multidata field ids */

	PR_DFE_COMPOSITE1			= 1,
	PR_DFE_COMPOSITE2			= 2,
	PR_DFE_COMPOSITE3			= 3,
	PR_DFE_COMPOSITE4			= 4,
	PR_DFE_COMPOSITE5			= 5,

	PR_DFE_NAME					= 101,	/**< Full name */
	PR_DFE_GIVENNAME			= 102,	/**< Given name */
	PR_DFE_SURNAME				= 103,	/**< Surname */
	PR_DFE_SURNAME2				= 104,	/**< Second surname */
	PR_DFE_MIDDLENAME			= 105,	/**< Middle name */
	PR_DFE_MAIDEN_NAME			= 107,	/**< Maiden name */
	PR_DFE_MAIDEN_GIVENNAME		= 108,	/**< Maiden given name */
	PR_DFE_MAIDEN_SURNAME		= 109,	/**< Maiden surname */

	PR_DFE_BIRTH_DATE			= 113,	/**< Date of birth */
	PR_DFE_BIRTH_PLACE			= 114,	/**< Place of birth */
	PR_DFE_BIRTH_COUNTRY		= 115,	/**< Country of birth */
	PR_DFE_MOTHER_NAME			= 116,	/**< Mother's name */
	PR_DFE_MOTHER_GIVENNAME		= 117,	/**< Mother's given name */
	PR_DFE_MOTHER_SURNAME		= 118,	/**< Mother's surname */

	PR_DFE_NATIONALITY			= 119,	/**< Nationality */
	PR_DFE_SEX					= 120,	/**< Sex */
	PR_DFE_BIRTH_PROVINCE		= 121,	/**< Province of birth */
	PR_DFE_PARENTS_NAME			= 122,	/**< Parent's name */
	PR_DFE_FATHER_NAME			= 123,	/**< Father's name */
	PR_DFE_MARITAL_STATUS		= 124,	/**< Marital status */
	PR_DFE_FATHER_GIVENNAME		= 125,	/**< Father's given name */
	PR_DFE_FATHER_SURNAME		= 126,	/**< Father's surname */

	PR_DFE_DOCUMENT_NUMBER		= 130,	/**< Document number */
	PR_DFE_TYPE					= 131,	/**< Document type (Px-passport, Ix-id, Vx-visa) */
	PR_DFE_ISSUE_COUNTRY		= 132,	/**< Issue country */
	PR_DFE_ISSUE_PLACE			= 133,	/**< Issue place */
	PR_DFE_ISSUE_PROVINCE		= 134,	/**< Province of issue */
	PR_DFE_ISSUE_DATE			= 135,	/**< Date of issue */
	PR_DFE_EXPIRY_DATE			= 136,	/**< Date of expiration */
	PR_DFE_ISSUE_ORG			= 137,	/**< Issue organization */
	PR_DFE_PROVISIONAL_END_DATE	= 138,	/**< Provisional end date */

	PR_DFE_PERSONAL_NUMBER		= 140,	/**< Personal number */
	PR_DFE_HEALTH_INS_NUMBER	= 141,	/**< Health insurence number */
	PR_DFE_REGISTRATION_NUMBER	= 142,	/**< Registration number */
	PR_DFE_DUF_NUMBER			= 143,	/**< DUF */
	PR_DFE_CAN					= 144,	/**< Card Access Number */

	PR_DFE_DOCTYPE				= 149,	/**< Type of the document */

	PR_DFE_PERSONAL_DATA1		= 160,	/**< Content of this data is up to the issuing country / organization */
	PR_DFE_PERSONAL_DATA2		= 161,	/**< Content of this data is up to the issuing country / organization */

	PR_DFE_ADDRESS				= 200,	/**< Address */
	PR_DFE_ADDR_ZIP				= 201,	/**< Zip code */
	PR_DFE_ADDR_CITY			= 202,	/**< City */
	PR_DFE_ADDR_STREET			= 203,	/**< Street */
	PR_DFE_ADDR_HOUSE			= 204,	/**< House address */
	PR_DFE_ADDR_FLAT			= 205,	/**< Flat number */
	PR_DFE_ADDR_DATE			= 206,	/**< Date of booking */
	PR_DFE_ADDR_STATE			= 209,	/**< State */
	PR_DFE_ADDR_PROVINCE		= 210,	/**< Province */
	PR_DFE_ADDR_MUNICIPALITY	= 212,	/**< Municipality */

	PR_DFE_TEMPADDRESS			= 220,	/**< Temporary address */
	PR_DFE_TEMPADDR_ZIP			= 221,	/**< Temporary address */
	PR_DFE_TEMPADDR_CITY		= 222,	/**< Temporary address */
	PR_DFE_TEMPADDR_STREET		= 223,	/**< Temporary address */
	PR_DFE_TEMPADDR_HOUSE		= 224,	/**< Temporary address */
	PR_DFE_TEMPADDR_FLAT		= 225,	/**< Temporary address */
	PR_DFE_TEMPADDR_DATE		= 226,	/**< Temporary address */
	PR_DFE_TEMPADDR_DATEEND		= 227,	/**< Temporary address */
	PR_DFE_TEMPADDR_STATE		= 229,	/**< Temporary address */
	PR_DFE_TEMPADDR_PROVINCE	= 230,	/**< Temporary address */
	PR_DFE_TEMPADDR_MUNICIPALITY= 232,	/**< Temporary address */

	PR_DFE_VALID_AREA			= 240,	/**< Valid area (of a visa) */
	PR_DFE_START_OF_VALIDITY	= 241,	/**< Start date of validity */
	PR_DFE_NUMBER_OF_ENTRIES	= 242,	/**< Number of entries */
	PR_DFE_DURATION_OF_STAY		= 243,	/**< Duration of stay */

	PR_DFE_REFERENCE			= 300,	/**< Reference code (on hungarian postal cheque) */
	PR_DFE_AMOUNT				= 301,	/**< Amount (on hungarian postal cheque) */
	PR_DFE_BANK_ACCOUNT			= 302,	/**< Bank account (on hungarian postal cheque) */
	PR_DFE_POSTAL_REFERENCE		= 303,	/**< Postal reference (on hungarian postal cheque) */
	PR_DFE_TRANSACTION_CODE		= 304,	/**< Transaction code (on hungarian postal cheque) */
	PR_DFE_SUPPLIER				= 305,	/**< Supplier (on hungarian postal cheque) */
	PR_DFE_OUTPUT_CODE			= 306,	/**< Output code (on hungarian postal cheque) */

	PR_DFE_FROMADDR				= 320,	/**< From address */
	PR_DFE_DESTADDR				= 321,	/**< Destination address */
	PR_DFE_FLIGHTNO				= 322,	/**< Flight number */
	PR_DFE_COMPARTMENT			= 323,	/**< Compartment */
	PR_DFE_SEATNO				= 324,	/**< Seat number */

	PR_DFE_FACE					= 400,	/**< Face */
	PR_DFE_SIGNATURE			= 420,	/**< Signature */
	PR_DFE_FINGERPRINT			= 430,	/**< Fingerprint */
	PR_DFE_IRIS					= 440,	/**< Iris */

	PR_DFE_HEIGHT				= 490,	/**< Height */
	PR_DFE_WEIGHT				= 491,	/**< Weight */
	PR_DFE_EYECOLOR				= 492,	/**< Eye color */
	PR_DFE_HAIRCOLOR			= 493,	/**< Hair color */

	PR_DFE_AUTHENTICITY			= 500,
	PR_DFE_AUTHENTICITY1		= 501,
	PR_DFE_AUTHENTICITY2		= 502,
	PR_DFE_AUTHENTICITY3		= 503,
	PR_DFE_AUTHENTICITY4		= 504,
	PR_DFE_AUTHENTICITY5		= 505,

	PR_DFE_TELEPHONE			= 600,	/**< Telephone number */
	PR_DFE_PROFESSION			= 601,	/**< Profession */
	PR_DFE_TITLE				= 602,	/**< Title */
	PR_DFE_PERSONAL_SUMMARY		= 603,	/**< Personal summary */
	PR_DFE_PROOF_OF_CITIZENSHIP	= 604,	/**< Proof of citizenship */
	PR_DFE_OTHER_TD_NUMBERS		= 605,	/**< Other (valid) TD numbers */
	PR_DFE_CUSTODY_INFORMATION	= 606,	/**< Custody information */
	PR_DFE_OTHER_NAME			= 607,	/**< Other name */
	PR_DFE_OTHER_PEOPLE			= 608,	/**< Other people */
	PR_DFE_OBSERVATIONS			= 609,	/**< Observations */
	PR_DFE_TAX					= 610,	/**< Tax / Exit Requirements */
	PR_DFE_FRONT_IMAGE			= 611,	/**< Image of front of document */
	PR_DFE_REAR_IMAGE			= 612,	/**< Image of rear of document */
	PR_DFE_PERSONALIZATION_DATE	= 613,	/**< Date and time of document personalization */
	PR_DFE_PERSONALIZATION_SYSTEM	= 614,	/**< Serial number of personalization system */
	PR_DFE_ORGAN_DONOR			= 615,	/**< Organ donor */
	PR_DFE_REMARKS				= 616,	/**< Remarks */

	PR_DFE_CAR					= 620,	/**< Certification Authority Reference */
	PR_DFE_CHR					= 621,	/**< Certificate Holder Reference */

	PR_DFE_LOWLEVEL				= 997,	/**< Low level data */
	PR_DFE_FORMAT_CHECK			= 998,	/**< Quality check */
	PR_DFE_DOCUMENT_DESCRIPTOR	= 999,	/**< Document descriptor field code */

//Machine Readable Zone (MRZ)
	PR_DF_MRZ_FIELDS			= 1000,	/**< \b Machine \b Readable \b Zone \b Ids (\b MRZ) */

	PR_DF_MRZ1					= PR_DF_MRZ_FIELDS + PR_DFE_COMPOSITE1,		/**< Numbered row in MRZ (1) */
	PR_DF_MRZ2					= PR_DF_MRZ_FIELDS + PR_DFE_COMPOSITE2,		/**< Numbered row in MRZ (2) */
	PR_DF_MRZ3					= PR_DF_MRZ_FIELDS + PR_DFE_COMPOSITE3,		/**< Numbered row in MRZ (3) */

	PR_DF_MRZ_NAME				= PR_DF_MRZ_FIELDS + PR_DFE_NAME,			/**< Full name in MRZ */
	PR_DF_MRZ_GIVENNAME			= PR_DF_MRZ_FIELDS + PR_DFE_GIVENNAME,
	PR_DF_MRZ_SURNAME			= PR_DF_MRZ_FIELDS + PR_DFE_SURNAME,
	PR_DF_MRZ_BIRTH_DATE		= PR_DF_MRZ_FIELDS + PR_DFE_BIRTH_DATE,
	PR_DF_MRZ_NATIONALITY		= PR_DF_MRZ_FIELDS + PR_DFE_NATIONALITY,
	PR_DF_MRZ_SEX				= PR_DF_MRZ_FIELDS + PR_DFE_SEX,

	PR_DF_MRZ_DOCUMENT_NUMBER	= PR_DF_MRZ_FIELDS + PR_DFE_DOCUMENT_NUMBER,
	PR_DF_MRZ_TYPE				= PR_DF_MRZ_FIELDS + PR_DFE_TYPE,			/**< Document type (Px-passport, Ix-id, Vx-visa) */
	PR_DF_MRZ_ISSUE_COUNTRY		= PR_DF_MRZ_FIELDS + PR_DFE_ISSUE_COUNTRY,
	PR_DF_MRZ_ISSUE_PROVINCE	= PR_DF_MRZ_FIELDS + PR_DFE_ISSUE_PROVINCE,
	PR_DF_MRZ_EXPIRY_DATE		= PR_DF_MRZ_FIELDS + PR_DFE_EXPIRY_DATE,

	PR_DF_MRZ_PERSONAL_DATA		= PR_DF_MRZ_FIELDS + PR_DFE_PERSONAL_DATA1,	/**< Content of this data is up to the issuing country / organization */
	PR_DF_MRZ_PERSONAL_DATA2	= PR_DF_MRZ_FIELDS + PR_DFE_PERSONAL_DATA2,	/**< Content of this data is up to the issuing country / organization */

	PR_DF_MRZ_REFERENCE			= PR_DF_MRZ_FIELDS + PR_DFE_REFERENCE,		/**< on hungarian postal cheque */
	PR_DF_MRZ_AMOUNT			= PR_DF_MRZ_FIELDS + PR_DFE_AMOUNT,			/**< on hungarian postal cheque */
	PR_DF_MRZ_BANK_ACCOUNT		= PR_DF_MRZ_FIELDS + PR_DFE_BANK_ACCOUNT,	/**< on hungarian postal cheque */
	PR_DF_MRZ_POSTAL_REFERENCE	= PR_DF_MRZ_FIELDS + PR_DFE_POSTAL_REFERENCE,	/**< on hungarian postal cheque */
	PR_DF_MRZ_TRANSACTION_CODE	= PR_DF_MRZ_FIELDS + PR_DFE_TRANSACTION_CODE,	/**< on hungarian postal cheque */
	PR_DF_MRZ_SUPPLIER			= PR_DF_MRZ_FIELDS + PR_DFE_SUPPLIER,		/**< on hungarian postal cheque */
	PR_DF_MRZ_OUTPUT_CODE		= PR_DF_MRZ_FIELDS + PR_DFE_OUTPUT_CODE,	/**< on hungarian postal cheque */

	PR_DF_MRZ_AUTH_B900			= 1551,

//Visual Inspection Zone (VIZ)
	PR_DF_VIZ_FIELDS			= 2000,	/**< \b Visual \b Inspection \b Zone \b Ids (\b VIZ) */

	PR_DF_VIZ1					= PR_DF_VIZ_FIELDS + PR_DFE_COMPOSITE1,
	PR_DF_VIZ2					= PR_DF_VIZ_FIELDS + PR_DFE_COMPOSITE2,
	PR_DF_VIZ3					= PR_DF_VIZ_FIELDS + PR_DFE_COMPOSITE3,

	PR_DF_VIZ_NAME				= PR_DF_VIZ_FIELDS + PR_DFE_NAME,			/**< Full name in VIZ */
	PR_DF_VIZ_GIVENNAME			= PR_DF_VIZ_FIELDS + PR_DFE_GIVENNAME,
	PR_DF_VIZ_SURNAME			= PR_DF_VIZ_FIELDS + PR_DFE_SURNAME,
	PR_DF_VIZ_SURNAME2			= PR_DF_VIZ_FIELDS + PR_DFE_SURNAME2,

	PR_DF_VIZ_MAIDEN_NAME		= PR_DF_VIZ_FIELDS + PR_DFE_MAIDEN_NAME,	/**< Maiden name */

	PR_DF_VIZ_BIRTH_DATE		= PR_DF_VIZ_FIELDS + PR_DFE_BIRTH_DATE,
	PR_DF_VIZ_BIRTH_PLACE		= PR_DF_VIZ_FIELDS + PR_DFE_BIRTH_PLACE,
	PR_DF_VIZ_BIRTH_COUNTRY		= PR_DF_VIZ_FIELDS + PR_DFE_BIRTH_COUNTRY,
	PR_DF_VIZ_MOTHER_NAME		= PR_DF_VIZ_FIELDS + PR_DFE_MOTHER_NAME,	/**< Mother's name */
	PR_DF_VIZ_NATIONALITY		= PR_DF_VIZ_FIELDS + PR_DFE_NATIONALITY,
	PR_DF_VIZ_SEX				= PR_DF_VIZ_FIELDS + PR_DFE_SEX,
	PR_DF_VIZ_BIRTH_PROVINCE	= PR_DF_VIZ_FIELDS + PR_DFE_BIRTH_PROVINCE,
	PR_DF_VIZ_PARENTS_NAME		= PR_DF_VIZ_FIELDS + PR_DFE_PARENTS_NAME,

	PR_DF_VIZ_DOCUMENT_NUMBER	= PR_DF_VIZ_FIELDS + PR_DFE_DOCUMENT_NUMBER,
	PR_DF_VIZ_TYPE				= PR_DF_VIZ_FIELDS + PR_DFE_TYPE,
	PR_DF_VIZ_ISSUE_COUNTRY		= PR_DF_VIZ_FIELDS + PR_DFE_ISSUE_COUNTRY,
	PR_DF_VIZ_ISSUE_PLACE		= PR_DF_VIZ_FIELDS + PR_DFE_ISSUE_PLACE,
	PR_DF_VIZ_ISSUE_DATE		= PR_DF_VIZ_FIELDS + PR_DFE_ISSUE_DATE,
	PR_DF_VIZ_EXPIRY_DATE		= PR_DF_VIZ_FIELDS + PR_DFE_EXPIRY_DATE,
	PR_DF_VIZ_ISSUE_ORG			= PR_DF_VIZ_FIELDS + PR_DFE_ISSUE_ORG,

	PR_DF_VIZ_PERSONAL_NUMBER	= PR_DF_VIZ_FIELDS + PR_DFE_PERSONAL_NUMBER,
	PR_DF_VIZ_HEALTH_INS_NUMBER	= PR_DF_VIZ_FIELDS + PR_DFE_HEALTH_INS_NUMBER,

	PR_DF_VIZ_ADDRESS			= PR_DF_VIZ_FIELDS + PR_DFE_ADDRESS,
	PR_DF_VIZ_ADDR_ZIP			= PR_DF_VIZ_FIELDS + PR_DFE_ADDR_ZIP,
	PR_DF_VIZ_ADDR_CITY			= PR_DF_VIZ_FIELDS + PR_DFE_ADDR_CITY,
	PR_DF_VIZ_ADDR_STREET		= PR_DF_VIZ_FIELDS + PR_DFE_ADDR_STREET,
	PR_DF_VIZ_ADDR_HOUSE		= PR_DF_VIZ_FIELDS + PR_DFE_ADDR_HOUSE,
	PR_DF_VIZ_ADDR_FLAT			= PR_DF_VIZ_FIELDS + PR_DFE_ADDR_FLAT,
	PR_DF_VIZ_ADDR_DATE			= PR_DF_VIZ_FIELDS + PR_DFE_ADDR_DATE,
	PR_DF_VIZ_ADDR_PROVINCE		= PR_DF_VIZ_FIELDS + PR_DFE_ADDR_PROVINCE,

	PR_DF_VIZ_TEMPADDRESS		= PR_DF_VIZ_FIELDS + PR_DFE_TEMPADDRESS,	/**< Temporary address */
	PR_DF_VIZ_TEMPADDR_ZIP		= PR_DF_VIZ_FIELDS + PR_DFE_TEMPADDR_ZIP,	/**< Temporary address */
	PR_DF_VIZ_TEMPADDR_CITY		= PR_DF_VIZ_FIELDS + PR_DFE_TEMPADDR_CITY,	/**< Temporary address */
	PR_DF_VIZ_TEMPADDR_STREET	= PR_DF_VIZ_FIELDS + PR_DFE_TEMPADDR_STREET,/**< Temporary address */
	PR_DF_VIZ_TEMPADDR_HOUSE	= PR_DF_VIZ_FIELDS + PR_DFE_TEMPADDR_HOUSE,	/**< Temporary address */
	PR_DF_VIZ_TEMPADDR_FLAT		= PR_DF_VIZ_FIELDS + PR_DFE_TEMPADDR_FLAT,	/**< Temporary address */
	PR_DF_VIZ_TEMPADDR_DATE		= PR_DF_VIZ_FIELDS + PR_DFE_TEMPADDR_DATE,	/**< Temporary address */
	PR_DF_VIZ_TEMPADDR_DATEEND	= PR_DF_VIZ_FIELDS + PR_DFE_TEMPADDR_DATEEND,	/**< Temporary address */

	PR_DF_VIZ_REFERENCE			= PR_DF_VIZ_FIELDS + PR_DFE_REFERENCE,		/**< on hungarian postal cheque */
	PR_DF_VIZ_AMOUNT			= PR_DF_VIZ_FIELDS + PR_DFE_AMOUNT,			/**< on hungarian postal cheque */
//	PR_DF_VIZ_BANK_ACCOUNT		= PR_DF_VIZ_FIELDS + PR_DFE_BANK_ACCOUNT,

	PR_DF_VIZ_FACE				= PR_DF_VIZ_FIELDS + PR_DFE_FACE,			/**< Face */
	PR_DF_VIZ_SIGNATURE			= PR_DF_VIZ_FIELDS + PR_DFE_SIGNATURE,		/**< Signature */
	PR_DF_VIZ_FINGERPRINT		= PR_DF_VIZ_FIELDS + PR_DFE_FINGERPRINT,	/**< Fingerprint */
	PR_DF_VIZ_IRIS				= PR_DF_VIZ_FIELDS + PR_DFE_IRIS,			/**< Iris */

	PR_DF_VIZ_AUTHENTICITY		= PR_DF_VIZ_FIELDS + PR_DFE_AUTHENTICITY,
	PR_DF_VIZ_AUTHENTICITY1		= PR_DF_VIZ_FIELDS + PR_DFE_AUTHENTICITY1,
	PR_DF_VIZ_AUTHENTICITY2		= PR_DF_VIZ_FIELDS + PR_DFE_AUTHENTICITY2,
	PR_DF_VIZ_AUTHENTICITY3		= PR_DF_VIZ_FIELDS + PR_DFE_AUTHENTICITY3,
	PR_DF_VIZ_AUTHENTICITY4		= PR_DF_VIZ_FIELDS + PR_DFE_AUTHENTICITY4,
	PR_DF_VIZ_AUTHENTICITY5		= PR_DF_VIZ_FIELDS + PR_DFE_AUTHENTICITY5,

	PR_DF_VIZ_AUTH_COMPOSITE	= 2500,
	PR_DF_VIZ_AUTH_DOCAREA		= 2551,
	PR_DF_VIZ_AUTH_ACCORDANCE	= 2552,

//Barcode Reading (BC)
	PR_DF_BC_FIELDS				= 3000,		/**< \b Barcode \b Reading \b Ids (\b BC) */

	PR_DF_BC1					= PR_DF_BC_FIELDS + PR_DFE_COMPOSITE1,		/**< Composite data in barcode */

//Magnetic Stripe (MS)
	PR_DF_MS_FIELDS				= 4000,		/**< \b Magnetic \b Stripe \b Ids (\b MS) */

// RFID data
	PR_DF_RFID_FIELDS			= 0x400000,		/**<	\b RFID reading ids */

	PR_DF_RFID_MRZ				= PR_DF_RFID_FIELDS | 0x010000,		/**< MRZ field in RFID */
	PR_DF_RFID_FACE				= PR_DF_RFID_FIELDS | 0x020000,		/**< Face images stored in RFID */
	PR_DF_RFID_FINGERPRINT		= PR_DF_RFID_FIELDS | 0x030000,		/**< Fingerprint images stored in RFID */
	PR_DF_RFID_IRIS				= PR_DF_RFID_FIELDS | 0x040000,		/**< Iris images stored in RFID */
	PR_DF_RFID_SIGNATURE		= PR_DF_RFID_FIELDS | 0x050000,		/**< Signatures stored in RFID */

//Final formatted data
	PR_DF_FORMATTED				= 10000,	/**< \b Final \b formatted \b data \b Ids */

	PR_DF_NAME					= PR_DF_FORMATTED + PR_DFE_NAME,			/**< Full name */
	PR_DF_GIVENNAME				= PR_DF_FORMATTED + PR_DFE_GIVENNAME,
	PR_DF_SURNAME				= PR_DF_FORMATTED + PR_DFE_SURNAME,
	PR_DF_SURNAME2				= PR_DF_FORMATTED + PR_DFE_SURNAME2,
	PR_DF_MIDDLENAME			= PR_DF_FORMATTED + PR_DFE_MIDDLENAME,
	PR_DF_MAIDEN_NAME			= PR_DF_FORMATTED + PR_DFE_MAIDEN_NAME,
	PR_DF_MAIDEN_GIVENNAME		= PR_DF_FORMATTED + PR_DFE_MAIDEN_GIVENNAME,
	PR_DF_MAIDEN_SURNAME		= PR_DF_FORMATTED + PR_DFE_MAIDEN_SURNAME,

	PR_DF_BIRTH_DATE			= PR_DF_FORMATTED + PR_DFE_BIRTH_DATE,
	PR_DF_BIRTH_PLACE			= PR_DF_FORMATTED + PR_DFE_BIRTH_PLACE,
	PR_DF_BIRTH_COUNTRY			= PR_DF_FORMATTED + PR_DFE_BIRTH_COUNTRY,
	PR_DF_MOTHER_NAME			= PR_DF_FORMATTED + PR_DFE_MOTHER_NAME,
	PR_DF_MOTHER_GIVENNAME		= PR_DF_FORMATTED + PR_DFE_MOTHER_GIVENNAME,
	PR_DF_MOTHER_SURNAME		= PR_DF_FORMATTED + PR_DFE_MOTHER_SURNAME,

	PR_DF_NATIONALITY			= PR_DF_FORMATTED + PR_DFE_NATIONALITY,
	PR_DF_SEX					= PR_DF_FORMATTED + PR_DFE_SEX,
	PR_DF_BIRTH_PROVINCE		= PR_DF_FORMATTED + PR_DFE_BIRTH_PROVINCE,
	PR_DF_PARENTS_NAME			= PR_DF_FORMATTED + PR_DFE_PARENTS_NAME,

	PR_DF_DOCUMENT_NUMBER		= PR_DF_FORMATTED + PR_DFE_DOCUMENT_NUMBER,
	PR_DF_TYPE					= PR_DF_FORMATTED + PR_DFE_TYPE,
	PR_DF_ISSUE_COUNTRY			= PR_DF_FORMATTED + PR_DFE_ISSUE_COUNTRY,
	PR_DF_ISSUE_PLACE			= PR_DF_FORMATTED + PR_DFE_ISSUE_PLACE,
	PR_DF_ISSUE_PROVINCE		= PR_DF_FORMATTED + PR_DFE_ISSUE_PROVINCE,
	PR_DF_ISSUE_DATE			= PR_DF_FORMATTED + PR_DFE_ISSUE_DATE,
	PR_DF_EXPIRY_DATE			= PR_DF_FORMATTED + PR_DFE_EXPIRY_DATE,
	PR_DF_ISSUE_ORG				= PR_DF_FORMATTED + PR_DFE_ISSUE_ORG,

	PR_DF_PERSONAL_NUMBER		= PR_DF_FORMATTED + PR_DFE_PERSONAL_NUMBER,
	PR_DF_HEALTH_INS_NUMBER		= PR_DF_FORMATTED + PR_DFE_HEALTH_INS_NUMBER,

	PR_DF_DOCTYPE				= PR_DF_FORMATTED + PR_DFE_DOCTYPE,

	PR_DF_PERSONAL_DATA			= PR_DF_FORMATTED + PR_DFE_PERSONAL_DATA1,
	PR_DF_PERSONAL_DATA2		= PR_DF_FORMATTED + PR_DFE_PERSONAL_DATA2,

	PR_DF_ADDR_ZIP				= PR_DF_FORMATTED + PR_DFE_ADDR_ZIP,
	PR_DF_ADDR_CITY				= PR_DF_FORMATTED + PR_DFE_ADDR_CITY,
	PR_DF_ADDR_STREET			= PR_DF_FORMATTED + PR_DFE_ADDR_STREET,
	PR_DF_ADDR_HOUSE			= PR_DF_FORMATTED + PR_DFE_ADDR_HOUSE,
	PR_DF_ADDR_FLAT				= PR_DF_FORMATTED + PR_DFE_ADDR_FLAT,
	PR_DF_ADDR_DATE				= PR_DF_FORMATTED + PR_DFE_ADDR_DATE,
	PR_DF_ADDR_PROVINCE			= PR_DF_FORMATTED + PR_DFE_ADDR_PROVINCE,

	PR_DF_TEMPADDR_ZIP			= PR_DF_FORMATTED + PR_DFE_TEMPADDR_ZIP,
	PR_DF_TEMPADDR_CITY			= PR_DF_FORMATTED + PR_DFE_TEMPADDR_CITY,
	PR_DF_TEMPADDR_STREET		= PR_DF_FORMATTED + PR_DFE_TEMPADDR_STREET,
	PR_DF_TEMPADDR_HOUSE		= PR_DF_FORMATTED + PR_DFE_TEMPADDR_HOUSE,
	PR_DF_TEMPADDR_FLAT			= PR_DF_FORMATTED + PR_DFE_TEMPADDR_FLAT,
	PR_DF_TEMPADDR_DATE			= PR_DF_FORMATTED + PR_DFE_TEMPADDR_DATE,
	PR_DF_TEMPADDR_DATEEND		= PR_DF_FORMATTED + PR_DFE_TEMPADDR_DATEEND,
	PR_DF_TEMPADDR_PROVINCE		= PR_DF_FORMATTED + PR_DFE_TEMPADDR_PROVINCE,

	PR_DF_REFERENCE				= PR_DF_FORMATTED + PR_DFE_REFERENCE,
	PR_DF_AMOUNT				= PR_DF_FORMATTED + PR_DFE_AMOUNT,
	PR_DF_BANK_ACCOUNT			= PR_DF_FORMATTED + PR_DFE_BANK_ACCOUNT,
	PR_DF_POSTAL_REFERENCE		= PR_DF_FORMATTED + PR_DFE_POSTAL_REFERENCE,
	PR_DF_TRANSACTION_CODE		= PR_DF_FORMATTED + PR_DFE_TRANSACTION_CODE,
	PR_DF_SUPPLIER				= PR_DF_FORMATTED + PR_DFE_SUPPLIER,
	PR_DF_OUTPUT_CODE			= PR_DF_FORMATTED + PR_DFE_OUTPUT_CODE,

	PR_DF_FACE					= PR_DF_FORMATTED + PR_DFE_FACE,

	PR_DF_HEIGHT				= PR_DF_FORMATTED + PR_DFE_HEIGHT,
	PR_DF_WEIGHT				= PR_DF_FORMATTED + PR_DFE_WEIGHT,
	PR_DF_EYECOLOR				= PR_DF_FORMATTED + PR_DFE_EYECOLOR,

	PR_DF_AUTHENTICITY			= PR_DF_FORMATTED + PR_DFE_AUTHENTICITY,

};

/** Available property types.
 *
 * \note In case of unspecified property types, the application must handle the case exceptions. */
GX_ENUM PR_PROP_TYPE {
	PR_PROP_TYPE_BASE		= 0x000000,	/**< Base properties */
	PR_PROP_TYPE_GENERAL	= 0xF00000,	/**< General property */
	PR_PROP_TYPE_COMPOSITE	= 0xF10000,	/**< Composite property. Two or more properties merged in a single buffer. */

	PR_PROP_TYPE_BARCODE_TYPE	= PR_PROP_TYPE_BASE | 0x01,	/**< Barcode type */
	PR_PROP_TYPE_RFID_FILES		= PR_PROP_TYPE_BASE | 0x02,	/**< RFID files on chip */
	PR_PROP_TYPE_CONFIDENCE		= PR_PROP_TYPE_BASE | 0x03,	/**< Confidence level */

	PR_PROP_TYPE_FACIAL_RECORD_HEADER	= PR_PROP_TYPE_COMPOSITE | 0x01,	/**< Facial record header structure */
	PR_PROP_TYPE_FACIAL_INFORMATION		= PR_PROP_TYPE_COMPOSITE | 0x02,	/**< Facial information structure */
	PR_PROP_TYPE_FEATURE_POINTS			= PR_PROP_TYPE_COMPOSITE | 0x03,	/**< Feature points structure */
	PR_PROP_TYPE_IMAGE_INFORMATION		= PR_PROP_TYPE_COMPOSITE | 0x04,	/**< Image information structure */
};

/** Available data types for the doc item's data. */
GX_ENUM PR_DATA_TYPE {
	PR_DATA_TYPE_BINARY		= 0x00,	/**< Some kind of binary data */
	PR_DATA_TYPE_ASCII		= 0x01,	/**< ASCII characters */
	PR_DATA_TYPE_UNICODE	= 0x02,	/**< Unicode characters */

	PR_DATA_TYPE_INT8		= 0x11,	/**< One byte data */
	PR_DATA_TYPE_INT16		= 0x12, /**< Two bytes data */
	PR_DATA_TYPE_INT32		= 0x14, /**< Four bytes data */

	PR_DATA_TYPE_DATETIME	= 0x20,	/**< Date and time */
	PR_DATA_TYPE_DATE		= 0x21,	/**< Date value */
	PR_DATA_TYPE_TIME		= 0x22,	/**< Time value */

	PR_DATA_TYPE_STRUCT		= 0x6bc0100,	/**< General structure */
	PR_DATA_TYPE_STRUCT_FACIAL_RECORD_HEADER	= PR_DATA_TYPE_STRUCT | 0x01,	/**< Facial record header structure */
	PR_DATA_TYPE_STRUCT_FACIAL_INFORMATION		= PR_DATA_TYPE_STRUCT | 0x02,	/**< Facial information structure */
	PR_DATA_TYPE_STRUCT_FEATURE_POINTS			= PR_DATA_TYPE_STRUCT | 0x04,	/**< Feature points structure */
	PR_DATA_TYPE_STRUCT_IMAGE_INFORMATION		= PR_DATA_TYPE_STRUCT | 0x08,	/**< Image information structure */
};
/******************************************************************************/
#ifdef GX_NAMESPACES
	}
#endif
/******************************************************************************/
#endif//PRDOCTYPES_INCL
