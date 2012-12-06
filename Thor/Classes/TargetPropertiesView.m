#import "TargetPropertiesView.h"
#import "CollectionView.h"

@implementation TargetPropertiesView

@synthesize hostnameField, hostnameLabel, hostnameHidden = _hostnameHidden;

- (void)setHostnameHidden:(BOOL)value {
    _hostnameHidden = value;
    hostnameLabel.hidden = value;
    hostnameField.hidden = value;
}

- (NSSize)intrinsicContentSize {
   return NSMakeSize(480, 124);
}

@end
