/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Felipe Carlin $
   $Notice: $
   ======================================================================== */

#include "opengl_astroids.h"

// TODO(felipe): implent scanf myself
#include <stdio.h>

global_variable HMODULE OpenGLDLL;
global_variable ast_gl_version GLVersion;
global_variable int OpenGLLoadedMajor;
global_variable int OpenGLLoadedMinor;

typedef void* (APIENTRYP PFNWGLGETPROCADDRESSPROC_PRIVATE)(const char*);
internal PFNWGLGETPROCADDRESSPROC_PRIVATE ASTGetProcAddressPtr;

internal int
InternalLoadOpenGLDLL()
{
    int Result = 0;
    OpenGLDLL = LoadLibraryA("opengl32.dll");
    if(OpenGLDLL)
    {
        void (* tmp)(void);
        tmp = (void(*)(void)) GetProcAddress(OpenGLDLL, "wglGetProcAddress");
        ASTGetProcAddressPtr = (PFNWGLGETPROCADDRESSPROC_PRIVATE) tmp;
        Result = (ASTGetProcAddressPtr != 0);
    }

    return Result;
}

static void
InternalCloseOpenGLDLL()
{
    if(OpenGLDLL)
    {
        FreeLibrary((HMODULE) OpenGLDLL);
        OpenGLDLL = 0;
    }
}

internal void *
GetOpenGLProc(const char *ProcName)
{
    void *Result = 0;

    if(OpenGLDLL) 
    {
        if(ASTGetProcAddressPtr)
        {
            Result = ASTGetProcAddressPtr(ProcName);
        }
        
        if(Result == 0)
        {
            Result = (void*)GetProcAddress((HMODULE) OpenGLDLL, ProcName);
        }
    }

    return Result;
}

// Definitions
//
//

int AST_GL_VERSION_1_0 = 0;
int AST_GL_VERSION_1_1 = 0;
int AST_GL_VERSION_1_2 = 0;
int AST_GL_VERSION_1_3 = 0;
int AST_GL_VERSION_1_4 = 0;
int AST_GL_VERSION_1_5 = 0;
int AST_GL_VERSION_2_0 = 0;
int AST_GL_VERSION_2_1 = 0;
int AST_GL_VERSION_3_0 = 0;
int AST_GL_VERSION_3_1 = 0;



PFNGLACCUMPROC ast_glAccum = 0;
PFNGLACTIVETEXTUREPROC ast_glActiveTexture = 0;
PFNGLALPHAFUNCPROC ast_glAlphaFunc = 0;
PFNGLARETEXTURESRESIDENTPROC ast_glAreTexturesResident = 0;
PFNGLARRAYELEMENTPROC ast_glArrayElement = 0;
PFNGLATTACHSHADERPROC ast_glAttachShader = 0;
PFNGLBEGINPROC ast_glBegin = 0;
PFNGLBEGINCONDITIONALRENDERPROC ast_glBeginConditionalRender = 0;
PFNGLBEGINQUERYPROC ast_glBeginQuery = 0;
PFNGLBEGINTRANSFORMFEEDBACKPROC ast_glBeginTransformFeedback = 0;
PFNGLBINDATTRIBLOCATIONPROC ast_glBindAttribLocation = 0;
PFNGLBINDBUFFERPROC ast_glBindBuffer = 0;
PFNGLBINDBUFFERBASEPROC ast_glBindBufferBase = 0;
PFNGLBINDBUFFERRANGEPROC ast_glBindBufferRange = 0;
PFNGLBINDFRAGDATALOCATIONPROC ast_glBindFragDataLocation = 0;
PFNGLBINDFRAMEBUFFERPROC ast_glBindFramebuffer = 0;
PFNGLBINDRENDERBUFFERPROC ast_glBindRenderbuffer = 0;
PFNGLBINDTEXTUREPROC ast_glBindTexture = 0;
PFNGLBINDVERTEXARRAYPROC ast_glBindVertexArray = 0;
PFNGLBITMAPPROC ast_glBitmap = 0;
PFNGLBLENDCOLORPROC ast_glBlendColor = 0;
PFNGLBLENDEQUATIONPROC ast_glBlendEquation = 0;
PFNGLBLENDEQUATIONSEPARATEPROC ast_glBlendEquationSeparate = 0;
PFNGLBLENDFUNCPROC ast_glBlendFunc = 0;
PFNGLBLENDFUNCSEPARATEPROC ast_glBlendFuncSeparate = 0;
PFNGLBLITFRAMEBUFFERPROC ast_glBlitFramebuffer = 0;
PFNGLBUFFERDATAPROC ast_glBufferData = 0;
PFNGLBUFFERSUBDATAPROC ast_glBufferSubData = 0;
PFNGLCALLLISTPROC ast_glCallList = 0;
PFNGLCALLLISTSPROC ast_glCallLists = 0;
PFNGLCHECKFRAMEBUFFERSTATUSPROC ast_glCheckFramebufferStatus = 0;
PFNGLCLAMPCOLORPROC ast_glClampColor = 0;
PFNGLCLEARPROC ast_glClear = 0;
PFNGLCLEARACCUMPROC ast_glClearAccum = 0;
PFNGLCLEARBUFFERFIPROC ast_glClearBufferfi = 0;
PFNGLCLEARBUFFERFVPROC ast_glClearBufferfv = 0;
PFNGLCLEARBUFFERIVPROC ast_glClearBufferiv = 0;
PFNGLCLEARBUFFERUIVPROC ast_glClearBufferuiv = 0;
PFNGLCLEARCOLORPROC ast_glClearColor = 0;
PFNGLCLEARDEPTHPROC ast_glClearDepth = 0;
PFNGLCLEARINDEXPROC ast_glClearIndex = 0;
PFNGLCLEARSTENCILPROC ast_glClearStencil = 0;
PFNGLCLIENTACTIVETEXTUREPROC ast_glClientActiveTexture = 0;
PFNGLCLIPPLANEPROC ast_glClipPlane = 0;
PFNGLCOLOR3BPROC ast_glColor3b = 0;
PFNGLCOLOR3BVPROC ast_glColor3bv = 0;
PFNGLCOLOR3DPROC ast_glColor3d = 0;
PFNGLCOLOR3DVPROC ast_glColor3dv = 0;
PFNGLCOLOR3FPROC ast_glColor3f = 0;
PFNGLCOLOR3FVPROC ast_glColor3fv = 0;
PFNGLCOLOR3IPROC ast_glColor3i = 0;
PFNGLCOLOR3IVPROC ast_glColor3iv = 0;
PFNGLCOLOR3SPROC ast_glColor3s = 0;
PFNGLCOLOR3SVPROC ast_glColor3sv = 0;
PFNGLCOLOR3UBPROC ast_glColor3ub = 0;
PFNGLCOLOR3UBVPROC ast_glColor3ubv = 0;
PFNGLCOLOR3UIPROC ast_glColor3ui = 0;
PFNGLCOLOR3UIVPROC ast_glColor3uiv = 0;
PFNGLCOLOR3USPROC ast_glColor3us = 0;
PFNGLCOLOR3USVPROC ast_glColor3usv = 0;
PFNGLCOLOR4BPROC ast_glColor4b = 0;
PFNGLCOLOR4BVPROC ast_glColor4bv = 0;
PFNGLCOLOR4DPROC ast_glColor4d = 0;
PFNGLCOLOR4DVPROC ast_glColor4dv = 0;
PFNGLCOLOR4FPROC ast_glColor4f = 0;
PFNGLCOLOR4FVPROC ast_glColor4fv = 0;
PFNGLCOLOR4IPROC ast_glColor4i = 0;
PFNGLCOLOR4IVPROC ast_glColor4iv = 0;
PFNGLCOLOR4SPROC ast_glColor4s = 0;
PFNGLCOLOR4SVPROC ast_glColor4sv = 0;
PFNGLCOLOR4UBPROC ast_glColor4ub = 0;
PFNGLCOLOR4UBVPROC ast_glColor4ubv = 0;
PFNGLCOLOR4UIPROC ast_glColor4ui = 0;
PFNGLCOLOR4UIVPROC ast_glColor4uiv = 0;
PFNGLCOLOR4USPROC ast_glColor4us = 0;
PFNGLCOLOR4USVPROC ast_glColor4usv = 0;
PFNGLCOLORMASKPROC ast_glColorMask = 0;
PFNGLCOLORMASKIPROC ast_glColorMaski = 0;
PFNGLCOLORMATERIALPROC ast_glColorMaterial = 0;
PFNGLCOLORPOINTERPROC ast_glColorPointer = 0;
PFNGLCOMPILESHADERPROC ast_glCompileShader = 0;
PFNGLCOMPRESSEDTEXIMAGE1DPROC ast_glCompressedTexImage1D = 0;
PFNGLCOMPRESSEDTEXIMAGE2DPROC ast_glCompressedTexImage2D = 0;
PFNGLCOMPRESSEDTEXIMAGE3DPROC ast_glCompressedTexImage3D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC ast_glCompressedTexSubImage1D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC ast_glCompressedTexSubImage2D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC ast_glCompressedTexSubImage3D = 0;
PFNGLCOPYBUFFERSUBDATAPROC ast_glCopyBufferSubData = 0;
PFNGLCOPYPIXELSPROC ast_glCopyPixels = 0;
PFNGLCOPYTEXIMAGE1DPROC ast_glCopyTexImage1D = 0;
PFNGLCOPYTEXIMAGE2DPROC ast_glCopyTexImage2D = 0;
PFNGLCOPYTEXSUBIMAGE1DPROC ast_glCopyTexSubImage1D = 0;
PFNGLCOPYTEXSUBIMAGE2DPROC ast_glCopyTexSubImage2D = 0;
PFNGLCOPYTEXSUBIMAGE3DPROC ast_glCopyTexSubImage3D = 0;
PFNGLCREATEPROGRAMPROC ast_glCreateProgram = 0;
PFNGLCREATESHADERPROC ast_glCreateShader = 0;
PFNGLCULLFACEPROC ast_glCullFace = 0;
PFNGLDELETEBUFFERSPROC ast_glDeleteBuffers = 0;
PFNGLDELETEFRAMEBUFFERSPROC ast_glDeleteFramebuffers = 0;
PFNGLDELETELISTSPROC ast_glDeleteLists = 0;
PFNGLDELETEPROGRAMPROC ast_glDeleteProgram = 0;
PFNGLDELETEQUERIESPROC ast_glDeleteQueries = 0;
PFNGLDELETERENDERBUFFERSPROC ast_glDeleteRenderbuffers = 0;
PFNGLDELETESHADERPROC ast_glDeleteShader = 0;
PFNGLDELETETEXTURESPROC ast_glDeleteTextures = 0;
PFNGLDELETEVERTEXARRAYSPROC ast_glDeleteVertexArrays = 0;
PFNGLDEPTHFUNCPROC ast_glDepthFunc = 0;
PFNGLDEPTHMASKPROC ast_glDepthMask = 0;
PFNGLDEPTHRANGEPROC ast_glDepthRange = 0;
PFNGLDETACHSHADERPROC ast_glDetachShader = 0;
PFNGLDISABLEPROC ast_glDisable = 0;
PFNGLDISABLECLIENTSTATEPROC ast_glDisableClientState = 0;
PFNGLDISABLEVERTEXATTRIBARRAYPROC ast_glDisableVertexAttribArray = 0;
PFNGLDISABLEIPROC ast_glDisablei = 0;
PFNGLDRAWARRAYSPROC ast_glDrawArrays = 0;
PFNGLDRAWARRAYSINSTANCEDPROC ast_glDrawArraysInstanced = 0;
PFNGLDRAWBUFFERPROC ast_glDrawBuffer = 0;
PFNGLDRAWBUFFERSPROC ast_glDrawBuffers = 0;
PFNGLDRAWELEMENTSPROC ast_glDrawElements = 0;
PFNGLDRAWELEMENTSINSTANCEDPROC ast_glDrawElementsInstanced = 0;
PFNGLDRAWPIXELSPROC ast_glDrawPixels = 0;
PFNGLDRAWRANGEELEMENTSPROC ast_glDrawRangeElements = 0;
PFNGLEDGEFLAGPROC ast_glEdgeFlag = 0;
PFNGLEDGEFLAGPOINTERPROC ast_glEdgeFlagPointer = 0;
PFNGLEDGEFLAGVPROC ast_glEdgeFlagv = 0;
PFNGLENABLEPROC ast_glEnable = 0;
PFNGLENABLECLIENTSTATEPROC ast_glEnableClientState = 0;
PFNGLENABLEVERTEXATTRIBARRAYPROC ast_glEnableVertexAttribArray = 0;
PFNGLENABLEIPROC ast_glEnablei = 0;
PFNGLENDPROC ast_glEnd = 0;
PFNGLENDCONDITIONALRENDERPROC ast_glEndConditionalRender = 0;
PFNGLENDLISTPROC ast_glEndList = 0;
PFNGLENDQUERYPROC ast_glEndQuery = 0;
PFNGLENDTRANSFORMFEEDBACKPROC ast_glEndTransformFeedback = 0;
PFNGLEVALCOORD1DPROC ast_glEvalCoord1d = 0;
PFNGLEVALCOORD1DVPROC ast_glEvalCoord1dv = 0;
PFNGLEVALCOORD1FPROC ast_glEvalCoord1f = 0;
PFNGLEVALCOORD1FVPROC ast_glEvalCoord1fv = 0;
PFNGLEVALCOORD2DPROC ast_glEvalCoord2d = 0;
PFNGLEVALCOORD2DVPROC ast_glEvalCoord2dv = 0;
PFNGLEVALCOORD2FPROC ast_glEvalCoord2f = 0;
PFNGLEVALCOORD2FVPROC ast_glEvalCoord2fv = 0;
PFNGLEVALMESH1PROC ast_glEvalMesh1 = 0;
PFNGLEVALMESH2PROC ast_glEvalMesh2 = 0;
PFNGLEVALPOINT1PROC ast_glEvalPoint1 = 0;
PFNGLEVALPOINT2PROC ast_glEvalPoint2 = 0;
PFNGLFEEDBACKBUFFERPROC ast_glFeedbackBuffer = 0;
PFNGLFINISHPROC ast_glFinish = 0;
PFNGLFLUSHPROC ast_glFlush = 0;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC ast_glFlushMappedBufferRange = 0;
PFNGLFOGCOORDPOINTERPROC ast_glFogCoordPointer = 0;
PFNGLFOGCOORDDPROC ast_glFogCoordd = 0;
PFNGLFOGCOORDDVPROC ast_glFogCoorddv = 0;
PFNGLFOGCOORDFPROC ast_glFogCoordf = 0;
PFNGLFOGCOORDFVPROC ast_glFogCoordfv = 0;
PFNGLFOGFPROC ast_glFogf = 0;
PFNGLFOGFVPROC ast_glFogfv = 0;
PFNGLFOGIPROC ast_glFogi = 0;
PFNGLFOGIVPROC ast_glFogiv = 0;
PFNGLFRAMEBUFFERRENDERBUFFERPROC ast_glFramebufferRenderbuffer = 0;
PFNGLFRAMEBUFFERTEXTURE1DPROC ast_glFramebufferTexture1D = 0;
PFNGLFRAMEBUFFERTEXTURE2DPROC ast_glFramebufferTexture2D = 0;
PFNGLFRAMEBUFFERTEXTURE3DPROC ast_glFramebufferTexture3D = 0;
PFNGLFRAMEBUFFERTEXTURELAYERPROC ast_glFramebufferTextureLayer = 0;
PFNGLFRONTFACEPROC ast_glFrontFace = 0;
PFNGLFRUSTUMPROC ast_glFrustum = 0;
PFNGLGENBUFFERSPROC ast_glGenBuffers = 0;
PFNGLGENFRAMEBUFFERSPROC ast_glGenFramebuffers = 0;
PFNGLGENLISTSPROC ast_glGenLists = 0;
PFNGLGENQUERIESPROC ast_glGenQueries = 0;
PFNGLGENRENDERBUFFERSPROC ast_glGenRenderbuffers = 0;
PFNGLGENTEXTURESPROC ast_glGenTextures = 0;
PFNGLGENVERTEXARRAYSPROC ast_glGenVertexArrays = 0;
PFNGLGENERATEMIPMAPPROC ast_glGenerateMipmap = 0;
PFNGLGETACTIVEATTRIBPROC ast_glGetActiveAttrib = 0;
PFNGLGETACTIVEUNIFORMPROC ast_glGetActiveUniform = 0;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC ast_glGetActiveUniformBlockName = 0;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC ast_glGetActiveUniformBlockiv = 0;
PFNGLGETACTIVEUNIFORMNAMEPROC ast_glGetActiveUniformName = 0;
PFNGLGETACTIVEUNIFORMSIVPROC ast_glGetActiveUniformsiv = 0;
PFNGLGETATTACHEDSHADERSPROC ast_glGetAttachedShaders = 0;
PFNGLGETATTRIBLOCATIONPROC ast_glGetAttribLocation = 0;
PFNGLGETBOOLEANI_VPROC ast_glGetBooleani_v = 0;
PFNGLGETBOOLEANVPROC ast_glGetBooleanv = 0;
PFNGLGETBUFFERPARAMETERIVPROC ast_glGetBufferParameteriv = 0;
PFNGLGETBUFFERPOINTERVPROC ast_glGetBufferPointerv = 0;
PFNGLGETBUFFERSUBDATAPROC ast_glGetBufferSubData = 0;
PFNGLGETCLIPPLANEPROC ast_glGetClipPlane = 0;
PFNGLGETCOMPRESSEDTEXIMAGEPROC ast_glGetCompressedTexImage = 0;
PFNGLGETDOUBLEVPROC ast_glGetDoublev = 0;
PFNGLGETERRORPROC ast_glGetError = 0;
PFNGLGETFLOATVPROC ast_glGetFloatv = 0;
PFNGLGETFRAGDATALOCATIONPROC ast_glGetFragDataLocation = 0;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC ast_glGetFramebufferAttachmentParameteriv = 0;
PFNGLGETINTEGERI_VPROC ast_glGetIntegeri_v = 0;
PFNGLGETINTEGERVPROC ast_glGetIntegerv = 0;
PFNGLGETLIGHTFVPROC ast_glGetLightfv = 0;
PFNGLGETLIGHTIVPROC ast_glGetLightiv = 0;
PFNGLGETMAPDVPROC ast_glGetMapdv = 0;
PFNGLGETMAPFVPROC ast_glGetMapfv = 0;
PFNGLGETMAPIVPROC ast_glGetMapiv = 0;
PFNGLGETMATERIALFVPROC ast_glGetMaterialfv = 0;
PFNGLGETMATERIALIVPROC ast_glGetMaterialiv = 0;
PFNGLGETPIXELMAPFVPROC ast_glGetPixelMapfv = 0;
PFNGLGETPIXELMAPUIVPROC ast_glGetPixelMapuiv = 0;
PFNGLGETPIXELMAPUSVPROC ast_glGetPixelMapusv = 0;
PFNGLGETPOINTERVPROC ast_glGetPointerv = 0;
PFNGLGETPOLYGONSTIPPLEPROC ast_glGetPolygonStipple = 0;
PFNGLGETPROGRAMINFOLOGPROC ast_glGetProgramInfoLog = 0;
PFNGLGETPROGRAMIVPROC ast_glGetProgramiv = 0;
PFNGLGETQUERYOBJECTIVPROC ast_glGetQueryObjectiv = 0;
PFNGLGETQUERYOBJECTUIVPROC ast_glGetQueryObjectuiv = 0;
PFNGLGETQUERYIVPROC ast_glGetQueryiv = 0;
PFNGLGETRENDERBUFFERPARAMETERIVPROC ast_glGetRenderbufferParameteriv = 0;
PFNGLGETSHADERINFOLOGPROC ast_glGetShaderInfoLog = 0;
PFNGLGETSHADERSOURCEPROC ast_glGetShaderSource = 0;
PFNGLGETSHADERIVPROC ast_glGetShaderiv = 0;
PFNGLGETSTRINGPROC ast_glGetString = 0;
PFNGLGETSTRINGIPROC ast_glGetStringi = 0;
PFNGLGETTEXENVFVPROC ast_glGetTexEnvfv = 0;
PFNGLGETTEXENVIVPROC ast_glGetTexEnviv = 0;
PFNGLGETTEXGENDVPROC ast_glGetTexGendv = 0;
PFNGLGETTEXGENFVPROC ast_glGetTexGenfv = 0;
PFNGLGETTEXGENIVPROC ast_glGetTexGeniv = 0;
PFNGLGETTEXIMAGEPROC ast_glGetTexImage = 0;
PFNGLGETTEXLEVELPARAMETERFVPROC ast_glGetTexLevelParameterfv = 0;
PFNGLGETTEXLEVELPARAMETERIVPROC ast_glGetTexLevelParameteriv = 0;
PFNGLGETTEXPARAMETERIIVPROC ast_glGetTexParameterIiv = 0;
PFNGLGETTEXPARAMETERIUIVPROC ast_glGetTexParameterIuiv = 0;
PFNGLGETTEXPARAMETERFVPROC ast_glGetTexParameterfv = 0;
PFNGLGETTEXPARAMETERIVPROC ast_glGetTexParameteriv = 0;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC ast_glGetTransformFeedbackVarying = 0;
PFNGLGETUNIFORMBLOCKINDEXPROC ast_glGetUniformBlockIndex = 0;
PFNGLGETUNIFORMINDICESPROC ast_glGetUniformIndices = 0;
PFNGLGETUNIFORMLOCATIONPROC ast_glGetUniformLocation = 0;
PFNGLGETUNIFORMFVPROC ast_glGetUniformfv = 0;
PFNGLGETUNIFORMIVPROC ast_glGetUniformiv = 0;
PFNGLGETUNIFORMUIVPROC ast_glGetUniformuiv = 0;
PFNGLGETVERTEXATTRIBIIVPROC ast_glGetVertexAttribIiv = 0;
PFNGLGETVERTEXATTRIBIUIVPROC ast_glGetVertexAttribIuiv = 0;
PFNGLGETVERTEXATTRIBPOINTERVPROC ast_glGetVertexAttribPointerv = 0;
PFNGLGETVERTEXATTRIBDVPROC ast_glGetVertexAttribdv = 0;
PFNGLGETVERTEXATTRIBFVPROC ast_glGetVertexAttribfv = 0;
PFNGLGETVERTEXATTRIBIVPROC ast_glGetVertexAttribiv = 0;
PFNGLHINTPROC ast_glHint = 0;
PFNGLINDEXMASKPROC ast_glIndexMask = 0;
PFNGLINDEXPOINTERPROC ast_glIndexPointer = 0;
PFNGLINDEXDPROC ast_glIndexd = 0;
PFNGLINDEXDVPROC ast_glIndexdv = 0;
PFNGLINDEXFPROC ast_glIndexf = 0;
PFNGLINDEXFVPROC ast_glIndexfv = 0;
PFNGLINDEXIPROC ast_glIndexi = 0;
PFNGLINDEXIVPROC ast_glIndexiv = 0;
PFNGLINDEXSPROC ast_glIndexs = 0;
PFNGLINDEXSVPROC ast_glIndexsv = 0;
PFNGLINDEXUBPROC ast_glIndexub = 0;
PFNGLINDEXUBVPROC ast_glIndexubv = 0;
PFNGLINITNAMESPROC ast_glInitNames = 0;
PFNGLINTERLEAVEDARRAYSPROC ast_glInterleavedArrays = 0;
PFNGLISBUFFERPROC ast_glIsBuffer = 0;
PFNGLISENABLEDPROC ast_glIsEnabled = 0;
PFNGLISENABLEDIPROC ast_glIsEnabledi = 0;
PFNGLISFRAMEBUFFERPROC ast_glIsFramebuffer = 0;
PFNGLISLISTPROC ast_glIsList = 0;
PFNGLISPROGRAMPROC ast_glIsProgram = 0;
PFNGLISQUERYPROC ast_glIsQuery = 0;
PFNGLISRENDERBUFFERPROC ast_glIsRenderbuffer = 0;
PFNGLISSHADERPROC ast_glIsShader = 0;
PFNGLISTEXTUREPROC ast_glIsTexture = 0;
PFNGLISVERTEXARRAYPROC ast_glIsVertexArray = 0;
PFNGLLIGHTMODELFPROC ast_glLightModelf = 0;
PFNGLLIGHTMODELFVPROC ast_glLightModelfv = 0;
PFNGLLIGHTMODELIPROC ast_glLightModeli = 0;
PFNGLLIGHTMODELIVPROC ast_glLightModeliv = 0;
PFNGLLIGHTFPROC ast_glLightf = 0;
PFNGLLIGHTFVPROC ast_glLightfv = 0;
PFNGLLIGHTIPROC ast_glLighti = 0;
PFNGLLIGHTIVPROC ast_glLightiv = 0;
PFNGLLINESTIPPLEPROC ast_glLineStipple = 0;
PFNGLLINEWIDTHPROC ast_glLineWidth = 0;
PFNGLLINKPROGRAMPROC ast_glLinkProgram = 0;
PFNGLLISTBASEPROC ast_glListBase = 0;
PFNGLLOADIDENTITYPROC ast_glLoadIdentity = 0;
PFNGLLOADMATRIXDPROC ast_glLoadMatrixd = 0;
PFNGLLOADMATRIXFPROC ast_glLoadMatrixf = 0;
PFNGLLOADNAMEPROC ast_glLoadName = 0;
PFNGLLOADTRANSPOSEMATRIXDPROC ast_glLoadTransposeMatrixd = 0;
PFNGLLOADTRANSPOSEMATRIXFPROC ast_glLoadTransposeMatrixf = 0;
PFNGLLOGICOPPROC ast_glLogicOp = 0;
PFNGLMAP1DPROC ast_glMap1d = 0;
PFNGLMAP1FPROC ast_glMap1f = 0;
PFNGLMAP2DPROC ast_glMap2d = 0;
PFNGLMAP2FPROC ast_glMap2f = 0;
PFNGLMAPBUFFERPROC ast_glMapBuffer = 0;
PFNGLMAPBUFFERRANGEPROC ast_glMapBufferRange = 0;
PFNGLMAPGRID1DPROC ast_glMapGrid1d = 0;
PFNGLMAPGRID1FPROC ast_glMapGrid1f = 0;
PFNGLMAPGRID2DPROC ast_glMapGrid2d = 0;
PFNGLMAPGRID2FPROC ast_glMapGrid2f = 0;
PFNGLMATERIALFPROC ast_glMaterialf = 0;
PFNGLMATERIALFVPROC ast_glMaterialfv = 0;
PFNGLMATERIALIPROC ast_glMateriali = 0;
PFNGLMATERIALIVPROC ast_glMaterialiv = 0;
PFNGLMATRIXMODEPROC ast_glMatrixMode = 0;
PFNGLMULTMATRIXDPROC ast_glMultMatrixd = 0;
PFNGLMULTMATRIXFPROC ast_glMultMatrixf = 0;
PFNGLMULTTRANSPOSEMATRIXDPROC ast_glMultTransposeMatrixd = 0;
PFNGLMULTTRANSPOSEMATRIXFPROC ast_glMultTransposeMatrixf = 0;
PFNGLMULTIDRAWARRAYSPROC ast_glMultiDrawArrays = 0;
PFNGLMULTIDRAWELEMENTSPROC ast_glMultiDrawElements = 0;
PFNGLMULTITEXCOORD1DPROC ast_glMultiTexCoord1d = 0;
PFNGLMULTITEXCOORD1DVPROC ast_glMultiTexCoord1dv = 0;
PFNGLMULTITEXCOORD1FPROC ast_glMultiTexCoord1f = 0;
PFNGLMULTITEXCOORD1FVPROC ast_glMultiTexCoord1fv = 0;
PFNGLMULTITEXCOORD1IPROC ast_glMultiTexCoord1i = 0;
PFNGLMULTITEXCOORD1IVPROC ast_glMultiTexCoord1iv = 0;
PFNGLMULTITEXCOORD1SPROC ast_glMultiTexCoord1s = 0;
PFNGLMULTITEXCOORD1SVPROC ast_glMultiTexCoord1sv = 0;
PFNGLMULTITEXCOORD2DPROC ast_glMultiTexCoord2d = 0;
PFNGLMULTITEXCOORD2DVPROC ast_glMultiTexCoord2dv = 0;
PFNGLMULTITEXCOORD2FPROC ast_glMultiTexCoord2f = 0;
PFNGLMULTITEXCOORD2FVPROC ast_glMultiTexCoord2fv = 0;
PFNGLMULTITEXCOORD2IPROC ast_glMultiTexCoord2i = 0;
PFNGLMULTITEXCOORD2IVPROC ast_glMultiTexCoord2iv = 0;
PFNGLMULTITEXCOORD2SPROC ast_glMultiTexCoord2s = 0;
PFNGLMULTITEXCOORD2SVPROC ast_glMultiTexCoord2sv = 0;
PFNGLMULTITEXCOORD3DPROC ast_glMultiTexCoord3d = 0;
PFNGLMULTITEXCOORD3DVPROC ast_glMultiTexCoord3dv = 0;
PFNGLMULTITEXCOORD3FPROC ast_glMultiTexCoord3f = 0;
PFNGLMULTITEXCOORD3FVPROC ast_glMultiTexCoord3fv = 0;
PFNGLMULTITEXCOORD3IPROC ast_glMultiTexCoord3i = 0;
PFNGLMULTITEXCOORD3IVPROC ast_glMultiTexCoord3iv = 0;
PFNGLMULTITEXCOORD3SPROC ast_glMultiTexCoord3s = 0;
PFNGLMULTITEXCOORD3SVPROC ast_glMultiTexCoord3sv = 0;
PFNGLMULTITEXCOORD4DPROC ast_glMultiTexCoord4d = 0;
PFNGLMULTITEXCOORD4DVPROC ast_glMultiTexCoord4dv = 0;
PFNGLMULTITEXCOORD4FPROC ast_glMultiTexCoord4f = 0;
PFNGLMULTITEXCOORD4FVPROC ast_glMultiTexCoord4fv = 0;
PFNGLMULTITEXCOORD4IPROC ast_glMultiTexCoord4i = 0;
PFNGLMULTITEXCOORD4IVPROC ast_glMultiTexCoord4iv = 0;
PFNGLMULTITEXCOORD4SPROC ast_glMultiTexCoord4s = 0;
PFNGLMULTITEXCOORD4SVPROC ast_glMultiTexCoord4sv = 0;
PFNGLNEWLISTPROC ast_glNewList = 0;
PFNGLNORMAL3BPROC ast_glNormal3b = 0;
PFNGLNORMAL3BVPROC ast_glNormal3bv = 0;
PFNGLNORMAL3DPROC ast_glNormal3d = 0;
PFNGLNORMAL3DVPROC ast_glNormal3dv = 0;
PFNGLNORMAL3FPROC ast_glNormal3f = 0;
PFNGLNORMAL3FVPROC ast_glNormal3fv = 0;
PFNGLNORMAL3IPROC ast_glNormal3i = 0;
PFNGLNORMAL3IVPROC ast_glNormal3iv = 0;
PFNGLNORMAL3SPROC ast_glNormal3s = 0;
PFNGLNORMAL3SVPROC ast_glNormal3sv = 0;
PFNGLNORMALPOINTERPROC ast_glNormalPointer = 0;
PFNGLORTHOPROC ast_glOrtho = 0;
PFNGLPASSTHROUGHPROC ast_glPassThrough = 0;
PFNGLPIXELMAPFVPROC ast_glPixelMapfv = 0;
PFNGLPIXELMAPUIVPROC ast_glPixelMapuiv = 0;
PFNGLPIXELMAPUSVPROC ast_glPixelMapusv = 0;
PFNGLPIXELSTOREFPROC ast_glPixelStoref = 0;
PFNGLPIXELSTOREIPROC ast_glPixelStorei = 0;
PFNGLPIXELTRANSFERFPROC ast_glPixelTransferf = 0;
PFNGLPIXELTRANSFERIPROC ast_glPixelTransferi = 0;
PFNGLPIXELZOOMPROC ast_glPixelZoom = 0;
PFNGLPOINTPARAMETERFPROC ast_glPointParameterf = 0;
PFNGLPOINTPARAMETERFVPROC ast_glPointParameterfv = 0;
PFNGLPOINTPARAMETERIPROC ast_glPointParameteri = 0;
PFNGLPOINTPARAMETERIVPROC ast_glPointParameteriv = 0;
PFNGLPOINTSIZEPROC ast_glPointSize = 0;
PFNGLPOLYGONMODEPROC ast_glPolygonMode = 0;
PFNGLPOLYGONOFFSETPROC ast_glPolygonOffset = 0;
PFNGLPOLYGONSTIPPLEPROC ast_glPolygonStipple = 0;
PFNGLPOPATTRIBPROC ast_glPopAttrib = 0;
PFNGLPOPCLIENTATTRIBPROC ast_glPopClientAttrib = 0;
PFNGLPOPMATRIXPROC ast_glPopMatrix = 0;
PFNGLPOPNAMEPROC ast_glPopName = 0;
PFNGLPRIMITIVERESTARTINDEXPROC ast_glPrimitiveRestartIndex = 0;
PFNGLPRIORITIZETEXTURESPROC ast_glPrioritizeTextures = 0;
PFNGLPUSHATTRIBPROC ast_glPushAttrib = 0;
PFNGLPUSHCLIENTATTRIBPROC ast_glPushClientAttrib = 0;
PFNGLPUSHMATRIXPROC ast_glPushMatrix = 0;
PFNGLPUSHNAMEPROC ast_glPushName = 0;
PFNGLRASTERPOS2DPROC ast_glRasterPos2d = 0;
PFNGLRASTERPOS2DVPROC ast_glRasterPos2dv = 0;
PFNGLRASTERPOS2FPROC ast_glRasterPos2f = 0;
PFNGLRASTERPOS2FVPROC ast_glRasterPos2fv = 0;
PFNGLRASTERPOS2IPROC ast_glRasterPos2i = 0;
PFNGLRASTERPOS2IVPROC ast_glRasterPos2iv = 0;
PFNGLRASTERPOS2SPROC ast_glRasterPos2s = 0;
PFNGLRASTERPOS2SVPROC ast_glRasterPos2sv = 0;
PFNGLRASTERPOS3DPROC ast_glRasterPos3d = 0;
PFNGLRASTERPOS3DVPROC ast_glRasterPos3dv = 0;
PFNGLRASTERPOS3FPROC ast_glRasterPos3f = 0;
PFNGLRASTERPOS3FVPROC ast_glRasterPos3fv = 0;
PFNGLRASTERPOS3IPROC ast_glRasterPos3i = 0;
PFNGLRASTERPOS3IVPROC ast_glRasterPos3iv = 0;
PFNGLRASTERPOS3SPROC ast_glRasterPos3s = 0;
PFNGLRASTERPOS3SVPROC ast_glRasterPos3sv = 0;
PFNGLRASTERPOS4DPROC ast_glRasterPos4d = 0;
PFNGLRASTERPOS4DVPROC ast_glRasterPos4dv = 0;
PFNGLRASTERPOS4FPROC ast_glRasterPos4f = 0;
PFNGLRASTERPOS4FVPROC ast_glRasterPos4fv = 0;
PFNGLRASTERPOS4IPROC ast_glRasterPos4i = 0;
PFNGLRASTERPOS4IVPROC ast_glRasterPos4iv = 0;
PFNGLRASTERPOS4SPROC ast_glRasterPos4s = 0;
PFNGLRASTERPOS4SVPROC ast_glRasterPos4sv = 0;
PFNGLREADBUFFERPROC ast_glReadBuffer = 0;
PFNGLREADPIXELSPROC ast_glReadPixels = 0;
PFNGLRECTDPROC ast_glRectd = 0;
PFNGLRECTDVPROC ast_glRectdv = 0;
PFNGLRECTFPROC ast_glRectf = 0;
PFNGLRECTFVPROC ast_glRectfv = 0;
PFNGLRECTIPROC ast_glRecti = 0;
PFNGLRECTIVPROC ast_glRectiv = 0;
PFNGLRECTSPROC ast_glRects = 0;
PFNGLRECTSVPROC ast_glRectsv = 0;
PFNGLRENDERMODEPROC ast_glRenderMode = 0;
PFNGLRENDERBUFFERSTORAGEPROC ast_glRenderbufferStorage = 0;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC ast_glRenderbufferStorageMultisample = 0;
PFNGLROTATEDPROC ast_glRotated = 0;
PFNGLROTATEFPROC ast_glRotatef = 0;
PFNGLSAMPLECOVERAGEPROC ast_glSampleCoverage = 0;
PFNGLSCALEDPROC ast_glScaled = 0;
PFNGLSCALEFPROC ast_glScalef = 0;
PFNGLSCISSORPROC ast_glScissor = 0;
PFNGLSECONDARYCOLOR3BPROC ast_glSecondaryColor3b = 0;
PFNGLSECONDARYCOLOR3BVPROC ast_glSecondaryColor3bv = 0;
PFNGLSECONDARYCOLOR3DPROC ast_glSecondaryColor3d = 0;
PFNGLSECONDARYCOLOR3DVPROC ast_glSecondaryColor3dv = 0;
PFNGLSECONDARYCOLOR3FPROC ast_glSecondaryColor3f = 0;
PFNGLSECONDARYCOLOR3FVPROC ast_glSecondaryColor3fv = 0;
PFNGLSECONDARYCOLOR3IPROC ast_glSecondaryColor3i = 0;
PFNGLSECONDARYCOLOR3IVPROC ast_glSecondaryColor3iv = 0;
PFNGLSECONDARYCOLOR3SPROC ast_glSecondaryColor3s = 0;
PFNGLSECONDARYCOLOR3SVPROC ast_glSecondaryColor3sv = 0;
PFNGLSECONDARYCOLOR3UBPROC ast_glSecondaryColor3ub = 0;
PFNGLSECONDARYCOLOR3UBVPROC ast_glSecondaryColor3ubv = 0;
PFNGLSECONDARYCOLOR3UIPROC ast_glSecondaryColor3ui = 0;
PFNGLSECONDARYCOLOR3UIVPROC ast_glSecondaryColor3uiv = 0;
PFNGLSECONDARYCOLOR3USPROC ast_glSecondaryColor3us = 0;
PFNGLSECONDARYCOLOR3USVPROC ast_glSecondaryColor3usv = 0;
PFNGLSECONDARYCOLORPOINTERPROC ast_glSecondaryColorPointer = 0;
PFNGLSELECTBUFFERPROC ast_glSelectBuffer = 0;
PFNGLSHADEMODELPROC ast_glShadeModel = 0;
PFNGLSHADERSOURCEPROC ast_glShaderSource = 0;
PFNGLSTENCILFUNCPROC ast_glStencilFunc = 0;
PFNGLSTENCILFUNCSEPARATEPROC ast_glStencilFuncSeparate = 0;
PFNGLSTENCILMASKPROC ast_glStencilMask = 0;
PFNGLSTENCILMASKSEPARATEPROC ast_glStencilMaskSeparate = 0;
PFNGLSTENCILOPPROC ast_glStencilOp = 0;
PFNGLSTENCILOPSEPARATEPROC ast_glStencilOpSeparate = 0;
PFNGLTEXBUFFERPROC ast_glTexBuffer = 0;
PFNGLTEXCOORD1DPROC ast_glTexCoord1d = 0;
PFNGLTEXCOORD1DVPROC ast_glTexCoord1dv = 0;
PFNGLTEXCOORD1FPROC ast_glTexCoord1f = 0;
PFNGLTEXCOORD1FVPROC ast_glTexCoord1fv = 0;
PFNGLTEXCOORD1IPROC ast_glTexCoord1i = 0;
PFNGLTEXCOORD1IVPROC ast_glTexCoord1iv = 0;
PFNGLTEXCOORD1SPROC ast_glTexCoord1s = 0;
PFNGLTEXCOORD1SVPROC ast_glTexCoord1sv = 0;
PFNGLTEXCOORD2DPROC ast_glTexCoord2d = 0;
PFNGLTEXCOORD2DVPROC ast_glTexCoord2dv = 0;
PFNGLTEXCOORD2FPROC ast_glTexCoord2f = 0;
PFNGLTEXCOORD2FVPROC ast_glTexCoord2fv = 0;
PFNGLTEXCOORD2IPROC ast_glTexCoord2i = 0;
PFNGLTEXCOORD2IVPROC ast_glTexCoord2iv = 0;
PFNGLTEXCOORD2SPROC ast_glTexCoord2s = 0;
PFNGLTEXCOORD2SVPROC ast_glTexCoord2sv = 0;
PFNGLTEXCOORD3DPROC ast_glTexCoord3d = 0;
PFNGLTEXCOORD3DVPROC ast_glTexCoord3dv = 0;
PFNGLTEXCOORD3FPROC ast_glTexCoord3f = 0;
PFNGLTEXCOORD3FVPROC ast_glTexCoord3fv = 0;
PFNGLTEXCOORD3IPROC ast_glTexCoord3i = 0;
PFNGLTEXCOORD3IVPROC ast_glTexCoord3iv = 0;
PFNGLTEXCOORD3SPROC ast_glTexCoord3s = 0;
PFNGLTEXCOORD3SVPROC ast_glTexCoord3sv = 0;
PFNGLTEXCOORD4DPROC ast_glTexCoord4d = 0;
PFNGLTEXCOORD4DVPROC ast_glTexCoord4dv = 0;
PFNGLTEXCOORD4FPROC ast_glTexCoord4f = 0;
PFNGLTEXCOORD4FVPROC ast_glTexCoord4fv = 0;
PFNGLTEXCOORD4IPROC ast_glTexCoord4i = 0;
PFNGLTEXCOORD4IVPROC ast_glTexCoord4iv = 0;
PFNGLTEXCOORD4SPROC ast_glTexCoord4s = 0;
PFNGLTEXCOORD4SVPROC ast_glTexCoord4sv = 0;
PFNGLTEXCOORDPOINTERPROC ast_glTexCoordPointer = 0;
PFNGLTEXENVFPROC ast_glTexEnvf = 0;
PFNGLTEXENVFVPROC ast_glTexEnvfv = 0;
PFNGLTEXENVIPROC ast_glTexEnvi = 0;
PFNGLTEXENVIVPROC ast_glTexEnviv = 0;
PFNGLTEXGENDPROC ast_glTexGend = 0;
PFNGLTEXGENDVPROC ast_glTexGendv = 0;
PFNGLTEXGENFPROC ast_glTexGenf = 0;
PFNGLTEXGENFVPROC ast_glTexGenfv = 0;
PFNGLTEXGENIPROC ast_glTexGeni = 0;
PFNGLTEXGENIVPROC ast_glTexGeniv = 0;
PFNGLTEXIMAGE1DPROC ast_glTexImage1D = 0;
PFNGLTEXIMAGE2DPROC ast_glTexImage2D = 0;
PFNGLTEXIMAGE3DPROC ast_glTexImage3D = 0;
PFNGLTEXPARAMETERIIVPROC ast_glTexParameterIiv = 0;
PFNGLTEXPARAMETERIUIVPROC ast_glTexParameterIuiv = 0;
PFNGLTEXPARAMETERFPROC ast_glTexParameterf = 0;
PFNGLTEXPARAMETERFVPROC ast_glTexParameterfv = 0;
PFNGLTEXPARAMETERIPROC ast_glTexParameteri = 0;
PFNGLTEXPARAMETERIVPROC ast_glTexParameteriv = 0;
PFNGLTEXSUBIMAGE1DPROC ast_glTexSubImage1D = 0;
PFNGLTEXSUBIMAGE2DPROC ast_glTexSubImage2D = 0;
PFNGLTEXSUBIMAGE3DPROC ast_glTexSubImage3D = 0;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC ast_glTransformFeedbackVaryings = 0;
PFNGLTRANSLATEDPROC ast_glTranslated = 0;
PFNGLTRANSLATEFPROC ast_glTranslatef = 0;
PFNGLUNIFORM1FPROC ast_glUniform1f = 0;
PFNGLUNIFORM1FVPROC ast_glUniform1fv = 0;
PFNGLUNIFORM1IPROC ast_glUniform1i = 0;
PFNGLUNIFORM1IVPROC ast_glUniform1iv = 0;
PFNGLUNIFORM1UIPROC ast_glUniform1ui = 0;
PFNGLUNIFORM1UIVPROC ast_glUniform1uiv = 0;
PFNGLUNIFORM2FPROC ast_glUniform2f = 0;
PFNGLUNIFORM2FVPROC ast_glUniform2fv = 0;
PFNGLUNIFORM2IPROC ast_glUniform2i = 0;
PFNGLUNIFORM2IVPROC ast_glUniform2iv = 0;
PFNGLUNIFORM2UIPROC ast_glUniform2ui = 0;
PFNGLUNIFORM2UIVPROC ast_glUniform2uiv = 0;
PFNGLUNIFORM3FPROC ast_glUniform3f = 0;
PFNGLUNIFORM3FVPROC ast_glUniform3fv = 0;
PFNGLUNIFORM3IPROC ast_glUniform3i = 0;
PFNGLUNIFORM3IVPROC ast_glUniform3iv = 0;
PFNGLUNIFORM3UIPROC ast_glUniform3ui = 0;
PFNGLUNIFORM3UIVPROC ast_glUniform3uiv = 0;
PFNGLUNIFORM4FPROC ast_glUniform4f = 0;
PFNGLUNIFORM4FVPROC ast_glUniform4fv = 0;
PFNGLUNIFORM4IPROC ast_glUniform4i = 0;
PFNGLUNIFORM4IVPROC ast_glUniform4iv = 0;
PFNGLUNIFORM4UIPROC ast_glUniform4ui = 0;
PFNGLUNIFORM4UIVPROC ast_glUniform4uiv = 0;
PFNGLUNIFORMBLOCKBINDINGPROC ast_glUniformBlockBinding = 0;
PFNGLUNIFORMMATRIX2FVPROC ast_glUniformMatrix2fv = 0;
PFNGLUNIFORMMATRIX2X3FVPROC ast_glUniformMatrix2x3fv = 0;
PFNGLUNIFORMMATRIX2X4FVPROC ast_glUniformMatrix2x4fv = 0;
PFNGLUNIFORMMATRIX3FVPROC ast_glUniformMatrix3fv = 0;
PFNGLUNIFORMMATRIX3X2FVPROC ast_glUniformMatrix3x2fv = 0;
PFNGLUNIFORMMATRIX3X4FVPROC ast_glUniformMatrix3x4fv = 0;
PFNGLUNIFORMMATRIX4FVPROC ast_glUniformMatrix4fv = 0;
PFNGLUNIFORMMATRIX4X2FVPROC ast_glUniformMatrix4x2fv = 0;
PFNGLUNIFORMMATRIX4X3FVPROC ast_glUniformMatrix4x3fv = 0;
PFNGLUNMAPBUFFERPROC ast_glUnmapBuffer = 0;
PFNGLUSEPROGRAMPROC ast_glUseProgram = 0;
PFNGLVALIDATEPROGRAMPROC ast_glValidateProgram = 0;
PFNGLVERTEX2DPROC ast_glVertex2d = 0;
PFNGLVERTEX2DVPROC ast_glVertex2dv = 0;
PFNGLVERTEX2FPROC ast_glVertex2f = 0;
PFNGLVERTEX2FVPROC ast_glVertex2fv = 0;
PFNGLVERTEX2IPROC ast_glVertex2i = 0;
PFNGLVERTEX2IVPROC ast_glVertex2iv = 0;
PFNGLVERTEX2SPROC ast_glVertex2s = 0;
PFNGLVERTEX2SVPROC ast_glVertex2sv = 0;
PFNGLVERTEX3DPROC ast_glVertex3d = 0;
PFNGLVERTEX3DVPROC ast_glVertex3dv = 0;
PFNGLVERTEX3FPROC ast_glVertex3f = 0;
PFNGLVERTEX3FVPROC ast_glVertex3fv = 0;
PFNGLVERTEX3IPROC ast_glVertex3i = 0;
PFNGLVERTEX3IVPROC ast_glVertex3iv = 0;
PFNGLVERTEX3SPROC ast_glVertex3s = 0;
PFNGLVERTEX3SVPROC ast_glVertex3sv = 0;
PFNGLVERTEX4DPROC ast_glVertex4d = 0;
PFNGLVERTEX4DVPROC ast_glVertex4dv = 0;
PFNGLVERTEX4FPROC ast_glVertex4f = 0;
PFNGLVERTEX4FVPROC ast_glVertex4fv = 0;
PFNGLVERTEX4IPROC ast_glVertex4i = 0;
PFNGLVERTEX4IVPROC ast_glVertex4iv = 0;
PFNGLVERTEX4SPROC ast_glVertex4s = 0;
PFNGLVERTEX4SVPROC ast_glVertex4sv = 0;
PFNGLVERTEXATTRIB1DPROC ast_glVertexAttrib1d = 0;
PFNGLVERTEXATTRIB1DVPROC ast_glVertexAttrib1dv = 0;
PFNGLVERTEXATTRIB1FPROC ast_glVertexAttrib1f = 0;
PFNGLVERTEXATTRIB1FVPROC ast_glVertexAttrib1fv = 0;
PFNGLVERTEXATTRIB1SPROC ast_glVertexAttrib1s = 0;
PFNGLVERTEXATTRIB1SVPROC ast_glVertexAttrib1sv = 0;
PFNGLVERTEXATTRIB2DPROC ast_glVertexAttrib2d = 0;
PFNGLVERTEXATTRIB2DVPROC ast_glVertexAttrib2dv = 0;
PFNGLVERTEXATTRIB2FPROC ast_glVertexAttrib2f = 0;
PFNGLVERTEXATTRIB2FVPROC ast_glVertexAttrib2fv = 0;
PFNGLVERTEXATTRIB2SPROC ast_glVertexAttrib2s = 0;
PFNGLVERTEXATTRIB2SVPROC ast_glVertexAttrib2sv = 0;
PFNGLVERTEXATTRIB3DPROC ast_glVertexAttrib3d = 0;
PFNGLVERTEXATTRIB3DVPROC ast_glVertexAttrib3dv = 0;
PFNGLVERTEXATTRIB3FPROC ast_glVertexAttrib3f = 0;
PFNGLVERTEXATTRIB3FVPROC ast_glVertexAttrib3fv = 0;
PFNGLVERTEXATTRIB3SPROC ast_glVertexAttrib3s = 0;
PFNGLVERTEXATTRIB3SVPROC ast_glVertexAttrib3sv = 0;
PFNGLVERTEXATTRIB4NBVPROC ast_glVertexAttrib4Nbv = 0;
PFNGLVERTEXATTRIB4NIVPROC ast_glVertexAttrib4Niv = 0;
PFNGLVERTEXATTRIB4NSVPROC ast_glVertexAttrib4Nsv = 0;
PFNGLVERTEXATTRIB4NUBPROC ast_glVertexAttrib4Nub = 0;
PFNGLVERTEXATTRIB4NUBVPROC ast_glVertexAttrib4Nubv = 0;
PFNGLVERTEXATTRIB4NUIVPROC ast_glVertexAttrib4Nuiv = 0;
PFNGLVERTEXATTRIB4NUSVPROC ast_glVertexAttrib4Nusv = 0;
PFNGLVERTEXATTRIB4BVPROC ast_glVertexAttrib4bv = 0;
PFNGLVERTEXATTRIB4DPROC ast_glVertexAttrib4d = 0;
PFNGLVERTEXATTRIB4DVPROC ast_glVertexAttrib4dv = 0;
PFNGLVERTEXATTRIB4FPROC ast_glVertexAttrib4f = 0;
PFNGLVERTEXATTRIB4FVPROC ast_glVertexAttrib4fv = 0;
PFNGLVERTEXATTRIB4IVPROC ast_glVertexAttrib4iv = 0;
PFNGLVERTEXATTRIB4SPROC ast_glVertexAttrib4s = 0;
PFNGLVERTEXATTRIB4SVPROC ast_glVertexAttrib4sv = 0;
PFNGLVERTEXATTRIB4UBVPROC ast_glVertexAttrib4ubv = 0;
PFNGLVERTEXATTRIB4UIVPROC ast_glVertexAttrib4uiv = 0;
PFNGLVERTEXATTRIB4USVPROC ast_glVertexAttrib4usv = 0;
PFNGLVERTEXATTRIBI1IPROC ast_glVertexAttribI1i = 0;
PFNGLVERTEXATTRIBI1IVPROC ast_glVertexAttribI1iv = 0;
PFNGLVERTEXATTRIBI1UIPROC ast_glVertexAttribI1ui = 0;
PFNGLVERTEXATTRIBI1UIVPROC ast_glVertexAttribI1uiv = 0;
PFNGLVERTEXATTRIBI2IPROC ast_glVertexAttribI2i = 0;
PFNGLVERTEXATTRIBI2IVPROC ast_glVertexAttribI2iv = 0;
PFNGLVERTEXATTRIBI2UIPROC ast_glVertexAttribI2ui = 0;
PFNGLVERTEXATTRIBI2UIVPROC ast_glVertexAttribI2uiv = 0;
PFNGLVERTEXATTRIBI3IPROC ast_glVertexAttribI3i = 0;
PFNGLVERTEXATTRIBI3IVPROC ast_glVertexAttribI3iv = 0;
PFNGLVERTEXATTRIBI3UIPROC ast_glVertexAttribI3ui = 0;
PFNGLVERTEXATTRIBI3UIVPROC ast_glVertexAttribI3uiv = 0;
PFNGLVERTEXATTRIBI4BVPROC ast_glVertexAttribI4bv = 0;
PFNGLVERTEXATTRIBI4IPROC ast_glVertexAttribI4i = 0;
PFNGLVERTEXATTRIBI4IVPROC ast_glVertexAttribI4iv = 0;
PFNGLVERTEXATTRIBI4SVPROC ast_glVertexAttribI4sv = 0;
PFNGLVERTEXATTRIBI4UBVPROC ast_glVertexAttribI4ubv = 0;
PFNGLVERTEXATTRIBI4UIPROC ast_glVertexAttribI4ui = 0;
PFNGLVERTEXATTRIBI4UIVPROC ast_glVertexAttribI4uiv = 0;
PFNGLVERTEXATTRIBI4USVPROC ast_glVertexAttribI4usv = 0;
PFNGLVERTEXATTRIBIPOINTERPROC ast_glVertexAttribIPointer = 0;
PFNGLVERTEXATTRIBPOINTERPROC ast_glVertexAttribPointer = 0;
PFNGLVERTEXPOINTERPROC ast_glVertexPointer = 0;
PFNGLVIEWPORTPROC ast_glViewport = 0;
PFNGLWINDOWPOS2DPROC ast_glWindowPos2d = 0;
PFNGLWINDOWPOS2DVPROC ast_glWindowPos2dv = 0;
PFNGLWINDOWPOS2FPROC ast_glWindowPos2f = 0;
PFNGLWINDOWPOS2FVPROC ast_glWindowPos2fv = 0;
PFNGLWINDOWPOS2IPROC ast_glWindowPos2i = 0;
PFNGLWINDOWPOS2IVPROC ast_glWindowPos2iv = 0;
PFNGLWINDOWPOS2SPROC ast_glWindowPos2s = 0;
PFNGLWINDOWPOS2SVPROC ast_glWindowPos2sv = 0;
PFNGLWINDOWPOS3DPROC ast_glWindowPos3d = 0;
PFNGLWINDOWPOS3DVPROC ast_glWindowPos3dv = 0;
PFNGLWINDOWPOS3FPROC ast_glWindowPos3f = 0;
PFNGLWINDOWPOS3FVPROC ast_glWindowPos3fv = 0;
PFNGLWINDOWPOS3IPROC ast_glWindowPos3i = 0;
PFNGLWINDOWPOS3IVPROC ast_glWindowPos3iv = 0;
PFNGLWINDOWPOS3SPROC ast_glWindowPos3s = 0;
PFNGLWINDOWPOS3SVPROC ast_glWindowPos3sv = 0;


// Function loaders
//
//


internal void
Load_GL_VERSION_1_0(ASTLoadProc LoadOpenGLProc)
{
    if(AST_GL_VERSION_1_0)
    {
        ast_glCullFace = (PFNGLCULLFACEPROC)LoadOpenGLProc("glCullFace");
        ast_glFrontFace = (PFNGLFRONTFACEPROC)LoadOpenGLProc("glFrontFace");
        ast_glHint = (PFNGLHINTPROC)LoadOpenGLProc("glHint");
        ast_glLineWidth = (PFNGLLINEWIDTHPROC)LoadOpenGLProc("glLineWidth");
        ast_glPointSize = (PFNGLPOINTSIZEPROC)LoadOpenGLProc("glPointSize");
        ast_glPolygonMode = (PFNGLPOLYGONMODEPROC)LoadOpenGLProc("glPolygonMode");
        ast_glScissor = (PFNGLSCISSORPROC)LoadOpenGLProc("glScissor");
        ast_glTexParameterf = (PFNGLTEXPARAMETERFPROC)LoadOpenGLProc("glTexParameterf");
        ast_glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)LoadOpenGLProc("glTexParameterfv");
        ast_glTexParameteri = (PFNGLTEXPARAMETERIPROC)LoadOpenGLProc("glTexParameteri");
        ast_glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)LoadOpenGLProc("glTexParameteriv");
        ast_glTexImage1D = (PFNGLTEXIMAGE1DPROC)LoadOpenGLProc("glTexImage1D");
        ast_glTexImage2D = (PFNGLTEXIMAGE2DPROC)LoadOpenGLProc("glTexImage2D");
        ast_glDrawBuffer = (PFNGLDRAWBUFFERPROC)LoadOpenGLProc("glDrawBuffer");
        ast_glClear = (PFNGLCLEARPROC)LoadOpenGLProc("glClear");
        ast_glClearColor = (PFNGLCLEARCOLORPROC)LoadOpenGLProc("glClearColor");
        ast_glClearStencil = (PFNGLCLEARSTENCILPROC)LoadOpenGLProc("glClearStencil");
        ast_glClearDepth = (PFNGLCLEARDEPTHPROC)LoadOpenGLProc("glClearDepth");
        ast_glStencilMask = (PFNGLSTENCILMASKPROC)LoadOpenGLProc("glStencilMask");
        ast_glColorMask = (PFNGLCOLORMASKPROC)LoadOpenGLProc("glColorMask");
        ast_glDepthMask = (PFNGLDEPTHMASKPROC)LoadOpenGLProc("glDepthMask");
        ast_glDisable = (PFNGLDISABLEPROC)LoadOpenGLProc("glDisable");
        ast_glEnable = (PFNGLENABLEPROC)LoadOpenGLProc("glEnable");
        ast_glFinish = (PFNGLFINISHPROC)LoadOpenGLProc("glFinish");
        ast_glFlush = (PFNGLFLUSHPROC)LoadOpenGLProc("glFlush");
        ast_glBlendFunc = (PFNGLBLENDFUNCPROC)LoadOpenGLProc("glBlendFunc");
        ast_glLogicOp = (PFNGLLOGICOPPROC)LoadOpenGLProc("glLogicOp");
        ast_glStencilFunc = (PFNGLSTENCILFUNCPROC)LoadOpenGLProc("glStencilFunc");
        ast_glStencilOp = (PFNGLSTENCILOPPROC)LoadOpenGLProc("glStencilOp");
        ast_glDepthFunc = (PFNGLDEPTHFUNCPROC)LoadOpenGLProc("glDepthFunc");
        ast_glPixelStoref = (PFNGLPIXELSTOREFPROC)LoadOpenGLProc("glPixelStoref");
        ast_glPixelStorei = (PFNGLPIXELSTOREIPROC)LoadOpenGLProc("glPixelStorei");
        ast_glReadBuffer = (PFNGLREADBUFFERPROC)LoadOpenGLProc("glReadBuffer");
        ast_glReadPixels = (PFNGLREADPIXELSPROC)LoadOpenGLProc("glReadPixels");
        ast_glGetBooleanv = (PFNGLGETBOOLEANVPROC)LoadOpenGLProc("glGetBooleanv");
        ast_glGetDoublev = (PFNGLGETDOUBLEVPROC)LoadOpenGLProc("glGetDoublev");
        ast_glGetError = (PFNGLGETERRORPROC)LoadOpenGLProc("glGetError");
        ast_glGetFloatv = (PFNGLGETFLOATVPROC)LoadOpenGLProc("glGetFloatv");
        ast_glGetIntegerv = (PFNGLGETINTEGERVPROC)LoadOpenGLProc("glGetIntegerv");
        ast_glGetString = (PFNGLGETSTRINGPROC)LoadOpenGLProc("glGetString");
        ast_glGetTexImage = (PFNGLGETTEXIMAGEPROC)LoadOpenGLProc("glGetTexImage");
        ast_glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)LoadOpenGLProc("glGetTexParameterfv");
        ast_glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)LoadOpenGLProc("glGetTexParameteriv");
        ast_glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC)LoadOpenGLProc("glGetTexLevelParameterfv");
        ast_glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC)LoadOpenGLProc("glGetTexLevelParameteriv");
        ast_glIsEnabled = (PFNGLISENABLEDPROC)LoadOpenGLProc("glIsEnabled");
        ast_glDepthRange = (PFNGLDEPTHRANGEPROC)LoadOpenGLProc("glDepthRange");
        ast_glViewport = (PFNGLVIEWPORTPROC)LoadOpenGLProc("glViewport");
        ast_glNewList = (PFNGLNEWLISTPROC)LoadOpenGLProc("glNewList");
        ast_glEndList = (PFNGLENDLISTPROC)LoadOpenGLProc("glEndList");
        ast_glCallList = (PFNGLCALLLISTPROC)LoadOpenGLProc("glCallList");
        ast_glCallLists = (PFNGLCALLLISTSPROC)LoadOpenGLProc("glCallLists");
        ast_glDeleteLists = (PFNGLDELETELISTSPROC)LoadOpenGLProc("glDeleteLists");
        ast_glGenLists = (PFNGLGENLISTSPROC)LoadOpenGLProc("glGenLists");
        ast_glListBase = (PFNGLLISTBASEPROC)LoadOpenGLProc("glListBase");
        ast_glBegin = (PFNGLBEGINPROC)LoadOpenGLProc("glBegin");
        ast_glBitmap = (PFNGLBITMAPPROC)LoadOpenGLProc("glBitmap");
        ast_glColor3b = (PFNGLCOLOR3BPROC)LoadOpenGLProc("glColor3b");
        ast_glColor3bv = (PFNGLCOLOR3BVPROC)LoadOpenGLProc("glColor3bv");
        ast_glColor3d = (PFNGLCOLOR3DPROC)LoadOpenGLProc("glColor3d");
        ast_glColor3dv = (PFNGLCOLOR3DVPROC)LoadOpenGLProc("glColor3dv");
        ast_glColor3f = (PFNGLCOLOR3FPROC)LoadOpenGLProc("glColor3f");
        ast_glColor3fv = (PFNGLCOLOR3FVPROC)LoadOpenGLProc("glColor3fv");
        ast_glColor3i = (PFNGLCOLOR3IPROC)LoadOpenGLProc("glColor3i");
        ast_glColor3iv = (PFNGLCOLOR3IVPROC)LoadOpenGLProc("glColor3iv");
        ast_glColor3s = (PFNGLCOLOR3SPROC)LoadOpenGLProc("glColor3s");
        ast_glColor3sv = (PFNGLCOLOR3SVPROC)LoadOpenGLProc("glColor3sv");
        ast_glColor3ub = (PFNGLCOLOR3UBPROC)LoadOpenGLProc("glColor3ub");
        ast_glColor3ubv = (PFNGLCOLOR3UBVPROC)LoadOpenGLProc("glColor3ubv");
        ast_glColor3ui = (PFNGLCOLOR3UIPROC)LoadOpenGLProc("glColor3ui");
        ast_glColor3uiv = (PFNGLCOLOR3UIVPROC)LoadOpenGLProc("glColor3uiv");
        ast_glColor3us = (PFNGLCOLOR3USPROC)LoadOpenGLProc("glColor3us");
        ast_glColor3usv = (PFNGLCOLOR3USVPROC)LoadOpenGLProc("glColor3usv");
        ast_glColor4b = (PFNGLCOLOR4BPROC)LoadOpenGLProc("glColor4b");
        ast_glColor4bv = (PFNGLCOLOR4BVPROC)LoadOpenGLProc("glColor4bv");
        ast_glColor4d = (PFNGLCOLOR4DPROC)LoadOpenGLProc("glColor4d");
        ast_glColor4dv = (PFNGLCOLOR4DVPROC)LoadOpenGLProc("glColor4dv");
        ast_glColor4f = (PFNGLCOLOR4FPROC)LoadOpenGLProc("glColor4f");
        ast_glColor4fv = (PFNGLCOLOR4FVPROC)LoadOpenGLProc("glColor4fv");
        ast_glColor4i = (PFNGLCOLOR4IPROC)LoadOpenGLProc("glColor4i");
        ast_glColor4iv = (PFNGLCOLOR4IVPROC)LoadOpenGLProc("glColor4iv");
        ast_glColor4s = (PFNGLCOLOR4SPROC)LoadOpenGLProc("glColor4s");
        ast_glColor4sv = (PFNGLCOLOR4SVPROC)LoadOpenGLProc("glColor4sv");
        ast_glColor4ub = (PFNGLCOLOR4UBPROC)LoadOpenGLProc("glColor4ub");
        ast_glColor4ubv = (PFNGLCOLOR4UBVPROC)LoadOpenGLProc("glColor4ubv");
        ast_glColor4ui = (PFNGLCOLOR4UIPROC)LoadOpenGLProc("glColor4ui");
        ast_glColor4uiv = (PFNGLCOLOR4UIVPROC)LoadOpenGLProc("glColor4uiv");
        ast_glColor4us = (PFNGLCOLOR4USPROC)LoadOpenGLProc("glColor4us");
        ast_glColor4usv = (PFNGLCOLOR4USVPROC)LoadOpenGLProc("glColor4usv");
        ast_glEdgeFlag = (PFNGLEDGEFLAGPROC)LoadOpenGLProc("glEdgeFlag");
        ast_glEdgeFlagv = (PFNGLEDGEFLAGVPROC)LoadOpenGLProc("glEdgeFlagv");
        ast_glEnd = (PFNGLENDPROC)LoadOpenGLProc("glEnd");
        ast_glIndexd = (PFNGLINDEXDPROC)LoadOpenGLProc("glIndexd");
        ast_glIndexdv = (PFNGLINDEXDVPROC)LoadOpenGLProc("glIndexdv");
        ast_glIndexf = (PFNGLINDEXFPROC)LoadOpenGLProc("glIndexf");
        ast_glIndexfv = (PFNGLINDEXFVPROC)LoadOpenGLProc("glIndexfv");
        ast_glIndexi = (PFNGLINDEXIPROC)LoadOpenGLProc("glIndexi");
        ast_glIndexiv = (PFNGLINDEXIVPROC)LoadOpenGLProc("glIndexiv");
        ast_glIndexs = (PFNGLINDEXSPROC)LoadOpenGLProc("glIndexs");
        ast_glIndexsv = (PFNGLINDEXSVPROC)LoadOpenGLProc("glIndexsv");
        ast_glNormal3b = (PFNGLNORMAL3BPROC)LoadOpenGLProc("glNormal3b");
        ast_glNormal3bv = (PFNGLNORMAL3BVPROC)LoadOpenGLProc("glNormal3bv");
        ast_glNormal3d = (PFNGLNORMAL3DPROC)LoadOpenGLProc("glNormal3d");
        ast_glNormal3dv = (PFNGLNORMAL3DVPROC)LoadOpenGLProc("glNormal3dv");
        ast_glNormal3f = (PFNGLNORMAL3FPROC)LoadOpenGLProc("glNormal3f");
        ast_glNormal3fv = (PFNGLNORMAL3FVPROC)LoadOpenGLProc("glNormal3fv");
        ast_glNormal3i = (PFNGLNORMAL3IPROC)LoadOpenGLProc("glNormal3i");
        ast_glNormal3iv = (PFNGLNORMAL3IVPROC)LoadOpenGLProc("glNormal3iv");
        ast_glNormal3s = (PFNGLNORMAL3SPROC)LoadOpenGLProc("glNormal3s");
        ast_glNormal3sv = (PFNGLNORMAL3SVPROC)LoadOpenGLProc("glNormal3sv");
        ast_glRasterPos2d = (PFNGLRASTERPOS2DPROC)LoadOpenGLProc("glRasterPos2d");
        ast_glRasterPos2dv = (PFNGLRASTERPOS2DVPROC)LoadOpenGLProc("glRasterPos2dv");
        ast_glRasterPos2f = (PFNGLRASTERPOS2FPROC)LoadOpenGLProc("glRasterPos2f");
        ast_glRasterPos2fv = (PFNGLRASTERPOS2FVPROC)LoadOpenGLProc("glRasterPos2fv");
        ast_glRasterPos2i = (PFNGLRASTERPOS2IPROC)LoadOpenGLProc("glRasterPos2i");
        ast_glRasterPos2iv = (PFNGLRASTERPOS2IVPROC)LoadOpenGLProc("glRasterPos2iv");
        ast_glRasterPos2s = (PFNGLRASTERPOS2SPROC)LoadOpenGLProc("glRasterPos2s");
        ast_glRasterPos2sv = (PFNGLRASTERPOS2SVPROC)LoadOpenGLProc("glRasterPos2sv");
        ast_glRasterPos3d = (PFNGLRASTERPOS3DPROC)LoadOpenGLProc("glRasterPos3d");
        ast_glRasterPos3dv = (PFNGLRASTERPOS3DVPROC)LoadOpenGLProc("glRasterPos3dv");
        ast_glRasterPos3f = (PFNGLRASTERPOS3FPROC)LoadOpenGLProc("glRasterPos3f");
        ast_glRasterPos3fv = (PFNGLRASTERPOS3FVPROC)LoadOpenGLProc("glRasterPos3fv");
        ast_glRasterPos3i = (PFNGLRASTERPOS3IPROC)LoadOpenGLProc("glRasterPos3i");
        ast_glRasterPos3iv = (PFNGLRASTERPOS3IVPROC)LoadOpenGLProc("glRasterPos3iv");
        ast_glRasterPos3s = (PFNGLRASTERPOS3SPROC)LoadOpenGLProc("glRasterPos3s");
        ast_glRasterPos3sv = (PFNGLRASTERPOS3SVPROC)LoadOpenGLProc("glRasterPos3sv");
        ast_glRasterPos4d = (PFNGLRASTERPOS4DPROC)LoadOpenGLProc("glRasterPos4d");
        ast_glRasterPos4dv = (PFNGLRASTERPOS4DVPROC)LoadOpenGLProc("glRasterPos4dv");
        ast_glRasterPos4f = (PFNGLRASTERPOS4FPROC)LoadOpenGLProc("glRasterPos4f");
        ast_glRasterPos4fv = (PFNGLRASTERPOS4FVPROC)LoadOpenGLProc("glRasterPos4fv");
        ast_glRasterPos4i = (PFNGLRASTERPOS4IPROC)LoadOpenGLProc("glRasterPos4i");
        ast_glRasterPos4iv = (PFNGLRASTERPOS4IVPROC)LoadOpenGLProc("glRasterPos4iv");
        ast_glRasterPos4s = (PFNGLRASTERPOS4SPROC)LoadOpenGLProc("glRasterPos4s");
        ast_glRasterPos4sv = (PFNGLRASTERPOS4SVPROC)LoadOpenGLProc("glRasterPos4sv");
        ast_glRectd = (PFNGLRECTDPROC)LoadOpenGLProc("glRectd");
        ast_glRectdv = (PFNGLRECTDVPROC)LoadOpenGLProc("glRectdv");
        ast_glRectf = (PFNGLRECTFPROC)LoadOpenGLProc("glRectf");
        ast_glRectfv = (PFNGLRECTFVPROC)LoadOpenGLProc("glRectfv");
        ast_glRecti = (PFNGLRECTIPROC)LoadOpenGLProc("glRecti");
        ast_glRectiv = (PFNGLRECTIVPROC)LoadOpenGLProc("glRectiv");
        ast_glRects = (PFNGLRECTSPROC)LoadOpenGLProc("glRects");
        ast_glRectsv = (PFNGLRECTSVPROC)LoadOpenGLProc("glRectsv");
        ast_glTexCoord1d = (PFNGLTEXCOORD1DPROC)LoadOpenGLProc("glTexCoord1d");
        ast_glTexCoord1dv = (PFNGLTEXCOORD1DVPROC)LoadOpenGLProc("glTexCoord1dv");
        ast_glTexCoord1f = (PFNGLTEXCOORD1FPROC)LoadOpenGLProc("glTexCoord1f");
        ast_glTexCoord1fv = (PFNGLTEXCOORD1FVPROC)LoadOpenGLProc("glTexCoord1fv");
        ast_glTexCoord1i = (PFNGLTEXCOORD1IPROC)LoadOpenGLProc("glTexCoord1i");
        ast_glTexCoord1iv = (PFNGLTEXCOORD1IVPROC)LoadOpenGLProc("glTexCoord1iv");
        ast_glTexCoord1s = (PFNGLTEXCOORD1SPROC)LoadOpenGLProc("glTexCoord1s");
        ast_glTexCoord1sv = (PFNGLTEXCOORD1SVPROC)LoadOpenGLProc("glTexCoord1sv");
        ast_glTexCoord2d = (PFNGLTEXCOORD2DPROC)LoadOpenGLProc("glTexCoord2d");
        ast_glTexCoord2dv = (PFNGLTEXCOORD2DVPROC)LoadOpenGLProc("glTexCoord2dv");
        ast_glTexCoord2f = (PFNGLTEXCOORD2FPROC)LoadOpenGLProc("glTexCoord2f");
        ast_glTexCoord2fv = (PFNGLTEXCOORD2FVPROC)LoadOpenGLProc("glTexCoord2fv");
        ast_glTexCoord2i = (PFNGLTEXCOORD2IPROC)LoadOpenGLProc("glTexCoord2i");
        ast_glTexCoord2iv = (PFNGLTEXCOORD2IVPROC)LoadOpenGLProc("glTexCoord2iv");
        ast_glTexCoord2s = (PFNGLTEXCOORD2SPROC)LoadOpenGLProc("glTexCoord2s");
        ast_glTexCoord2sv = (PFNGLTEXCOORD2SVPROC)LoadOpenGLProc("glTexCoord2sv");
        ast_glTexCoord3d = (PFNGLTEXCOORD3DPROC)LoadOpenGLProc("glTexCoord3d");
        ast_glTexCoord3dv = (PFNGLTEXCOORD3DVPROC)LoadOpenGLProc("glTexCoord3dv");
        ast_glTexCoord3f = (PFNGLTEXCOORD3FPROC)LoadOpenGLProc("glTexCoord3f");
        ast_glTexCoord3fv = (PFNGLTEXCOORD3FVPROC)LoadOpenGLProc("glTexCoord3fv");
        ast_glTexCoord3i = (PFNGLTEXCOORD3IPROC)LoadOpenGLProc("glTexCoord3i");
        ast_glTexCoord3iv = (PFNGLTEXCOORD3IVPROC)LoadOpenGLProc("glTexCoord3iv");
        ast_glTexCoord3s = (PFNGLTEXCOORD3SPROC)LoadOpenGLProc("glTexCoord3s");
        ast_glTexCoord3sv = (PFNGLTEXCOORD3SVPROC)LoadOpenGLProc("glTexCoord3sv");
        ast_glTexCoord4d = (PFNGLTEXCOORD4DPROC)LoadOpenGLProc("glTexCoord4d");
        ast_glTexCoord4dv = (PFNGLTEXCOORD4DVPROC)LoadOpenGLProc("glTexCoord4dv");
        ast_glTexCoord4f = (PFNGLTEXCOORD4FPROC)LoadOpenGLProc("glTexCoord4f");
        ast_glTexCoord4fv = (PFNGLTEXCOORD4FVPROC)LoadOpenGLProc("glTexCoord4fv");
        ast_glTexCoord4i = (PFNGLTEXCOORD4IPROC)LoadOpenGLProc("glTexCoord4i");
        ast_glTexCoord4iv = (PFNGLTEXCOORD4IVPROC)LoadOpenGLProc("glTexCoord4iv");
        ast_glTexCoord4s = (PFNGLTEXCOORD4SPROC)LoadOpenGLProc("glTexCoord4s");
        ast_glTexCoord4sv = (PFNGLTEXCOORD4SVPROC)LoadOpenGLProc("glTexCoord4sv");
        ast_glVertex2d = (PFNGLVERTEX2DPROC)LoadOpenGLProc("glVertex2d");
        ast_glVertex2dv = (PFNGLVERTEX2DVPROC)LoadOpenGLProc("glVertex2dv");
        ast_glVertex2f = (PFNGLVERTEX2FPROC)LoadOpenGLProc("glVertex2f");
        ast_glVertex2fv = (PFNGLVERTEX2FVPROC)LoadOpenGLProc("glVertex2fv");
        ast_glVertex2i = (PFNGLVERTEX2IPROC)LoadOpenGLProc("glVertex2i");
        ast_glVertex2iv = (PFNGLVERTEX2IVPROC)LoadOpenGLProc("glVertex2iv");
        ast_glVertex2s = (PFNGLVERTEX2SPROC)LoadOpenGLProc("glVertex2s");
        ast_glVertex2sv = (PFNGLVERTEX2SVPROC)LoadOpenGLProc("glVertex2sv");
        ast_glVertex3d = (PFNGLVERTEX3DPROC)LoadOpenGLProc("glVertex3d");
        ast_glVertex3dv = (PFNGLVERTEX3DVPROC)LoadOpenGLProc("glVertex3dv");
        ast_glVertex3f = (PFNGLVERTEX3FPROC)LoadOpenGLProc("glVertex3f");
        ast_glVertex3fv = (PFNGLVERTEX3FVPROC)LoadOpenGLProc("glVertex3fv");
        ast_glVertex3i = (PFNGLVERTEX3IPROC)LoadOpenGLProc("glVertex3i");
        ast_glVertex3iv = (PFNGLVERTEX3IVPROC)LoadOpenGLProc("glVertex3iv");
        ast_glVertex3s = (PFNGLVERTEX3SPROC)LoadOpenGLProc("glVertex3s");
        ast_glVertex3sv = (PFNGLVERTEX3SVPROC)LoadOpenGLProc("glVertex3sv");
        ast_glVertex4d = (PFNGLVERTEX4DPROC)LoadOpenGLProc("glVertex4d");
        ast_glVertex4dv = (PFNGLVERTEX4DVPROC)LoadOpenGLProc("glVertex4dv");
        ast_glVertex4f = (PFNGLVERTEX4FPROC)LoadOpenGLProc("glVertex4f");
        ast_glVertex4fv = (PFNGLVERTEX4FVPROC)LoadOpenGLProc("glVertex4fv");
        ast_glVertex4i = (PFNGLVERTEX4IPROC)LoadOpenGLProc("glVertex4i");
        ast_glVertex4iv = (PFNGLVERTEX4IVPROC)LoadOpenGLProc("glVertex4iv");
        ast_glVertex4s = (PFNGLVERTEX4SPROC)LoadOpenGLProc("glVertex4s");
        ast_glVertex4sv = (PFNGLVERTEX4SVPROC)LoadOpenGLProc("glVertex4sv");
        ast_glClipPlane = (PFNGLCLIPPLANEPROC)LoadOpenGLProc("glClipPlane");
        ast_glColorMaterial = (PFNGLCOLORMATERIALPROC)LoadOpenGLProc("glColorMaterial");
        ast_glFogf = (PFNGLFOGFPROC)LoadOpenGLProc("glFogf");
        ast_glFogfv = (PFNGLFOGFVPROC)LoadOpenGLProc("glFogfv");
        ast_glFogi = (PFNGLFOGIPROC)LoadOpenGLProc("glFogi");
        ast_glFogiv = (PFNGLFOGIVPROC)LoadOpenGLProc("glFogiv");
        ast_glLightf = (PFNGLLIGHTFPROC)LoadOpenGLProc("glLightf");
        ast_glLightfv = (PFNGLLIGHTFVPROC)LoadOpenGLProc("glLightfv");
        ast_glLighti = (PFNGLLIGHTIPROC)LoadOpenGLProc("glLighti");
        ast_glLightiv = (PFNGLLIGHTIVPROC)LoadOpenGLProc("glLightiv");
        ast_glLightModelf = (PFNGLLIGHTMODELFPROC)LoadOpenGLProc("glLightModelf");
        ast_glLightModelfv = (PFNGLLIGHTMODELFVPROC)LoadOpenGLProc("glLightModelfv");
        ast_glLightModeli = (PFNGLLIGHTMODELIPROC)LoadOpenGLProc("glLightModeli");
        ast_glLightModeliv = (PFNGLLIGHTMODELIVPROC)LoadOpenGLProc("glLightModeliv");
        ast_glLineStipple = (PFNGLLINESTIPPLEPROC)LoadOpenGLProc("glLineStipple");
        ast_glMaterialf = (PFNGLMATERIALFPROC)LoadOpenGLProc("glMaterialf");
        ast_glMaterialfv = (PFNGLMATERIALFVPROC)LoadOpenGLProc("glMaterialfv");
        ast_glMateriali = (PFNGLMATERIALIPROC)LoadOpenGLProc("glMateriali");
        ast_glMaterialiv = (PFNGLMATERIALIVPROC)LoadOpenGLProc("glMaterialiv");
        ast_glPolygonStipple = (PFNGLPOLYGONSTIPPLEPROC)LoadOpenGLProc("glPolygonStipple");
        ast_glShadeModel = (PFNGLSHADEMODELPROC)LoadOpenGLProc("glShadeModel");
        ast_glTexEnvf = (PFNGLTEXENVFPROC)LoadOpenGLProc("glTexEnvf");
        ast_glTexEnvfv = (PFNGLTEXENVFVPROC)LoadOpenGLProc("glTexEnvfv");
        ast_glTexEnvi = (PFNGLTEXENVIPROC)LoadOpenGLProc("glTexEnvi");
        ast_glTexEnviv = (PFNGLTEXENVIVPROC)LoadOpenGLProc("glTexEnviv");
        ast_glTexGend = (PFNGLTEXGENDPROC)LoadOpenGLProc("glTexGend");
        ast_glTexGendv = (PFNGLTEXGENDVPROC)LoadOpenGLProc("glTexGendv");
        ast_glTexGenf = (PFNGLTEXGENFPROC)LoadOpenGLProc("glTexGenf");
        ast_glTexGenfv = (PFNGLTEXGENFVPROC)LoadOpenGLProc("glTexGenfv");
        ast_glTexGeni = (PFNGLTEXGENIPROC)LoadOpenGLProc("glTexGeni");
        ast_glTexGeniv = (PFNGLTEXGENIVPROC)LoadOpenGLProc("glTexGeniv");
        ast_glFeedbackBuffer = (PFNGLFEEDBACKBUFFERPROC)LoadOpenGLProc("glFeedbackBuffer");
        ast_glSelectBuffer = (PFNGLSELECTBUFFERPROC)LoadOpenGLProc("glSelectBuffer");
        ast_glRenderMode = (PFNGLRENDERMODEPROC)LoadOpenGLProc("glRenderMode");
        ast_glInitNames = (PFNGLINITNAMESPROC)LoadOpenGLProc("glInitNames");
        ast_glLoadName = (PFNGLLOADNAMEPROC)LoadOpenGLProc("glLoadOpenGLProcName");
        ast_glPassThrough = (PFNGLPASSTHROUGHPROC)LoadOpenGLProc("glPassThrough");
        ast_glPopName = (PFNGLPOPNAMEPROC)LoadOpenGLProc("glPopName");
        ast_glPushName = (PFNGLPUSHNAMEPROC)LoadOpenGLProc("glPushName");
        ast_glClearAccum = (PFNGLCLEARACCUMPROC)LoadOpenGLProc("glClearAccum");
        ast_glClearIndex = (PFNGLCLEARINDEXPROC)LoadOpenGLProc("glClearIndex");
        ast_glIndexMask = (PFNGLINDEXMASKPROC)LoadOpenGLProc("glIndexMask");
        ast_glAccum = (PFNGLACCUMPROC)LoadOpenGLProc("glAccum");
        ast_glPopAttrib = (PFNGLPOPATTRIBPROC)LoadOpenGLProc("glPopAttrib");
        ast_glPushAttrib = (PFNGLPUSHATTRIBPROC)LoadOpenGLProc("glPushAttrib");
        ast_glMap1d = (PFNGLMAP1DPROC)LoadOpenGLProc("glMap1d");
        ast_glMap1f = (PFNGLMAP1FPROC)LoadOpenGLProc("glMap1f");
        ast_glMap2d = (PFNGLMAP2DPROC)LoadOpenGLProc("glMap2d");
        ast_glMap2f = (PFNGLMAP2FPROC)LoadOpenGLProc("glMap2f");
        ast_glMapGrid1d = (PFNGLMAPGRID1DPROC)LoadOpenGLProc("glMapGrid1d");
        ast_glMapGrid1f = (PFNGLMAPGRID1FPROC)LoadOpenGLProc("glMapGrid1f");
        ast_glMapGrid2d = (PFNGLMAPGRID2DPROC)LoadOpenGLProc("glMapGrid2d");
        ast_glMapGrid2f = (PFNGLMAPGRID2FPROC)LoadOpenGLProc("glMapGrid2f");
        ast_glEvalCoord1d = (PFNGLEVALCOORD1DPROC)LoadOpenGLProc("glEvalCoord1d");
        ast_glEvalCoord1dv = (PFNGLEVALCOORD1DVPROC)LoadOpenGLProc("glEvalCoord1dv");
        ast_glEvalCoord1f = (PFNGLEVALCOORD1FPROC)LoadOpenGLProc("glEvalCoord1f");
        ast_glEvalCoord1fv = (PFNGLEVALCOORD1FVPROC)LoadOpenGLProc("glEvalCoord1fv");
        ast_glEvalCoord2d = (PFNGLEVALCOORD2DPROC)LoadOpenGLProc("glEvalCoord2d");
        ast_glEvalCoord2dv = (PFNGLEVALCOORD2DVPROC)LoadOpenGLProc("glEvalCoord2dv");
        ast_glEvalCoord2f = (PFNGLEVALCOORD2FPROC)LoadOpenGLProc("glEvalCoord2f");
        ast_glEvalCoord2fv = (PFNGLEVALCOORD2FVPROC)LoadOpenGLProc("glEvalCoord2fv");
        ast_glEvalMesh1 = (PFNGLEVALMESH1PROC)LoadOpenGLProc("glEvalMesh1");
        ast_glEvalPoint1 = (PFNGLEVALPOINT1PROC)LoadOpenGLProc("glEvalPoint1");
        ast_glEvalMesh2 = (PFNGLEVALMESH2PROC)LoadOpenGLProc("glEvalMesh2");
        ast_glEvalPoint2 = (PFNGLEVALPOINT2PROC)LoadOpenGLProc("glEvalPoint2");
        ast_glAlphaFunc = (PFNGLALPHAFUNCPROC)LoadOpenGLProc("glAlphaFunc");
        ast_glPixelZoom = (PFNGLPIXELZOOMPROC)LoadOpenGLProc("glPixelZoom");
        ast_glPixelTransferf = (PFNGLPIXELTRANSFERFPROC)LoadOpenGLProc("glPixelTransferf");
        ast_glPixelTransferi = (PFNGLPIXELTRANSFERIPROC)LoadOpenGLProc("glPixelTransferi");
        ast_glPixelMapfv = (PFNGLPIXELMAPFVPROC)LoadOpenGLProc("glPixelMapfv");
        ast_glPixelMapuiv = (PFNGLPIXELMAPUIVPROC)LoadOpenGLProc("glPixelMapuiv");
        ast_glPixelMapusv = (PFNGLPIXELMAPUSVPROC)LoadOpenGLProc("glPixelMapusv");
        ast_glCopyPixels = (PFNGLCOPYPIXELSPROC)LoadOpenGLProc("glCopyPixels");
        ast_glDrawPixels = (PFNGLDRAWPIXELSPROC)LoadOpenGLProc("glDrawPixels");
        ast_glGetClipPlane = (PFNGLGETCLIPPLANEPROC)LoadOpenGLProc("glGetClipPlane");
        ast_glGetLightfv = (PFNGLGETLIGHTFVPROC)LoadOpenGLProc("glGetLightfv");
        ast_glGetLightiv = (PFNGLGETLIGHTIVPROC)LoadOpenGLProc("glGetLightiv");
        ast_glGetMapdv = (PFNGLGETMAPDVPROC)LoadOpenGLProc("glGetMapdv");
        ast_glGetMapfv = (PFNGLGETMAPFVPROC)LoadOpenGLProc("glGetMapfv");
        ast_glGetMapiv = (PFNGLGETMAPIVPROC)LoadOpenGLProc("glGetMapiv");
        ast_glGetMaterialfv = (PFNGLGETMATERIALFVPROC)LoadOpenGLProc("glGetMaterialfv");
        ast_glGetMaterialiv = (PFNGLGETMATERIALIVPROC)LoadOpenGLProc("glGetMaterialiv");
        ast_glGetPixelMapfv = (PFNGLGETPIXELMAPFVPROC)LoadOpenGLProc("glGetPixelMapfv");
        ast_glGetPixelMapuiv = (PFNGLGETPIXELMAPUIVPROC)LoadOpenGLProc("glGetPixelMapuiv");
        ast_glGetPixelMapusv = (PFNGLGETPIXELMAPUSVPROC)LoadOpenGLProc("glGetPixelMapusv");
        ast_glGetPolygonStipple = (PFNGLGETPOLYGONSTIPPLEPROC)LoadOpenGLProc("glGetPolygonStipple");
        ast_glGetTexEnvfv = (PFNGLGETTEXENVFVPROC)LoadOpenGLProc("glGetTexEnvfv");
        ast_glGetTexEnviv = (PFNGLGETTEXENVIVPROC)LoadOpenGLProc("glGetTexEnviv");
        ast_glGetTexGendv = (PFNGLGETTEXGENDVPROC)LoadOpenGLProc("glGetTexGendv");
        ast_glGetTexGenfv = (PFNGLGETTEXGENFVPROC)LoadOpenGLProc("glGetTexGenfv");
        ast_glGetTexGeniv = (PFNGLGETTEXGENIVPROC)LoadOpenGLProc("glGetTexGeniv");
        ast_glIsList = (PFNGLISLISTPROC)LoadOpenGLProc("glIsList");
        ast_glFrustum = (PFNGLFRUSTUMPROC)LoadOpenGLProc("glFrustum");
        ast_glLoadIdentity = (PFNGLLOADIDENTITYPROC)LoadOpenGLProc("glLoadOpenGLProcIdentity");
        ast_glLoadMatrixf = (PFNGLLOADMATRIXFPROC)LoadOpenGLProc("glLoadOpenGLProcMatrixf");
        ast_glLoadMatrixd = (PFNGLLOADMATRIXDPROC)LoadOpenGLProc("glLoadOpenGLProcMatrixd");
        ast_glMatrixMode = (PFNGLMATRIXMODEPROC)LoadOpenGLProc("glMatrixMode");
        ast_glMultMatrixf = (PFNGLMULTMATRIXFPROC)LoadOpenGLProc("glMultMatrixf");
        ast_glMultMatrixd = (PFNGLMULTMATRIXDPROC)LoadOpenGLProc("glMultMatrixd");
        ast_glOrtho = (PFNGLORTHOPROC)LoadOpenGLProc("glOrtho");
        ast_glPopMatrix = (PFNGLPOPMATRIXPROC)LoadOpenGLProc("glPopMatrix");
        ast_glPushMatrix = (PFNGLPUSHMATRIXPROC)LoadOpenGLProc("glPushMatrix");
        ast_glRotated = (PFNGLROTATEDPROC)LoadOpenGLProc("glRotated");
        ast_glRotatef = (PFNGLROTATEFPROC)LoadOpenGLProc("glRotatef");
        ast_glScaled = (PFNGLSCALEDPROC)LoadOpenGLProc("glScaled");
        ast_glScalef = (PFNGLSCALEFPROC)LoadOpenGLProc("glScalef");
        ast_glTranslated = (PFNGLTRANSLATEDPROC)LoadOpenGLProc("glTranslated");
        ast_glTranslatef = (PFNGLTRANSLATEFPROC)LoadOpenGLProc("glTranslatef");
    }
}

internal void
Load_GL_VERSION_1_1(ASTLoadProc LoadOpenGLProc)
{
    if(AST_GL_VERSION_1_1)
    {
        ast_glDrawArrays = (PFNGLDRAWARRAYSPROC)LoadOpenGLProc("glDrawArrays");
        ast_glDrawElements = (PFNGLDRAWELEMENTSPROC)LoadOpenGLProc("glDrawElements");
        ast_glGetPointerv = (PFNGLGETPOINTERVPROC)LoadOpenGLProc("glGetPointerv");
        ast_glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)LoadOpenGLProc("glPolygonOffset");
        ast_glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC)LoadOpenGLProc("glCopyTexImage1D");
        ast_glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)LoadOpenGLProc("glCopyTexImage2D");
        ast_glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC)LoadOpenGLProc("glCopyTexSubImage1D");
        ast_glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)LoadOpenGLProc("glCopyTexSubImage2D");
        ast_glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)LoadOpenGLProc("glTexSubImage1D");
        ast_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)LoadOpenGLProc("glTexSubImage2D");
        ast_glBindTexture = (PFNGLBINDTEXTUREPROC)LoadOpenGLProc("glBindTexture");
        ast_glDeleteTextures = (PFNGLDELETETEXTURESPROC)LoadOpenGLProc("glDeleteTextures");
        ast_glGenTextures = (PFNGLGENTEXTURESPROC)LoadOpenGLProc("glGenTextures");
        ast_glIsTexture = (PFNGLISTEXTUREPROC)LoadOpenGLProc("glIsTexture");
        ast_glArrayElement = (PFNGLARRAYELEMENTPROC)LoadOpenGLProc("glArrayElement");
        ast_glColorPointer = (PFNGLCOLORPOINTERPROC)LoadOpenGLProc("glColorPointer");
        ast_glDisableClientState = (PFNGLDISABLECLIENTSTATEPROC)LoadOpenGLProc("glDisableClientState");
        ast_glEdgeFlagPointer = (PFNGLEDGEFLAGPOINTERPROC)LoadOpenGLProc("glEdgeFlagPointer");
        ast_glEnableClientState = (PFNGLENABLECLIENTSTATEPROC)LoadOpenGLProc("glEnableClientState");
        ast_glIndexPointer = (PFNGLINDEXPOINTERPROC)LoadOpenGLProc("glIndexPointer");
        ast_glInterleavedArrays = (PFNGLINTERLEAVEDARRAYSPROC)LoadOpenGLProc("glInterleavedArrays");
        ast_glNormalPointer = (PFNGLNORMALPOINTERPROC)LoadOpenGLProc("glNormalPointer");
        ast_glTexCoordPointer = (PFNGLTEXCOORDPOINTERPROC)LoadOpenGLProc("glTexCoordPointer");
        ast_glVertexPointer = (PFNGLVERTEXPOINTERPROC)LoadOpenGLProc("glVertexPointer");
        ast_glAreTexturesResident = (PFNGLARETEXTURESRESIDENTPROC)LoadOpenGLProc("glAreTexturesResident");
        ast_glPrioritizeTextures = (PFNGLPRIORITIZETEXTURESPROC)LoadOpenGLProc("glPrioritizeTextures");
        ast_glIndexub = (PFNGLINDEXUBPROC)LoadOpenGLProc("glIndexub");
        ast_glIndexubv = (PFNGLINDEXUBVPROC)LoadOpenGLProc("glIndexubv");
        ast_glPopClientAttrib = (PFNGLPOPCLIENTATTRIBPROC)LoadOpenGLProc("glPopClientAttrib");
        ast_glPushClientAttrib = (PFNGLPUSHCLIENTATTRIBPROC)LoadOpenGLProc("glPushClientAttrib");
    }
}

internal void
Load_GL_VERSION_1_2(ASTLoadProc LoadOpenGLProc)
{
    if(AST_GL_VERSION_1_2)
    {
        ast_glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)LoadOpenGLProc("glDrawRangeElements");
        ast_glTexImage3D = (PFNGLTEXIMAGE3DPROC)LoadOpenGLProc("glTexImage3D");
        ast_glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)LoadOpenGLProc("glTexSubImage3D");
        ast_glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)LoadOpenGLProc("glCopyTexSubImage3D");
    }
}

internal void
Load_GL_VERSION_1_3(ASTLoadProc LoadOpenGLProc)
{
    if(AST_GL_VERSION_1_3)
    {
        ast_glActiveTexture = (PFNGLACTIVETEXTUREPROC)LoadOpenGLProc("glActiveTexture");
        ast_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)LoadOpenGLProc("glSampleCoverage");
        ast_glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)LoadOpenGLProc("glCompressedTexImage3D");
        ast_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)LoadOpenGLProc("glCompressedTexImage2D");
        ast_glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)LoadOpenGLProc("glCompressedTexImage1D");
        ast_glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)LoadOpenGLProc("glCompressedTexSubImage3D");
        ast_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)LoadOpenGLProc("glCompressedTexSubImage2D");
        ast_glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)LoadOpenGLProc("glCompressedTexSubImage1D");
        ast_glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)LoadOpenGLProc("glGetCompressedTexImage");
        ast_glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC)LoadOpenGLProc("glClientActiveTexture");
        ast_glMultiTexCoord1d = (PFNGLMULTITEXCOORD1DPROC)LoadOpenGLProc("glMultiTexCoord1d");
        ast_glMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DVPROC)LoadOpenGLProc("glMultiTexCoord1dv");
        ast_glMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC)LoadOpenGLProc("glMultiTexCoord1f");
        ast_glMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FVPROC)LoadOpenGLProc("glMultiTexCoord1fv");
        ast_glMultiTexCoord1i = (PFNGLMULTITEXCOORD1IPROC)LoadOpenGLProc("glMultiTexCoord1i");
        ast_glMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IVPROC)LoadOpenGLProc("glMultiTexCoord1iv");
        ast_glMultiTexCoord1s = (PFNGLMULTITEXCOORD1SPROC)LoadOpenGLProc("glMultiTexCoord1s");
        ast_glMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SVPROC)LoadOpenGLProc("glMultiTexCoord1sv");
        ast_glMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC)LoadOpenGLProc("glMultiTexCoord2d");
        ast_glMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DVPROC)LoadOpenGLProc("glMultiTexCoord2dv");
        ast_glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC)LoadOpenGLProc("glMultiTexCoord2f");
        ast_glMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FVPROC)LoadOpenGLProc("glMultiTexCoord2fv");
        ast_glMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC)LoadOpenGLProc("glMultiTexCoord2i");
        ast_glMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IVPROC)LoadOpenGLProc("glMultiTexCoord2iv");
        ast_glMultiTexCoord2s = (PFNGLMULTITEXCOORD2SPROC)LoadOpenGLProc("glMultiTexCoord2s");
        ast_glMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SVPROC)LoadOpenGLProc("glMultiTexCoord2sv");
        ast_glMultiTexCoord3d = (PFNGLMULTITEXCOORD3DPROC)LoadOpenGLProc("glMultiTexCoord3d");
        ast_glMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DVPROC)LoadOpenGLProc("glMultiTexCoord3dv");
        ast_glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC)LoadOpenGLProc("glMultiTexCoord3f");
        ast_glMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FVPROC)LoadOpenGLProc("glMultiTexCoord3fv");
        ast_glMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC)LoadOpenGLProc("glMultiTexCoord3i");
        ast_glMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IVPROC)LoadOpenGLProc("glMultiTexCoord3iv");
        ast_glMultiTexCoord3s = (PFNGLMULTITEXCOORD3SPROC)LoadOpenGLProc("glMultiTexCoord3s");
        ast_glMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SVPROC)LoadOpenGLProc("glMultiTexCoord3sv");
        ast_glMultiTexCoord4d = (PFNGLMULTITEXCOORD4DPROC)LoadOpenGLProc("glMultiTexCoord4d");
        ast_glMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DVPROC)LoadOpenGLProc("glMultiTexCoord4dv");
        ast_glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC)LoadOpenGLProc("glMultiTexCoord4f");
        ast_glMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FVPROC)LoadOpenGLProc("glMultiTexCoord4fv");
        ast_glMultiTexCoord4i = (PFNGLMULTITEXCOORD4IPROC)LoadOpenGLProc("glMultiTexCoord4i");
        ast_glMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IVPROC)LoadOpenGLProc("glMultiTexCoord4iv");
        ast_glMultiTexCoord4s = (PFNGLMULTITEXCOORD4SPROC)LoadOpenGLProc("glMultiTexCoord4s");
        ast_glMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SVPROC)LoadOpenGLProc("glMultiTexCoord4sv");
        ast_glLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC)LoadOpenGLProc("glLoadTransposeMatrixf");
        ast_glLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC)LoadOpenGLProc("glLoadTransposeMatrixd");
        ast_glMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC)LoadOpenGLProc("glMultTransposeMatrixf");
        ast_glMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC)LoadOpenGLProc("glMultTransposeMatrixd");
    }
}

internal void
Load_GL_VERSION_1_4(ASTLoadProc LoadOpenGLProc)
{
    if(AST_GL_VERSION_1_4)
    {
        ast_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)LoadOpenGLProc("glBlendFuncSeparate");
        ast_glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)LoadOpenGLProc("glMultiDrawArrays");
        ast_glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)LoadOpenGLProc("glMultiDrawElements");
        ast_glPointParameterf = (PFNGLPOINTPARAMETERFPROC)LoadOpenGLProc("glPointParameterf");
        ast_glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)LoadOpenGLProc("glPointParameterfv");
        ast_glPointParameteri = (PFNGLPOINTPARAMETERIPROC)LoadOpenGLProc("glPointParameteri");
        ast_glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)LoadOpenGLProc("glPointParameteriv");
        ast_glFogCoordf = (PFNGLFOGCOORDFPROC)LoadOpenGLProc("glFogCoordf");
        ast_glFogCoordfv = (PFNGLFOGCOORDFVPROC)LoadOpenGLProc("glFogCoordfv");
        ast_glFogCoordd = (PFNGLFOGCOORDDPROC)LoadOpenGLProc("glFogCoordd");
        ast_glFogCoorddv = (PFNGLFOGCOORDDVPROC)LoadOpenGLProc("glFogCoorddv");
        ast_glFogCoordPointer = (PFNGLFOGCOORDPOINTERPROC)LoadOpenGLProc("glFogCoordPointer");
        ast_glSecondaryColor3b = (PFNGLSECONDARYCOLOR3BPROC)LoadOpenGLProc("glSecondaryColor3b");
        ast_glSecondaryColor3bv = (PFNGLSECONDARYCOLOR3BVPROC)LoadOpenGLProc("glSecondaryColor3bv");
        ast_glSecondaryColor3d = (PFNGLSECONDARYCOLOR3DPROC)LoadOpenGLProc("glSecondaryColor3d");
        ast_glSecondaryColor3dv = (PFNGLSECONDARYCOLOR3DVPROC)LoadOpenGLProc("glSecondaryColor3dv");
        ast_glSecondaryColor3f = (PFNGLSECONDARYCOLOR3FPROC)LoadOpenGLProc("glSecondaryColor3f");
        ast_glSecondaryColor3fv = (PFNGLSECONDARYCOLOR3FVPROC)LoadOpenGLProc("glSecondaryColor3fv");
        ast_glSecondaryColor3i = (PFNGLSECONDARYCOLOR3IPROC)LoadOpenGLProc("glSecondaryColor3i");
        ast_glSecondaryColor3iv = (PFNGLSECONDARYCOLOR3IVPROC)LoadOpenGLProc("glSecondaryColor3iv");
        ast_glSecondaryColor3s = (PFNGLSECONDARYCOLOR3SPROC)LoadOpenGLProc("glSecondaryColor3s");
        ast_glSecondaryColor3sv = (PFNGLSECONDARYCOLOR3SVPROC)LoadOpenGLProc("glSecondaryColor3sv");
        ast_glSecondaryColor3ub = (PFNGLSECONDARYCOLOR3UBPROC)LoadOpenGLProc("glSecondaryColor3ub");
        ast_glSecondaryColor3ubv = (PFNGLSECONDARYCOLOR3UBVPROC)LoadOpenGLProc("glSecondaryColor3ubv");
        ast_glSecondaryColor3ui = (PFNGLSECONDARYCOLOR3UIPROC)LoadOpenGLProc("glSecondaryColor3ui");
        ast_glSecondaryColor3uiv = (PFNGLSECONDARYCOLOR3UIVPROC)LoadOpenGLProc("glSecondaryColor3uiv");
        ast_glSecondaryColor3us = (PFNGLSECONDARYCOLOR3USPROC)LoadOpenGLProc("glSecondaryColor3us");
        ast_glSecondaryColor3usv = (PFNGLSECONDARYCOLOR3USVPROC)LoadOpenGLProc("glSecondaryColor3usv");
        ast_glSecondaryColorPointer = (PFNGLSECONDARYCOLORPOINTERPROC)LoadOpenGLProc("glSecondaryColorPointer");
        ast_glWindowPos2d = (PFNGLWINDOWPOS2DPROC)LoadOpenGLProc("glWindowPos2d");
        ast_glWindowPos2dv = (PFNGLWINDOWPOS2DVPROC)LoadOpenGLProc("glWindowPos2dv");
        ast_glWindowPos2f = (PFNGLWINDOWPOS2FPROC)LoadOpenGLProc("glWindowPos2f");
        ast_glWindowPos2fv = (PFNGLWINDOWPOS2FVPROC)LoadOpenGLProc("glWindowPos2fv");
        ast_glWindowPos2i = (PFNGLWINDOWPOS2IPROC)LoadOpenGLProc("glWindowPos2i");
        ast_glWindowPos2iv = (PFNGLWINDOWPOS2IVPROC)LoadOpenGLProc("glWindowPos2iv");
        ast_glWindowPos2s = (PFNGLWINDOWPOS2SPROC)LoadOpenGLProc("glWindowPos2s");
        ast_glWindowPos2sv = (PFNGLWINDOWPOS2SVPROC)LoadOpenGLProc("glWindowPos2sv");
        ast_glWindowPos3d = (PFNGLWINDOWPOS3DPROC)LoadOpenGLProc("glWindowPos3d");
        ast_glWindowPos3dv = (PFNGLWINDOWPOS3DVPROC)LoadOpenGLProc("glWindowPos3dv");
        ast_glWindowPos3f = (PFNGLWINDOWPOS3FPROC)LoadOpenGLProc("glWindowPos3f");
        ast_glWindowPos3fv = (PFNGLWINDOWPOS3FVPROC)LoadOpenGLProc("glWindowPos3fv");
        ast_glWindowPos3i = (PFNGLWINDOWPOS3IPROC)LoadOpenGLProc("glWindowPos3i");
        ast_glWindowPos3iv = (PFNGLWINDOWPOS3IVPROC)LoadOpenGLProc("glWindowPos3iv");
        ast_glWindowPos3s = (PFNGLWINDOWPOS3SPROC)LoadOpenGLProc("glWindowPos3s");
        ast_glWindowPos3sv = (PFNGLWINDOWPOS3SVPROC)LoadOpenGLProc("glWindowPos3sv");
        ast_glBlendColor = (PFNGLBLENDCOLORPROC)LoadOpenGLProc("glBlendColor");
        ast_glBlendEquation = (PFNGLBLENDEQUATIONPROC)LoadOpenGLProc("glBlendEquation");
    }
}

internal void
Load_GL_VERSION_1_5(ASTLoadProc LoadOpenGLProc)
{
    if(AST_GL_VERSION_1_5)
    {
        ast_glGenQueries = (PFNGLGENQUERIESPROC)LoadOpenGLProc("glGenQueries");
        ast_glDeleteQueries = (PFNGLDELETEQUERIESPROC)LoadOpenGLProc("glDeleteQueries");
        ast_glIsQuery = (PFNGLISQUERYPROC)LoadOpenGLProc("glIsQuery");
        ast_glBeginQuery = (PFNGLBEGINQUERYPROC)LoadOpenGLProc("glBeginQuery");
        ast_glEndQuery = (PFNGLENDQUERYPROC)LoadOpenGLProc("glEndQuery");
        ast_glGetQueryiv = (PFNGLGETQUERYIVPROC)LoadOpenGLProc("glGetQueryiv");
        ast_glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)LoadOpenGLProc("glGetQueryObjectiv");
        ast_glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)LoadOpenGLProc("glGetQueryObjectuiv");
        ast_glBindBuffer = (PFNGLBINDBUFFERPROC)LoadOpenGLProc("glBindBuffer");
        ast_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)LoadOpenGLProc("glDeleteBuffers");
        ast_glGenBuffers = (PFNGLGENBUFFERSPROC)LoadOpenGLProc("glGenBuffers");
        ast_glIsBuffer = (PFNGLISBUFFERPROC)LoadOpenGLProc("glIsBuffer");
        ast_glBufferData = (PFNGLBUFFERDATAPROC)LoadOpenGLProc("glBufferData");
        ast_glBufferSubData = (PFNGLBUFFERSUBDATAPROC)LoadOpenGLProc("glBufferSubData");
        ast_glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)LoadOpenGLProc("glGetBufferSubData");
        ast_glMapBuffer = (PFNGLMAPBUFFERPROC)LoadOpenGLProc("glMapBuffer");
        ast_glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)LoadOpenGLProc("glUnmapBuffer");
        ast_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)LoadOpenGLProc("glGetBufferParameteriv");
        ast_glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)LoadOpenGLProc("glGetBufferPointerv");
    }
}

internal void
Load_GL_VERSION_2_0(ASTLoadProc LoadOpenGLProc)
{
    if(AST_GL_VERSION_2_0)
    {
        ast_glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)LoadOpenGLProc("glBlendEquationSeparate");
        ast_glDrawBuffers = (PFNGLDRAWBUFFERSPROC)LoadOpenGLProc("glDrawBuffers");
        ast_glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)LoadOpenGLProc("glStencilOpSeparate");
        ast_glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)LoadOpenGLProc("glStencilFuncSeparate");
        ast_glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)LoadOpenGLProc("glStencilMaskSeparate");
        ast_glAttachShader = (PFNGLATTACHSHADERPROC)LoadOpenGLProc("glAttachShader");
        ast_glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)LoadOpenGLProc("glBindAttribLocation");
        ast_glCompileShader = (PFNGLCOMPILESHADERPROC)LoadOpenGLProc("glCompileShader");
        ast_glCreateProgram = (PFNGLCREATEPROGRAMPROC)LoadOpenGLProc("glCreateProgram");
        ast_glCreateShader = (PFNGLCREATESHADERPROC)LoadOpenGLProc("glCreateShader");
        ast_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)LoadOpenGLProc("glDeleteProgram");
        ast_glDeleteShader = (PFNGLDELETESHADERPROC)LoadOpenGLProc("glDeleteShader");
        ast_glDetachShader = (PFNGLDETACHSHADERPROC)LoadOpenGLProc("glDetachShader");
        ast_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)LoadOpenGLProc("glDisableVertexAttribArray");
        ast_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)LoadOpenGLProc("glEnableVertexAttribArray");
        ast_glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)LoadOpenGLProc("glGetActiveAttrib");
        ast_glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)LoadOpenGLProc("glGetActiveUniform");
        ast_glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)LoadOpenGLProc("glGetAttachedShaders");
        ast_glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)LoadOpenGLProc("glGetAttribLocation");
        ast_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)LoadOpenGLProc("glGetProgramiv");
        ast_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)LoadOpenGLProc("glGetProgramInfoLog");
        ast_glGetShaderiv = (PFNGLGETSHADERIVPROC)LoadOpenGLProc("glGetShaderiv");
        ast_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)LoadOpenGLProc("glGetShaderInfoLog");
        ast_glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)LoadOpenGLProc("glGetShaderSource");
        ast_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)LoadOpenGLProc("glGetUniformLocation");
        ast_glGetUniformfv = (PFNGLGETUNIFORMFVPROC)LoadOpenGLProc("glGetUniformfv");
        ast_glGetUniformiv = (PFNGLGETUNIFORMIVPROC)LoadOpenGLProc("glGetUniformiv");
        ast_glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)LoadOpenGLProc("glGetVertexAttribdv");
        ast_glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)LoadOpenGLProc("glGetVertexAttribfv");
        ast_glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)LoadOpenGLProc("glGetVertexAttribiv");
        ast_glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)LoadOpenGLProc("glGetVertexAttribPointerv");
        ast_glIsProgram = (PFNGLISPROGRAMPROC)LoadOpenGLProc("glIsProgram");
        ast_glIsShader = (PFNGLISSHADERPROC)LoadOpenGLProc("glIsShader");
        ast_glLinkProgram = (PFNGLLINKPROGRAMPROC)LoadOpenGLProc("glLinkProgram");
        ast_glShaderSource = (PFNGLSHADERSOURCEPROC)LoadOpenGLProc("glShaderSource");
        ast_glUseProgram = (PFNGLUSEPROGRAMPROC)LoadOpenGLProc("glUseProgram");
        ast_glUniform1f = (PFNGLUNIFORM1FPROC)LoadOpenGLProc("glUniform1f");
        ast_glUniform2f = (PFNGLUNIFORM2FPROC)LoadOpenGLProc("glUniform2f");
        ast_glUniform3f = (PFNGLUNIFORM3FPROC)LoadOpenGLProc("glUniform3f");
        ast_glUniform4f = (PFNGLUNIFORM4FPROC)LoadOpenGLProc("glUniform4f");
        ast_glUniform1i = (PFNGLUNIFORM1IPROC)LoadOpenGLProc("glUniform1i");
        ast_glUniform2i = (PFNGLUNIFORM2IPROC)LoadOpenGLProc("glUniform2i");
        ast_glUniform3i = (PFNGLUNIFORM3IPROC)LoadOpenGLProc("glUniform3i");
        ast_glUniform4i = (PFNGLUNIFORM4IPROC)LoadOpenGLProc("glUniform4i");
        ast_glUniform1fv = (PFNGLUNIFORM1FVPROC)LoadOpenGLProc("glUniform1fv");
        ast_glUniform2fv = (PFNGLUNIFORM2FVPROC)LoadOpenGLProc("glUniform2fv");
        ast_glUniform3fv = (PFNGLUNIFORM3FVPROC)LoadOpenGLProc("glUniform3fv");
        ast_glUniform4fv = (PFNGLUNIFORM4FVPROC)LoadOpenGLProc("glUniform4fv");
        ast_glUniform1iv = (PFNGLUNIFORM1IVPROC)LoadOpenGLProc("glUniform1iv");
        ast_glUniform2iv = (PFNGLUNIFORM2IVPROC)LoadOpenGLProc("glUniform2iv");
        ast_glUniform3iv = (PFNGLUNIFORM3IVPROC)LoadOpenGLProc("glUniform3iv");
        ast_glUniform4iv = (PFNGLUNIFORM4IVPROC)LoadOpenGLProc("glUniform4iv");
        ast_glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)LoadOpenGLProc("glUniformMatrix2fv");
        ast_glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)LoadOpenGLProc("glUniformMatrix3fv");
        ast_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)LoadOpenGLProc("glUniformMatrix4fv");
        ast_glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)LoadOpenGLProc("glValidateProgram");
        ast_glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)LoadOpenGLProc("glVertexAttrib1d");
        ast_glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)LoadOpenGLProc("glVertexAttrib1dv");
        ast_glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)LoadOpenGLProc("glVertexAttrib1f");
        ast_glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)LoadOpenGLProc("glVertexAttrib1fv");
        ast_glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)LoadOpenGLProc("glVertexAttrib1s");
        ast_glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)LoadOpenGLProc("glVertexAttrib1sv");
        ast_glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)LoadOpenGLProc("glVertexAttrib2d");
        ast_glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)LoadOpenGLProc("glVertexAttrib2dv");
        ast_glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)LoadOpenGLProc("glVertexAttrib2f");
        ast_glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)LoadOpenGLProc("glVertexAttrib2fv");
        ast_glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)LoadOpenGLProc("glVertexAttrib2s");
        ast_glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)LoadOpenGLProc("glVertexAttrib2sv");
        ast_glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)LoadOpenGLProc("glVertexAttrib3d");
        ast_glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)LoadOpenGLProc("glVertexAttrib3dv");
        ast_glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)LoadOpenGLProc("glVertexAttrib3f");
        ast_glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)LoadOpenGLProc("glVertexAttrib3fv");
        ast_glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)LoadOpenGLProc("glVertexAttrib3s");
        ast_glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)LoadOpenGLProc("glVertexAttrib3sv");
        ast_glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)LoadOpenGLProc("glVertexAttrib4Nbv");
        ast_glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)LoadOpenGLProc("glVertexAttrib4Niv");
        ast_glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)LoadOpenGLProc("glVertexAttrib4Nsv");
        ast_glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)LoadOpenGLProc("glVertexAttrib4Nub");
        ast_glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)LoadOpenGLProc("glVertexAttrib4Nubv");
        ast_glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)LoadOpenGLProc("glVertexAttrib4Nuiv");
        ast_glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)LoadOpenGLProc("glVertexAttrib4Nusv");
        ast_glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)LoadOpenGLProc("glVertexAttrib4bv");
        ast_glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)LoadOpenGLProc("glVertexAttrib4d");
        ast_glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)LoadOpenGLProc("glVertexAttrib4dv");
        ast_glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)LoadOpenGLProc("glVertexAttrib4f");
        ast_glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)LoadOpenGLProc("glVertexAttrib4fv");
        ast_glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)LoadOpenGLProc("glVertexAttrib4iv");
        ast_glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)LoadOpenGLProc("glVertexAttrib4s");
        ast_glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)LoadOpenGLProc("glVertexAttrib4sv");
        ast_glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)LoadOpenGLProc("glVertexAttrib4ubv");
        ast_glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)LoadOpenGLProc("glVertexAttrib4uiv");
        ast_glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)LoadOpenGLProc("glVertexAttrib4usv");
        ast_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)LoadOpenGLProc("glVertexAttribPointer");
    }
}

internal void
Load_GL_VERSION_2_1(ASTLoadProc LoadOpenGLProc)
{
    if(AST_GL_VERSION_2_1)
    {
        ast_glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)LoadOpenGLProc("glUniformMatrix2x3fv");
        ast_glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)LoadOpenGLProc("glUniformMatrix3x2fv");
        ast_glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)LoadOpenGLProc("glUniformMatrix2x4fv");
        ast_glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)LoadOpenGLProc("glUniformMatrix4x2fv");
        ast_glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)LoadOpenGLProc("glUniformMatrix3x4fv");
        ast_glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)LoadOpenGLProc("glUniformMatrix4x3fv");
    }
}

internal void
Load_GL_VERSION_3_0(ASTLoadProc LoadOpenGLProc)
{
    if(AST_GL_VERSION_3_0)
    {
        ast_glColorMaski = (PFNGLCOLORMASKIPROC)LoadOpenGLProc("glColorMaski");
        ast_glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)LoadOpenGLProc("glGetBooleani_v");
        ast_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)LoadOpenGLProc("glGetIntegeri_v");
        ast_glEnablei = (PFNGLENABLEIPROC)LoadOpenGLProc("glEnablei");
        ast_glDisablei = (PFNGLDISABLEIPROC)LoadOpenGLProc("glDisablei");
        ast_glIsEnabledi = (PFNGLISENABLEDIPROC)LoadOpenGLProc("glIsEnabledi");
        ast_glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)LoadOpenGLProc("glBeginTransformFeedback");
        ast_glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)LoadOpenGLProc("glEndTransformFeedback");
        ast_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)LoadOpenGLProc("glBindBufferRange");
        ast_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)LoadOpenGLProc("glBindBufferBase");
        ast_glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)LoadOpenGLProc("glTransformFeedbackVaryings");
        ast_glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)LoadOpenGLProc("glGetTransformFeedbackVarying");
        ast_glClampColor = (PFNGLCLAMPCOLORPROC)LoadOpenGLProc("glClampColor");
        ast_glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)LoadOpenGLProc("glBeginConditionalRender");
        ast_glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)LoadOpenGLProc("glEndConditionalRender");
        ast_glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)LoadOpenGLProc("glVertexAttribIPointer");
        ast_glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)LoadOpenGLProc("glGetVertexAttribIiv");
        ast_glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)LoadOpenGLProc("glGetVertexAttribIuiv");
        ast_glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)LoadOpenGLProc("glVertexAttribI1i");
        ast_glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)LoadOpenGLProc("glVertexAttribI2i");
        ast_glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)LoadOpenGLProc("glVertexAttribI3i");
        ast_glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)LoadOpenGLProc("glVertexAttribI4i");
        ast_glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)LoadOpenGLProc("glVertexAttribI1ui");
        ast_glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)LoadOpenGLProc("glVertexAttribI2ui");
        ast_glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)LoadOpenGLProc("glVertexAttribI3ui");
        ast_glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)LoadOpenGLProc("glVertexAttribI4ui");
        ast_glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)LoadOpenGLProc("glVertexAttribI1iv");
        ast_glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)LoadOpenGLProc("glVertexAttribI2iv");
        ast_glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)LoadOpenGLProc("glVertexAttribI3iv");
        ast_glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)LoadOpenGLProc("glVertexAttribI4iv");
        ast_glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)LoadOpenGLProc("glVertexAttribI1uiv");
        ast_glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)LoadOpenGLProc("glVertexAttribI2uiv");
        ast_glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)LoadOpenGLProc("glVertexAttribI3uiv");
        ast_glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)LoadOpenGLProc("glVertexAttribI4uiv");
        ast_glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)LoadOpenGLProc("glVertexAttribI4bv");
        ast_glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)LoadOpenGLProc("glVertexAttribI4sv");
        ast_glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)LoadOpenGLProc("glVertexAttribI4ubv");
        ast_glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)LoadOpenGLProc("glVertexAttribI4usv");
        ast_glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)LoadOpenGLProc("glGetUniformuiv");
        ast_glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)LoadOpenGLProc("glBindFragDataLocation");
        ast_glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)LoadOpenGLProc("glGetFragDataLocation");
        ast_glUniform1ui = (PFNGLUNIFORM1UIPROC)LoadOpenGLProc("glUniform1ui");
        ast_glUniform2ui = (PFNGLUNIFORM2UIPROC)LoadOpenGLProc("glUniform2ui");
        ast_glUniform3ui = (PFNGLUNIFORM3UIPROC)LoadOpenGLProc("glUniform3ui");
        ast_glUniform4ui = (PFNGLUNIFORM4UIPROC)LoadOpenGLProc("glUniform4ui");
        ast_glUniform1uiv = (PFNGLUNIFORM1UIVPROC)LoadOpenGLProc("glUniform1uiv");
        ast_glUniform2uiv = (PFNGLUNIFORM2UIVPROC)LoadOpenGLProc("glUniform2uiv");
        ast_glUniform3uiv = (PFNGLUNIFORM3UIVPROC)LoadOpenGLProc("glUniform3uiv");
        ast_glUniform4uiv = (PFNGLUNIFORM4UIVPROC)LoadOpenGLProc("glUniform4uiv");
        ast_glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)LoadOpenGLProc("glTexParameterIiv");
        ast_glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)LoadOpenGLProc("glTexParameterIuiv");
        ast_glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)LoadOpenGLProc("glGetTexParameterIiv");
        ast_glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)LoadOpenGLProc("glGetTexParameterIuiv");
        ast_glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)LoadOpenGLProc("glClearBufferiv");
        ast_glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)LoadOpenGLProc("glClearBufferuiv");
        ast_glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)LoadOpenGLProc("glClearBufferfv");
        ast_glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)LoadOpenGLProc("glClearBufferfi");
        ast_glGetStringi = (PFNGLGETSTRINGIPROC)LoadOpenGLProc("glGetStringi");
        ast_glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)LoadOpenGLProc("glIsRenderbuffer");
        ast_glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)LoadOpenGLProc("glBindRenderbuffer");
        ast_glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)LoadOpenGLProc("glDeleteRenderbuffers");
        ast_glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)LoadOpenGLProc("glGenRenderbuffers");
        ast_glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)LoadOpenGLProc("glRenderbufferStorage");
        ast_glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)LoadOpenGLProc("glGetRenderbufferParameteriv");
        ast_glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)LoadOpenGLProc("glIsFramebuffer");
        ast_glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)LoadOpenGLProc("glBindFramebuffer");
        ast_glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)LoadOpenGLProc("glDeleteFramebuffers");
        ast_glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)LoadOpenGLProc("glGenFramebuffers");
        ast_glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)LoadOpenGLProc("glCheckFramebufferStatus");
        ast_glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)LoadOpenGLProc("glFramebufferTexture1D");
        ast_glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)LoadOpenGLProc("glFramebufferTexture2D");
        ast_glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)LoadOpenGLProc("glFramebufferTexture3D");
        ast_glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)LoadOpenGLProc("glFramebufferRenderbuffer");
        ast_glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)LoadOpenGLProc("glGetFramebufferAttachmentParameteriv");
        ast_glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)LoadOpenGLProc("glGenerateMipmap");
        ast_glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)LoadOpenGLProc("glBlitFramebuffer");
        ast_glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)LoadOpenGLProc("glRenderbufferStorageMultisample");
        ast_glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)LoadOpenGLProc("glFramebufferTextureLayer");
        ast_glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)LoadOpenGLProc("glMapBufferRange");
        ast_glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)LoadOpenGLProc("glFlushMappedBufferRange");
        ast_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)LoadOpenGLProc("glBindVertexArray");
        ast_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)LoadOpenGLProc("glDeleteVertexArrays");
        ast_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)LoadOpenGLProc("glGenVertexArrays");
        ast_glIsVertexArray = (PFNGLISVERTEXARRAYPROC)LoadOpenGLProc("glIsVertexArray");
    }
}

internal void
Load_GL_VERSION_3_1(ASTLoadProc LoadOpenGLProc)
{
    if(AST_GL_VERSION_3_1)
    {
        ast_glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)LoadOpenGLProc("glDrawArraysInstanced");
        ast_glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)LoadOpenGLProc("glDrawElementsInstanced");
        ast_glTexBuffer = (PFNGLTEXBUFFERPROC)LoadOpenGLProc("glTexBuffer");
        ast_glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)LoadOpenGLProc("glPrimitiveRestartIndex");
        ast_glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)LoadOpenGLProc("glCopyBufferSubData");
        ast_glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)LoadOpenGLProc("glGetUniformIndices");
        ast_glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)LoadOpenGLProc("glGetActiveUniformsiv");
        ast_glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)LoadOpenGLProc("glGetActiveUniformName");
        ast_glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)LoadOpenGLProc("glGetUniformBlockIndex");
        ast_glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)LoadOpenGLProc("glGetActiveUniformBlockiv");
        ast_glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)LoadOpenGLProc("glGetActiveUniformBlockName");
        ast_glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)LoadOpenGLProc("glUniformBlockBinding");
        ast_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)LoadOpenGLProc("glBindBufferRange");
        ast_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)LoadOpenGLProc("glBindBufferBase");
        ast_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)LoadOpenGLProc("glGetIntegeri_v");
    }
}


// Function Loaders Loaders
//
//


internal void
CheckOpenGLVersion()
{
    int major;
    int minor;

    const char* version;
    const char* prefixes[] =
        {
            "OpenGL ES-CM ",
            "OpenGL ES-CL ",
            "OpenGL ES ",
            0
        };

    version = (const char*) glGetString(GL_VERSION);
    if (version)
    {
        for (int i = 0;  prefixes[i];  i++)
        {
            const size_t length = strlen(prefixes[i]);
            if (strncmp(version, prefixes[i], length) == 0)
            {
                version += length;
            break;
            }
        }
        
        sscanf_s(version, "%d.%d", &major, &minor);
        
        GLVersion.Major = major;
        GLVersion.Minor = minor;
        OpenGLLoadedMajor = major;
        OpenGLLoadedMinor = minor;
        AST_GL_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
        AST_GL_VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
        AST_GL_VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
        AST_GL_VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
        AST_GL_VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;
        AST_GL_VERSION_1_5 = (major == 1 && minor >= 5) || major > 1;
        AST_GL_VERSION_2_0 = (major == 2 && minor >= 0) || major > 2;
        AST_GL_VERSION_2_1 = (major == 2 && minor >= 1) || major > 2;
        AST_GL_VERSION_3_0 = (major == 3 && minor >= 0) || major > 3;
        AST_GL_VERSION_3_1 = (major == 3 && minor >= 1) || major > 3;
        if (GLVersion.Major > 3 || (GLVersion.Major >= 3 && GLVersion.Minor >= 1))
        {
            OpenGLLoadedMajor = 3;
            OpenGLLoadedMinor = 1;
        }
    }
}

internal int
LoadOpenGL()
{
    int Result = 0;

    if(InternalLoadOpenGLDLL())
    {
        glGetString = (PFNGLGETSTRINGPROC)GetOpenGLProc("glGetString");
        Assert(glGetString);
    
        if(glGetString(GL_VERSION) != 0)
        {
            CheckOpenGLVersion();
            Load_GL_VERSION_1_0(&GetOpenGLProc);
            Load_GL_VERSION_1_1(&GetOpenGLProc);
            Load_GL_VERSION_1_2(&GetOpenGLProc);
            Load_GL_VERSION_1_3(&GetOpenGLProc);
            Load_GL_VERSION_1_4(&GetOpenGLProc);
            Load_GL_VERSION_1_5(&GetOpenGLProc);
            Load_GL_VERSION_2_0(&GetOpenGLProc);
            Load_GL_VERSION_2_1(&GetOpenGLProc);
            Load_GL_VERSION_3_0(&GetOpenGLProc);
            Load_GL_VERSION_3_1(&GetOpenGLProc);
            
            // TODO(felipe): Log the maximum GL version that
            // could be loaded.
            Result = ((GLVersion.Major != 0) || (GLVersion.Minor != 0));
        }
        else
        {
            // TODO(felipe): Diagnostics.
        }
    
        InternalCloseOpenGLDLL();
    }
    else
    {
        // TODO(felipe): Diagnostics.
    }

    return Result;
}
