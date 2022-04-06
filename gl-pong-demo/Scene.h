//
//  Scene.h
//  gl-pong-demo
//
//  Created by Jake Pauls on 2022-03-23.
//

#ifndef Scene_h
#define Scene_h

#import <GLKit/GLKit.h>

@interface Scene : NSObject

@property float playerPaddleXInput;
@property int playerScore;
@property int enemyScore;

- (void)setup:(GLKView *)view;
- (void)loadModels;
- (void)update;
- (void)draw;

+ (const char*)RetrieveFilePathByName:(const char*)fileName;

@end

#endif /* Scene_h */
