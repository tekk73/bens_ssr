cmake_minimum_required(VERSION 3.5)
cmake_policy(VERSION 3.5)

if(POLICY CMP0072)
	cmake_policy(SET CMP0072 NEW)
endif(POLICY CMP0072)

set(CMAKE_CXX_STANDARD 11)

project(simplescreenrecorder VERSION 0.4.4)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64|i386|i686")
	set(PROCESSOR_IS_X86 TRUE)
else()
	set(PROCESSOR_IS_X86 FALSE)
endif()

option(ENABLE_X86_ASM "Allow x86/x64 assembly or intrinsics." ${PROCESSOR_IS_X86})
option(ENABLE_FFMPEG_VERSIONS "Use FFmpeg version numbers for feature support tests. Enable when using FFmpeg, disable when using Libav." TRUE)
option(WITH_PULSEAUDIO "Build with PulseAudio support." TRUE)
option(WITH_QT5 "Build with Qt5 (instead of Qt4)." FALSE)
option(WITH_QT6 "Build with Qt6 (instead of Qt4/5)." FALSE)
option(WITH_SIMPLESCREENRECORDER "Build the 'simplescreenrecorder' executable." TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(FeatureSummary)
include(GNUInstallDirs)

if(WITH_SIMPLESCREENRECORDER)

	add_subdirectory(src)

	install(
		DIRECTORY data/output-profiles
		DESTINATION ${CMAKE_INSTALL_FULL_DATADIR}/simplescreenrecorder
	)
	install(
		DIRECTORY data/man/
		DESTINATION ${CMAKE_INSTALL_FULL_MANDIR}/man1
	)
	install(
		FILES data/be.maartenbaert.simplescreenrecorder.desktop
		DESTINATION ${CMAKE_INSTALL_FULL_DATADIR}/applications
	)
	install(
		FILES data/be.maartenbaert.simplescreenrecorder.metainfo.xml
		DESTINATION ${CMAKE_INSTALL_FULL_DATADIR}/metainfo
	)

	# icons
	set(icons_res 16 22 24 32 48 64 96 128 192 256)

	foreach(res IN LISTS icons_res)
		install(
			DIRECTORY data/icons/${res}/
			DESTINATION ${CMAKE_INSTALL_FULL_DATADIR}/icons/hicolor/${res}x${res}/apps
		)
	endforeach()

	install(
		DIRECTORY data/icons/scalable/
		DESTINATION ${CMAKE_INSTALL_FULL_DATADIR}/icons/hicolor/scalable/apps
	)

endif()

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
