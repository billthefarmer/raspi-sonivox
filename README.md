Raspberry Pi EAS Sonivox Library
================================

Raspberry Pi implementation of the Android EAS Sonivox MIDI library.

### To Use

Download the android/platform\_external\_sonivox sources from
https://github.com/android/platform_external_sonivox. For convenience
move the arm-wt-22k folder to your workspace. Copy the Makefile from
here to the folder. Run make. You will get a couple of warnings:

	lib_src/eas_reverb.c: In function 'ReverbCalculateSinCos':
	lib_src/eas_reverb.c:495:5: warning: this decimal constant is unsigned only in ISO C90 [enabled by default]
	lib_src/eas_reverb.c:500:5: warning: this decimal constant is unsigned only in ISO C90 [enabled by default]

I tried this originally for a bit of fun as I have used this
unsupported library in other android projecta. However I am impressed
with the quality of the output compared to other midi libraries using
large soundfont files. Try playing the two Carolan midi files.
