AFMacros
=============

AFMacros brings some handy macros for validation and accessing of common directories or info-plist values

## Example

``` objective-c
    CoreTextLabel * label = (id)@"String"; // Assign NSString to label
    if (VALID(label, CoreTextLabel)) 
    {
        ZLog(@"%p is valid", label);
    }
    else
    {
        ZLog(@"%p is not valid", label);
    }
```

## Install

Add AFMacros pod to your [Podfile](https://github.com/CocoaPods/CocoaPods/wiki/A-Podfile).

```
$ vim Podfile
```

```ruby
platform :ios, '5.0'
pod 'AFMacros', :head
```

And then you [install the dependencies](https://github.com/CocoaPods/CocoaPods/wiki/Creating-a-project-that-uses-CocoaPods) in your project.

```
$ pod install
```

Remember to always open the Xcode workspace instead of the project file when you're building.

```
$ open App.xcworkspace
```

## Requirements

AFMacros 1.0 and higher requires iOS 5.0 and above.

### ARC

AFMacros uses ARC.

If you are using AFMacros in your non-arc project, you will need to set a `-fobjc-arc` compiler flag on all of the AFMacros source files.

To set a compiler flag in Xcode, go to your active target and select the "Build Phases" tab. Now select all AFMacros source files, press Enter, insert `-fobjc-arc` or `-fno-objc-arc` and then "Done" to enable or disable ARC for AFMacros.

## Credits

AFMacros was created by [Daniel Kuhnke](https://github.com/appfarms/) for [appfarms GmbH & Co. KG](http://www.appfarms.com)


## License

AFMacros is available under the MIT license. See the LICENSE file for more info.