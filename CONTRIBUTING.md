<!--
Copyright (c) 2021-2026 The Khronos Group Inc.
SPDX-License-Identifier: Apache-2.0
-->

# Contribution Guidelines

Contributions to the libraries hosted in this repository are welcome.

## Reporting problems and making suggestions

If you find or suspect any bug, please file [an
issue](https://github.com/KhronosGroup/libclcxx/issues/new) to discuss the
details.

You can also file an issue to:

- suggest improvementsg;
- propose new functionality or an improvement to existing functionality.

## Contribute Changes

If you would like to contribute changes please submit a PR for review. Once it
is reviewed the changes will be merged into the repository.

When contributing non-trivial changes (e.g. new feature or large refactoring) it
is advisable to first discuss your contribution by filing an issue or using
other channels prior to creating a PR.

## Acceptance Conditions

Changes can be reviewed by any experienced contributor. Please, use `git
blame`/`git log` on the sources to find relevant contributors.

## Contributor License Agreement (CLA)

When you propose a pull request on libclcxx you must execute the [Apache-2.0
WITH LLVM Contributor License
Agreement](https://cla-assistant.io/KhronosGroup/libclcxx), to confirm you own
your work and are granting Khronos the necessary permissions to redistribute it
under our licenses.

A bot will automatically request that you complete this when you open your first
PR on the repository.

## AI-Assisted Contributions

By submitting a Contribution to this repository, you additionally represent
that, to the extent any of Your Contributions were developed with the assistance
of artificial intelligence tools or AI-generated code, You have exercised
sufficient review, judgment, and creative direction over such tools and
resulting material to reasonably consider it Your original creation, and You are
not aware of any third-party license, intellectual property claim, or other
restriction arising from such use that is associated with any part of Your
Contribution or use thereof.

## Contributions under MIT CLA

Prior to the adoption of the Apache 2.0 with LLVM Exception CLA, this repository
used an MIT CLA. The following commits were contributed under the MIT CLA. All
subsequent contributions are made under the Apache 2.0 with LLVM Exception CLA.

| Commit                                                                                                 | GitHub ID | Commit Date          | CLA Signed At            | Message                                                                                   |
| ------------------------------------------------------------------------------------------------------ | --------- | -------------------- | ------------------------ | ----------------------------------------------------------------------------------------- |
| [a6899337dd](https://github.com/KhronosGroup/libclcxx/commit/a6899337dd251f4cf836c7c41b410671fdc55731) | @ish222   | 2021-08-26T15:17:34Z | 2021-06-25T11:26:06.183Z | Added custom vector type traits, tests and updated documentation (#57)                    |
| [41c5fde2a2](https://github.com/KhronosGroup/libclcxx/commit/41c5fde2a2d3d91ab2aa8d422f85f8be2912d550) | @ish222   | 2021-08-24T18:29:10Z | 2021-06-25T11:26:06.183Z | Add CI via Github actions (#51)                                                           |
| [6276edbaa2](https://github.com/KhronosGroup/libclcxx/commit/6276edbaa2955e06c73be2c905d38db608612cf7) | @ish222   | 2021-08-20T09:48:43Z | 2021-06-25T11:26:06.183Z | Comment out bugged tests (#55)                                                            |
| [adcaba2ab0](https://github.com/KhronosGroup/libclcxx/commit/adcaba2ab0e3988bfe6381d1b0a7e8345faf250b) | @ish222   | 2021-08-17T11:52:03Z | 2021-06-25T11:26:06.183Z | Change target all to build-all (#54)                                                      |
| [b3d297c914](https://github.com/KhronosGroup/libclcxx/commit/b3d297c9143d14ef26466c6721e78a1b098e1b6a) | @ish222   | 2021-08-17T11:29:16Z | 2021-06-25T11:26:06.183Z | Add Doxygen documentation (#44)                                                           |
| [9852cd6b67](https://github.com/KhronosGroup/libclcxx/commit/9852cd6b67c906bb74b57690bd0dfdf46b244872) | @ish222   | 2021-08-17T10:45:08Z | 2021-06-25T11:26:06.183Z | Added target all and updated documentation (#49)                                          |
| [c4d22fb39d](https://github.com/KhronosGroup/libclcxx/commit/c4d22fb39d5082fb397660286a970f8eea704d30) | @ish222   | 2021-08-10T21:32:00Z | 2021-06-25T11:26:06.183Z | Change CMake target clean to clean-all (#48)                                              |
| [91282f8537](https://github.com/KhronosGroup/libclcxx/commit/91282f85370442082e22c696ec5fea0f2aa70065) | @ish222   | 2021-08-09T09:51:34Z | 2021-06-25T11:26:06.183Z | Enabled remove_reference and remove_pointer type traits and imporved on other tests (#46) |
| [5e6d434935](https://github.com/KhronosGroup/libclcxx/commit/5e6d434935bce871cf374061b85359774afc1ab3) | @ish222   | 2021-08-09T09:49:43Z | 2021-06-25T11:26:06.183Z | Add CMake integration for automatic building (#42)                                        |
| [782e53b5d3](https://github.com/KhronosGroup/libclcxx/commit/782e53b5d3911eca538c71501c771338b690e39e) | @ish222   | 2021-08-06T09:31:12Z | 2021-06-25T11:26:06.183Z | Remove whole file clang guard and only add to test causing bug in clang-12 (#43)          |
| [a4afaaf411](https://github.com/KhronosGroup/libclcxx/commit/a4afaaf411b8200779d05c4e615fd8664d6e49ee) | @ish222   | 2021-08-06T09:29:38Z | 2021-06-25T11:26:06.183Z | Added clang version guard for tests failing in clang-12 (#45)                             |
| [4d39445145](https://github.com/KhronosGroup/libclcxx/commit/4d39445145cdf58233eeaaea29616d1b8e0619ba) | @ish222   | 2021-08-02T10:26:42Z | 2021-06-25T11:26:06.183Z | git subrepo clone https://github.com/llvm/llvm-project (#41)                              |
| [40f1d0423b](https://github.com/KhronosGroup/libclcxx/commit/40f1d0423b472e221d2877237f1276b8fa5a2e2f) | @ish222   | 2021-07-30T13:30:19Z | 2021-06-25T11:26:06.183Z | Add support for remove pointer/reference address space type traits (#37)                  |
| [3562e85629](https://github.com/KhronosGroup/libclcxx/commit/3562e856291f041acd7923d4a390227fc3bb3f18) | @ish222   | 2021-07-26T16:08:51Z | 2021-06-25T11:26:06.183Z | Add floating point type traits support for half type (#31)                                |
| [e7a59a50cd](https://github.com/KhronosGroup/libclcxx/commit/e7a59a50cd38ff9abe3e6524362a1d4f078d79fa) | @ish222   | 2021-07-16T16:52:13Z | 2021-06-25T11:26:06.183Z | Added type aliases when adding address spaces to types (#36)                              |
| [ec81734090](https://github.com/KhronosGroup/libclcxx/commit/ec81734090a055777aeec860338ebead508ac92c) | @ish222   | 2021-07-16T16:51:33Z | 2021-06-25T11:26:06.183Z | Added type and value aliases for newly added type traits (#39)                            |
| [930227c0c0](https://github.com/KhronosGroup/libclcxx/commit/930227c0c0a34dc887b9f4cdb8d401f428b4f44f) | @ish222   | 2021-07-16T14:45:09Z | 2021-06-25T11:26:06.183Z | Added =2Egitignore (#38)                                                                  |
| [3015aa3633](https://github.com/KhronosGroup/libclcxx/commit/3015aa3633c38647e8bae8807b1fe12ef844732f) | @ish222   | 2021-07-13T16:09:51Z | 2021-06-25T11:26:06.183Z | Add makefile for automatic testing (#29)                                                  |
| [5a74850d46](https://github.com/KhronosGroup/libclcxx/commit/5a74850d468a1a6d400aa6180a4e79d4dc6378fb) | @ish222   | 2021-07-09T09:21:04Z | 2021-06-25T11:26:06.183Z | Fixed error in function name (#34)                                                        |
| [e988318d0c](https://github.com/KhronosGroup/libclcxx/commit/e988318d0c9a74f8b58718323241aac6bea402de) | @ish222   | 2021-07-09T09:20:20Z | 2021-06-25T11:26:06.183Z | Changed file extension of new test to clcpp (#33)                                         |
| [dac987967b](https://github.com/KhronosGroup/libclcxx/commit/dac987967b5bc30b4b9897f14b97f4469e2a9394) | @ish222   | 2021-07-06T11:38:31Z | 2021-06-25T11:26:06.183Z | Added image type traits and tests (#28)                                                   |
| [0ce28534cc](https://github.com/KhronosGroup/libclcxx/commit/0ce28534ccc616129af4155912ad48e6dbdec617) | @ish222   | 2021-07-06T11:35:46Z | 2021-06-25T11:26:06.183Z | Added address space type traits and tests (#27)                                           |
| [52572aaf29](https://github.com/KhronosGroup/libclcxx/commit/52572aaf2978821e61652f09fa13cb3c2089005c) | @ish222   | 2021-07-05T15:36:39Z | 2021-06-25T11:26:06.183Z | Add support for un/signed vector type traits and exhuastive testing (#26)                 |
| [4496ec2ca0](https://github.com/KhronosGroup/libclcxx/commit/4496ec2ca037bfda5e22ba862e09f6ee020474f3) | @ish222   | 2021-06-29T10:50:14Z | 2021-06-25T11:26:06.183Z | Add library support for type traits (#25)                                                 |
| [c1244b6d40](https://github.com/KhronosGroup/libclcxx/commit/c1244b6d40832936a3aa2d3564383020f543269f) | @ish222   | 2021-06-28T13:25:50Z | 2021-06-25T11:26:06.183Z | Add library support for new (#24)                                                         |
| [61d5af0b79](https://github.com/KhronosGroup/libclcxx/commit/61d5af0b7997519511bc8a322eac5cf827f7e588) | @ish222   | 2021-06-28T10:16:28Z | 2021-06-25T11:26:06.183Z | Update include guard                                                                      |
| [886f157e18](https://github.com/KhronosGroup/libclcxx/commit/886f157e18dc349a280973f141ba5bee10b1b3f7) | @ish222   | 2021-06-28T10:04:58Z | 2021-06-25T11:26:06.183Z | Fixed include guard                                                                       |
| [53cd1963cc](https://github.com/KhronosGroup/libclcxx/commit/53cd1963ccb3742cb101ae7302a201eac2941554) | @ish222   | 2021-06-28T08:48:04Z | 2021-06-25T11:26:06.183Z | Added include guards and more tests                                                       |
