Contributing to ANALIB
======================

Thank you for your interest in extending ANALIB. Before continuing, take your time to read through these guidelines on how to proceed.


Adding a module
----------------
Before adding a new module, make sure the following points are fulfilled:

 * There should be no dependencies on other module. If it is, you have probably found the need of a library on its on.

 * The module should contain the following files:

   + One and only one interface file. For a module which contains program code, the interface file must not expose more than 10 API entry points. which should be fully documented with valid expressions, and pre and post conditions. If the module contain data, that is a csv database, textures for a certain material etc, there is no upper limit on the number of records. In the case of a material, each texture is considered as one record.
   + One optional implementation file. Having a separate implementation file is not mandatory if it more appropriate to put the implementation in the interface file.
   + One and only one test driver that does not rely on any external test framework. The test driver should test as much as possible of the documented behaviour.

 * It should be possible to release the module under the MIT license.

 * If you are writing a C++ module, assume C++14
