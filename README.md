Copyright (C) 2011 The Android Open Source Project
==================================================

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Description:
EF52S Platform Source for AOSP 4.1.2 - android-4.1.2_r1 Branch

Build requirements:
* branch android-4.1.2_r1

How to Build Platform:

1. Get Android Open Source.
: version info - Android Jelly Bean 4.1.2 - android-4.1.2_r1 Branch
( Download Site : http://source.android.com )

2. Overwrite modules that you want to build.

- \external\bluetooth
- \external\dbus
- \external\webkit
- \external\wpa_supplicant_8
- \hardware\qcom

3. Run following scripts to build android
a) . build/envsetup.sh
b) lunch full_ef52s-userdebug
c) make -j8
