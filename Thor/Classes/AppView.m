#import "AppView.h"
#import "BoxGroupView.h"

@interface AppSettingsView : NSView

@end

@implementation AppSettingsView

- (NSSize)intrinsicContentSize {
    return NSMakeSize(NSViewNoInstrinsicMetric, 135);
}

@end

@implementation AppView

@synthesize scrollView, deploymentsGrid, deploymentsBox, settingsBox, settingsView;

- (void)layout {
    [BoxGroupView layoutInBounds:self.bounds scrollView:scrollView box1:settingsBox boxContent1:settingsView box2:deploymentsBox boxContent2:deploymentsGrid];
    
    [super layout];
}

@end
