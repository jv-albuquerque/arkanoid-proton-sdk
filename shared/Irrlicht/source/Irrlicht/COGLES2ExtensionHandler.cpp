// Copyright (C) 2009-2010 Amundis
// Heavily based on the OpenGL driver implemented by Nikolaus Gebhardt
// and OpenGL ES driver implemented by Christian Stehno
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in Irrlicht.h
#include "IrrCompileConfig.h"

#ifdef _IRR_COMPILE_WITH_OGLES2_

#include "COGLES2ExtensionHandler.h"
#include "COGLES2Driver.h"
#include "fast_atof.h"
#include "irrString.h"

namespace irr
{
    namespace video
    {

        static const char* const OGLES2FeatureStrings[COGLES2ExtensionHandler::IRR_OGLES2_Feature_Count] =
        {
            "GL_AMD_compressed_3DC_texture",
            "GL_AMD_compressed_ATC_texture",
            "GL_AMD_performance_monitor",
            "GL_AMD_program_binary_Z400",
            "GL_ARB_texture_env_combine",
            "GL_ARB_texture_env_dot3",
            "GL_EXT_multi_draw_arrays",
            "GL_EXT_texture_compression_dxt1",
            "GL_EXT_texture_filter_anisotropic",
            "GL_EXT_texture_format_BGRA8888",
            "GL_EXT_texture_type_2_10_10_10_REV",
            "GL_IMG_read_format",
            "GL_IMG_texture_compression_pvrtc",
            "GL_IMG_texture_env_enhanced_fixed_function",
            "GL_IMG_texture_format_BGRA8888",
            "GL_IMG_user_clip_planes",
            "GL_IMG_vertex_program",
            "GL_NV_fence",
            "GL_OES_blend_equation_separate",
            "GL_OES_blend_func_separate",
            "GL_OES_blend_subtract",
            "GL_OES_byte_coordinates",
            "GL_OES_compressed_ETC1_RGB8_texture",
            "GL_OES_compressed_paletted_texture",
            "GL_OES_depth24",
            "GL_OES_depth32",
            "GL_OES_depth_texture",
            "GL_OES_draw_texture",
            "GL_OES_EGL_image",
            "GL_OES_element_index_uint",
            "GL_OES_extended_matrix_palette",
            "GL_OES_fbo_render_mipmap",
            "GL_OES_fixed_point",
            "GL_OES_fragment_precision_high",
            "GL_OES_framebuffer_object",
            "GL_OES_get_program_binary",
            "GL_OES_mapbuffer",
            "GL_OES_matrix_get",
            "GL_OES_matrix_palette",
            "GL_OES_packed_depth_stencil",
            "GL_OES_point_size_array",
            "GL_OES_point_sprite",
            "GL_OES_query_matrix",
            "GL_OES_read_format",
            "GL_OES_rgb8_rgba8",
            "GL_OES_single_precision",
            "GL_OES_standard_derivatives",
            "GL_OES_stencil1",
            "GL_OES_stencil4",
            "GL_OES_stencil8",
            "GL_OES_stencil_wrap",
            "GL_OES_texture_3D",
            "GL_OES_texture_cube_map",
            "GL_OES_texture_env_crossbar",
            "GL_OES_texture_float",
            "GL_OES_texture_float_linear",
            "GL_OES_texture_half_float",
            "GL_OES_texture_half_float_linear",
            "GL_OES_texture_mirrored_repeat",
            "GL_OES_texture_npot",
            "GL_OES_vertex_half_float",
            "GL_OES_vertex_type_10_10_10_2",
            "GL_QCOM_driver_control",
            "GL_QCOM_performance_monitor_global_mode"
        };


        COGLES2ExtensionHandler::COGLES2ExtensionHandler() :
                EGLVersion( 0 ), Version( 0 ), MaxTextureUnits( 0 ), MaxLights( 0 ), MaxAnisotropy( 1 ),
                MaxUserClipPlanes( 1 ), MaxTextureSize(1), CommonProfile( false ), MultiTextureExtension( false ),
                MultiSamplingExtension( false ), StencilBuffer( false )
        {
            for ( u32 i = 0; i < IRR_OGLES2_Feature_Count; ++i )
                FeatureAvailable[i] = false;
        }


        void COGLES2ExtensionHandler::dump() const
        {
            for ( u32 i = 0; i < IRR_OGLES2_Feature_Count; ++i )
                os::Printer::log( OGLES2FeatureStrings[i], FeatureAvailable[i] ? " true" : " false" );
        }


        void COGLES2ExtensionHandler::initExtensions( COGLES2Driver* driver,
                                                      EGLDisplay display,
                                                      bool withStencil )
        {
#ifdef EGL_VERSION_1_0
            const f32 egl_ver = core::fast_atof( reinterpret_cast<const c8*>( eglQueryString( display, EGL_VERSION ) ) );
            EGLVersion = static_cast<u16>( core::floor32( egl_ver ) * 100 + core::round32( core::fract( egl_ver ) * 10.0f ) );
            core::stringc eglExtensions = eglQueryString( display, EGL_EXTENSIONS );
            os::Printer::log( eglExtensions.c_str() );
#endif
            const core::stringc stringVer( glGetString( GL_VERSION ) );
            //CommonProfile = ( stringVer[11] == 'M' );
            const f32 ogl_ver = core::fast_atof( stringVer.c_str() + 13 );
            Version = static_cast<u16>( core::floor32( ogl_ver ) * 100 + core::round32( core::fract( ogl_ver ) * 10.0f ) );
            core::stringc extensions = glGetString( GL_EXTENSIONS );
            os::Printer::log( extensions.c_str() );
            {
                const u32 size = extensions.size() + 1;
                c8* str = new c8[size];
                strncpy( str, extensions.c_str(), extensions.size() );
                str[extensions.size()] = ' ';
                c8* p = str;

                for ( u32 i = 0; i < size; ++i )
                {
                    if ( str[i] == ' ' )
                    {
                        str[i] = 0;
                        if ( *p )
                            for ( u32 j = 0; j < IRR_OGLES2_Feature_Count; ++j )
                            {
                                if ( !strcmp( OGLES2FeatureStrings[j], p ) )
                                {
                                    FeatureAvailable[j] = true;
                                    break;
                                }
                            }

                        p = p + strlen( p ) + 1;
                    }
                }

                delete [] str;
            }
#ifndef GL_BGRA
            // whoa, pretty badly implemented extension...
            if ( FeatureAvailable[IRR_IMG_texture_format_BGRA8888] || FeatureAvailable[IRR_EXT_texture_format_BGRA8888] )
                GL_BGRA = 0x80E1;
            else
                GL_BGRA = GL_RGBA;
#endif

            GLint val = 0;
            glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &val );
            MaxTextureUnits = core::min_( MATERIAL_MAX_TEXTURES, static_cast<u32>( val ) );
            MultiTextureExtension = true;
            //TODO : OpenGL ES 2.0 Port
            //glGetIntegerv(GL_MAX_LIGHTS, &val);
            MaxLights = static_cast<u8>( val );
#ifdef GL_EXT_texture_filter_anisotropic
            if ( FeatureAvailable[GL_EXT_texture_filter_anisotropic] )
            {
                glGetIntegerv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &val );
                MaxAnisotropy = static_cast<u8>( val );
            }
#endif
			glGetIntegerv(GL_MAX_TEXTURE_SIZE, &val);
			MaxTextureSize=static_cast<u32>(val);
            if (( Version > 100 ) || FeatureAvailable[IRR_IMG_user_clip_planes] )
            {
                //TODO : OpenGL ES 2.0 Port
                //glGetIntegerv(GL_MAX_CLIP_PLANES, &val);
                val = 6;
                MaxUserClipPlanes = static_cast<u8>( val );
            }
        }

    } // end namespace video
} // end namespace irr


#endif // _IRR_COMPILE_WITH_OGLES21_
