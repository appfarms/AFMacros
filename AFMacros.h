//
//  AFMacros.h
//  AFMacros
//
//  Created by Daniel Kuhnke on 12.08.13.
//  Copyright (c) 2014 appfarms GmbH & Co. KG. All rights reserved.
//

/*
 The MIT License (MIT)
 
 Copyright (c) 2014 appfarms GmbH & Co. KG
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Directories
//
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef AF_CACHE_DIR
#define AF_CACHE_DIR      [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject]
#endif

#ifndef AF_DOCUMENTS_DIR
#define AF_DOCUMENTS_DIR  [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// NSLocalizedString
//
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef AF_LOCALIZE
#define AF_LOCALIZE(__NSSTRING) NSLocalizedString(__NSSTRING, __NSSTRING);
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// UUID
//
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef AF_UUID
#define AF_UUID AF_NSUUIDString()
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// NSLocale
//
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef AF_PREFERRED_LANGUAGE_IDENTIFIER
#define AF_PREFERRED_LANGUAGE_IDENTIFIER [[NSLocale preferredLanguages] objectAtIndex:0]
#endif

#ifndef AF_PREFERRED_LANGUAGE_CODE
#define AF_PREFERRED_LANGUAGE_CODE [[NSLocale componentsFromLocaleIdentifier:AF_PREFERRED_LANGUAGE_IDENTIFIER] objectForKey:NSLocaleLanguageCode]
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// NSLog
//
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef ZLog
#define ZLog(fmt, ...) NSLog((@"%s (%d) " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// NSManagedObject
//
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef AF_MOC
#define AF_MOC ([[UIApplication sharedApplication].delegate respondsToSelector:@selector(managedObjectContext)] ? (NSManagedObjectContext *)[[UIApplication sharedApplication].delegate performSelector:@selector(managedObjectContext)] : nil)
#endif

#ifndef AF_SAVEMOC
#define AF_SAVEMOC(__OBJECT) { NSError *_error = nil; if(AF_VALID(__OBJECT, NSManagedObjectContext)){ [__OBJECT save:&_error]; } if(AF_VALID(_error, NSError)) { NSLog(@"%s Error '%@'", __PRETTY_FUNCTION__ _error); } }
#endif

#ifndef AF_SAVEMAINMOC
#define AF_SAVEMAINMOC() { NSError *_error = nil; [AF_MOC save:&_error]; if(AF_VALID(_error, NSError)) { NSLog(@"%s Error '%@'", __PRETTY_FUNCTION__ _error); } }
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Validation
//
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef AF_EMPTY
#define AF_EMPTY(__OBJECT) ((nil == __OBJECT) ? YES : ((nil != __OBJECT && [__OBJECT respondsToSelector:@selector(count)]) ? ([__OBJECT performSelector:@selector(count)] <= 0) : ((nil != __OBJECT && [__OBJECT respondsToSelector:@selector(length)]) ? ([__OBJECT performSelector:@selector(length)] <= 0) : NO)))
#endif

#ifndef AF_NOTEMPTY
#define AF_NOTEMPTY(__OBJECT) (EMPTY(__OBJECT) == NO)
#endif

#ifndef AF_VALID
#define AF_VALID(__OBJECT, __CLASSNAME) (nil != __OBJECT && [__OBJECT isKindOfClass:[__CLASSNAME class]])
#endif

#ifndef AF_VALID_EMPTY
#define AF_VALID_EMPTY(__OBJECT, __CLASSNAME) (AF_VALID(__OBJECT, __CLASSNAME) == YES && AF_EMPTY(__OBJECT) == YES)
#endif

#ifndef AF_VALID_NOTEMPTY
#define AF_VALID_NOTEMPTY(__OBJECT, __CLASSNAME) (AF_VALID(__OBJECT, __CLASSNAME) == YES && AF_EMPTY(__OBJECT) == NO)
#endif

#ifndef AF_RADIANS
#define AF_RADIANS(__FLOAT) ((__FLOAT * M_PI) / 180.0)
#endif

#ifndef AF_ARRAY_INDEX_EXISTS
#define AF_ARRAY_INDEX_EXISTS(__ARRAY, __INDEX) (AF_VALID(__ARRAY, NSArray) && __INDEX >= 0 && __INDEX < [(NSArray *)__ARRAY count])
#endif

#ifndef AF_ARRAY_OBJECT_AT_INDEX
#define AF_ARRAY_OBJECT_AT_INDEX(__ARRAY, __INDEX) (AF_ARRAY_INDEX_EXISTS(__ARRAY, __INDEX) ? [__ARRAY objectAtIndex:__INDEX] : nil)
#endif

#ifndef AF_PERFORM_SAFE_SELECTOR
#define AF_PERFORM_SAFE_SELECTOR(__OBJECT, __SEL) ({ if (__OBJECT != nil && [(NSObject *)__OBJECT respondsToSelector:__SEL]) { [(NSObject *)__OBJECT performSelector:__SEL]; } })
#endif

#ifndef AF_PERFORM_SAFE_SELECTOR_WITH_OBJECT
#define AF_PERFORM_SAFE_SELECTOR_WITH_OBJECT(__OBJECT, __SEL, __PARAM1) ({ if (__OBJECT != nil && [(NSObject *)__OBJECT respondsToSelector:__SEL]) { [(NSObject *)__OBJECT performSelector:__SEL withObject:__PARAM1]; } })
#endif

#ifndef AF_PERFORM_SAFE_SELECTOR_WITH_OBJECT_WITH_OBJECT
#define AF_PERFORM_SAFE_SELECTOR_WITH_OBJECT_WITH_OBJECT(__OBJECT, __SEL, __PARAM1, __PARAM2) ({ if (__OBJECT != nil && [(NSObject *)__OBJECT respondsToSelector:__SEL]) { [(NSObject *)__OBJECT performSelector:__SEL withObject:__PARAM1 withObject:__PARAM2]; } })
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
//
// App Version / Info Plist
//
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef AF_BUNDLE_SHORT_VERSION_STRING
#define AF_BUNDLE_SHORT_VERSION_STRING [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"]
#endif

#ifndef AF_BUNDLE_VERSION_STRING
#define AF_BUNDLE_VERSION_STRING [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"]
#endif

#ifndef AF_BUNDLE_VERSION_VALUE
#define AF_BUNDLE_VERSION_VALUE [AF_BUNDLE_VERSION_STRING intValue]
#endif

#ifndef AF_APP_VERSION_STRING
#define AF_APP_VERSION_STRING   [NSString stringWithFormat:@"%@ (%@)", AF_BUNDLE_SHORT_VERSION_STRING, AF_BUNDLE_VERSION_STRING]
#endif

#ifndef AF_BUNDLE_IDENTIFIER
#define AF_BUNDLE_IDENTIFIER (NSString *)([[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleIdentifier"])
#endif

#ifndef AF_DEVICE_MACHINE_NAME
#define AF_DEVICE_MACHINE_NAME (NSString *)(AF_NSStringMachineNameFromCurrentDevice())
#endif

#ifndef AF_DEVICE_SYSTEM_VERSION
#define AF_DEVICE_SYSTEM_VERSION [[UIDevice currentDevice] systemVersion]
#endif

#ifndef AF_SCREEN_SCALE
#define AF_SCREEN_SCALE ([[UIScreen mainScreen] respondsToSelector:NSSelectorFromString(@"scale")] ? [[UIScreen mainScreen] scale] : 1.f)
#endif

#ifndef AF_DEBUG_APP_CONFIG_STRING
#define AF_DEBUG_APP_CONFIG_STRING [NSString stringWithFormat:@"App Version: '%@' System Version: '%@' Machine Name '%@' Bundle Identifier: '%@'", AF_APP_VERSION_STRING, AF_DEVICE_SYSTEM_VERSION, AF_DEVICE_MACHINE_NAME, AF_BUNDLE_IDENTIFIER]
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// NSDate + NSDateFormatter
//
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef AF_DATE_FORMATTER_STRING_UTC
#define AF_DATE_FORMATTER_STRING_UTC @"yyyy-MM-dd HH:mm:ss z"
#endif

#ifndef AF_DATE_FORMATTER_STRING_ZULU
#define AF_DATE_FORMATTER_STRING_ZULU @"yyyy-MM-dd'T'HH:mm:ss'Z'"
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Helper Methods
//
///////////////////////////////////////////////////////////////////////////////////////////////////


NSString * AF_NSStringByEncodingData(NSData * data);
NSString * AF_NSStringMachineNameFromCurrentDevice();
NSString * AF_NSUUIDCreateString();
NSString * AF_NSUUIDString();

NSDate * AF_NSDateFromStringWithFormat(NSString * dateString, NSString * formatString);
NSDate * AF_NSDateFromUTCString(NSString * dateString);
NSDate * AF_NSDateFromZULUString(NSString * dateString);


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// UIColor
//
///////////////////////////////////////////////////////////////////////////////////////////////////


UIColor * AF_UIColorWithHexString(NSString * string);
UIColor * AF_UIColorWithRGBString(NSString * string);

#ifndef AF_COLOR_HEX
#define AF_COLOR_HEX(__STRING) AF_UIColorWithHexString(__STRING)
#endif

#ifndef AF_COLOR_RGB
#define AF_COLOR_RGB(__STRING) AF_UIColorWithRGBString(__STRING)
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// UIFont
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef AF_FONT
#define AF_FONT

#define AF_FONT_WITH_NAME(__FONTNAME__, __FONTSIZE__) [UIFont fontWithName:__FONTNAME__ size:__FONTSIZE__]

// Academy Engraved LET
#define AF_FONT_ACADEMYENGRAVEDLETPLAIN @"AcademyEngravedLetPlain"

// Akzidenz-Grotesk Pro
#define AF_FONT_AKZIDENZGROTESKPRO_BOLDEXIT @"AkzidenzGroteskPro-BoldExIt"
#define AF_FONT_AKZIDENZGROTESKPRO_MEDEXTIT @"AkzidenzGroteskPro-MedExtIt"
#define AF_FONT_AKZIDENZGROTESKPRO_LIGEXTIT @"AkzidenzGroteskPro-LigExtIt"
#define AF_FONT_AKZIDENZGROTESKPRO_EXTITALIC @"AkzidenzGroteskPro-ExtItalic"
#define AF_FONT_AKZIDENZGROTESKPRO_MD @"AkzidenzGroteskPro-Md"
#define AF_FONT_AKZIDENZGROTESKPRO_MDEX @"AkzidenzGroteskPro-MdEx"
#define AF_FONT_AKZIDENZGROTESKPRO_LIGHTEX @"AkzidenzGroteskPro-LightEx"
#define AF_FONT_AKZIDENZGROTESKPRO_REGULAR @"AkzidenzGroteskPro-Regular"
#define AF_FONT_AKZIDENZGROTESKPRO_LIGHT @"AkzidenzGroteskPro-Light"
#define AF_FONT_AKZIDENZGROTESKPRO_BOLDEX @"AkzidenzGroteskPro-BoldEx"
#define AF_FONT_AKZIDENZGROTESKPRO_BOLD @"AkzidenzGroteskPro-Bold"
#define AF_FONT_AKZIDENZGROTESKPRO_EXT @"AkzidenzGroteskPro-Ext"

// Al Nile
#define AF_FONT_ALNILE_BOLD @"AlNile-Bold"
#define AF_FONT_ALNILE @"AlNile"

// American Typewriter
#define AF_FONT_AMERICANTYPEWRITER_LIGHT @"AmericanTypewriter-Light"
#define AF_FONT_AMERICANTYPEWRITER_CONDENSEDLIGHT @"AmericanTypewriter-CondensedLight"
#define AF_FONT_AMERICANTYPEWRITER_CONDENSEDBOLD @"AmericanTypewriter-CondensedBold"
#define AF_FONT_AMERICANTYPEWRITER @"AmericanTypewriter"
#define AF_FONT_AMERICANTYPEWRITER_CONDENSED @"AmericanTypewriter-Condensed"
#define AF_FONT_AMERICANTYPEWRITER_BOLD @"AmericanTypewriter-Bold"

// Apercu
#define AF_FONT_APERCU @"Apercu"

// Apple Color Emoji
#define AF_FONT_APPLECOLOREMOJI @"AppleColorEmoji"

// Apple SD Gothic Neo
#define AF_FONT_APPLESDGOTHICNEO_THIN @"AppleSDGothicNeo-Thin"
#define AF_FONT_APPLESDGOTHICNEO_SEMIBOLD @"AppleSDGothicNeo-SemiBold"
#define AF_FONT_APPLESDGOTHICNEO_MEDIUM @"AppleSDGothicNeo-Medium"
#define AF_FONT_APPLESDGOTHICNEO_REGULAR @"AppleSDGothicNeo-Regular"
#define AF_FONT_APPLESDGOTHICNEO_BOLD @"AppleSDGothicNeo-Bold"
#define AF_FONT_APPLESDGOTHICNEO_LIGHT @"AppleSDGothicNeo-Light"

// Arial
#define AF_FONT_ARIALMT @"ArialMT"
#define AF_FONT_ARIAL_BOLDITALICMT @"Arial-BoldItalicMT"
#define AF_FONT_ARIAL_ITALICMT @"Arial-ItalicMT"
#define AF_FONT_ARIAL_BOLDMT @"Arial-BoldMT"

// Arial Hebrew
#define AF_FONT_ARIALHEBREW_BOLD @"ArialHebrew-Bold"
#define AF_FONT_ARIALHEBREW_LIGHT @"ArialHebrew-Light"
#define AF_FONT_ARIALHEBREW @"ArialHebrew"

// Arial Rounded MT Bold
#define AF_FONT_ARIALROUNDEDMTBOLD @"ArialRoundedMTBold"

// Avenir
#define AF_FONT_AVENIR_HEAVY @"Avenir-Heavy"
#define AF_FONT_AVENIR_OBLIQUE @"Avenir-Oblique"
#define AF_FONT_AVENIR_BLACK @"Avenir-Black"
#define AF_FONT_AVENIR_BOOK @"Avenir-Book"
#define AF_FONT_AVENIR_BLACKOBLIQUE @"Avenir-BlackOblique"
#define AF_FONT_AVENIR_HEAVYOBLIQUE @"Avenir-HeavyOblique"
#define AF_FONT_AVENIR_LIGHT @"Avenir-Light"
#define AF_FONT_AVENIR_MEDIUMOBLIQUE @"Avenir-MediumOblique"
#define AF_FONT_AVENIR_MEDIUM @"Avenir-Medium"
#define AF_FONT_AVENIR_LIGHTOBLIQUE @"Avenir-LightOblique"
#define AF_FONT_AVENIR_ROMAN @"Avenir-Roman"
#define AF_FONT_AVENIR_BOOKOBLIQUE @"Avenir-BookOblique"

// Avenir Next
#define AF_FONT_AVENIRNEXT_MEDIUMITALIC @"AvenirNext-MediumItalic"
#define AF_FONT_AVENIRNEXT_BOLD @"AvenirNext-Bold"
#define AF_FONT_AVENIRNEXT_ULTRALIGHT @"AvenirNext-UltraLight"
#define AF_FONT_AVENIRNEXT_DEMIBOLD @"AvenirNext-DemiBold"
#define AF_FONT_AVENIRNEXT_HEAVYITALIC @"AvenirNext-HeavyItalic"
#define AF_FONT_AVENIRNEXT_HEAVY @"AvenirNext-Heavy"
#define AF_FONT_AVENIRNEXT_MEDIUM @"AvenirNext-Medium"
#define AF_FONT_AVENIRNEXT_ITALIC @"AvenirNext-Italic"
#define AF_FONT_AVENIRNEXT_ULTRALIGHTITALIC @"AvenirNext-UltraLightItalic"
#define AF_FONT_AVENIRNEXT_BOLDITALIC @"AvenirNext-BoldItalic"
#define AF_FONT_AVENIRNEXT_REGULAR @"AvenirNext-Regular"
#define AF_FONT_AVENIRNEXT_DEMIBOLDITALIC @"AvenirNext-DemiBoldItalic"

// Avenir Next Condensed
#define AF_FONT_AVENIRNEXTCONDENSED_REGULAR @"AvenirNextCondensed-Regular"
#define AF_FONT_AVENIRNEXTCONDENSED_MEDIUMITALIC @"AvenirNextCondensed-MediumItalic"
#define AF_FONT_AVENIRNEXTCONDENSED_ULTRALIGHTITALIC @"AvenirNextCondensed-UltraLightItalic"
#define AF_FONT_AVENIRNEXTCONDENSED_ULTRALIGHT @"AvenirNextCondensed-UltraLight"
#define AF_FONT_AVENIRNEXTCONDENSED_BOLDITALIC @"AvenirNextCondensed-BoldItalic"
#define AF_FONT_AVENIRNEXTCONDENSED_ITALIC @"AvenirNextCondensed-Italic"
#define AF_FONT_AVENIRNEXTCONDENSED_MEDIUM @"AvenirNextCondensed-Medium"
#define AF_FONT_AVENIRNEXTCONDENSED_HEAVYITALIC @"AvenirNextCondensed-HeavyItalic"
#define AF_FONT_AVENIRNEXTCONDENSED_HEAVY @"AvenirNextCondensed-Heavy"
#define AF_FONT_AVENIRNEXTCONDENSED_DEMIBOLDITALIC @"AvenirNextCondensed-DemiBoldItalic"
#define AF_FONT_AVENIRNEXTCONDENSED_DEMIBOLD @"AvenirNextCondensed-DemiBold"
#define AF_FONT_AVENIRNEXTCONDENSED_BOLD @"AvenirNextCondensed-Bold"

// Bangla Sangam MN
#define AF_FONT_BANGLASANGAMMN @"BanglaSangamMN"
#define AF_FONT_BANGLASANGAMMN_BOLD @"BanglaSangamMN-Bold"

// Baskerville
#define AF_FONT_BASKERVILLE_BOLD @"Baskerville-Bold"
#define AF_FONT_BASKERVILLE_SEMIBOLDITALIC @"Baskerville-SemiBoldItalic"
#define AF_FONT_BASKERVILLE_BOLDITALIC @"Baskerville-BoldItalic"
#define AF_FONT_BASKERVILLE @"Baskerville"
#define AF_FONT_BASKERVILLE_SEMIBOLD @"Baskerville-SemiBold"
#define AF_FONT_BASKERVILLE_ITALIC @"Baskerville-Italic"

// Bodoni 72
#define AF_FONT_BODONISVTYTWOITCTT_BOOK @"BodoniSvtyTwoITCTT-Book"
#define AF_FONT_BODONISVTYTWOITCTT_BOLD @"BodoniSvtyTwoITCTT-Bold"
#define AF_FONT_BODONISVTYTWOITCTT_BOOKITA @"BodoniSvtyTwoITCTT-BookIta"

// Bodoni 72 Oldstyle
#define AF_FONT_BODONISVTYTWOOSITCTT_BOOKIT @"BodoniSvtyTwoOSITCTT-BookIt"
#define AF_FONT_BODONISVTYTWOOSITCTT_BOLD @"BodoniSvtyTwoOSITCTT-Bold"
#define AF_FONT_BODONISVTYTWOOSITCTT_BOOK @"BodoniSvtyTwoOSITCTT-Book"

// Bodoni 72 Smallcaps
#define AF_FONT_BODONISVTYTWOSCITCTT_BOOK @"BodoniSvtyTwoSCITCTT-Book"

// Bodoni Ornaments
#define AF_FONT_BODONIORNAMENTSITCTT @"BodoniOrnamentsITCTT"

// Bradley Hand
#define AF_FONT_BRADLEYHANDITCTT_BOLD @"BradleyHandITCTT-Bold"

// Chalkboard SE
#define AF_FONT_CHALKBOARDSE_LIGHT @"ChalkboardSE-Light"
#define AF_FONT_CHALKBOARDSE_REGULAR @"ChalkboardSE-Regular"
#define AF_FONT_CHALKBOARDSE_BOLD @"ChalkboardSE-Bold"

// Chalkduster
#define AF_FONT_CHALKDUSTER @"Chalkduster"

// Cochin
#define AF_FONT_COCHIN_BOLD @"Cochin-Bold"
#define AF_FONT_COCHIN_BOLDITALIC @"Cochin-BoldItalic"
#define AF_FONT_COCHIN_ITALIC @"Cochin-Italic"
#define AF_FONT_COCHIN @"Cochin"

// Copperplate
#define AF_FONT_COPPERPLATE @"Copperplate"
#define AF_FONT_COPPERPLATE_LIGHT @"Copperplate-Light"
#define AF_FONT_COPPERPLATE_BOLD @"Copperplate-Bold"

// Courier
#define AF_FONT_COURIER @"Courier"
#define AF_FONT_COURIER_OBLIQUE @"Courier-Oblique"
#define AF_FONT_COURIER_BOLDOBLIQUE @"Courier-BoldOblique"
#define AF_FONT_COURIER_BOLD @"Courier-Bold"

// Courier New
#define AF_FONT_COURIERNEWPSMT @"CourierNewPSMT"
#define AF_FONT_COURIERNEWPS_BOLDMT @"CourierNewPS-BoldMT"
#define AF_FONT_COURIERNEWPS_ITALICMT @"CourierNewPS-ItalicMT"
#define AF_FONT_COURIERNEWPS_BOLDITALICMT @"CourierNewPS-BoldItalicMT"

// Damascus
#define AF_FONT_DAMASCUSBOLD @"DamascusBold"
#define AF_FONT_DAMASCUS @"Damascus"
#define AF_FONT_DAMASCUSMEDIUM @"DamascusMedium"
#define AF_FONT_DAMASCUSSEMIBOLD @"DamascusSemiBold"

// Devanagari Sangam MN
#define AF_FONT_DEVANAGARISANGAMMN @"DevanagariSangamMN"
#define AF_FONT_DEVANAGARISANGAMMN_BOLD @"DevanagariSangamMN-Bold"

// Didot
#define AF_FONT_DIDOT_BOLD @"Didot-Bold"
#define AF_FONT_DIDOT_ITALIC @"Didot-Italic"
#define AF_FONT_DIDOT @"Didot"

// DIN Alternate
#define AF_FONT_DINALTERNATE_BOLD @"DINAlternate-Bold"

// DIN Condensed
#define AF_FONT_DINCONDENSED_BOLD @"DINCondensed-Bold"

// Euphemia UCAS
#define AF_FONT_EUPHEMIAUCAS @"EuphemiaUCAS"
#define AF_FONT_EUPHEMIAUCAS_BOLD @"EuphemiaUCAS-Bold"
#define AF_FONT_EUPHEMIAUCAS_ITALIC @"EuphemiaUCAS-Italic"

// Farah
#define AF_FONT_FARAH @"Farah"

// Futura
#define AF_FONT_FUTURA_MEDIUM @"Futura-Medium"
#define AF_FONT_FUTURA_CONDENSEDMEDIUM @"Futura-CondensedMedium"
#define AF_FONT_FUTURA_MEDIUMITALIC @"Futura-MediumItalic"
#define AF_FONT_FUTURA_CONDENSEDEXTRABOLD @"Futura-CondensedExtraBold"

// Geeza Pro
#define AF_FONT_GEEZAPRO_BOLD @"GeezaPro-Bold"
#define AF_FONT_GEEZAPRO @"GeezaPro"
#define AF_FONT_GEEZAPRO_LIGHT @"GeezaPro-Light"

// Georgia
#define AF_FONT_GEORGIA_BOLDITALIC @"Georgia-BoldItalic"
#define AF_FONT_GEORGIA_BOLD @"Georgia-Bold"
#define AF_FONT_GEORGIA_ITALIC @"Georgia-Italic"
#define AF_FONT_GEORGIA @"Georgia"

// Gill Sans
#define AF_FONT_GILLSANS @"GillSans"
#define AF_FONT_GILLSANS_ITALIC @"GillSans-Italic"
#define AF_FONT_GILLSANS_BOLDITALIC @"GillSans-BoldItalic"
#define AF_FONT_GILLSANS_LIGHT @"GillSans-Light"
#define AF_FONT_GILLSANS_LIGHTITALIC @"GillSans-LightItalic"
#define AF_FONT_GILLSANS_BOLD @"GillSans-Bold"

// Gujarati Sangam MN
#define AF_FONT_GUJARATISANGAMMN_BOLD @"GujaratiSangamMN-Bold"
#define AF_FONT_GUJARATISANGAMMN @"GujaratiSangamMN"

// Gurmukhi MN
#define AF_FONT_GURMUKHIMN_BOLD @"GurmukhiMN-Bold"
#define AF_FONT_GURMUKHIMN @"GurmukhiMN"

// Heiti SC
#define AF_FONT_STHEITISC_MEDIUM @"STHeitiSC-Medium"
#define AF_FONT_STHEITISC_LIGHT @"STHeitiSC-Light"

// Heiti TC
#define AF_FONT_STHEITITC_MEDIUM @"STHeitiTC-Medium"
#define AF_FONT_STHEITITC_LIGHT @"STHeitiTC-Light"

// Helvetica
#define AF_FONT_HELVETICA_OBLIQUE @"Helvetica-Oblique"
#define AF_FONT_HELVETICA_LIGHT @"Helvetica-Light"
#define AF_FONT_HELVETICA_BOLD @"Helvetica-Bold"
#define AF_FONT_HELVETICA @"Helvetica"
#define AF_FONT_HELVETICA_BOLDOBLIQUE @"Helvetica-BoldOblique"
#define AF_FONT_HELVETICA_LIGHTOBLIQUE @"Helvetica-LightOblique"

// Helvetica Neue
#define AF_FONT_HELVETICANEUE_BOLDITALIC @"HelveticaNeue-BoldItalic"
#define AF_FONT_HELVETICANEUE_LIGHT @"HelveticaNeue-Light"
#define AF_FONT_HELVETICANEUE_ITALIC @"HelveticaNeue-Italic"
#define AF_FONT_HELVETICANEUE_ULTRALIGHTITALIC @"HelveticaNeue-UltraLightItalic"
#define AF_FONT_HELVETICANEUE_CONDENSEDBOLD @"HelveticaNeue-CondensedBold"
#define AF_FONT_HELVETICANEUE_MEDIUMITALIC @"HelveticaNeue-MediumItalic"
#define AF_FONT_HELVETICANEUE_THIN @"HelveticaNeue-Thin"
#define AF_FONT_HELVETICANEUE_MEDIUM @"HelveticaNeue-Medium"
#define AF_FONT_HELVETICANEUE_THINITALIC @"HelveticaNeue-ThinItalic"
#define AF_FONT_HELVETICANEUE_LIGHTITALIC @"HelveticaNeue-LightItalic"
#define AF_FONT_HELVETICANEUE_ULTRALIGHT @"HelveticaNeue-UltraLight"
#define AF_FONT_HELVETICANEUE_BOLD @"HelveticaNeue-Bold"
#define AF_FONT_HELVETICANEUE @"HelveticaNeue"
#define AF_FONT_HELVETICANEUE_CONDENSEDBLACK @"HelveticaNeue-CondensedBlack"

// Hiragino Kaku Gothic ProN
#define AF_FONT_HIRAKAKUPRON_W6 @"HiraKakuProN-W6"
#define AF_FONT_HIRAKAKUPRON_W3 @"HiraKakuProN-W3"

// Hiragino Mincho ProN
#define AF_FONT_HIRAMINPRON_W6 @"HiraMinProN-W6"
#define AF_FONT_HIRAMINPRON_W3 @"HiraMinProN-W3"

// Hoefler Text
#define AF_FONT_HOEFLERTEXT_REGULAR @"HoeflerText-Regular"
#define AF_FONT_HOEFLERTEXT_BLACKITALIC @"HoeflerText-BlackItalic"
#define AF_FONT_HOEFLERTEXT_ITALIC @"HoeflerText-Italic"
#define AF_FONT_HOEFLERTEXT_BLACK @"HoeflerText-Black"

// Iowan Old Style
#define AF_FONT_IOWANOLDSTYLE_BOLD @"IowanOldStyle-Bold"
#define AF_FONT_IOWANOLDSTYLE_BOLDITALIC @"IowanOldStyle-BoldItalic"
#define AF_FONT_IOWANOLDSTYLE_ITALIC @"IowanOldStyle-Italic"
#define AF_FONT_IOWANOLDSTYLE_ROMAN @"IowanOldStyle-Roman"

// Kailasa
#define AF_FONT_KAILASA @"Kailasa"
#define AF_FONT_KAILASA_BOLD @"Kailasa-Bold"

// Kannada Sangam MN
#define AF_FONT_KANNADASANGAMMN @"KannadaSangamMN"
#define AF_FONT_KANNADASANGAMMN_BOLD @"KannadaSangamMN-Bold"

// Malayalam Sangam MN
#define AF_FONT_MALAYALAMSANGAMMN @"MalayalamSangamMN"
#define AF_FONT_MALAYALAMSANGAMMN_BOLD @"MalayalamSangamMN-Bold"

// Marion
#define AF_FONT_MARION_REGULAR @"Marion-Regular"
#define AF_FONT_MARION_ITALIC @"Marion-Italic"
#define AF_FONT_MARION_BOLD @"Marion-Bold"

// Marker Felt
#define AF_FONT_MARKERFELT_THIN @"MarkerFelt-Thin"
#define AF_FONT_MARKERFELT_WIDE @"MarkerFelt-Wide"

// Menlo
#define AF_FONT_MENLO_BOLDITALIC @"Menlo-BoldItalic"
#define AF_FONT_MENLO_REGULAR @"Menlo-Regular"
#define AF_FONT_MENLO_BOLD @"Menlo-Bold"
#define AF_FONT_MENLO_ITALIC @"Menlo-Italic"

// Mishafi
#define AF_FONT_DIWANMISHAFI @"DiwanMishafi"

// Noteworthy
#define AF_FONT_NOTEWORTHY_BOLD @"Noteworthy-Bold"
#define AF_FONT_NOTEWORTHY_LIGHT @"Noteworthy-Light"

// Optima
#define AF_FONT_OPTIMA_REGULAR @"Optima-Regular"
#define AF_FONT_OPTIMA_ITALIC @"Optima-Italic"
#define AF_FONT_OPTIMA_BOLD @"Optima-Bold"
#define AF_FONT_OPTIMA_BOLDITALIC @"Optima-BoldItalic"
#define AF_FONT_OPTIMA_EXTRABLACK @"Optima-ExtraBlack"

// Oriya Sangam MN
#define AF_FONT_ORIYASANGAMMN @"OriyaSangamMN"
#define AF_FONT_ORIYASANGAMMN_BOLD @"OriyaSangamMN-Bold"

// Palatino
#define AF_FONT_PALATINO_ROMAN @"Palatino-Roman"
#define AF_FONT_PALATINO_ITALIC @"Palatino-Italic"
#define AF_FONT_PALATINO_BOLD @"Palatino-Bold"
#define AF_FONT_PALATINO_BOLDITALIC @"Palatino-BoldItalic"

// Papyrus
#define AF_FONT_PAPYRUS_CONDENSED @"Papyrus-Condensed"
#define AF_FONT_PAPYRUS @"Papyrus"

// Party LET
#define AF_FONT_PARTYLETPLAIN @"PartyLetPlain"

// Savoye LET
#define AF_FONT_SAVOYELETPLAIN @"SavoyeLetPlain"

// Sinhala Sangam MN
#define AF_FONT_SINHALASANGAMMN @"SinhalaSangamMN"
#define AF_FONT_SINHALASANGAMMN_BOLD @"SinhalaSangamMN-Bold"

// Snell Roundhand
#define AF_FONT_SNELLROUNDHAND_BLACK @"SnellRoundhand-Black"
#define AF_FONT_SNELLROUNDHAND_BOLD @"SnellRoundhand-Bold"
#define AF_FONT_SNELLROUNDHAND @"SnellRoundhand"

// Superclarendon
#define AF_FONT_SUPERCLARENDON_REGULAR @"Superclarendon-Regular"
#define AF_FONT_SUPERCLARENDON_BOLDITALIC @"Superclarendon-BoldItalic"
#define AF_FONT_SUPERCLARENDON_LIGHT @"Superclarendon-Light"
#define AF_FONT_SUPERCLARENDON_BLACKITALIC @"Superclarendon-BlackItalic"
#define AF_FONT_SUPERCLARENDON_ITALIC @"Superclarendon-Italic"
#define AF_FONT_SUPERCLARENDON_LIGHTITALIC @"Superclarendon-LightItalic"
#define AF_FONT_SUPERCLARENDON_BOLD @"Superclarendon-Bold"
#define AF_FONT_SUPERCLARENDON_BLACK @"Superclarendon-Black"

// Symbol
#define AF_FONT_SYMBOL @"Symbol"

// Tamil Sangam MN
#define AF_FONT_TAMILSANGAMMN @"TamilSangamMN"
#define AF_FONT_TAMILSANGAMMN_BOLD @"TamilSangamMN-Bold"

// Telugu Sangam MN
#define AF_FONT_TELUGUSANGAMMN @"TeluguSangamMN"
#define AF_FONT_TELUGUSANGAMMN_BOLD @"TeluguSangamMN-Bold"

// Thonburi
#define AF_FONT_THONBURI_BOLD @"Thonburi-Bold"
#define AF_FONT_THONBURI @"Thonburi"
#define AF_FONT_THONBURI_LIGHT @"Thonburi-Light"

// Times New Roman
#define AF_FONT_TIMESNEWROMANPS_BOLDITALICMT @"TimesNewRomanPS-BoldItalicMT"
#define AF_FONT_TIMESNEWROMANPSMT @"TimesNewRomanPSMT"
#define AF_FONT_TIMESNEWROMANPS_BOLDMT @"TimesNewRomanPS-BoldMT"
#define AF_FONT_TIMESNEWROMANPS_ITALICMT @"TimesNewRomanPS-ItalicMT"

// Trebuchet MS
#define AF_FONT_TREBUCHET_BOLDITALIC @"Trebuchet-BoldItalic"
#define AF_FONT_TREBUCHETMS @"TrebuchetMS"
#define AF_FONT_TREBUCHETMS_BOLD @"TrebuchetMS-Bold"
#define AF_FONT_TREBUCHETMS_ITALIC @"TrebuchetMS-Italic"

// Verdana
#define AF_FONT_VERDANA_BOLDITALIC @"Verdana-BoldItalic"
#define AF_FONT_VERDANA_ITALIC @"Verdana-Italic"
#define AF_FONT_VERDANA @"Verdana"
#define AF_FONT_VERDANA_BOLD @"Verdana-Bold"

// Zapf Dingbats
#define AF_FONT_ZAPFDINGBATSITC @"ZapfDingbatsITC"

// Zapfino
#define AF_FONT_ZAPFINO @"Zapfino"

#endif