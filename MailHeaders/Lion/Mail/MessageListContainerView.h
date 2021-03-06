/*
 *     Generated by class-dump 3.3.3 (64 bit).
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2010 by Steve Nygard.
 */

#import "NSView.h"

@class MessageViewer, NSTableHeaderView, NSTableView, RichMessageListSortView;

@interface MessageListContainerView : NSView
{
    NSTableView *_messageListTableView;
    MessageViewer *_messageViewer;
    NSTableHeaderView *_previousHeaderView;
    RichMessageListSortView *_sortView;
    BOOL _isRichMessageList;
}

- (void)showSortView:(BOOL)arg1;
@property(nonatomic) BOOL isRichMessageList;
- (void)dealloc;
- (id)accessibilityAttributeNames;
- (id)accessibilityAttributeValue:(id)arg1;
- (BOOL)accessibilityIsAttributeSettable:(id)arg1;
- (BOOL)accessibilityIsIgnored;
@property(retain) RichMessageListSortView *sortView; // @synthesize sortView=_sortView;
@property NSTableView *messageListTableView; // @synthesize messageListTableView=_messageListTableView;

@end

