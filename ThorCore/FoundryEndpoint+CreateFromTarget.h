#import "FoundryClient.h"
#import "ThorCore.h"

@interface FoundryEndpoint (CreateFromTarget)

+ (FoundryEndpoint *)endpointWithTarget:(Target *)target;

@end