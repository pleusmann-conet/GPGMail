/* GPGMailBundle.h created by dave on Thu 29-Jun-2000 */

/*
 * Copyright (c) 2000-2011, GPGTools Project Team <gpgtools-devel@lists.gpgtools.org>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of GPGTools Project Team nor the names of GPGMail
 *       contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE GPGTools Project Team ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE GPGTools Project Team BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <MVMailBundle.h>

#import <CoreFoundation/CoreFoundation.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSMapTable.h>
#import <AppKit/NSNibDeclarations.h>
#import <Libmacgpg/Libmacgpg.h>

@class MessageHeaders;
@class NSMenu;
@class NSMutableDictionary;
@class Message;
@class SUUpdater;


// The following strings are used as toolbarItem identifiers and userDefault keys (value is the position index)
extern NSString *GPGAuthenticateMessageToolbarItemIdentifier;
extern NSString *GPGDecryptMessageToolbarItemIdentifier;
extern NSString *GPGSignMessageToolbarItemIdentifier;
extern NSString *GPGEncryptMessageToolbarItemIdentifier;

extern NSString *GPGKeyListWasInvalidatedNotification;
extern NSString *GPGPreferencesDidChangeNotification;

extern NSString *GPGMailException;
extern NSString *GPGKeyGroupsChangedNotification;

extern NSString *GPGMissingKeysNotification;
// Notification object can be anything; posted when misses key on message verification or message encryption
// UserInfo: 'fingerprints' = NSArray of fingerprints as NSStrings,
//           'emails' = NSArray of email addresses as NSStrings

#define GPGENCRYPTION_MENU_ITEMS_COUNT (5)


typedef enum {
	GPGAutomaticMailFormat,
	GPGLegacyPGPMailFormat,
	GPGOpenPGPMailFormat,
	GPGSMIMEMailFormat
} GPGMailFormat;


enum {
	GPGMailDebug_SaveInputDataMask = 0x0001
};

typedef void (^gpgmail_decryption_task_t)(void);

@interface GPGMailBundle : NSObject <NSToolbarDelegate> {
	IBOutlet NSMenuItem *decryptMenuItem;
	IBOutlet NSMenuItem *authenticateMenuItem;
	IBOutlet NSMenuItem *encryptsNewMessageMenuItem;
	IBOutlet NSMenuItem *signsNewMessageMenuItem;
	IBOutlet NSMenuItem *personalKeysMenuItem;
	IBOutlet NSMenuItem *choosePublicKeysMenuItem;
	IBOutlet NSMenuItem *automaticPublicKeysMenuItem;
	IBOutlet NSMenuItem *usesOnlyOpenPGPStyleMenuItem;
	IBOutlet NSMenuItem *symetricEncryptionMenuItem;
	GPGKey *defaultKey;
	NSMutableDictionary *realToolbarDelegates;
	NSMutableDictionary *additionalToolbarItemIdentifiersPerToolbarIdentifier;
	NSArray *cachedPersonalKeys;
	NSArray *cachedPublicKeys;
	NSMapTable *cachedUserIDsPerKey;
	NSArray *cachedKeyGroups;
#if 0
	IBOutlet NSMenu *PGPMenu;                                 // Do not remove that line! (kludge for IB)
	IBOutlet NSMenu *PGPViewMenu;                             // Do not remove that line! (kludge for IB)
#endif
	NSMenuItem *pgpMenuItem;
	NSMenuItem *pgpViewMenuItem;
	IBOutlet NSMenuItem *allUserIDsMenuItem;
	NSDictionary *locale;
    
    NSSet *cachedPersonalGPGKeys;
    NSSet *cachedPublicGPGKeys;
    NSSet *cachedGPGKeys;
    
    // A serial queue which makes sure that only one pinentry
    // password request is run at once.
    dispatch_queue_t decryptionQueue;
    // Map which uses a fingerprint to lookup a personal key.
    NSDictionary *_cachedPersonalGPGKeysByFingerprint;
    // Map which uses a fingerprint to lookup a public key.
    NSDictionary *_cachedPublicGPGKeysByFingerprint;
    // Map which uses the email address to lookup a personal key.
    NSDictionary *_cachedPersonalGPGKeysByEmail;
    // Map which uses the email address to lookup a public key.
    NSDictionary *_cachedPublicGPGKeysByEmail;
	
	SUUpdater *updater;
}

+ (id)sharedInstance;
// Install all methods used by GPGMail. 
+ (void)_installGPGMail;
// Load all necessary images.
+ (void)_loadImages;
// Install the Sparkle Updater.
+ (void)_installSparkleUpdater;
// Returns the bundle version.
+ (NSString *)bundleVersion;
// Returns the string used for the x-pgp-agent message header.
+ (NSString *)agentHeader;
- (void)workspaceDidMount:(NSNotification *)notification;
- (void)workspaceDidUnmount:(NSNotification *)notification;
- (void)setAlwaysSignMessages:(BOOL)flag;
- (BOOL)alwaysSignMessages;
- (void)setAlwaysEncryptMessages:(BOOL)flag;
- (BOOL)alwaysEncryptMessages;
- (void)setEncryptMessagesWhenPossible:(BOOL)flag;
- (BOOL)encryptMessagesWhenPossible;
- (void)setDefaultKey:(GPGKey *)key;
- (GPGKey *)defaultKey;
- (void)setRemembersPassphrasesDuringSession:(BOOL)flag;
- (BOOL)remembersPassphrasesDuringSession;
- (void)setDecryptsMessagesAutomatically:(BOOL)flag;
- (BOOL)decryptsMessagesAutomatically;
- (void)setAuthenticatesMessagesAutomatically:(BOOL)flag;
- (BOOL)authenticatesMessagesAutomatically;
- (void)setDisplaysButtonsInComposeWindow:(BOOL)flag;
- (BOOL)displaysButtonsInComposeWindow;
- (void)setEncryptsToSelf:(BOOL)flag;
- (BOOL)encryptsToSelf;
 - (void) setUsesKeychain:(BOOL)flag;
 - (BOOL) usesKeychain;
@property BOOL usesKeychain;
- (void)setDecryptsOnlyUnreadMessagesAutomatically:(BOOL)flag;
- (BOOL)decryptsOnlyUnreadMessagesAutomatically;
- (void)setAuthenticatesOnlyUnreadMessagesAutomatically:(BOOL)flag;
- (BOOL)authenticatesOnlyUnreadMessagesAutomatically;
- (void)setUsesOnlyOpenPGPStyle:(BOOL)flag;
- (BOOL)usesOnlyOpenPGPStyle;
- (void)setUsesEncapsulatedSignature:(BOOL)flag;
- (BOOL)usesEncapsulatedSignature;
- (void)setUsesOnlyOpenPGPStyle:(BOOL)flag;
- (BOOL)usesOnlyOpenPGPStyle;
- (void)setUsesEncapsulatedSignature:(BOOL)flag;
- (BOOL)usesEncapsulatedSignature;
- (void)setUsesBCCRecipients:(BOOL)flag;
- (BOOL)usesBCCRecipients;
- (void)setTrustsAllKeys:(BOOL)flag;
- (BOOL)trustsAllKeys;
- (void)setAutomaticallyShowsAllInfo:(BOOL)flag;
- (BOOL)automaticallyShowsAllInfo;
- (void)setPassphraseFlushTimeout:(NSTimeInterval)timeout;
- (NSTimeInterval)passphraseFlushTimeout;
- (void)setChoosesPersonalKeyAccordingToAccount:(BOOL)flag;
- (BOOL)choosesPersonalKeyAccordingToAccount;
- (void)setButtonsShowState:(BOOL)flag;
- (BOOL)buttonsShowState;
- (void)setSignWhenEncrypting:(BOOL)flag;
- (BOOL)signWhenEncrypting;
- (NSArray *)allDisplayedKeyIdentifiers;
- (void)setDisplayedKeyIdentifiers:(NSArray *)keyIdentifiers;
- (NSArray *)displayedKeyIdentifiers;
- (void)setDisplaysAllUserIDs:(BOOL)flag;
- (BOOL)displaysAllUserIDs;
- (void)setFiltersOutUnusableKeys:(BOOL)flag;
- (BOOL)filtersOutUnusableKeys;
- (void)setShowsPassphrase:(BOOL)flag;
- (BOOL)showsPassphrase;
- (void)setLineWrappingLength:(int)value;
- (long)lineWrappingLength;
- (void)setIgnoresPGPPresence:(BOOL)flag;
- (BOOL)ignoresPGPPresence;
- (void)setRefreshesKeysOnVolumeMount:(BOOL)flag;
- (BOOL)refreshesKeysOnVolumeMount;
- (void)setDisablesSMIME:(BOOL)flag;
- (BOOL)disablesSMIME;
- (void)setWarnedAboutMissingPrivateKeys:(BOOL)flag;
- (BOOL)warnedAboutMissingPrivateKeys;
- (void)setEncryptsReplyToEncryptedMessage:(BOOL)flag;
- (BOOL)encryptsReplyToEncryptedMessage;
- (void)setSignsReplyToSignedMessage:(BOOL)flag;
- (BOOL)signsReplyToSignedMessage;
- (void)setUsesABEntriesRules:(BOOL)flag;
- (BOOL)usesABEntriesRules;
- (void)setAddsCustomHeaders:(BOOL)flag;
- (BOOL)addsCustomHeaders;

@property (assign) NSMenuItem *decryptMenuItem;
@property (assign) NSMenuItem *authenticateMenuItem;
@property (assign) NSMenuItem *encryptsNewMessageMenuItem;
@property (assign) NSMenuItem *signsNewMessageMenuItem;
@property (assign) NSMenuItem *personalKeysMenuItem;
@property (assign) NSMenuItem *choosePublicKeysMenuItem;
@property (assign) NSMenuItem *automaticPublicKeysMenuItem;
@property (assign) NSMenuItem *symetricEncryptionMenuItem;
@property (assign) NSMenuItem *usesOnlyOpenPGPStyleMenuItem;
@property (assign) NSMenuItem *pgpMenuItem;
@property (assign) NSMenuItem *pgpViewMenuItem;
@property (assign) NSMenuItem *allUserIDsMenuItem;

@property (nonatomic, retain) NSSet *cachedPersonalGPGKeys;
@property (nonatomic, retain) NSSet *cachedPublicGPGKeys;
@property (nonatomic, retain) NSSet *cachedGPGKeys;

@property (nonatomic, readonly, retain) SUUpdater *updater;


- (NSString *)version;
- (NSString *)versionDescription;
+ (BOOL)gpgMailWorks;
- (BOOL)gpgMailWorks;

- (void)mailTo:(id)sender;

- (NSArray *)keysForSearchPatterns:(NSArray *)searchPatterns attributeName:(NSString *)attributeKeyPath secretKeys:(BOOL)secretKeys;
- (NSSet *)personalKeys;
- (NSSet *)publicKeys;
- (NSArray *)secondaryUserIDsForKey:(GPGKey *)key;
- (NSArray *)keyGroups;
- (IBAction)gpgReloadPGPKeys:(id)sender;

- (IBAction)gpgToggleEncryptionForNewMessage:(id)sender;
- (IBAction)gpgToggleSignatureForNewMessage:(id)sender;
- (IBAction)gpgChoosePublicKeys:(id)sender;
- (IBAction)gpgChoosePersonalKey:(id)sender;
- (IBAction)gpgChoosePublicKey:(id)sender;
- (IBAction)gpgToggleAutomaticPublicKeysChoice:(id)sender;
- (IBAction)gpgToggleSymetricEncryption:(id)sender;
- (IBAction)gpgToggleUsesOnlyOpenPGPStyle:(id)sender;
- (IBAction)gpgToggleDisplayAllUserIDs:(id)sender;
- (IBAction)gpgToggleShowKeyInformation:(id)sender;

- (NSString *)menuItemTitleForKey:(GPGKey *)key;
- (NSString *)menuItemTitleForUserID:(GPGUserID *)userID indent:(unsigned)indent;

- (void)refreshKeyIdentifiersDisplayInMenu:(NSMenu *)menu;

- (BOOL)canKeyBeUsedForEncryption:(GPGKey *)key;
- (BOOL)canKeyBeUsedForSigning:(GPGKey *)key;
- (BOOL)canUserIDBeUsed:(GPGUserID *)userID;
- (GPGKey *)publicKeyForSecretKey:(GPGKey *)secretKey;

//- (NSString *)descriptionForError:(GPGError)error;
- (NSString *)descriptionForException:(NSException *)exception;

//- (NSString *)hashAlgorithmDescription:(GPGHashAlgorithm)algorithm;
//- (NSString *)gpgErrorDescription:(GPGError)error;
//- (GPGErrorCode)gpgErrorCodeFromError:(GPGError)error;
//- (GPGErrorSource)gpgErrorSourceFromError:(GPGError)error;
//- (GPGError)gpgMakeErrorWithSource:(GPGErrorSource) source code:(GPGErrorCode)code;

- (id)locale;

- (NSSet *)loadGPGKeys;
- (NSSet *)allGPGKeys;
- (NSMutableSet *)publicKeyListForAddresses:(NSArray *)recipients;
- (BOOL)canEncryptMessagesToAddress:(NSString *)address;
- (BOOL)canSignMessagesFromAddress:(NSString *)address;
- (NSMutableSet *)signingKeyListForAddresses:(NSArray *)senders;

// Allows to schedule decryption tasks which will block as
// long as a second decryption task is running, but shouldn't
// block the main thread.
- (void)addDecryptionTask:(gpgmail_decryption_task_t)task;

@end

@interface GPGMailBundle (AddressGroups)

- (void)synchronizeKeyGroupsWithAddressBookGroups;

@end