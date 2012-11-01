#import "DeploymentPropertiesController.h"
#import "NSObject+AssociateDisposable.h"
#import "RACSubscribable+Extensions.h"

@interface DeploymentPropertiesController ()

@property (nonatomic, strong) FoundryService *service;

@end

@implementation DeploymentPropertiesController

+ (DeploymentPropertiesController *)deploymentControllerWithDeployment:(Deployment *)deployment {
    DeploymentPropertiesController *result = [[DeploymentPropertiesController alloc] init];
    result.bindingObject = deployment;
    result.service = [[FoundryService alloc] initWithEndpoint:[FoundryEndpoint endpointWithTarget:deployment.target]];
    return result;
}

+ (DeploymentPropertiesController *)deploymentControllerWithApp:(FoundryApp *)app service:(FoundryService *)service {
    DeploymentPropertiesController *result = [[DeploymentPropertiesController alloc] init];
    result.bindingObject = app;
    result.service = service;
    return result;
}

@synthesize objectController, deploymentPropertiesView, wizardController, title, commitButtonTitle, service, bindingObject;

- (id)init {
    if (self = [super initWithNibName:@"DeploymentPropertiesView" bundle:[NSBundle mainBundle]]) {
        self.commitButtonTitle = @"Done";
    }
    return self;
}

#define ThorDeploymentPropertiesControllerErrorDomain @"ThorDeploymentPropertiesControllerErrorDomain"
#define ThorAppAlreadyExistsErrorCode 0xabcdbeef

- (RACSubscribable *)ensureServiceDoesNotHaveAppWithName:(NSString *)name {
    return [RACSubscribable createSubscribable:^RACDisposable *(id<RACSubscriber> subscriber) {
        return [[service getAppWithName:name]
                subscribeNext:^ (id i) {
                    [subscriber sendError:[NSError errorWithDomain:ThorDeploymentPropertiesControllerErrorDomain code:ThorAppAlreadyExistsErrorCode userInfo:@{
                            NSLocalizedDescriptionKey : [NSString stringWithFormat:@"An app named %@ already exists on the host.", name]
                    }]];
                }
                error:^ (NSError *error) {
                    [subscriber sendNext:[NSNull null]];
                    [subscriber sendCompleted];
                }
                completed:^ {
                }];
    }];
}

- (void)commitWizardPanel {
    [objectController commitEditing];
    
    // TODO display spinner while waiting.
    self.wizardController.commitButtonEnabled = NO;
    
    FoundryApp *app = nil;
    Deployment *deployment = nil;
    RACSubscribable *subscribable;
    
    if ([bindingObject isKindOfClass:[Deployment class]]) {
        deployment = (Deployment *)bindingObject;
        app = [FoundryApp appWithDeployment:deployment];
        
        if (deployment.managedObjectContext)
            subscribable = [service updateApp:app];
        else {
            subscribable = [[self ensureServiceDoesNotHaveAppWithName:app.name] continueWith:[service createApp:app]];
            [[ThorBackend sharedContext] insertObject:deployment];
        }
    }
    else {
        app = (FoundryApp *)bindingObject;
        subscribable = [service updateApp:app];
    }
        
    self.associatedDisposable = [subscribable subscribeNext:^ (id n) {
        NSLog(@"%@", n);
    } error:^ (NSError *error) {
        [NSApp presentError:error];
        self.wizardController.commitButtonEnabled = YES;
    } completed:^ {
        NSError *error = nil;
        if (![[ThorBackend sharedContext] save:&error]) {
            [NSApp presentError:error];
            NSLog(@"There was an error! %@", [error.userInfo objectForKey:NSLocalizedDescriptionKey]);
        }
        [self.wizardController dismissWithReturnCode:NSOKButton];
    }];
}

- (void)rollbackWizardPanel {
    [[ThorBackend sharedContext] rollback];
}

@end
