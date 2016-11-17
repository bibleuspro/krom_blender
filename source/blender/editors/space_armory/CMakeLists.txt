# ***** BEGIN GPL LICENSE BLOCK *****
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# ***** END GPL LICENSE BLOCK *****

set(INC
	../include
	../../blenfont
	../../blenkernel
	../../blenlib
	../../gpu
	../../imbuf
	../../makesdna
	../../makesrna
	../../windowmanager
	../../../../intern/guardedalloc
	../../../../intern/glew-mx
	../../barmory
	./V8/include
	./Kore/Sources
	./Kore/Backends/OpenGL2/Sources
	./Kore/Backends/Windows/Sources
)
 
set(INC_SYS
	${GLEW_INCLUDE_PATH}
)
 
set(SRC
	V8/include/libplatform/libplatform-export.h
	V8/include/libplatform/libplatform.h
	V8/include/libplatform/v8-tracing.h
	V8/include/src/allocation.h
	V8/include/src/base/atomic-utils.h
	V8/include/src/base/atomicops.h
	V8/include/src/base/atomicops_internals_x86_msvc.h
	V8/include/src/base/base-export.h
	V8/include/src/base/bits.h
	V8/include/src/base/build_config.h
	V8/include/src/base/compiler-specific.h
	V8/include/src/base/format-macros.h
	V8/include/src/base/lazy-instance.h
	V8/include/src/base/logging.h
	V8/include/src/base/macros.h
	V8/include/src/base/once.h
	V8/include/src/base/platform/mutex.h
	V8/include/src/base/platform/platform.h
	V8/include/src/base/platform/semaphore.h
	V8/include/src/base/win32-headers.h
	V8/include/src/checks.h
	V8/include/src/flag-definitions.h
	V8/include/src/flags.h
	V8/include/src/globals.h
	V8/include/src/list.h
	V8/include/src/locked-queue-inl.h
	V8/include/src/locked-queue.h
	V8/include/src/utils.h
	V8/include/src/vector.h
	V8/include/v8-debug.h
	V8/include/v8-experimental.h
	V8/include/v8-inspector-protocol.h
	V8/include/v8-inspector.h
	V8/include/v8-platform.h
	V8/include/v8-profiler.h
	V8/include/v8-testing.h
	V8/include/v8-util.h
	V8/include/v8-version.h
	V8/include/v8.h
	V8/include/v8config.h

	Kore/Backends/OpenGL2/Sources/GL/eglew.h
	Kore/Backends/OpenGL2/Sources/GL/glew.c
	Kore/Backends/OpenGL2/Sources/GL/glew.h
	Kore/Backends/OpenGL2/Sources/GL/glxew.h
	Kore/Backends/OpenGL2/Sources/GL/wglew.h
	Kore/Backends/OpenGL2/Sources/Kore/ComputeImpl.cpp
	Kore/Backends/OpenGL2/Sources/Kore/ComputeImpl.h
	Kore/Backends/OpenGL2/Sources/Kore/GraphicsImpl.h
	Kore/Backends/OpenGL2/Sources/Kore/IndexBufferImpl.cpp
	Kore/Backends/OpenGL2/Sources/Kore/IndexBufferImpl.h
	Kore/Backends/OpenGL2/Sources/Kore/ogl.h
	Kore/Backends/OpenGL2/Sources/Kore/OpenGL.cpp
	Kore/Backends/OpenGL2/Sources/Kore/OpenGL.h
	Kore/Backends/OpenGL2/Sources/Kore/pch.h
	Kore/Backends/OpenGL2/Sources/Kore/ProgramImpl.cpp
	Kore/Backends/OpenGL2/Sources/Kore/ProgramImpl.h
	Kore/Backends/OpenGL2/Sources/Kore/RenderTargetImpl.cpp
	Kore/Backends/OpenGL2/Sources/Kore/RenderTargetImpl.h
	Kore/Backends/OpenGL2/Sources/Kore/ShaderImpl.cpp
	Kore/Backends/OpenGL2/Sources/Kore/ShaderImpl.h
	Kore/Backends/OpenGL2/Sources/Kore/TextureImpl.cpp
	Kore/Backends/OpenGL2/Sources/Kore/TextureImpl.h
	Kore/Backends/OpenGL2/Sources/Kore/VertexBufferImpl.cpp
	Kore/Backends/OpenGL2/Sources/Kore/VertexBufferImpl.h
	Kore/Backends/Windows/Sources/Kore/Audio.cpp
	Kore/Backends/Windows/Sources/Kore/Display.cpp
	Kore/Backends/Windows/Sources/Kore/Display.h
	Kore/Backends/Windows/Sources/Kore/Input/Mouse.cpp
	Kore/Backends/Windows/Sources/Kore/Mutex.cpp
	Kore/Backends/Windows/Sources/Kore/pch.h
	Kore/Backends/Windows/Sources/Kore/System.cpp
	Kore/Backends/Windows/Sources/Kore/Thread.cpp
	Kore/Backends/Windows/Sources/Kore/Video.h
	Kore/Backends/Windows/Sources/Kore/VideoSoundStream.h
	Kore/Backends/Windows/Sources/Kore/WinError.cpp
	Kore/Backends/Windows/Sources/Kore/WinError.h
	Kore/Backends/Windows/Sources/Kore/Vr/pch.h
	Kore/Backends/Windows/Sources/Kore/Vr/VrInterface.cpp
	Kore/Backends/Windows/Sources/Kore/Vr/VrInterface.h
	Kore/Sources/Kore/Audio/Audio.cpp
	Kore/Sources/Kore/Audio/Audio.h
	Kore/Sources/Kore/Audio/Mixer.cpp
	Kore/Sources/Kore/Audio/Mixer.h
	Kore/Sources/Kore/Audio/pch.h
	Kore/Sources/Kore/Audio/Sound.cpp
	Kore/Sources/Kore/Audio/Sound.h
	Kore/Sources/Kore/Audio/SoundStream.cpp
	Kore/Sources/Kore/Audio/SoundStream.h
	Kore/Sources/Kore/Audio/stb_vorbis.cpp
	Kore/Sources/Kore/Audio/stb_vorbis.h
	Kore/Sources/Kore/CodeStyle.cpp
	Kore/Sources/Kore/Compute/Compute.h
	Kore/Sources/Kore/Error.cpp
	Kore/Sources/Kore/Error.h
	Kore/Sources/Kore/ErrorArgs.h
	Kore/Sources/Kore/Graphics/Color.cpp
	Kore/Sources/Kore/Graphics/Color.h
	Kore/Sources/Kore/Graphics/Graphics.cpp
	Kore/Sources/Kore/Graphics/Graphics.h
	Kore/Sources/Kore/Graphics/Graphics2.cpp
	Kore/Sources/Kore/Graphics/Graphics2.h
	Kore/Sources/Kore/Graphics/Image.cpp
	Kore/Sources/Kore/Graphics/Image.h
	Kore/Sources/Kore/Graphics/Kravur.cpp
	Kore/Sources/Kore/Graphics/Kravur.h
	Kore/Sources/Kore/Graphics/pch.h
	Kore/Sources/Kore/Graphics/PipelineState.cpp
	Kore/Sources/Kore/Graphics/PipelineState.h
	Kore/Sources/Kore/Graphics/PipelineStateBase.h
	Kore/Sources/Kore/Graphics/Shader.h
	Kore/Sources/Kore/Graphics/stb_image.h
	Kore/Sources/Kore/Graphics/Texture.h
	Kore/Sources/Kore/Graphics/VertexStructure.h
	Kore/Sources/Kore/Input/Gamepad.cpp
	Kore/Sources/Kore/Input/Gamepad.h
	Kore/Sources/Kore/Input/Keyboard.cpp
	Kore/Sources/Kore/Input/Keyboard.h
	Kore/Sources/Kore/Input/Mouse.cpp
	Kore/Sources/Kore/Input/Mouse.h
	Kore/Sources/Kore/Input/pch.h
	Kore/Sources/Kore/Input/Sensor.cpp
	Kore/Sources/Kore/Input/Sensor.h
	Kore/Sources/Kore/Input/Surface.cpp
	Kore/Sources/Kore/Input/Surface.h
	Kore/Sources/Kore/IO/FileReader.h
	Kore/Sources/Kore/IO/FileReader.winrt.cpp
	Kore/Sources/Kore/IO/FileWriter.cpp
	Kore/Sources/Kore/IO/FileWriter.h
	Kore/Sources/Kore/IO/pch.h
	Kore/Sources/Kore/IO/Reader.cpp
	Kore/Sources/Kore/IO/Reader.h
	Kore/Sources/Kore/IO/snappy/COPYING
	Kore/Sources/Kore/IO/snappy/snappy-c.cc
	Kore/Sources/Kore/IO/snappy/snappy-c.h
	Kore/Sources/Kore/IO/snappy/snappy-internal.h
	Kore/Sources/Kore/IO/snappy/snappy-sinksource.cc
	Kore/Sources/Kore/IO/snappy/snappy-sinksource.h
	Kore/Sources/Kore/IO/snappy/snappy-stubs-internal.cc
	Kore/Sources/Kore/IO/snappy/snappy-stubs-internal.h
	Kore/Sources/Kore/IO/snappy/snappy-stubs-public.h
	Kore/Sources/Kore/IO/snappy/snappy.cc
	Kore/Sources/Kore/IO/snappy/snappy.h
	Kore/Sources/Kore/IO/Writer.cpp
	Kore/Sources/Kore/IO/Writer.h
	Kore/Sources/Kore/Log.cpp
	Kore/Sources/Kore/Log.h
	Kore/Sources/Kore/LogArgs.h
	Kore/Sources/Kore/Math/Core.cpp
	Kore/Sources/Kore/Math/Core.h
	Kore/Sources/Kore/Math/Matrix.h
	Kore/Sources/Kore/Math/pch.h
	Kore/Sources/Kore/Math/Quaternion.cpp
	Kore/Sources/Kore/Math/Quaternion.h
	Kore/Sources/Kore/Math/Random.cpp
	Kore/Sources/Kore/Math/Random.h
	Kore/Sources/Kore/Math/Vector.h
	Kore/Sources/Kore/Network/Http.cpp
	Kore/Sources/Kore/Network/Http.h
	Kore/Sources/Kore/Network/pch.h
	Kore/Sources/Kore/Network/Socket.cpp
	Kore/Sources/Kore/Network/Socket.h
	Kore/Sources/Kore/pch.h
	Kore/Sources/Kore/Simd/float32x4.h
	Kore/Sources/Kore/System.cpp
	Kore/Sources/Kore/System.h
	Kore/Sources/Kore/Threads/Mutex.h
	Kore/Sources/Kore/Threads/Thread.h
	Kore/Sources/Kore/Window.h


	space_armory.c
	ArmoryWrapper.cpp
)

add_definitions(-DSYS_WINDOWS)
add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
 
blender_add_lib(bf_editor_space_armory "${SRC}" "${INC}" "${INC_SYS}")


macro(AddExternalFramework fwname appname libpath)
	unset(FRAMEWORK_${fwname} CACHE)

    find_library(FRAMEWORK_${fwname}
        NAMES Chromium\ Embedded\ Framework
        PATHS ${libpath} 
        NO_DEFAULT_PATH)
    if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
        MESSAGE(ERROR ": Framework ${fwname} not found: ${FRAMEWORK_${fwname}}")
    else()
        TARGET_LINK_LIBRARIES(${appname} ${FRAMEWORK_${fwname}})
        MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
    endif()
endmacro(AddExternalFramework)

#AddExternalFramework(ChromiumEmbeddedFramework bf_editor_space_armory /Users/lubos/armory/blender-build/blender/source/blender/editors/space_armory/cef/Frameworks)

LINK_DIRECTORIES(/Users/lubos/armory/blender-build/blender/source/blender/editors/space_armory/V8/Libraries/macos/release)

TARGET_LINK_LIBRARIES(bf_editor_space_armory C:/blender-git/blender/source/blender/editors/space_armory/V8/Libraries/win32/release/v8.dll.lib)
TARGET_LINK_LIBRARIES(bf_editor_space_armory C:/blender-git/blender/source/blender/editors/space_armory/V8/Libraries/win32/release/v8_libplatform.dll.lib)
TARGET_LINK_LIBRARIES(bf_editor_space_armory C:/blender-git/blender/source/blender/editors/space_armory/V8/Libraries/win32/release/v8_libbase.dll.lib)

#TARGET_LINK_LIBRARIES(bf_editor_space_armory, ws2_32, dxguid, dsound, dinput8)


#TARGET_LINK_LIBRARIES(bf_editor_space_armory /Users/lubos/armory/blender-build/blender/source/blender/editors/space_armory/V8/Libraries/macos/release/libc++.tbd)
