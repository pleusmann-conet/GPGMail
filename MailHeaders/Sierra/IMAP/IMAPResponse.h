//
//     Generated by class-dump 3.5 (64 bit).
//
//     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2013 by Steve Nygard.
//

//#import "NSObject.h"

@class NSError, NSString;

@interface IMAPResponse : NSObject
{
    BOOL _wasHandled;	// 8 = 0x8
    NSString *_tag;	// 16 = 0x10
    NSError *_error;	// 24 = 0x18
}

+ (BOOL)handlesResponseWithName:(const char *)arg1 ofLength:(unsigned long long)arg2;	// IMP=0x00000000000589ce
+ (id)newIMAPResponseWithConnection:(id)arg1 error:(id *)arg2;	// IMP=0x000000000005881f
@property(retain, nonatomic) NSError *error; // @synthesize error=_error;
@property(copy, nonatomic) NSString *tag; // @synthesize tag=_tag;
@property(nonatomic) BOOL wasHandled; // @synthesize wasHandled=_wasHandled;
- (void).cxx_destruct;	// IMP=0x0000000000058b5e
- (id)description;	// IMP=0x0000000000058a0a
@property(readonly, nonatomic) BOOL isUntagged;

@end
