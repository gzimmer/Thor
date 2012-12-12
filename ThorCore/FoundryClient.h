#import <ReactiveCocoa/ReactiveCocoa.h>

@interface RestEndpoint : NSObject

- (RACSubscribable *)requestWithHost:(NSString *)host method:(NSString *)method path:(NSString *)path headers:(NSDictionary *)headers body:(id)body;

@end

@interface FoundryEndpoint : NSObject

@property (nonatomic, copy) NSString *hostname, *email, *password;

// result is parsed JSON of response body
- (RACSubscribable *)authenticatedRequestWithMethod:(NSString *)method path:(NSString *)path headers:(NSDictionary *)headers body:(id)body;

- (RACSubscribable *)verifyCredentials;

@end

typedef enum {
    FoundryAppStateStarted,
    FoundryAppStateStopped,
    FoundryAppStateUnknown
} FoundryAppState;

typedef enum {
    FoundryAppMemoryAmountUnknown = -1,
    FoundryAppMemoryAmount64 = 0,
    FoundryAppMemoryAmount128 = 1,
    FoundryAppMemoryAmount256 = 2,
    FoundryAppMemoryAmount512 = 3,
    FoundryAppMemoryAmount1024 = 4,
    FoundryAppMemoryAmount2048 = 5,
} FoundryAppMemoryAmount;

NSUInteger FoundryAppMemoryAmountIntegerFromAmount(FoundryAppMemoryAmount amount);
FoundryAppMemoryAmount FoundryAppMemoryAmountAmountFromInteger(NSUInteger integer);
NSString * FoundryAppMemoryAmountStringFromAmount(FoundryAppMemoryAmount amount);

@interface FoundryApp : NSObject

@property (nonatomic, copy) NSString *name, *stagingFramework, *stagingRuntime;
@property (nonatomic, copy) NSArray *uris, *services;
@property (nonatomic, assign) NSUInteger
    instances,
    memory,
    disk;
@property (nonatomic, assign) FoundryAppState state;

+ (FoundryApp *)appWithDictionary:(NSDictionary *)appDict;
- (NSDictionary *)dictionaryRepresentation;

@end

@interface FoundryAppInstanceStats : NSObject

@property (nonatomic, assign) bool isDown;
@property (nonatomic, copy) NSString *ID, *host;
@property (nonatomic, assign) NSInteger port, disk;
@property (nonatomic, assign) float cpu, memory, uptime;

+ (FoundryAppInstanceStats *)instantsStatsWithID:(NSString *)lID dictionary:(NSDictionary *)dictionary;

@end

@interface FoundrySlug : NSObject

@property (nonatomic, strong) NSURL *zipFile;
@property (nonatomic, copy) NSArray *manifiest;

@end

NSString *DetectFrameworkFromPath(NSURL *rootURL);

@protocol SlugService <NSObject>

// this is a potentially long-running operation that involves
// recursively traversing the file system and generating
// checksums
- (id)createManifestFromPath:(NSURL *)rootURL;

// this is a potentially long-running operation that creates
// a zip archive on disk containing all the files in the manifest.
// you should delete the file when you're done with it.
- (NSURL *)createSlugFromManifest:(id)manifest path:(NSURL *)rootURL;

// per thread: http://lists.apple.com/archives/macnetworkprog/2007/May/msg00051.html
//
// we're gonna write out the multipart message to a temp file,
// post a stream over that temp file, then delete it when we're done.
//
// not the world's most efficient approach, but should work much more
// predictably than trying to subclass NSInputStream and dealing
// with undocumented private API weirdness.
- (BOOL)createMultipartMessageFromManifest:(id)manifest slug:(NSURL *)slugFile outMessagePath:(NSString **)outMessagePath outContentLength:(NSNumber **)outContentLength outBoundary:(NSString **)outBoundary error:(NSError **)error;

@end

@interface SlugService : NSObject <SlugService>

@end

@interface FoundryServiceInfo : NSObject

@property (nonatomic, copy) NSString *description, *vendor, *version, *type;

@end

@interface FoundryService : NSObject

@property (nonatomic, copy) NSString *name, *vendor, *version, *type;

@end

typedef enum {
    FoundryPushStageBuildingManifest,
    FoundryPushStageCompressingFiles,
    FoundryPushStageWritingPackage,
    FoundryPushStageUploadingPackage,
    FoundryPushStageFinished,
} FoundryPushStage;

NSString *FoundryPushStageString(FoundryPushStage stage);

@protocol FoundryClient <NSObject>

- (RACSubscribable *)getApps; // NSArray of FoundryApp
- (RACSubscribable *)getAppWithName:(NSString *)name; // FoundryApp
- (RACSubscribable *)getStatsForAppWithName:(NSString *)name; // NSArray of FoundryAppInstanceStats

- (RACSubscribable *)createApp:(FoundryApp *)app;
- (RACSubscribable *)updateApp:(FoundryApp *)app;
- (RACSubscribable *)deleteAppWithName:(NSString *)name;

// subscription is a long-running operation. subscribe on background scheduler.
- (RACSubscribable *)pushAppWithName:(NSString *)name fromLocalPath:(NSString *)localPath;

- (RACSubscribable *)getServicesInfo; // NSArray of FoundryServiceInfo
- (RACSubscribable *)getServices; // NSArray of FoundryService
- (RACSubscribable *)getServiceWithName:(NSString *)name;
- (RACSubscribable *)createService:(FoundryService *)service;
- (RACSubscribable *)deleteServiceWithName:(NSString *)name;

@end

extern NSString *FoundryClientErrorDomain;

const static NSInteger FoundryClientInvalidCredentials = 1;

@interface FoundryClient : NSObject <FoundryClient>

@property (nonatomic, strong) FoundryEndpoint *endpoint;

- (id)initWithEndpoint:(FoundryEndpoint *)endpoint;

@end
