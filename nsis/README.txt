The Qt SDK likes to install a lot of different versions of DLLs.  If you
get warnings about how it couldn't find an entry point, you went and 
grabbed the wrong DLL: try others.  I had good luck copying them from
C:\QtSDK\Desktop\Qt\4.8.1\msvc2010\lib\*.dll, first into the release dir.
Once I had it working there, I copied them over in here to complete the
buildout.

Don't forget to include the MSVC2010SP1 redistributable package.