/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Felipe Carlin $
   $Notice: $
   ======================================================================== */

#include "opengl_cubicsquarecreft.h"

static HMODULE OpenGLDLL;
static csc_gl_version GLVersion;
static int OpenGLLoadedMajor;
static int OpenGLLoadedMinor;


typedef void* (APIENTRYP PFNWGLGETPROCADDRESSPROC_PRIVATE)(const char*);
static PFNWGLGETPROCADDRESSPROC_PRIVATE CSCGetProcAddressPtr;

internal int
InternalLoadOpenGLDLL()
{
    int Result = 0;
    OpenGLDLL = LoadLibraryA("opengl32.dll");
    if(OpenGLDLL)
    {
        void (* tmp)(void);
        tmp = (void(*)(void)) GetProcAddress(OpenGLDLL, "wglGetProcAddress");
        CSCGetProcAddressPtr = (PFNWGLGETPROCADDRESSPROC_PRIVATE) tmp;
        Result = (CSCGetProcAddressPtr != 0);
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
        if(CSCGetProcAddressPtr)
        {
            Result = CSCGetProcAddressPtr(ProcName);
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

int CSC_GL_VERSION_1_0 = 0;
int CSC_GL_VERSION_1_1 = 0;
int CSC_GL_VERSION_1_2 = 0;
int CSC_GL_VERSION_1_3 = 0;
int CSC_GL_VERSION_1_4 = 0;
int CSC_GL_VERSION_1_5 = 0;
int CSC_GL_VERSION_2_0 = 0;
int CSC_GL_VERSION_2_1 = 0;
int CSC_GL_VERSION_3_0 = 0;
int CSC_GL_VERSION_3_1 = 0;

PFNGLACCUMPROC csc_glAccum = 0;
PFNGLACTIVETEXTUREPROC csc_glActiveTexture = 0;
PFNGLALPHAFUNCPROC csc_glAlphaFunc = 0;
PFNGLARETEXTURESRESIDENTPROC csc_glAreTexturesResident = 0;
PFNGLARRAYELEMENTPROC csc_glArrayElement = 0;
PFNGLATTACHSHADERPROC csc_glAttachShader = 0;
PFNGLBEGINPROC csc_glBegin = 0;
PFNGLBEGINCONDITIONALRENDERPROC csc_glBeginConditionalRender = 0;
PFNGLBEGINQUERYPROC csc_glBeginQuery = 0;
PFNGLBEGINTRANSFORMFEEDBACKPROC csc_glBeginTransformFeedback = 0;
PFNGLBINDATTRIBLOCATIONPROC csc_glBindAttribLocation = 0;
PFNGLBINDBUFFERPROC csc_glBindBuffer = 0;
PFNGLBINDBUFFERBASEPROC csc_glBindBufferBase = 0;
PFNGLBINDBUFFERRANGEPROC csc_glBindBufferRange = 0;
PFNGLBINDFRAGDATALOCATIONPROC csc_glBindFragDataLocation = 0;
PFNGLBINDFRAMEBUFFERPROC csc_glBindFramebuffer = 0;
PFNGLBINDRENDERBUFFERPROC csc_glBindRenderbuffer = 0;
PFNGLBINDTEXTUREPROC csc_glBindTexture = 0;
PFNGLBINDVERTEXARRAYPROC csc_glBindVertexArray = 0;
PFNGLBITMAPPROC csc_glBitmap = 0;
PFNGLBLENDCOLORPROC csc_glBlendColor = 0;
PFNGLBLENDEQUATIONPROC csc_glBlendEquation = 0;
PFNGLBLENDEQUATIONSEPARATEPROC csc_glBlendEquationSeparate = 0;
PFNGLBLENDFUNCPROC csc_glBlendFunc = 0;
PFNGLBLENDFUNCSEPARATEPROC csc_glBlendFuncSeparate = 0;
PFNGLBLITFRAMEBUFFERPROC csc_glBlitFramebuffer = 0;
PFNGLBUFFERDATAPROC csc_glBufferData = 0;
PFNGLBUFFERSUBDATAPROC csc_glBufferSubData = 0;
PFNGLCALLLISTPROC csc_glCallList = 0;
PFNGLCALLLISTSPROC csc_glCallLists = 0;
PFNGLCHECKFRAMEBUFFERSTATUSPROC csc_glCheckFramebufferStatus = 0;
PFNGLCLAMPCOLORPROC csc_glClampColor = 0;
PFNGLCLEARPROC csc_glClear = 0;
PFNGLCLEARACCUMPROC csc_glClearAccum = 0;
PFNGLCLEARBUFFERFIPROC csc_glClearBufferfi = 0;
PFNGLCLEARBUFFERFVPROC csc_glClearBufferfv = 0;
PFNGLCLEARBUFFERIVPROC csc_glClearBufferiv = 0;
PFNGLCLEARBUFFERUIVPROC csc_glClearBufferuiv = 0;
PFNGLCLEARCOLORPROC csc_glClearColor = 0;
PFNGLCLEARDEPTHPROC csc_glClearDepth = 0;
PFNGLCLEARINDEXPROC csc_glClearIndex = 0;
PFNGLCLEARSTENCILPROC csc_glClearStencil = 0;
PFNGLCLIENTACTIVETEXTUREPROC csc_glClientActiveTexture = 0;
PFNGLCLIPPLANEPROC csc_glClipPlane = 0;
PFNGLCOLOR3BPROC csc_glColor3b = 0;
PFNGLCOLOR3BVPROC csc_glColor3bv = 0;
PFNGLCOLOR3DPROC csc_glColor3d = 0;
PFNGLCOLOR3DVPROC csc_glColor3dv = 0;
PFNGLCOLOR3FPROC csc_glColor3f = 0;
PFNGLCOLOR3FVPROC csc_glColor3fv = 0;
PFNGLCOLOR3IPROC csc_glColor3i = 0;
PFNGLCOLOR3IVPROC csc_glColor3iv = 0;
PFNGLCOLOR3SPROC csc_glColor3s = 0;
PFNGLCOLOR3SVPROC csc_glColor3sv = 0;
PFNGLCOLOR3UBPROC csc_glColor3ub = 0;
PFNGLCOLOR3UBVPROC csc_glColor3ubv = 0;
PFNGLCOLOR3UIPROC csc_glColor3ui = 0;
PFNGLCOLOR3UIVPROC csc_glColor3uiv = 0;
PFNGLCOLOR3USPROC csc_glColor3us = 0;
PFNGLCOLOR3USVPROC csc_glColor3usv = 0;
PFNGLCOLOR4BPROC csc_glColor4b = 0;
PFNGLCOLOR4BVPROC csc_glColor4bv = 0;
PFNGLCOLOR4DPROC csc_glColor4d = 0;
PFNGLCOLOR4DVPROC csc_glColor4dv = 0;
PFNGLCOLOR4FPROC csc_glColor4f = 0;
PFNGLCOLOR4FVPROC csc_glColor4fv = 0;
PFNGLCOLOR4IPROC csc_glColor4i = 0;
PFNGLCOLOR4IVPROC csc_glColor4iv = 0;
PFNGLCOLOR4SPROC csc_glColor4s = 0;
PFNGLCOLOR4SVPROC csc_glColor4sv = 0;
PFNGLCOLOR4UBPROC csc_glColor4ub = 0;
PFNGLCOLOR4UBVPROC csc_glColor4ubv = 0;
PFNGLCOLOR4UIPROC csc_glColor4ui = 0;
PFNGLCOLOR4UIVPROC csc_glColor4uiv = 0;
PFNGLCOLOR4USPROC csc_glColor4us = 0;
PFNGLCOLOR4USVPROC csc_glColor4usv = 0;
PFNGLCOLORMASKPROC csc_glColorMask = 0;
PFNGLCOLORMASKIPROC csc_glColorMaski = 0;
PFNGLCOLORMATERIALPROC csc_glColorMaterial = 0;
PFNGLCOLORPOINTERPROC csc_glColorPointer = 0;
PFNGLCOMPILESHADERPROC csc_glCompileShader = 0;
PFNGLCOMPRESSEDTEXIMAGE1DPROC csc_glCompressedTexImage1D = 0;
PFNGLCOMPRESSEDTEXIMAGE2DPROC csc_glCompressedTexImage2D = 0;
PFNGLCOMPRESSEDTEXIMAGE3DPROC csc_glCompressedTexImage3D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC csc_glCompressedTexSubImage1D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC csc_glCompressedTexSubImage2D = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC csc_glCompressedTexSubImage3D = 0;
PFNGLCOPYBUFFERSUBDATAPROC csc_glCopyBufferSubData = 0;
PFNGLCOPYPIXELSPROC csc_glCopyPixels = 0;
PFNGLCOPYTEXIMAGE1DPROC csc_glCopyTexImage1D = 0;
PFNGLCOPYTEXIMAGE2DPROC csc_glCopyTexImage2D = 0;
PFNGLCOPYTEXSUBIMAGE1DPROC csc_glCopyTexSubImage1D = 0;
PFNGLCOPYTEXSUBIMAGE2DPROC csc_glCopyTexSubImage2D = 0;
PFNGLCOPYTEXSUBIMAGE3DPROC csc_glCopyTexSubImage3D = 0;
PFNGLCREATEPROGRAMPROC csc_glCreateProgram = 0;
PFNGLCREATESHADERPROC csc_glCreateShader = 0;
PFNGLCULLFACEPROC csc_glCullFace = 0;
PFNGLDELETEBUFFERSPROC csc_glDeleteBuffers = 0;
PFNGLDELETEFRAMEBUFFERSPROC csc_glDeleteFramebuffers = 0;
PFNGLDELETELISTSPROC csc_glDeleteLists = 0;
PFNGLDELETEPROGRAMPROC csc_glDeleteProgram = 0;
PFNGLDELETEQUERIESPROC csc_glDeleteQueries = 0;
PFNGLDELETERENDERBUFFERSPROC csc_glDeleteRenderbuffers = 0;
PFNGLDELETESHADERPROC csc_glDeleteShader = 0;
PFNGLDELETETEXTURESPROC csc_glDeleteTextures = 0;
PFNGLDELETEVERTEXARRAYSPROC csc_glDeleteVertexArrays = 0;
PFNGLDEPTHFUNCPROC csc_glDepthFunc = 0;
PFNGLDEPTHMASKPROC csc_glDepthMask = 0;
PFNGLDEPTHRANGEPROC csc_glDepthRange = 0;
PFNGLDETACHSHADERPROC csc_glDetachShader = 0;
PFNGLDISABLEPROC csc_glDisable = 0;
PFNGLDISABLECLIENTSTATEPROC csc_glDisableClientState = 0;
PFNGLDISABLEVERTEXATTRIBARRAYPROC csc_glDisableVertexAttribArray = 0;
PFNGLDISABLEIPROC csc_glDisablei = 0;
PFNGLDRAWARRAYSPROC csc_glDrawArrays = 0;
PFNGLDRAWARRAYSINSTANCEDPROC csc_glDrawArraysInstanced = 0;
PFNGLDRAWBUFFERPROC csc_glDrawBuffer = 0;
PFNGLDRAWBUFFERSPROC csc_glDrawBuffers = 0;
PFNGLDRAWELEMENTSPROC csc_glDrawElements = 0;
PFNGLDRAWELEMENTSINSTANCEDPROC csc_glDrawElementsInstanced = 0;
PFNGLDRAWPIXELSPROC csc_glDrawPixels = 0;
PFNGLDRAWRANGEELEMENTSPROC csc_glDrawRangeElements = 0;
PFNGLEDGEFLAGPROC csc_glEdgeFlag = 0;
PFNGLEDGEFLAGPOINTERPROC csc_glEdgeFlagPointer = 0;
PFNGLEDGEFLAGVPROC csc_glEdgeFlagv = 0;
PFNGLENABLEPROC csc_glEnable = 0;
PFNGLENABLECLIENTSTATEPROC csc_glEnableClientState = 0;
PFNGLENABLEVERTEXATTRIBARRAYPROC csc_glEnableVertexAttribArray = 0;
PFNGLENABLEIPROC csc_glEnablei = 0;
PFNGLENDPROC csc_glEnd = 0;
PFNGLENDCONDITIONALRENDERPROC csc_glEndConditionalRender = 0;
PFNGLENDLISTPROC csc_glEndList = 0;
PFNGLENDQUERYPROC csc_glEndQuery = 0;
PFNGLENDTRANSFORMFEEDBACKPROC csc_glEndTransformFeedback = 0;
PFNGLEVALCOORD1DPROC csc_glEvalCoord1d = 0;
PFNGLEVALCOORD1DVPROC csc_glEvalCoord1dv = 0;
PFNGLEVALCOORD1FPROC csc_glEvalCoord1f = 0;
PFNGLEVALCOORD1FVPROC csc_glEvalCoord1fv = 0;
PFNGLEVALCOORD2DPROC csc_glEvalCoord2d = 0;
PFNGLEVALCOORD2DVPROC csc_glEvalCoord2dv = 0;
PFNGLEVALCOORD2FPROC csc_glEvalCoord2f = 0;
PFNGLEVALCOORD2FVPROC csc_glEvalCoord2fv = 0;
PFNGLEVALMESH1PROC csc_glEvalMesh1 = 0;
PFNGLEVALMESH2PROC csc_glEvalMesh2 = 0;
PFNGLEVALPOINT1PROC csc_glEvalPoint1 = 0;
PFNGLEVALPOINT2PROC csc_glEvalPoint2 = 0;
PFNGLFEEDBACKBUFFERPROC csc_glFeedbackBuffer = 0;
PFNGLFINISHPROC csc_glFinish = 0;
PFNGLFLUSHPROC csc_glFlush = 0;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC csc_glFlushMappedBufferRange = 0;
PFNGLFOGCOORDPOINTERPROC csc_glFogCoordPointer = 0;
PFNGLFOGCOORDDPROC csc_glFogCoordd = 0;
PFNGLFOGCOORDDVPROC csc_glFogCoorddv = 0;
PFNGLFOGCOORDFPROC csc_glFogCoordf = 0;
PFNGLFOGCOORDFVPROC csc_glFogCoordfv = 0;
PFNGLFOGFPROC csc_glFogf = 0;
PFNGLFOGFVPROC csc_glFogfv = 0;
PFNGLFOGIPROC csc_glFogi = 0;
PFNGLFOGIVPROC csc_glFogiv = 0;
PFNGLFRAMEBUFFERRENDERBUFFERPROC csc_glFramebufferRenderbuffer = 0;
PFNGLFRAMEBUFFERTEXTURE1DPROC csc_glFramebufferTexture1D = 0;
PFNGLFRAMEBUFFERTEXTURE2DPROC csc_glFramebufferTexture2D = 0;
PFNGLFRAMEBUFFERTEXTURE3DPROC csc_glFramebufferTexture3D = 0;
PFNGLFRAMEBUFFERTEXTURELAYERPROC csc_glFramebufferTextureLayer = 0;
PFNGLFRONTFACEPROC csc_glFrontFace = 0;
PFNGLFRUSTUMPROC csc_glFrustum = 0;
PFNGLGENBUFFERSPROC csc_glGenBuffers = 0;
PFNGLGENFRAMEBUFFERSPROC csc_glGenFramebuffers = 0;
PFNGLGENLISTSPROC csc_glGenLists = 0;
PFNGLGENQUERIESPROC csc_glGenQueries = 0;
PFNGLGENRENDERBUFFERSPROC csc_glGenRenderbuffers = 0;
PFNGLGENTEXTURESPROC csc_glGenTextures = 0;
PFNGLGENVERTEXARRAYSPROC csc_glGenVertexArrays = 0;
PFNGLGENERATEMIPMAPPROC csc_glGenerateMipmap = 0;
PFNGLGETACTIVEATTRIBPROC csc_glGetActiveAttrib = 0;
PFNGLGETACTIVEUNIFORMPROC csc_glGetActiveUniform = 0;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC csc_glGetActiveUniformBlockName = 0;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC csc_glGetActiveUniformBlockiv = 0;
PFNGLGETACTIVEUNIFORMNAMEPROC csc_glGetActiveUniformName = 0;
PFNGLGETACTIVEUNIFORMSIVPROC csc_glGetActiveUniformsiv = 0;
PFNGLGETATTACHEDSHADERSPROC csc_glGetAttachedShaders = 0;
PFNGLGETATTRIBLOCATIONPROC csc_glGetAttribLocation = 0;
PFNGLGETBOOLEANI_VPROC csc_glGetBooleani_v = 0;
PFNGLGETBOOLEANVPROC csc_glGetBooleanv = 0;
PFNGLGETBUFFERPARAMETERIVPROC csc_glGetBufferParameteriv = 0;
PFNGLGETBUFFERPOINTERVPROC csc_glGetBufferPointerv = 0;
PFNGLGETBUFFERSUBDATAPROC csc_glGetBufferSubData = 0;
PFNGLGETCLIPPLANEPROC csc_glGetClipPlane = 0;
PFNGLGETCOMPRESSEDTEXIMAGEPROC csc_glGetCompressedTexImage = 0;
PFNGLGETDOUBLEVPROC csc_glGetDoublev = 0;
PFNGLGETERRORPROC csc_glGetError = 0;
PFNGLGETFLOATVPROC csc_glGetFloatv = 0;
PFNGLGETFRAGDATALOCATIONPROC csc_glGetFragDataLocation = 0;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC csc_glGetFramebufferAttachmentParameteriv = 0;
PFNGLGETINTEGERI_VPROC csc_glGetIntegeri_v = 0;
PFNGLGETINTEGERVPROC csc_glGetIntegerv = 0;
PFNGLGETLIGHTFVPROC csc_glGetLightfv = 0;
PFNGLGETLIGHTIVPROC csc_glGetLightiv = 0;
PFNGLGETMAPDVPROC csc_glGetMapdv = 0;
PFNGLGETMAPFVPROC csc_glGetMapfv = 0;
PFNGLGETMAPIVPROC csc_glGetMapiv = 0;
PFNGLGETMATERIALFVPROC csc_glGetMaterialfv = 0;
PFNGLGETMATERIALIVPROC csc_glGetMaterialiv = 0;
PFNGLGETPIXELMAPFVPROC csc_glGetPixelMapfv = 0;
PFNGLGETPIXELMAPUIVPROC csc_glGetPixelMapuiv = 0;
PFNGLGETPIXELMAPUSVPROC csc_glGetPixelMapusv = 0;
PFNGLGETPOINTERVPROC csc_glGetPointerv = 0;
PFNGLGETPOLYGONSTIPPLEPROC csc_glGetPolygonStipple = 0;
PFNGLGETPROGRAMINFOLOGPROC csc_glGetProgramInfoLog = 0;
PFNGLGETPROGRAMIVPROC csc_glGetProgramiv = 0;
PFNGLGETQUERYOBJECTIVPROC csc_glGetQueryObjectiv = 0;
PFNGLGETQUERYOBJECTUIVPROC csc_glGetQueryObjectuiv = 0;
PFNGLGETQUERYIVPROC csc_glGetQueryiv = 0;
PFNGLGETRENDERBUFFERPARAMETERIVPROC csc_glGetRenderbufferParameteriv = 0;
PFNGLGETSHADERINFOLOGPROC csc_glGetShaderInfoLog = 0;
PFNGLGETSHADERSOURCEPROC csc_glGetShaderSource = 0;
PFNGLGETSHADERIVPROC csc_glGetShaderiv = 0;
PFNGLGETSTRINGPROC csc_glGetString = 0;
PFNGLGETSTRINGIPROC csc_glGetStringi = 0;
PFNGLGETTEXENVFVPROC csc_glGetTexEnvfv = 0;
PFNGLGETTEXENVIVPROC csc_glGetTexEnviv = 0;
PFNGLGETTEXGENDVPROC csc_glGetTexGendv = 0;
PFNGLGETTEXGENFVPROC csc_glGetTexGenfv = 0;
PFNGLGETTEXGENIVPROC csc_glGetTexGeniv = 0;
PFNGLGETTEXIMAGEPROC csc_glGetTexImage = 0;
PFNGLGETTEXLEVELPARAMETERFVPROC csc_glGetTexLevelParameterfv = 0;
PFNGLGETTEXLEVELPARAMETERIVPROC csc_glGetTexLevelParameteriv = 0;
PFNGLGETTEXPARAMETERIIVPROC csc_glGetTexParameterIiv = 0;
PFNGLGETTEXPARAMETERIUIVPROC csc_glGetTexParameterIuiv = 0;
PFNGLGETTEXPARAMETERFVPROC csc_glGetTexParameterfv = 0;
PFNGLGETTEXPARAMETERIVPROC csc_glGetTexParameteriv = 0;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC csc_glGetTransformFeedbackVarying = 0;
PFNGLGETUNIFORMBLOCKINDEXPROC csc_glGetUniformBlockIndex = 0;
PFNGLGETUNIFORMINDICESPROC csc_glGetUniformIndices = 0;
PFNGLGETUNIFORMLOCATIONPROC csc_glGetUniformLocation = 0;
PFNGLGETUNIFORMFVPROC csc_glGetUniformfv = 0;
PFNGLGETUNIFORMIVPROC csc_glGetUniformiv = 0;
PFNGLGETUNIFORMUIVPROC csc_glGetUniformuiv = 0;
PFNGLGETVERTEXATTRIBIIVPROC csc_glGetVertexAttribIiv = 0;
PFNGLGETVERTEXATTRIBIUIVPROC csc_glGetVertexAttribIuiv = 0;
PFNGLGETVERTEXATTRIBPOINTERVPROC csc_glGetVertexAttribPointerv = 0;
PFNGLGETVERTEXATTRIBDVPROC csc_glGetVertexAttribdv = 0;
PFNGLGETVERTEXATTRIBFVPROC csc_glGetVertexAttribfv = 0;
PFNGLGETVERTEXATTRIBIVPROC csc_glGetVertexAttribiv = 0;
PFNGLHINTPROC csc_glHint = 0;
PFNGLINDEXMASKPROC csc_glIndexMask = 0;
PFNGLINDEXPOINTERPROC csc_glIndexPointer = 0;
PFNGLINDEXDPROC csc_glIndexd = 0;
PFNGLINDEXDVPROC csc_glIndexdv = 0;
PFNGLINDEXFPROC csc_glIndexf = 0;
PFNGLINDEXFVPROC csc_glIndexfv = 0;
PFNGLINDEXIPROC csc_glIndexi = 0;
PFNGLINDEXIVPROC csc_glIndexiv = 0;
PFNGLINDEXSPROC csc_glIndexs = 0;
PFNGLINDEXSVPROC csc_glIndexsv = 0;
PFNGLINDEXUBPROC csc_glIndexub = 0;
PFNGLINDEXUBVPROC csc_glIndexubv = 0;
PFNGLINITNAMESPROC csc_glInitNames = 0;
PFNGLINTERLEAVEDARRAYSPROC csc_glInterleavedArrays = 0;
PFNGLISBUFFERPROC csc_glIsBuffer = 0;
PFNGLISENABLEDPROC csc_glIsEnabled = 0;
PFNGLISENABLEDIPROC csc_glIsEnabledi = 0;
PFNGLISFRAMEBUFFERPROC csc_glIsFramebuffer = 0;
PFNGLISLISTPROC csc_glIsList = 0;
PFNGLISPROGRAMPROC csc_glIsProgram = 0;
PFNGLISQUERYPROC csc_glIsQuery = 0;
PFNGLISRENDERBUFFERPROC csc_glIsRenderbuffer = 0;
PFNGLISSHADERPROC csc_glIsShader = 0;
PFNGLISTEXTUREPROC csc_glIsTexture = 0;
PFNGLISVERTEXARRAYPROC csc_glIsVertexArray = 0;
PFNGLLIGHTMODELFPROC csc_glLightModelf = 0;
PFNGLLIGHTMODELFVPROC csc_glLightModelfv = 0;
PFNGLLIGHTMODELIPROC csc_glLightModeli = 0;
PFNGLLIGHTMODELIVPROC csc_glLightModeliv = 0;
PFNGLLIGHTFPROC csc_glLightf = 0;
PFNGLLIGHTFVPROC csc_glLightfv = 0;
PFNGLLIGHTIPROC csc_glLighti = 0;
PFNGLLIGHTIVPROC csc_glLightiv = 0;
PFNGLLINESTIPPLEPROC csc_glLineStipple = 0;
PFNGLLINEWIDTHPROC csc_glLineWidth = 0;
PFNGLLINKPROGRAMPROC csc_glLinkProgram = 0;
PFNGLLISTBASEPROC csc_glListBase = 0;
PFNGLLOADIDENTITYPROC csc_glLoadIdentity = 0;
PFNGLLOADMATRIXDPROC csc_glLoadMatrixd = 0;
PFNGLLOADMATRIXFPROC csc_glLoadMatrixf = 0;
PFNGLLOADNAMEPROC csc_glLoadName = 0;
PFNGLLOADTRANSPOSEMATRIXDPROC csc_glLoadTransposeMatrixd = 0;
PFNGLLOADTRANSPOSEMATRIXFPROC csc_glLoadTransposeMatrixf = 0;
PFNGLLOGICOPPROC csc_glLogicOp = 0;
PFNGLMAP1DPROC csc_glMap1d = 0;
PFNGLMAP1FPROC csc_glMap1f = 0;
PFNGLMAP2DPROC csc_glMap2d = 0;
PFNGLMAP2FPROC csc_glMap2f = 0;
PFNGLMAPBUFFERPROC csc_glMapBuffer = 0;
PFNGLMAPBUFFERRANGEPROC csc_glMapBufferRange = 0;
PFNGLMAPGRID1DPROC csc_glMapGrid1d = 0;
PFNGLMAPGRID1FPROC csc_glMapGrid1f = 0;
PFNGLMAPGRID2DPROC csc_glMapGrid2d = 0;
PFNGLMAPGRID2FPROC csc_glMapGrid2f = 0;
PFNGLMATERIALFPROC csc_glMaterialf = 0;
PFNGLMATERIALFVPROC csc_glMaterialfv = 0;
PFNGLMATERIALIPROC csc_glMateriali = 0;
PFNGLMATERIALIVPROC csc_glMaterialiv = 0;
PFNGLMATRIXMODEPROC csc_glMatrixMode = 0;
PFNGLMULTMATRIXDPROC csc_glMultMatrixd = 0;
PFNGLMULTMATRIXFPROC csc_glMultMatrixf = 0;
PFNGLMULTTRANSPOSEMATRIXDPROC csc_glMultTransposeMatrixd = 0;
PFNGLMULTTRANSPOSEMATRIXFPROC csc_glMultTransposeMatrixf = 0;
PFNGLMULTIDRAWARRAYSPROC csc_glMultiDrawArrays = 0;
PFNGLMULTIDRAWELEMENTSPROC csc_glMultiDrawElements = 0;
PFNGLMULTITEXCOORD1DPROC csc_glMultiTexCoord1d = 0;
PFNGLMULTITEXCOORD1DVPROC csc_glMultiTexCoord1dv = 0;
PFNGLMULTITEXCOORD1FPROC csc_glMultiTexCoord1f = 0;
PFNGLMULTITEXCOORD1FVPROC csc_glMultiTexCoord1fv = 0;
PFNGLMULTITEXCOORD1IPROC csc_glMultiTexCoord1i = 0;
PFNGLMULTITEXCOORD1IVPROC csc_glMultiTexCoord1iv = 0;
PFNGLMULTITEXCOORD1SPROC csc_glMultiTexCoord1s = 0;
PFNGLMULTITEXCOORD1SVPROC csc_glMultiTexCoord1sv = 0;
PFNGLMULTITEXCOORD2DPROC csc_glMultiTexCoord2d = 0;
PFNGLMULTITEXCOORD2DVPROC csc_glMultiTexCoord2dv = 0;
PFNGLMULTITEXCOORD2FPROC csc_glMultiTexCoord2f = 0;
PFNGLMULTITEXCOORD2FVPROC csc_glMultiTexCoord2fv = 0;
PFNGLMULTITEXCOORD2IPROC csc_glMultiTexCoord2i = 0;
PFNGLMULTITEXCOORD2IVPROC csc_glMultiTexCoord2iv = 0;
PFNGLMULTITEXCOORD2SPROC csc_glMultiTexCoord2s = 0;
PFNGLMULTITEXCOORD2SVPROC csc_glMultiTexCoord2sv = 0;
PFNGLMULTITEXCOORD3DPROC csc_glMultiTexCoord3d = 0;
PFNGLMULTITEXCOORD3DVPROC csc_glMultiTexCoord3dv = 0;
PFNGLMULTITEXCOORD3FPROC csc_glMultiTexCoord3f = 0;
PFNGLMULTITEXCOORD3FVPROC csc_glMultiTexCoord3fv = 0;
PFNGLMULTITEXCOORD3IPROC csc_glMultiTexCoord3i = 0;
PFNGLMULTITEXCOORD3IVPROC csc_glMultiTexCoord3iv = 0;
PFNGLMULTITEXCOORD3SPROC csc_glMultiTexCoord3s = 0;
PFNGLMULTITEXCOORD3SVPROC csc_glMultiTexCoord3sv = 0;
PFNGLMULTITEXCOORD4DPROC csc_glMultiTexCoord4d = 0;
PFNGLMULTITEXCOORD4DVPROC csc_glMultiTexCoord4dv = 0;
PFNGLMULTITEXCOORD4FPROC csc_glMultiTexCoord4f = 0;
PFNGLMULTITEXCOORD4FVPROC csc_glMultiTexCoord4fv = 0;
PFNGLMULTITEXCOORD4IPROC csc_glMultiTexCoord4i = 0;
PFNGLMULTITEXCOORD4IVPROC csc_glMultiTexCoord4iv = 0;
PFNGLMULTITEXCOORD4SPROC csc_glMultiTexCoord4s = 0;
PFNGLMULTITEXCOORD4SVPROC csc_glMultiTexCoord4sv = 0;
PFNGLNEWLISTPROC csc_glNewList = 0;
PFNGLNORMAL3BPROC csc_glNormal3b = 0;
PFNGLNORMAL3BVPROC csc_glNormal3bv = 0;
PFNGLNORMAL3DPROC csc_glNormal3d = 0;
PFNGLNORMAL3DVPROC csc_glNormal3dv = 0;
PFNGLNORMAL3FPROC csc_glNormal3f = 0;
PFNGLNORMAL3FVPROC csc_glNormal3fv = 0;
PFNGLNORMAL3IPROC csc_glNormal3i = 0;
PFNGLNORMAL3IVPROC csc_glNormal3iv = 0;
PFNGLNORMAL3SPROC csc_glNormal3s = 0;
PFNGLNORMAL3SVPROC csc_glNormal3sv = 0;
PFNGLNORMALPOINTERPROC csc_glNormalPointer = 0;
PFNGLORTHOPROC csc_glOrtho = 0;
PFNGLPASSTHROUGHPROC csc_glPassThrough = 0;
PFNGLPIXELMAPFVPROC csc_glPixelMapfv = 0;
PFNGLPIXELMAPUIVPROC csc_glPixelMapuiv = 0;
PFNGLPIXELMAPUSVPROC csc_glPixelMapusv = 0;
PFNGLPIXELSTOREFPROC csc_glPixelStoref = 0;
PFNGLPIXELSTOREIPROC csc_glPixelStorei = 0;
PFNGLPIXELTRANSFERFPROC csc_glPixelTransferf = 0;
PFNGLPIXELTRANSFERIPROC csc_glPixelTransferi = 0;
PFNGLPIXELZOOMPROC csc_glPixelZoom = 0;
PFNGLPOINTPARAMETERFPROC csc_glPointParameterf = 0;
PFNGLPOINTPARAMETERFVPROC csc_glPointParameterfv = 0;
PFNGLPOINTPARAMETERIPROC csc_glPointParameteri = 0;
PFNGLPOINTPARAMETERIVPROC csc_glPointParameteriv = 0;
PFNGLPOINTSIZEPROC csc_glPointSize = 0;
PFNGLPOLYGONMODEPROC csc_glPolygonMode = 0;
PFNGLPOLYGONOFFSETPROC csc_glPolygonOffset = 0;
PFNGLPOLYGONSTIPPLEPROC csc_glPolygonStipple = 0;
PFNGLPOPATTRIBPROC csc_glPopAttrib = 0;
PFNGLPOPCLIENTATTRIBPROC csc_glPopClientAttrib = 0;
PFNGLPOPMATRIXPROC csc_glPopMatrix = 0;
PFNGLPOPNAMEPROC csc_glPopName = 0;
PFNGLPRIMITIVERESTARTINDEXPROC csc_glPrimitiveRestartIndex = 0;
PFNGLPRIORITIZETEXTURESPROC csc_glPrioritizeTextures = 0;
PFNGLPUSHATTRIBPROC csc_glPushAttrib = 0;
PFNGLPUSHCLIENTATTRIBPROC csc_glPushClientAttrib = 0;
PFNGLPUSHMATRIXPROC csc_glPushMatrix = 0;
PFNGLPUSHNAMEPROC csc_glPushName = 0;
PFNGLRASTERPOS2DPROC csc_glRasterPos2d = 0;
PFNGLRASTERPOS2DVPROC csc_glRasterPos2dv = 0;
PFNGLRASTERPOS2FPROC csc_glRasterPos2f = 0;
PFNGLRASTERPOS2FVPROC csc_glRasterPos2fv = 0;
PFNGLRASTERPOS2IPROC csc_glRasterPos2i = 0;
PFNGLRASTERPOS2IVPROC csc_glRasterPos2iv = 0;
PFNGLRASTERPOS2SPROC csc_glRasterPos2s = 0;
PFNGLRASTERPOS2SVPROC csc_glRasterPos2sv = 0;
PFNGLRASTERPOS3DPROC csc_glRasterPos3d = 0;
PFNGLRASTERPOS3DVPROC csc_glRasterPos3dv = 0;
PFNGLRASTERPOS3FPROC csc_glRasterPos3f = 0;
PFNGLRASTERPOS3FVPROC csc_glRasterPos3fv = 0;
PFNGLRASTERPOS3IPROC csc_glRasterPos3i = 0;
PFNGLRASTERPOS3IVPROC csc_glRasterPos3iv = 0;
PFNGLRASTERPOS3SPROC csc_glRasterPos3s = 0;
PFNGLRASTERPOS3SVPROC csc_glRasterPos3sv = 0;
PFNGLRASTERPOS4DPROC csc_glRasterPos4d = 0;
PFNGLRASTERPOS4DVPROC csc_glRasterPos4dv = 0;
PFNGLRASTERPOS4FPROC csc_glRasterPos4f = 0;
PFNGLRASTERPOS4FVPROC csc_glRasterPos4fv = 0;
PFNGLRASTERPOS4IPROC csc_glRasterPos4i = 0;
PFNGLRASTERPOS4IVPROC csc_glRasterPos4iv = 0;
PFNGLRASTERPOS4SPROC csc_glRasterPos4s = 0;
PFNGLRASTERPOS4SVPROC csc_glRasterPos4sv = 0;
PFNGLREADBUFFERPROC csc_glReadBuffer = 0;
PFNGLREADPIXELSPROC csc_glReadPixels = 0;
PFNGLRECTDPROC csc_glRectd = 0;
PFNGLRECTDVPROC csc_glRectdv = 0;
PFNGLRECTFPROC csc_glRectf = 0;
PFNGLRECTFVPROC csc_glRectfv = 0;
PFNGLRECTIPROC csc_glRecti = 0;
PFNGLRECTIVPROC csc_glRectiv = 0;
PFNGLRECTSPROC csc_glRects = 0;
PFNGLRECTSVPROC csc_glRectsv = 0;
PFNGLRENDERMODEPROC csc_glRenderMode = 0;
PFNGLRENDERBUFFERSTORAGEPROC csc_glRenderbufferStorage = 0;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC csc_glRenderbufferStorageMultisample = 0;
PFNGLROTATEDPROC csc_glRotated = 0;
PFNGLROTATEFPROC csc_glRotatef = 0;
PFNGLSAMPLECOVERAGEPROC csc_glSampleCoverage = 0;
PFNGLSCALEDPROC csc_glScaled = 0;
PFNGLSCALEFPROC csc_glScalef = 0;
PFNGLSCISSORPROC csc_glScissor = 0;
PFNGLSECONDARYCOLOR3BPROC csc_glSecondaryColor3b = 0;
PFNGLSECONDARYCOLOR3BVPROC csc_glSecondaryColor3bv = 0;
PFNGLSECONDARYCOLOR3DPROC csc_glSecondaryColor3d = 0;
PFNGLSECONDARYCOLOR3DVPROC csc_glSecondaryColor3dv = 0;
PFNGLSECONDARYCOLOR3FPROC csc_glSecondaryColor3f = 0;
PFNGLSECONDARYCOLOR3FVPROC csc_glSecondaryColor3fv = 0;
PFNGLSECONDARYCOLOR3IPROC csc_glSecondaryColor3i = 0;
PFNGLSECONDARYCOLOR3IVPROC csc_glSecondaryColor3iv = 0;
PFNGLSECONDARYCOLOR3SPROC csc_glSecondaryColor3s = 0;
PFNGLSECONDARYCOLOR3SVPROC csc_glSecondaryColor3sv = 0;
PFNGLSECONDARYCOLOR3UBPROC csc_glSecondaryColor3ub = 0;
PFNGLSECONDARYCOLOR3UBVPROC csc_glSecondaryColor3ubv = 0;
PFNGLSECONDARYCOLOR3UIPROC csc_glSecondaryColor3ui = 0;
PFNGLSECONDARYCOLOR3UIVPROC csc_glSecondaryColor3uiv = 0;
PFNGLSECONDARYCOLOR3USPROC csc_glSecondaryColor3us = 0;
PFNGLSECONDARYCOLOR3USVPROC csc_glSecondaryColor3usv = 0;
PFNGLSECONDARYCOLORPOINTERPROC csc_glSecondaryColorPointer = 0;
PFNGLSELECTBUFFERPROC csc_glSelectBuffer = 0;
PFNGLSHADEMODELPROC csc_glShadeModel = 0;
PFNGLSHADERSOURCEPROC csc_glShaderSource = 0;
PFNGLSTENCILFUNCPROC csc_glStencilFunc = 0;
PFNGLSTENCILFUNCSEPARATEPROC csc_glStencilFuncSeparate = 0;
PFNGLSTENCILMASKPROC csc_glStencilMask = 0;
PFNGLSTENCILMASKSEPARATEPROC csc_glStencilMaskSeparate = 0;
PFNGLSTENCILOPPROC csc_glStencilOp = 0;
PFNGLSTENCILOPSEPARATEPROC csc_glStencilOpSeparate = 0;
PFNGLTEXBUFFERPROC csc_glTexBuffer = 0;
PFNGLTEXCOORD1DPROC csc_glTexCoord1d = 0;
PFNGLTEXCOORD1DVPROC csc_glTexCoord1dv = 0;
PFNGLTEXCOORD1FPROC csc_glTexCoord1f = 0;
PFNGLTEXCOORD1FVPROC csc_glTexCoord1fv = 0;
PFNGLTEXCOORD1IPROC csc_glTexCoord1i = 0;
PFNGLTEXCOORD1IVPROC csc_glTexCoord1iv = 0;
PFNGLTEXCOORD1SPROC csc_glTexCoord1s = 0;
PFNGLTEXCOORD1SVPROC csc_glTexCoord1sv = 0;
PFNGLTEXCOORD2DPROC csc_glTexCoord2d = 0;
PFNGLTEXCOORD2DVPROC csc_glTexCoord2dv = 0;
PFNGLTEXCOORD2FPROC csc_glTexCoord2f = 0;
PFNGLTEXCOORD2FVPROC csc_glTexCoord2fv = 0;
PFNGLTEXCOORD2IPROC csc_glTexCoord2i = 0;
PFNGLTEXCOORD2IVPROC csc_glTexCoord2iv = 0;
PFNGLTEXCOORD2SPROC csc_glTexCoord2s = 0;
PFNGLTEXCOORD2SVPROC csc_glTexCoord2sv = 0;
PFNGLTEXCOORD3DPROC csc_glTexCoord3d = 0;
PFNGLTEXCOORD3DVPROC csc_glTexCoord3dv = 0;
PFNGLTEXCOORD3FPROC csc_glTexCoord3f = 0;
PFNGLTEXCOORD3FVPROC csc_glTexCoord3fv = 0;
PFNGLTEXCOORD3IPROC csc_glTexCoord3i = 0;
PFNGLTEXCOORD3IVPROC csc_glTexCoord3iv = 0;
PFNGLTEXCOORD3SPROC csc_glTexCoord3s = 0;
PFNGLTEXCOORD3SVPROC csc_glTexCoord3sv = 0;
PFNGLTEXCOORD4DPROC csc_glTexCoord4d = 0;
PFNGLTEXCOORD4DVPROC csc_glTexCoord4dv = 0;
PFNGLTEXCOORD4FPROC csc_glTexCoord4f = 0;
PFNGLTEXCOORD4FVPROC csc_glTexCoord4fv = 0;
PFNGLTEXCOORD4IPROC csc_glTexCoord4i = 0;
PFNGLTEXCOORD4IVPROC csc_glTexCoord4iv = 0;
PFNGLTEXCOORD4SPROC csc_glTexCoord4s = 0;
PFNGLTEXCOORD4SVPROC csc_glTexCoord4sv = 0;
PFNGLTEXCOORDPOINTERPROC csc_glTexCoordPointer = 0;
PFNGLTEXENVFPROC csc_glTexEnvf = 0;
PFNGLTEXENVFVPROC csc_glTexEnvfv = 0;
PFNGLTEXENVIPROC csc_glTexEnvi = 0;
PFNGLTEXENVIVPROC csc_glTexEnviv = 0;
PFNGLTEXGENDPROC csc_glTexGend = 0;
PFNGLTEXGENDVPROC csc_glTexGendv = 0;
PFNGLTEXGENFPROC csc_glTexGenf = 0;
PFNGLTEXGENFVPROC csc_glTexGenfv = 0;
PFNGLTEXGENIPROC csc_glTexGeni = 0;
PFNGLTEXGENIVPROC csc_glTexGeniv = 0;
PFNGLTEXIMAGE1DPROC csc_glTexImage1D = 0;
PFNGLTEXIMAGE2DPROC csc_glTexImage2D = 0;
PFNGLTEXIMAGE3DPROC csc_glTexImage3D = 0;
PFNGLTEXPARAMETERIIVPROC csc_glTexParameterIiv = 0;
PFNGLTEXPARAMETERIUIVPROC csc_glTexParameterIuiv = 0;
PFNGLTEXPARAMETERFPROC csc_glTexParameterf = 0;
PFNGLTEXPARAMETERFVPROC csc_glTexParameterfv = 0;
PFNGLTEXPARAMETERIPROC csc_glTexParameteri = 0;
PFNGLTEXPARAMETERIVPROC csc_glTexParameteriv = 0;
PFNGLTEXSUBIMAGE1DPROC csc_glTexSubImage1D = 0;
PFNGLTEXSUBIMAGE2DPROC csc_glTexSubImage2D = 0;
PFNGLTEXSUBIMAGE3DPROC csc_glTexSubImage3D = 0;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC csc_glTransformFeedbackVaryings = 0;
PFNGLTRANSLATEDPROC csc_glTranslated = 0;
PFNGLTRANSLATEFPROC csc_glTranslatef = 0;
PFNGLUNIFORM1FPROC csc_glUniform1f = 0;
PFNGLUNIFORM1FVPROC csc_glUniform1fv = 0;
PFNGLUNIFORM1IPROC csc_glUniform1i = 0;
PFNGLUNIFORM1IVPROC csc_glUniform1iv = 0;
PFNGLUNIFORM1UIPROC csc_glUniform1ui = 0;
PFNGLUNIFORM1UIVPROC csc_glUniform1uiv = 0;
PFNGLUNIFORM2FPROC csc_glUniform2f = 0;
PFNGLUNIFORM2FVPROC csc_glUniform2fv = 0;
PFNGLUNIFORM2IPROC csc_glUniform2i = 0;
PFNGLUNIFORM2IVPROC csc_glUniform2iv = 0;
PFNGLUNIFORM2UIPROC csc_glUniform2ui = 0;
PFNGLUNIFORM2UIVPROC csc_glUniform2uiv = 0;
PFNGLUNIFORM3FPROC csc_glUniform3f = 0;
PFNGLUNIFORM3FVPROC csc_glUniform3fv = 0;
PFNGLUNIFORM3IPROC csc_glUniform3i = 0;
PFNGLUNIFORM3IVPROC csc_glUniform3iv = 0;
PFNGLUNIFORM3UIPROC csc_glUniform3ui = 0;
PFNGLUNIFORM3UIVPROC csc_glUniform3uiv = 0;
PFNGLUNIFORM4FPROC csc_glUniform4f = 0;
PFNGLUNIFORM4FVPROC csc_glUniform4fv = 0;
PFNGLUNIFORM4IPROC csc_glUniform4i = 0;
PFNGLUNIFORM4IVPROC csc_glUniform4iv = 0;
PFNGLUNIFORM4UIPROC csc_glUniform4ui = 0;
PFNGLUNIFORM4UIVPROC csc_glUniform4uiv = 0;
PFNGLUNIFORMBLOCKBINDINGPROC csc_glUniformBlockBinding = 0;
PFNGLUNIFORMMATRIX2FVPROC csc_glUniformMatrix2fv = 0;
PFNGLUNIFORMMATRIX2X3FVPROC csc_glUniformMatrix2x3fv = 0;
PFNGLUNIFORMMATRIX2X4FVPROC csc_glUniformMatrix2x4fv = 0;
PFNGLUNIFORMMATRIX3FVPROC csc_glUniformMatrix3fv = 0;
PFNGLUNIFORMMATRIX3X2FVPROC csc_glUniformMatrix3x2fv = 0;
PFNGLUNIFORMMATRIX3X4FVPROC csc_glUniformMatrix3x4fv = 0;
PFNGLUNIFORMMATRIX4FVPROC csc_glUniformMatrix4fv = 0;
PFNGLUNIFORMMATRIX4X2FVPROC csc_glUniformMatrix4x2fv = 0;
PFNGLUNIFORMMATRIX4X3FVPROC csc_glUniformMatrix4x3fv = 0;
PFNGLUNMAPBUFFERPROC csc_glUnmapBuffer = 0;
PFNGLUSEPROGRAMPROC csc_glUseProgram = 0;
PFNGLVALIDATEPROGRAMPROC csc_glValidateProgram = 0;
PFNGLVERTEX2DPROC csc_glVertex2d = 0;
PFNGLVERTEX2DVPROC csc_glVertex2dv = 0;
PFNGLVERTEX2FPROC csc_glVertex2f = 0;
PFNGLVERTEX2FVPROC csc_glVertex2fv = 0;
PFNGLVERTEX2IPROC csc_glVertex2i = 0;
PFNGLVERTEX2IVPROC csc_glVertex2iv = 0;
PFNGLVERTEX2SPROC csc_glVertex2s = 0;
PFNGLVERTEX2SVPROC csc_glVertex2sv = 0;
PFNGLVERTEX3DPROC csc_glVertex3d = 0;
PFNGLVERTEX3DVPROC csc_glVertex3dv = 0;
PFNGLVERTEX3FPROC csc_glVertex3f = 0;
PFNGLVERTEX3FVPROC csc_glVertex3fv = 0;
PFNGLVERTEX3IPROC csc_glVertex3i = 0;
PFNGLVERTEX3IVPROC csc_glVertex3iv = 0;
PFNGLVERTEX3SPROC csc_glVertex3s = 0;
PFNGLVERTEX3SVPROC csc_glVertex3sv = 0;
PFNGLVERTEX4DPROC csc_glVertex4d = 0;
PFNGLVERTEX4DVPROC csc_glVertex4dv = 0;
PFNGLVERTEX4FPROC csc_glVertex4f = 0;
PFNGLVERTEX4FVPROC csc_glVertex4fv = 0;
PFNGLVERTEX4IPROC csc_glVertex4i = 0;
PFNGLVERTEX4IVPROC csc_glVertex4iv = 0;
PFNGLVERTEX4SPROC csc_glVertex4s = 0;
PFNGLVERTEX4SVPROC csc_glVertex4sv = 0;
PFNGLVERTEXATTRIB1DPROC csc_glVertexAttrib1d = 0;
PFNGLVERTEXATTRIB1DVPROC csc_glVertexAttrib1dv = 0;
PFNGLVERTEXATTRIB1FPROC csc_glVertexAttrib1f = 0;
PFNGLVERTEXATTRIB1FVPROC csc_glVertexAttrib1fv = 0;
PFNGLVERTEXATTRIB1SPROC csc_glVertexAttrib1s = 0;
PFNGLVERTEXATTRIB1SVPROC csc_glVertexAttrib1sv = 0;
PFNGLVERTEXATTRIB2DPROC csc_glVertexAttrib2d = 0;
PFNGLVERTEXATTRIB2DVPROC csc_glVertexAttrib2dv = 0;
PFNGLVERTEXATTRIB2FPROC csc_glVertexAttrib2f = 0;
PFNGLVERTEXATTRIB2FVPROC csc_glVertexAttrib2fv = 0;
PFNGLVERTEXATTRIB2SPROC csc_glVertexAttrib2s = 0;
PFNGLVERTEXATTRIB2SVPROC csc_glVertexAttrib2sv = 0;
PFNGLVERTEXATTRIB3DPROC csc_glVertexAttrib3d = 0;
PFNGLVERTEXATTRIB3DVPROC csc_glVertexAttrib3dv = 0;
PFNGLVERTEXATTRIB3FPROC csc_glVertexAttrib3f = 0;
PFNGLVERTEXATTRIB3FVPROC csc_glVertexAttrib3fv = 0;
PFNGLVERTEXATTRIB3SPROC csc_glVertexAttrib3s = 0;
PFNGLVERTEXATTRIB3SVPROC csc_glVertexAttrib3sv = 0;
PFNGLVERTEXATTRIB4NBVPROC csc_glVertexAttrib4Nbv = 0;
PFNGLVERTEXATTRIB4NIVPROC csc_glVertexAttrib4Niv = 0;
PFNGLVERTEXATTRIB4NSVPROC csc_glVertexAttrib4Nsv = 0;
PFNGLVERTEXATTRIB4NUBPROC csc_glVertexAttrib4Nub = 0;
PFNGLVERTEXATTRIB4NUBVPROC csc_glVertexAttrib4Nubv = 0;
PFNGLVERTEXATTRIB4NUIVPROC csc_glVertexAttrib4Nuiv = 0;
PFNGLVERTEXATTRIB4NUSVPROC csc_glVertexAttrib4Nusv = 0;
PFNGLVERTEXATTRIB4BVPROC csc_glVertexAttrib4bv = 0;
PFNGLVERTEXATTRIB4DPROC csc_glVertexAttrib4d = 0;
PFNGLVERTEXATTRIB4DVPROC csc_glVertexAttrib4dv = 0;
PFNGLVERTEXATTRIB4FPROC csc_glVertexAttrib4f = 0;
PFNGLVERTEXATTRIB4FVPROC csc_glVertexAttrib4fv = 0;
PFNGLVERTEXATTRIB4IVPROC csc_glVertexAttrib4iv = 0;
PFNGLVERTEXATTRIB4SPROC csc_glVertexAttrib4s = 0;
PFNGLVERTEXATTRIB4SVPROC csc_glVertexAttrib4sv = 0;
PFNGLVERTEXATTRIB4UBVPROC csc_glVertexAttrib4ubv = 0;
PFNGLVERTEXATTRIB4UIVPROC csc_glVertexAttrib4uiv = 0;
PFNGLVERTEXATTRIB4USVPROC csc_glVertexAttrib4usv = 0;
PFNGLVERTEXATTRIBI1IPROC csc_glVertexAttribI1i = 0;
PFNGLVERTEXATTRIBI1IVPROC csc_glVertexAttribI1iv = 0;
PFNGLVERTEXATTRIBI1UIPROC csc_glVertexAttribI1ui = 0;
PFNGLVERTEXATTRIBI1UIVPROC csc_glVertexAttribI1uiv = 0;
PFNGLVERTEXATTRIBI2IPROC csc_glVertexAttribI2i = 0;
PFNGLVERTEXATTRIBI2IVPROC csc_glVertexAttribI2iv = 0;
PFNGLVERTEXATTRIBI2UIPROC csc_glVertexAttribI2ui = 0;
PFNGLVERTEXATTRIBI2UIVPROC csc_glVertexAttribI2uiv = 0;
PFNGLVERTEXATTRIBI3IPROC csc_glVertexAttribI3i = 0;
PFNGLVERTEXATTRIBI3IVPROC csc_glVertexAttribI3iv = 0;
PFNGLVERTEXATTRIBI3UIPROC csc_glVertexAttribI3ui = 0;
PFNGLVERTEXATTRIBI3UIVPROC csc_glVertexAttribI3uiv = 0;
PFNGLVERTEXATTRIBI4BVPROC csc_glVertexAttribI4bv = 0;
PFNGLVERTEXATTRIBI4IPROC csc_glVertexAttribI4i = 0;
PFNGLVERTEXATTRIBI4IVPROC csc_glVertexAttribI4iv = 0;
PFNGLVERTEXATTRIBI4SVPROC csc_glVertexAttribI4sv = 0;
PFNGLVERTEXATTRIBI4UBVPROC csc_glVertexAttribI4ubv = 0;
PFNGLVERTEXATTRIBI4UIPROC csc_glVertexAttribI4ui = 0;
PFNGLVERTEXATTRIBI4UIVPROC csc_glVertexAttribI4uiv = 0;
PFNGLVERTEXATTRIBI4USVPROC csc_glVertexAttribI4usv = 0;
PFNGLVERTEXATTRIBIPOINTERPROC csc_glVertexAttribIPointer = 0;
PFNGLVERTEXATTRIBPOINTERPROC csc_glVertexAttribPointer = 0;
PFNGLVERTEXPOINTERPROC csc_glVertexPointer = 0;
PFNGLVIEWPORTPROC csc_glViewport = 0;
PFNGLWINDOWPOS2DPROC csc_glWindowPos2d = 0;
PFNGLWINDOWPOS2DVPROC csc_glWindowPos2dv = 0;
PFNGLWINDOWPOS2FPROC csc_glWindowPos2f = 0;
PFNGLWINDOWPOS2FVPROC csc_glWindowPos2fv = 0;
PFNGLWINDOWPOS2IPROC csc_glWindowPos2i = 0;
PFNGLWINDOWPOS2IVPROC csc_glWindowPos2iv = 0;
PFNGLWINDOWPOS2SPROC csc_glWindowPos2s = 0;
PFNGLWINDOWPOS2SVPROC csc_glWindowPos2sv = 0;
PFNGLWINDOWPOS3DPROC csc_glWindowPos3d = 0;
PFNGLWINDOWPOS3DVPROC csc_glWindowPos3dv = 0;
PFNGLWINDOWPOS3FPROC csc_glWindowPos3f = 0;
PFNGLWINDOWPOS3FVPROC csc_glWindowPos3fv = 0;
PFNGLWINDOWPOS3IPROC csc_glWindowPos3i = 0;
PFNGLWINDOWPOS3IVPROC csc_glWindowPos3iv = 0;
PFNGLWINDOWPOS3SPROC csc_glWindowPos3s = 0;
PFNGLWINDOWPOS3SVPROC csc_glWindowPos3sv = 0;

// Function loaders
//
//

internal void
Load_GL_VERSION_1_0(CSCLoadProc LoadOpenGLProc)
{
    if(CSC_GL_VERSION_1_0)
    {
        csc_glCullFace = (PFNGLCULLFACEPROC)LoadOpenGLProc("glCullFace");
        csc_glFrontFace = (PFNGLFRONTFACEPROC)LoadOpenGLProc("glFrontFace");
        csc_glHint = (PFNGLHINTPROC)LoadOpenGLProc("glHint");
        csc_glLineWidth = (PFNGLLINEWIDTHPROC)LoadOpenGLProc("glLineWidth");
        csc_glPointSize = (PFNGLPOINTSIZEPROC)LoadOpenGLProc("glPointSize");
        csc_glPolygonMode = (PFNGLPOLYGONMODEPROC)LoadOpenGLProc("glPolygonMode");
        csc_glScissor = (PFNGLSCISSORPROC)LoadOpenGLProc("glScissor");
        csc_glTexParameterf = (PFNGLTEXPARAMETERFPROC)LoadOpenGLProc("glTexParameterf");
        csc_glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)LoadOpenGLProc("glTexParameterfv");
        csc_glTexParameteri = (PFNGLTEXPARAMETERIPROC)LoadOpenGLProc("glTexParameteri");
        csc_glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)LoadOpenGLProc("glTexParameteriv");
        csc_glTexImage1D = (PFNGLTEXIMAGE1DPROC)LoadOpenGLProc("glTexImage1D");
        csc_glTexImage2D = (PFNGLTEXIMAGE2DPROC)LoadOpenGLProc("glTexImage2D");
        csc_glDrawBuffer = (PFNGLDRAWBUFFERPROC)LoadOpenGLProc("glDrawBuffer");
        csc_glClear = (PFNGLCLEARPROC)LoadOpenGLProc("glClear");
        csc_glClearColor = (PFNGLCLEARCOLORPROC)LoadOpenGLProc("glClearColor");
        csc_glClearStencil = (PFNGLCLEARSTENCILPROC)LoadOpenGLProc("glClearStencil");
        csc_glClearDepth = (PFNGLCLEARDEPTHPROC)LoadOpenGLProc("glClearDepth");
        csc_glStencilMask = (PFNGLSTENCILMASKPROC)LoadOpenGLProc("glStencilMask");
        csc_glColorMask = (PFNGLCOLORMASKPROC)LoadOpenGLProc("glColorMask");
        csc_glDepthMask = (PFNGLDEPTHMASKPROC)LoadOpenGLProc("glDepthMask");
        csc_glDisable = (PFNGLDISABLEPROC)LoadOpenGLProc("glDisable");
        csc_glEnable = (PFNGLENABLEPROC)LoadOpenGLProc("glEnable");
        csc_glFinish = (PFNGLFINISHPROC)LoadOpenGLProc("glFinish");
        csc_glFlush = (PFNGLFLUSHPROC)LoadOpenGLProc("glFlush");
        csc_glBlendFunc = (PFNGLBLENDFUNCPROC)LoadOpenGLProc("glBlendFunc");
        csc_glLogicOp = (PFNGLLOGICOPPROC)LoadOpenGLProc("glLogicOp");
        csc_glStencilFunc = (PFNGLSTENCILFUNCPROC)LoadOpenGLProc("glStencilFunc");
        csc_glStencilOp = (PFNGLSTENCILOPPROC)LoadOpenGLProc("glStencilOp");
        csc_glDepthFunc = (PFNGLDEPTHFUNCPROC)LoadOpenGLProc("glDepthFunc");
        csc_glPixelStoref = (PFNGLPIXELSTOREFPROC)LoadOpenGLProc("glPixelStoref");
        csc_glPixelStorei = (PFNGLPIXELSTOREIPROC)LoadOpenGLProc("glPixelStorei");
        csc_glReadBuffer = (PFNGLREADBUFFERPROC)LoadOpenGLProc("glReadBuffer");
        csc_glReadPixels = (PFNGLREADPIXELSPROC)LoadOpenGLProc("glReadPixels");
        csc_glGetBooleanv = (PFNGLGETBOOLEANVPROC)LoadOpenGLProc("glGetBooleanv");
        csc_glGetDoublev = (PFNGLGETDOUBLEVPROC)LoadOpenGLProc("glGetDoublev");
        csc_glGetError = (PFNGLGETERRORPROC)LoadOpenGLProc("glGetError");
        csc_glGetFloatv = (PFNGLGETFLOATVPROC)LoadOpenGLProc("glGetFloatv");
        csc_glGetIntegerv = (PFNGLGETINTEGERVPROC)LoadOpenGLProc("glGetIntegerv");
        csc_glGetString = (PFNGLGETSTRINGPROC)LoadOpenGLProc("glGetString");
        csc_glGetTexImage = (PFNGLGETTEXIMAGEPROC)LoadOpenGLProc("glGetTexImage");
        csc_glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC)LoadOpenGLProc("glGetTexParameterfv");
        csc_glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC)LoadOpenGLProc("glGetTexParameteriv");
        csc_glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC)LoadOpenGLProc("glGetTexLevelParameterfv");
        csc_glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC)LoadOpenGLProc("glGetTexLevelParameteriv");
        csc_glIsEnabled = (PFNGLISENABLEDPROC)LoadOpenGLProc("glIsEnabled");
        csc_glDepthRange = (PFNGLDEPTHRANGEPROC)LoadOpenGLProc("glDepthRange");
        csc_glViewport = (PFNGLVIEWPORTPROC)LoadOpenGLProc("glViewport");
        csc_glNewList = (PFNGLNEWLISTPROC)LoadOpenGLProc("glNewList");
        csc_glEndList = (PFNGLENDLISTPROC)LoadOpenGLProc("glEndList");
        csc_glCallList = (PFNGLCALLLISTPROC)LoadOpenGLProc("glCallList");
        csc_glCallLists = (PFNGLCALLLISTSPROC)LoadOpenGLProc("glCallLists");
        csc_glDeleteLists = (PFNGLDELETELISTSPROC)LoadOpenGLProc("glDeleteLists");
        csc_glGenLists = (PFNGLGENLISTSPROC)LoadOpenGLProc("glGenLists");
        csc_glListBase = (PFNGLLISTBASEPROC)LoadOpenGLProc("glListBase");
        csc_glBegin = (PFNGLBEGINPROC)LoadOpenGLProc("glBegin");
        csc_glBitmap = (PFNGLBITMAPPROC)LoadOpenGLProc("glBitmap");
        csc_glColor3b = (PFNGLCOLOR3BPROC)LoadOpenGLProc("glColor3b");
        csc_glColor3bv = (PFNGLCOLOR3BVPROC)LoadOpenGLProc("glColor3bv");
        csc_glColor3d = (PFNGLCOLOR3DPROC)LoadOpenGLProc("glColor3d");
        csc_glColor3dv = (PFNGLCOLOR3DVPROC)LoadOpenGLProc("glColor3dv");
        csc_glColor3f = (PFNGLCOLOR3FPROC)LoadOpenGLProc("glColor3f");
        csc_glColor3fv = (PFNGLCOLOR3FVPROC)LoadOpenGLProc("glColor3fv");
        csc_glColor3i = (PFNGLCOLOR3IPROC)LoadOpenGLProc("glColor3i");
        csc_glColor3iv = (PFNGLCOLOR3IVPROC)LoadOpenGLProc("glColor3iv");
        csc_glColor3s = (PFNGLCOLOR3SPROC)LoadOpenGLProc("glColor3s");
        csc_glColor3sv = (PFNGLCOLOR3SVPROC)LoadOpenGLProc("glColor3sv");
        csc_glColor3ub = (PFNGLCOLOR3UBPROC)LoadOpenGLProc("glColor3ub");
        csc_glColor3ubv = (PFNGLCOLOR3UBVPROC)LoadOpenGLProc("glColor3ubv");
        csc_glColor3ui = (PFNGLCOLOR3UIPROC)LoadOpenGLProc("glColor3ui");
        csc_glColor3uiv = (PFNGLCOLOR3UIVPROC)LoadOpenGLProc("glColor3uiv");
        csc_glColor3us = (PFNGLCOLOR3USPROC)LoadOpenGLProc("glColor3us");
        csc_glColor3usv = (PFNGLCOLOR3USVPROC)LoadOpenGLProc("glColor3usv");
        csc_glColor4b = (PFNGLCOLOR4BPROC)LoadOpenGLProc("glColor4b");
        csc_glColor4bv = (PFNGLCOLOR4BVPROC)LoadOpenGLProc("glColor4bv");
        csc_glColor4d = (PFNGLCOLOR4DPROC)LoadOpenGLProc("glColor4d");
        csc_glColor4dv = (PFNGLCOLOR4DVPROC)LoadOpenGLProc("glColor4dv");
        csc_glColor4f = (PFNGLCOLOR4FPROC)LoadOpenGLProc("glColor4f");
        csc_glColor4fv = (PFNGLCOLOR4FVPROC)LoadOpenGLProc("glColor4fv");
        csc_glColor4i = (PFNGLCOLOR4IPROC)LoadOpenGLProc("glColor4i");
        csc_glColor4iv = (PFNGLCOLOR4IVPROC)LoadOpenGLProc("glColor4iv");
        csc_glColor4s = (PFNGLCOLOR4SPROC)LoadOpenGLProc("glColor4s");
        csc_glColor4sv = (PFNGLCOLOR4SVPROC)LoadOpenGLProc("glColor4sv");
        csc_glColor4ub = (PFNGLCOLOR4UBPROC)LoadOpenGLProc("glColor4ub");
        csc_glColor4ubv = (PFNGLCOLOR4UBVPROC)LoadOpenGLProc("glColor4ubv");
        csc_glColor4ui = (PFNGLCOLOR4UIPROC)LoadOpenGLProc("glColor4ui");
        csc_glColor4uiv = (PFNGLCOLOR4UIVPROC)LoadOpenGLProc("glColor4uiv");
        csc_glColor4us = (PFNGLCOLOR4USPROC)LoadOpenGLProc("glColor4us");
        csc_glColor4usv = (PFNGLCOLOR4USVPROC)LoadOpenGLProc("glColor4usv");
        csc_glEdgeFlag = (PFNGLEDGEFLAGPROC)LoadOpenGLProc("glEdgeFlag");
        csc_glEdgeFlagv = (PFNGLEDGEFLAGVPROC)LoadOpenGLProc("glEdgeFlagv");
        csc_glEnd = (PFNGLENDPROC)LoadOpenGLProc("glEnd");
        csc_glIndexd = (PFNGLINDEXDPROC)LoadOpenGLProc("glIndexd");
        csc_glIndexdv = (PFNGLINDEXDVPROC)LoadOpenGLProc("glIndexdv");
        csc_glIndexf = (PFNGLINDEXFPROC)LoadOpenGLProc("glIndexf");
        csc_glIndexfv = (PFNGLINDEXFVPROC)LoadOpenGLProc("glIndexfv");
        csc_glIndexi = (PFNGLINDEXIPROC)LoadOpenGLProc("glIndexi");
        csc_glIndexiv = (PFNGLINDEXIVPROC)LoadOpenGLProc("glIndexiv");
        csc_glIndexs = (PFNGLINDEXSPROC)LoadOpenGLProc("glIndexs");
        csc_glIndexsv = (PFNGLINDEXSVPROC)LoadOpenGLProc("glIndexsv");
        csc_glNormal3b = (PFNGLNORMAL3BPROC)LoadOpenGLProc("glNormal3b");
        csc_glNormal3bv = (PFNGLNORMAL3BVPROC)LoadOpenGLProc("glNormal3bv");
        csc_glNormal3d = (PFNGLNORMAL3DPROC)LoadOpenGLProc("glNormal3d");
        csc_glNormal3dv = (PFNGLNORMAL3DVPROC)LoadOpenGLProc("glNormal3dv");
        csc_glNormal3f = (PFNGLNORMAL3FPROC)LoadOpenGLProc("glNormal3f");
        csc_glNormal3fv = (PFNGLNORMAL3FVPROC)LoadOpenGLProc("glNormal3fv");
        csc_glNormal3i = (PFNGLNORMAL3IPROC)LoadOpenGLProc("glNormal3i");
        csc_glNormal3iv = (PFNGLNORMAL3IVPROC)LoadOpenGLProc("glNormal3iv");
        csc_glNormal3s = (PFNGLNORMAL3SPROC)LoadOpenGLProc("glNormal3s");
        csc_glNormal3sv = (PFNGLNORMAL3SVPROC)LoadOpenGLProc("glNormal3sv");
        csc_glRasterPos2d = (PFNGLRASTERPOS2DPROC)LoadOpenGLProc("glRasterPos2d");
        csc_glRasterPos2dv = (PFNGLRASTERPOS2DVPROC)LoadOpenGLProc("glRasterPos2dv");
        csc_glRasterPos2f = (PFNGLRASTERPOS2FPROC)LoadOpenGLProc("glRasterPos2f");
        csc_glRasterPos2fv = (PFNGLRASTERPOS2FVPROC)LoadOpenGLProc("glRasterPos2fv");
        csc_glRasterPos2i = (PFNGLRASTERPOS2IPROC)LoadOpenGLProc("glRasterPos2i");
        csc_glRasterPos2iv = (PFNGLRASTERPOS2IVPROC)LoadOpenGLProc("glRasterPos2iv");
        csc_glRasterPos2s = (PFNGLRASTERPOS2SPROC)LoadOpenGLProc("glRasterPos2s");
        csc_glRasterPos2sv = (PFNGLRASTERPOS2SVPROC)LoadOpenGLProc("glRasterPos2sv");
        csc_glRasterPos3d = (PFNGLRASTERPOS3DPROC)LoadOpenGLProc("glRasterPos3d");
        csc_glRasterPos3dv = (PFNGLRASTERPOS3DVPROC)LoadOpenGLProc("glRasterPos3dv");
        csc_glRasterPos3f = (PFNGLRASTERPOS3FPROC)LoadOpenGLProc("glRasterPos3f");
        csc_glRasterPos3fv = (PFNGLRASTERPOS3FVPROC)LoadOpenGLProc("glRasterPos3fv");
        csc_glRasterPos3i = (PFNGLRASTERPOS3IPROC)LoadOpenGLProc("glRasterPos3i");
        csc_glRasterPos3iv = (PFNGLRASTERPOS3IVPROC)LoadOpenGLProc("glRasterPos3iv");
        csc_glRasterPos3s = (PFNGLRASTERPOS3SPROC)LoadOpenGLProc("glRasterPos3s");
        csc_glRasterPos3sv = (PFNGLRASTERPOS3SVPROC)LoadOpenGLProc("glRasterPos3sv");
        csc_glRasterPos4d = (PFNGLRASTERPOS4DPROC)LoadOpenGLProc("glRasterPos4d");
        csc_glRasterPos4dv = (PFNGLRASTERPOS4DVPROC)LoadOpenGLProc("glRasterPos4dv");
        csc_glRasterPos4f = (PFNGLRASTERPOS4FPROC)LoadOpenGLProc("glRasterPos4f");
        csc_glRasterPos4fv = (PFNGLRASTERPOS4FVPROC)LoadOpenGLProc("glRasterPos4fv");
        csc_glRasterPos4i = (PFNGLRASTERPOS4IPROC)LoadOpenGLProc("glRasterPos4i");
        csc_glRasterPos4iv = (PFNGLRASTERPOS4IVPROC)LoadOpenGLProc("glRasterPos4iv");
        csc_glRasterPos4s = (PFNGLRASTERPOS4SPROC)LoadOpenGLProc("glRasterPos4s");
        csc_glRasterPos4sv = (PFNGLRASTERPOS4SVPROC)LoadOpenGLProc("glRasterPos4sv");
        csc_glRectd = (PFNGLRECTDPROC)LoadOpenGLProc("glRectd");
        csc_glRectdv = (PFNGLRECTDVPROC)LoadOpenGLProc("glRectdv");
        csc_glRectf = (PFNGLRECTFPROC)LoadOpenGLProc("glRectf");
        csc_glRectfv = (PFNGLRECTFVPROC)LoadOpenGLProc("glRectfv");
        csc_glRecti = (PFNGLRECTIPROC)LoadOpenGLProc("glRecti");
        csc_glRectiv = (PFNGLRECTIVPROC)LoadOpenGLProc("glRectiv");
        csc_glRects = (PFNGLRECTSPROC)LoadOpenGLProc("glRects");
        csc_glRectsv = (PFNGLRECTSVPROC)LoadOpenGLProc("glRectsv");
        csc_glTexCoord1d = (PFNGLTEXCOORD1DPROC)LoadOpenGLProc("glTexCoord1d");
        csc_glTexCoord1dv = (PFNGLTEXCOORD1DVPROC)LoadOpenGLProc("glTexCoord1dv");
        csc_glTexCoord1f = (PFNGLTEXCOORD1FPROC)LoadOpenGLProc("glTexCoord1f");
        csc_glTexCoord1fv = (PFNGLTEXCOORD1FVPROC)LoadOpenGLProc("glTexCoord1fv");
        csc_glTexCoord1i = (PFNGLTEXCOORD1IPROC)LoadOpenGLProc("glTexCoord1i");
        csc_glTexCoord1iv = (PFNGLTEXCOORD1IVPROC)LoadOpenGLProc("glTexCoord1iv");
        csc_glTexCoord1s = (PFNGLTEXCOORD1SPROC)LoadOpenGLProc("glTexCoord1s");
        csc_glTexCoord1sv = (PFNGLTEXCOORD1SVPROC)LoadOpenGLProc("glTexCoord1sv");
        csc_glTexCoord2d = (PFNGLTEXCOORD2DPROC)LoadOpenGLProc("glTexCoord2d");
        csc_glTexCoord2dv = (PFNGLTEXCOORD2DVPROC)LoadOpenGLProc("glTexCoord2dv");
        csc_glTexCoord2f = (PFNGLTEXCOORD2FPROC)LoadOpenGLProc("glTexCoord2f");
        csc_glTexCoord2fv = (PFNGLTEXCOORD2FVPROC)LoadOpenGLProc("glTexCoord2fv");
        csc_glTexCoord2i = (PFNGLTEXCOORD2IPROC)LoadOpenGLProc("glTexCoord2i");
        csc_glTexCoord2iv = (PFNGLTEXCOORD2IVPROC)LoadOpenGLProc("glTexCoord2iv");
        csc_glTexCoord2s = (PFNGLTEXCOORD2SPROC)LoadOpenGLProc("glTexCoord2s");
        csc_glTexCoord2sv = (PFNGLTEXCOORD2SVPROC)LoadOpenGLProc("glTexCoord2sv");
        csc_glTexCoord3d = (PFNGLTEXCOORD3DPROC)LoadOpenGLProc("glTexCoord3d");
        csc_glTexCoord3dv = (PFNGLTEXCOORD3DVPROC)LoadOpenGLProc("glTexCoord3dv");
        csc_glTexCoord3f = (PFNGLTEXCOORD3FPROC)LoadOpenGLProc("glTexCoord3f");
        csc_glTexCoord3fv = (PFNGLTEXCOORD3FVPROC)LoadOpenGLProc("glTexCoord3fv");
        csc_glTexCoord3i = (PFNGLTEXCOORD3IPROC)LoadOpenGLProc("glTexCoord3i");
        csc_glTexCoord3iv = (PFNGLTEXCOORD3IVPROC)LoadOpenGLProc("glTexCoord3iv");
        csc_glTexCoord3s = (PFNGLTEXCOORD3SPROC)LoadOpenGLProc("glTexCoord3s");
        csc_glTexCoord3sv = (PFNGLTEXCOORD3SVPROC)LoadOpenGLProc("glTexCoord3sv");
        csc_glTexCoord4d = (PFNGLTEXCOORD4DPROC)LoadOpenGLProc("glTexCoord4d");
        csc_glTexCoord4dv = (PFNGLTEXCOORD4DVPROC)LoadOpenGLProc("glTexCoord4dv");
        csc_glTexCoord4f = (PFNGLTEXCOORD4FPROC)LoadOpenGLProc("glTexCoord4f");
        csc_glTexCoord4fv = (PFNGLTEXCOORD4FVPROC)LoadOpenGLProc("glTexCoord4fv");
        csc_glTexCoord4i = (PFNGLTEXCOORD4IPROC)LoadOpenGLProc("glTexCoord4i");
        csc_glTexCoord4iv = (PFNGLTEXCOORD4IVPROC)LoadOpenGLProc("glTexCoord4iv");
        csc_glTexCoord4s = (PFNGLTEXCOORD4SPROC)LoadOpenGLProc("glTexCoord4s");
        csc_glTexCoord4sv = (PFNGLTEXCOORD4SVPROC)LoadOpenGLProc("glTexCoord4sv");
        csc_glVertex2d = (PFNGLVERTEX2DPROC)LoadOpenGLProc("glVertex2d");
        csc_glVertex2dv = (PFNGLVERTEX2DVPROC)LoadOpenGLProc("glVertex2dv");
        csc_glVertex2f = (PFNGLVERTEX2FPROC)LoadOpenGLProc("glVertex2f");
        csc_glVertex2fv = (PFNGLVERTEX2FVPROC)LoadOpenGLProc("glVertex2fv");
        csc_glVertex2i = (PFNGLVERTEX2IPROC)LoadOpenGLProc("glVertex2i");
        csc_glVertex2iv = (PFNGLVERTEX2IVPROC)LoadOpenGLProc("glVertex2iv");
        csc_glVertex2s = (PFNGLVERTEX2SPROC)LoadOpenGLProc("glVertex2s");
        csc_glVertex2sv = (PFNGLVERTEX2SVPROC)LoadOpenGLProc("glVertex2sv");
        csc_glVertex3d = (PFNGLVERTEX3DPROC)LoadOpenGLProc("glVertex3d");
        csc_glVertex3dv = (PFNGLVERTEX3DVPROC)LoadOpenGLProc("glVertex3dv");
        csc_glVertex3f = (PFNGLVERTEX3FPROC)LoadOpenGLProc("glVertex3f");
        csc_glVertex3fv = (PFNGLVERTEX3FVPROC)LoadOpenGLProc("glVertex3fv");
        csc_glVertex3i = (PFNGLVERTEX3IPROC)LoadOpenGLProc("glVertex3i");
        csc_glVertex3iv = (PFNGLVERTEX3IVPROC)LoadOpenGLProc("glVertex3iv");
        csc_glVertex3s = (PFNGLVERTEX3SPROC)LoadOpenGLProc("glVertex3s");
        csc_glVertex3sv = (PFNGLVERTEX3SVPROC)LoadOpenGLProc("glVertex3sv");
        csc_glVertex4d = (PFNGLVERTEX4DPROC)LoadOpenGLProc("glVertex4d");
        csc_glVertex4dv = (PFNGLVERTEX4DVPROC)LoadOpenGLProc("glVertex4dv");
        csc_glVertex4f = (PFNGLVERTEX4FPROC)LoadOpenGLProc("glVertex4f");
        csc_glVertex4fv = (PFNGLVERTEX4FVPROC)LoadOpenGLProc("glVertex4fv");
        csc_glVertex4i = (PFNGLVERTEX4IPROC)LoadOpenGLProc("glVertex4i");
        csc_glVertex4iv = (PFNGLVERTEX4IVPROC)LoadOpenGLProc("glVertex4iv");
        csc_glVertex4s = (PFNGLVERTEX4SPROC)LoadOpenGLProc("glVertex4s");
        csc_glVertex4sv = (PFNGLVERTEX4SVPROC)LoadOpenGLProc("glVertex4sv");
        csc_glClipPlane = (PFNGLCLIPPLANEPROC)LoadOpenGLProc("glClipPlane");
        csc_glColorMaterial = (PFNGLCOLORMATERIALPROC)LoadOpenGLProc("glColorMaterial");
        csc_glFogf = (PFNGLFOGFPROC)LoadOpenGLProc("glFogf");
        csc_glFogfv = (PFNGLFOGFVPROC)LoadOpenGLProc("glFogfv");
        csc_glFogi = (PFNGLFOGIPROC)LoadOpenGLProc("glFogi");
        csc_glFogiv = (PFNGLFOGIVPROC)LoadOpenGLProc("glFogiv");
        csc_glLightf = (PFNGLLIGHTFPROC)LoadOpenGLProc("glLightf");
        csc_glLightfv = (PFNGLLIGHTFVPROC)LoadOpenGLProc("glLightfv");
        csc_glLighti = (PFNGLLIGHTIPROC)LoadOpenGLProc("glLighti");
        csc_glLightiv = (PFNGLLIGHTIVPROC)LoadOpenGLProc("glLightiv");
        csc_glLightModelf = (PFNGLLIGHTMODELFPROC)LoadOpenGLProc("glLightModelf");
        csc_glLightModelfv = (PFNGLLIGHTMODELFVPROC)LoadOpenGLProc("glLightModelfv");
        csc_glLightModeli = (PFNGLLIGHTMODELIPROC)LoadOpenGLProc("glLightModeli");
        csc_glLightModeliv = (PFNGLLIGHTMODELIVPROC)LoadOpenGLProc("glLightModeliv");
        csc_glLineStipple = (PFNGLLINESTIPPLEPROC)LoadOpenGLProc("glLineStipple");
        csc_glMaterialf = (PFNGLMATERIALFPROC)LoadOpenGLProc("glMaterialf");
        csc_glMaterialfv = (PFNGLMATERIALFVPROC)LoadOpenGLProc("glMaterialfv");
        csc_glMateriali = (PFNGLMATERIALIPROC)LoadOpenGLProc("glMateriali");
        csc_glMaterialiv = (PFNGLMATERIALIVPROC)LoadOpenGLProc("glMaterialiv");
        csc_glPolygonStipple = (PFNGLPOLYGONSTIPPLEPROC)LoadOpenGLProc("glPolygonStipple");
        csc_glShadeModel = (PFNGLSHADEMODELPROC)LoadOpenGLProc("glShadeModel");
        csc_glTexEnvf = (PFNGLTEXENVFPROC)LoadOpenGLProc("glTexEnvf");
        csc_glTexEnvfv = (PFNGLTEXENVFVPROC)LoadOpenGLProc("glTexEnvfv");
        csc_glTexEnvi = (PFNGLTEXENVIPROC)LoadOpenGLProc("glTexEnvi");
        csc_glTexEnviv = (PFNGLTEXENVIVPROC)LoadOpenGLProc("glTexEnviv");
        csc_glTexGend = (PFNGLTEXGENDPROC)LoadOpenGLProc("glTexGend");
        csc_glTexGendv = (PFNGLTEXGENDVPROC)LoadOpenGLProc("glTexGendv");
        csc_glTexGenf = (PFNGLTEXGENFPROC)LoadOpenGLProc("glTexGenf");
        csc_glTexGenfv = (PFNGLTEXGENFVPROC)LoadOpenGLProc("glTexGenfv");
        csc_glTexGeni = (PFNGLTEXGENIPROC)LoadOpenGLProc("glTexGeni");
        csc_glTexGeniv = (PFNGLTEXGENIVPROC)LoadOpenGLProc("glTexGeniv");
        csc_glFeedbackBuffer = (PFNGLFEEDBACKBUFFERPROC)LoadOpenGLProc("glFeedbackBuffer");
        csc_glSelectBuffer = (PFNGLSELECTBUFFERPROC)LoadOpenGLProc("glSelectBuffer");
        csc_glRenderMode = (PFNGLRENDERMODEPROC)LoadOpenGLProc("glRenderMode");
        csc_glInitNames = (PFNGLINITNAMESPROC)LoadOpenGLProc("glInitNames");
        csc_glLoadName = (PFNGLLOADNAMEPROC)LoadOpenGLProc("glLoadOpenGLProcName");
        csc_glPassThrough = (PFNGLPASSTHROUGHPROC)LoadOpenGLProc("glPassThrough");
        csc_glPopName = (PFNGLPOPNAMEPROC)LoadOpenGLProc("glPopName");
        csc_glPushName = (PFNGLPUSHNAMEPROC)LoadOpenGLProc("glPushName");
        csc_glClearAccum = (PFNGLCLEARACCUMPROC)LoadOpenGLProc("glClearAccum");
        csc_glClearIndex = (PFNGLCLEARINDEXPROC)LoadOpenGLProc("glClearIndex");
        csc_glIndexMask = (PFNGLINDEXMASKPROC)LoadOpenGLProc("glIndexMask");
        csc_glAccum = (PFNGLACCUMPROC)LoadOpenGLProc("glAccum");
        csc_glPopAttrib = (PFNGLPOPATTRIBPROC)LoadOpenGLProc("glPopAttrib");
        csc_glPushAttrib = (PFNGLPUSHATTRIBPROC)LoadOpenGLProc("glPushAttrib");
        csc_glMap1d = (PFNGLMAP1DPROC)LoadOpenGLProc("glMap1d");
        csc_glMap1f = (PFNGLMAP1FPROC)LoadOpenGLProc("glMap1f");
        csc_glMap2d = (PFNGLMAP2DPROC)LoadOpenGLProc("glMap2d");
        csc_glMap2f = (PFNGLMAP2FPROC)LoadOpenGLProc("glMap2f");
        csc_glMapGrid1d = (PFNGLMAPGRID1DPROC)LoadOpenGLProc("glMapGrid1d");
        csc_glMapGrid1f = (PFNGLMAPGRID1FPROC)LoadOpenGLProc("glMapGrid1f");
        csc_glMapGrid2d = (PFNGLMAPGRID2DPROC)LoadOpenGLProc("glMapGrid2d");
        csc_glMapGrid2f = (PFNGLMAPGRID2FPROC)LoadOpenGLProc("glMapGrid2f");
        csc_glEvalCoord1d = (PFNGLEVALCOORD1DPROC)LoadOpenGLProc("glEvalCoord1d");
        csc_glEvalCoord1dv = (PFNGLEVALCOORD1DVPROC)LoadOpenGLProc("glEvalCoord1dv");
        csc_glEvalCoord1f = (PFNGLEVALCOORD1FPROC)LoadOpenGLProc("glEvalCoord1f");
        csc_glEvalCoord1fv = (PFNGLEVALCOORD1FVPROC)LoadOpenGLProc("glEvalCoord1fv");
        csc_glEvalCoord2d = (PFNGLEVALCOORD2DPROC)LoadOpenGLProc("glEvalCoord2d");
        csc_glEvalCoord2dv = (PFNGLEVALCOORD2DVPROC)LoadOpenGLProc("glEvalCoord2dv");
        csc_glEvalCoord2f = (PFNGLEVALCOORD2FPROC)LoadOpenGLProc("glEvalCoord2f");
        csc_glEvalCoord2fv = (PFNGLEVALCOORD2FVPROC)LoadOpenGLProc("glEvalCoord2fv");
        csc_glEvalMesh1 = (PFNGLEVALMESH1PROC)LoadOpenGLProc("glEvalMesh1");
        csc_glEvalPoint1 = (PFNGLEVALPOINT1PROC)LoadOpenGLProc("glEvalPoint1");
        csc_glEvalMesh2 = (PFNGLEVALMESH2PROC)LoadOpenGLProc("glEvalMesh2");
        csc_glEvalPoint2 = (PFNGLEVALPOINT2PROC)LoadOpenGLProc("glEvalPoint2");
        csc_glAlphaFunc = (PFNGLALPHAFUNCPROC)LoadOpenGLProc("glAlphaFunc");
        csc_glPixelZoom = (PFNGLPIXELZOOMPROC)LoadOpenGLProc("glPixelZoom");
        csc_glPixelTransferf = (PFNGLPIXELTRANSFERFPROC)LoadOpenGLProc("glPixelTransferf");
        csc_glPixelTransferi = (PFNGLPIXELTRANSFERIPROC)LoadOpenGLProc("glPixelTransferi");
        csc_glPixelMapfv = (PFNGLPIXELMAPFVPROC)LoadOpenGLProc("glPixelMapfv");
        csc_glPixelMapuiv = (PFNGLPIXELMAPUIVPROC)LoadOpenGLProc("glPixelMapuiv");
        csc_glPixelMapusv = (PFNGLPIXELMAPUSVPROC)LoadOpenGLProc("glPixelMapusv");
        csc_glCopyPixels = (PFNGLCOPYPIXELSPROC)LoadOpenGLProc("glCopyPixels");
        csc_glDrawPixels = (PFNGLDRAWPIXELSPROC)LoadOpenGLProc("glDrawPixels");
        csc_glGetClipPlane = (PFNGLGETCLIPPLANEPROC)LoadOpenGLProc("glGetClipPlane");
        csc_glGetLightfv = (PFNGLGETLIGHTFVPROC)LoadOpenGLProc("glGetLightfv");
        csc_glGetLightiv = (PFNGLGETLIGHTIVPROC)LoadOpenGLProc("glGetLightiv");
        csc_glGetMapdv = (PFNGLGETMAPDVPROC)LoadOpenGLProc("glGetMapdv");
        csc_glGetMapfv = (PFNGLGETMAPFVPROC)LoadOpenGLProc("glGetMapfv");
        csc_glGetMapiv = (PFNGLGETMAPIVPROC)LoadOpenGLProc("glGetMapiv");
        csc_glGetMaterialfv = (PFNGLGETMATERIALFVPROC)LoadOpenGLProc("glGetMaterialfv");
        csc_glGetMaterialiv = (PFNGLGETMATERIALIVPROC)LoadOpenGLProc("glGetMaterialiv");
        csc_glGetPixelMapfv = (PFNGLGETPIXELMAPFVPROC)LoadOpenGLProc("glGetPixelMapfv");
        csc_glGetPixelMapuiv = (PFNGLGETPIXELMAPUIVPROC)LoadOpenGLProc("glGetPixelMapuiv");
        csc_glGetPixelMapusv = (PFNGLGETPIXELMAPUSVPROC)LoadOpenGLProc("glGetPixelMapusv");
        csc_glGetPolygonStipple = (PFNGLGETPOLYGONSTIPPLEPROC)LoadOpenGLProc("glGetPolygonStipple");
        csc_glGetTexEnvfv = (PFNGLGETTEXENVFVPROC)LoadOpenGLProc("glGetTexEnvfv");
        csc_glGetTexEnviv = (PFNGLGETTEXENVIVPROC)LoadOpenGLProc("glGetTexEnviv");
        csc_glGetTexGendv = (PFNGLGETTEXGENDVPROC)LoadOpenGLProc("glGetTexGendv");
        csc_glGetTexGenfv = (PFNGLGETTEXGENFVPROC)LoadOpenGLProc("glGetTexGenfv");
        csc_glGetTexGeniv = (PFNGLGETTEXGENIVPROC)LoadOpenGLProc("glGetTexGeniv");
        csc_glIsList = (PFNGLISLISTPROC)LoadOpenGLProc("glIsList");
        csc_glFrustum = (PFNGLFRUSTUMPROC)LoadOpenGLProc("glFrustum");
        csc_glLoadIdentity = (PFNGLLOADIDENTITYPROC)LoadOpenGLProc("glLoadOpenGLProcIdentity");
        csc_glLoadMatrixf = (PFNGLLOADMATRIXFPROC)LoadOpenGLProc("glLoadOpenGLProcMatrixf");
        csc_glLoadMatrixd = (PFNGLLOADMATRIXDPROC)LoadOpenGLProc("glLoadOpenGLProcMatrixd");
        csc_glMatrixMode = (PFNGLMATRIXMODEPROC)LoadOpenGLProc("glMatrixMode");
        csc_glMultMatrixf = (PFNGLMULTMATRIXFPROC)LoadOpenGLProc("glMultMatrixf");
        csc_glMultMatrixd = (PFNGLMULTMATRIXDPROC)LoadOpenGLProc("glMultMatrixd");
        csc_glOrtho = (PFNGLORTHOPROC)LoadOpenGLProc("glOrtho");
        csc_glPopMatrix = (PFNGLPOPMATRIXPROC)LoadOpenGLProc("glPopMatrix");
        csc_glPushMatrix = (PFNGLPUSHMATRIXPROC)LoadOpenGLProc("glPushMatrix");
        csc_glRotated = (PFNGLROTATEDPROC)LoadOpenGLProc("glRotated");
        csc_glRotatef = (PFNGLROTATEFPROC)LoadOpenGLProc("glRotatef");
        csc_glScaled = (PFNGLSCALEDPROC)LoadOpenGLProc("glScaled");
        csc_glScalef = (PFNGLSCALEFPROC)LoadOpenGLProc("glScalef");
        csc_glTranslated = (PFNGLTRANSLATEDPROC)LoadOpenGLProc("glTranslated");
        csc_glTranslatef = (PFNGLTRANSLATEFPROC)LoadOpenGLProc("glTranslatef");
    }
}

internal void
Load_GL_VERSION_1_1(CSCLoadProc LoadOpenGLProc)
{
    if(CSC_GL_VERSION_1_1)
    {
        csc_glDrawArrays = (PFNGLDRAWARRAYSPROC)LoadOpenGLProc("glDrawArrays");
        csc_glDrawElements = (PFNGLDRAWELEMENTSPROC)LoadOpenGLProc("glDrawElements");
        csc_glGetPointerv = (PFNGLGETPOINTERVPROC)LoadOpenGLProc("glGetPointerv");
        csc_glPolygonOffset = (PFNGLPOLYGONOFFSETPROC)LoadOpenGLProc("glPolygonOffset");
        csc_glCopyTexImage1D = (PFNGLCOPYTEXIMAGE1DPROC)LoadOpenGLProc("glCopyTexImage1D");
        csc_glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC)LoadOpenGLProc("glCopyTexImage2D");
        csc_glCopyTexSubImage1D = (PFNGLCOPYTEXSUBIMAGE1DPROC)LoadOpenGLProc("glCopyTexSubImage1D");
        csc_glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC)LoadOpenGLProc("glCopyTexSubImage2D");
        csc_glTexSubImage1D = (PFNGLTEXSUBIMAGE1DPROC)LoadOpenGLProc("glTexSubImage1D");
        csc_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC)LoadOpenGLProc("glTexSubImage2D");
        csc_glBindTexture = (PFNGLBINDTEXTUREPROC)LoadOpenGLProc("glBindTexture");
        csc_glDeleteTextures = (PFNGLDELETETEXTURESPROC)LoadOpenGLProc("glDeleteTextures");
        csc_glGenTextures = (PFNGLGENTEXTURESPROC)LoadOpenGLProc("glGenTextures");
        csc_glIsTexture = (PFNGLISTEXTUREPROC)LoadOpenGLProc("glIsTexture");
        csc_glArrayElement = (PFNGLARRAYELEMENTPROC)LoadOpenGLProc("glArrayElement");
        csc_glColorPointer = (PFNGLCOLORPOINTERPROC)LoadOpenGLProc("glColorPointer");
        csc_glDisableClientState = (PFNGLDISABLECLIENTSTATEPROC)LoadOpenGLProc("glDisableClientState");
        csc_glEdgeFlagPointer = (PFNGLEDGEFLAGPOINTERPROC)LoadOpenGLProc("glEdgeFlagPointer");
        csc_glEnableClientState = (PFNGLENABLECLIENTSTATEPROC)LoadOpenGLProc("glEnableClientState");
        csc_glIndexPointer = (PFNGLINDEXPOINTERPROC)LoadOpenGLProc("glIndexPointer");
        csc_glInterleavedArrays = (PFNGLINTERLEAVEDARRAYSPROC)LoadOpenGLProc("glInterleavedArrays");
        csc_glNormalPointer = (PFNGLNORMALPOINTERPROC)LoadOpenGLProc("glNormalPointer");
        csc_glTexCoordPointer = (PFNGLTEXCOORDPOINTERPROC)LoadOpenGLProc("glTexCoordPointer");
        csc_glVertexPointer = (PFNGLVERTEXPOINTERPROC)LoadOpenGLProc("glVertexPointer");
        csc_glAreTexturesResident = (PFNGLARETEXTURESRESIDENTPROC)LoadOpenGLProc("glAreTexturesResident");
        csc_glPrioritizeTextures = (PFNGLPRIORITIZETEXTURESPROC)LoadOpenGLProc("glPrioritizeTextures");
        csc_glIndexub = (PFNGLINDEXUBPROC)LoadOpenGLProc("glIndexub");
        csc_glIndexubv = (PFNGLINDEXUBVPROC)LoadOpenGLProc("glIndexubv");
        csc_glPopClientAttrib = (PFNGLPOPCLIENTATTRIBPROC)LoadOpenGLProc("glPopClientAttrib");
        csc_glPushClientAttrib = (PFNGLPUSHCLIENTATTRIBPROC)LoadOpenGLProc("glPushClientAttrib");
    }
}

internal void
Load_GL_VERSION_1_2(CSCLoadProc LoadOpenGLProc)
{
    if(CSC_GL_VERSION_1_2)
    {
        csc_glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)LoadOpenGLProc("glDrawRangeElements");
        csc_glTexImage3D = (PFNGLTEXIMAGE3DPROC)LoadOpenGLProc("glTexImage3D");
        csc_glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)LoadOpenGLProc("glTexSubImage3D");
        csc_glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)LoadOpenGLProc("glCopyTexSubImage3D");
    }
}

internal void
Load_GL_VERSION_1_3(CSCLoadProc LoadOpenGLProc)
{
    if(CSC_GL_VERSION_1_3)
    {
        csc_glActiveTexture = (PFNGLACTIVETEXTUREPROC)LoadOpenGLProc("glActiveTexture");
        csc_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)LoadOpenGLProc("glSampleCoverage");
        csc_glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)LoadOpenGLProc("glCompressedTexImage3D");
        csc_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)LoadOpenGLProc("glCompressedTexImage2D");
        csc_glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)LoadOpenGLProc("glCompressedTexImage1D");
        csc_glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)LoadOpenGLProc("glCompressedTexSubImage3D");
        csc_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)LoadOpenGLProc("glCompressedTexSubImage2D");
        csc_glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)LoadOpenGLProc("glCompressedTexSubImage1D");
        csc_glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)LoadOpenGLProc("glGetCompressedTexImage");
        csc_glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC)LoadOpenGLProc("glClientActiveTexture");
        csc_glMultiTexCoord1d = (PFNGLMULTITEXCOORD1DPROC)LoadOpenGLProc("glMultiTexCoord1d");
        csc_glMultiTexCoord1dv = (PFNGLMULTITEXCOORD1DVPROC)LoadOpenGLProc("glMultiTexCoord1dv");
        csc_glMultiTexCoord1f = (PFNGLMULTITEXCOORD1FPROC)LoadOpenGLProc("glMultiTexCoord1f");
        csc_glMultiTexCoord1fv = (PFNGLMULTITEXCOORD1FVPROC)LoadOpenGLProc("glMultiTexCoord1fv");
        csc_glMultiTexCoord1i = (PFNGLMULTITEXCOORD1IPROC)LoadOpenGLProc("glMultiTexCoord1i");
        csc_glMultiTexCoord1iv = (PFNGLMULTITEXCOORD1IVPROC)LoadOpenGLProc("glMultiTexCoord1iv");
        csc_glMultiTexCoord1s = (PFNGLMULTITEXCOORD1SPROC)LoadOpenGLProc("glMultiTexCoord1s");
        csc_glMultiTexCoord1sv = (PFNGLMULTITEXCOORD1SVPROC)LoadOpenGLProc("glMultiTexCoord1sv");
        csc_glMultiTexCoord2d = (PFNGLMULTITEXCOORD2DPROC)LoadOpenGLProc("glMultiTexCoord2d");
        csc_glMultiTexCoord2dv = (PFNGLMULTITEXCOORD2DVPROC)LoadOpenGLProc("glMultiTexCoord2dv");
        csc_glMultiTexCoord2f = (PFNGLMULTITEXCOORD2FPROC)LoadOpenGLProc("glMultiTexCoord2f");
        csc_glMultiTexCoord2fv = (PFNGLMULTITEXCOORD2FVPROC)LoadOpenGLProc("glMultiTexCoord2fv");
        csc_glMultiTexCoord2i = (PFNGLMULTITEXCOORD2IPROC)LoadOpenGLProc("glMultiTexCoord2i");
        csc_glMultiTexCoord2iv = (PFNGLMULTITEXCOORD2IVPROC)LoadOpenGLProc("glMultiTexCoord2iv");
        csc_glMultiTexCoord2s = (PFNGLMULTITEXCOORD2SPROC)LoadOpenGLProc("glMultiTexCoord2s");
        csc_glMultiTexCoord2sv = (PFNGLMULTITEXCOORD2SVPROC)LoadOpenGLProc("glMultiTexCoord2sv");
        csc_glMultiTexCoord3d = (PFNGLMULTITEXCOORD3DPROC)LoadOpenGLProc("glMultiTexCoord3d");
        csc_glMultiTexCoord3dv = (PFNGLMULTITEXCOORD3DVPROC)LoadOpenGLProc("glMultiTexCoord3dv");
        csc_glMultiTexCoord3f = (PFNGLMULTITEXCOORD3FPROC)LoadOpenGLProc("glMultiTexCoord3f");
        csc_glMultiTexCoord3fv = (PFNGLMULTITEXCOORD3FVPROC)LoadOpenGLProc("glMultiTexCoord3fv");
        csc_glMultiTexCoord3i = (PFNGLMULTITEXCOORD3IPROC)LoadOpenGLProc("glMultiTexCoord3i");
        csc_glMultiTexCoord3iv = (PFNGLMULTITEXCOORD3IVPROC)LoadOpenGLProc("glMultiTexCoord3iv");
        csc_glMultiTexCoord3s = (PFNGLMULTITEXCOORD3SPROC)LoadOpenGLProc("glMultiTexCoord3s");
        csc_glMultiTexCoord3sv = (PFNGLMULTITEXCOORD3SVPROC)LoadOpenGLProc("glMultiTexCoord3sv");
        csc_glMultiTexCoord4d = (PFNGLMULTITEXCOORD4DPROC)LoadOpenGLProc("glMultiTexCoord4d");
        csc_glMultiTexCoord4dv = (PFNGLMULTITEXCOORD4DVPROC)LoadOpenGLProc("glMultiTexCoord4dv");
        csc_glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC)LoadOpenGLProc("glMultiTexCoord4f");
        csc_glMultiTexCoord4fv = (PFNGLMULTITEXCOORD4FVPROC)LoadOpenGLProc("glMultiTexCoord4fv");
        csc_glMultiTexCoord4i = (PFNGLMULTITEXCOORD4IPROC)LoadOpenGLProc("glMultiTexCoord4i");
        csc_glMultiTexCoord4iv = (PFNGLMULTITEXCOORD4IVPROC)LoadOpenGLProc("glMultiTexCoord4iv");
        csc_glMultiTexCoord4s = (PFNGLMULTITEXCOORD4SPROC)LoadOpenGLProc("glMultiTexCoord4s");
        csc_glMultiTexCoord4sv = (PFNGLMULTITEXCOORD4SVPROC)LoadOpenGLProc("glMultiTexCoord4sv");
        csc_glLoadTransposeMatrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC)LoadOpenGLProc("glLoadTransposeMatrixf");
        csc_glLoadTransposeMatrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC)LoadOpenGLProc("glLoadTransposeMatrixd");
        csc_glMultTransposeMatrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC)LoadOpenGLProc("glMultTransposeMatrixf");
        csc_glMultTransposeMatrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC)LoadOpenGLProc("glMultTransposeMatrixd");
    }
}

internal void
Load_GL_VERSION_1_4(CSCLoadProc LoadOpenGLProc)
{
    if(CSC_GL_VERSION_1_4)
    {
        csc_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)LoadOpenGLProc("glBlendFuncSeparate");
        csc_glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)LoadOpenGLProc("glMultiDrawArrays");
        csc_glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)LoadOpenGLProc("glMultiDrawElements");
        csc_glPointParameterf = (PFNGLPOINTPARAMETERFPROC)LoadOpenGLProc("glPointParameterf");
        csc_glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)LoadOpenGLProc("glPointParameterfv");
        csc_glPointParameteri = (PFNGLPOINTPARAMETERIPROC)LoadOpenGLProc("glPointParameteri");
        csc_glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)LoadOpenGLProc("glPointParameteriv");
        csc_glFogCoordf = (PFNGLFOGCOORDFPROC)LoadOpenGLProc("glFogCoordf");
        csc_glFogCoordfv = (PFNGLFOGCOORDFVPROC)LoadOpenGLProc("glFogCoordfv");
        csc_glFogCoordd = (PFNGLFOGCOORDDPROC)LoadOpenGLProc("glFogCoordd");
        csc_glFogCoorddv = (PFNGLFOGCOORDDVPROC)LoadOpenGLProc("glFogCoorddv");
        csc_glFogCoordPointer = (PFNGLFOGCOORDPOINTERPROC)LoadOpenGLProc("glFogCoordPointer");
        csc_glSecondaryColor3b = (PFNGLSECONDARYCOLOR3BPROC)LoadOpenGLProc("glSecondaryColor3b");
        csc_glSecondaryColor3bv = (PFNGLSECONDARYCOLOR3BVPROC)LoadOpenGLProc("glSecondaryColor3bv");
        csc_glSecondaryColor3d = (PFNGLSECONDARYCOLOR3DPROC)LoadOpenGLProc("glSecondaryColor3d");
        csc_glSecondaryColor3dv = (PFNGLSECONDARYCOLOR3DVPROC)LoadOpenGLProc("glSecondaryColor3dv");
        csc_glSecondaryColor3f = (PFNGLSECONDARYCOLOR3FPROC)LoadOpenGLProc("glSecondaryColor3f");
        csc_glSecondaryColor3fv = (PFNGLSECONDARYCOLOR3FVPROC)LoadOpenGLProc("glSecondaryColor3fv");
        csc_glSecondaryColor3i = (PFNGLSECONDARYCOLOR3IPROC)LoadOpenGLProc("glSecondaryColor3i");
        csc_glSecondaryColor3iv = (PFNGLSECONDARYCOLOR3IVPROC)LoadOpenGLProc("glSecondaryColor3iv");
        csc_glSecondaryColor3s = (PFNGLSECONDARYCOLOR3SPROC)LoadOpenGLProc("glSecondaryColor3s");
        csc_glSecondaryColor3sv = (PFNGLSECONDARYCOLOR3SVPROC)LoadOpenGLProc("glSecondaryColor3sv");
        csc_glSecondaryColor3ub = (PFNGLSECONDARYCOLOR3UBPROC)LoadOpenGLProc("glSecondaryColor3ub");
        csc_glSecondaryColor3ubv = (PFNGLSECONDARYCOLOR3UBVPROC)LoadOpenGLProc("glSecondaryColor3ubv");
        csc_glSecondaryColor3ui = (PFNGLSECONDARYCOLOR3UIPROC)LoadOpenGLProc("glSecondaryColor3ui");
        csc_glSecondaryColor3uiv = (PFNGLSECONDARYCOLOR3UIVPROC)LoadOpenGLProc("glSecondaryColor3uiv");
        csc_glSecondaryColor3us = (PFNGLSECONDARYCOLOR3USPROC)LoadOpenGLProc("glSecondaryColor3us");
        csc_glSecondaryColor3usv = (PFNGLSECONDARYCOLOR3USVPROC)LoadOpenGLProc("glSecondaryColor3usv");
        csc_glSecondaryColorPointer = (PFNGLSECONDARYCOLORPOINTERPROC)LoadOpenGLProc("glSecondaryColorPointer");
        csc_glWindowPos2d = (PFNGLWINDOWPOS2DPROC)LoadOpenGLProc("glWindowPos2d");
        csc_glWindowPos2dv = (PFNGLWINDOWPOS2DVPROC)LoadOpenGLProc("glWindowPos2dv");
        csc_glWindowPos2f = (PFNGLWINDOWPOS2FPROC)LoadOpenGLProc("glWindowPos2f");
        csc_glWindowPos2fv = (PFNGLWINDOWPOS2FVPROC)LoadOpenGLProc("glWindowPos2fv");
        csc_glWindowPos2i = (PFNGLWINDOWPOS2IPROC)LoadOpenGLProc("glWindowPos2i");
        csc_glWindowPos2iv = (PFNGLWINDOWPOS2IVPROC)LoadOpenGLProc("glWindowPos2iv");
        csc_glWindowPos2s = (PFNGLWINDOWPOS2SPROC)LoadOpenGLProc("glWindowPos2s");
        csc_glWindowPos2sv = (PFNGLWINDOWPOS2SVPROC)LoadOpenGLProc("glWindowPos2sv");
        csc_glWindowPos3d = (PFNGLWINDOWPOS3DPROC)LoadOpenGLProc("glWindowPos3d");
        csc_glWindowPos3dv = (PFNGLWINDOWPOS3DVPROC)LoadOpenGLProc("glWindowPos3dv");
        csc_glWindowPos3f = (PFNGLWINDOWPOS3FPROC)LoadOpenGLProc("glWindowPos3f");
        csc_glWindowPos3fv = (PFNGLWINDOWPOS3FVPROC)LoadOpenGLProc("glWindowPos3fv");
        csc_glWindowPos3i = (PFNGLWINDOWPOS3IPROC)LoadOpenGLProc("glWindowPos3i");
        csc_glWindowPos3iv = (PFNGLWINDOWPOS3IVPROC)LoadOpenGLProc("glWindowPos3iv");
        csc_glWindowPos3s = (PFNGLWINDOWPOS3SPROC)LoadOpenGLProc("glWindowPos3s");
        csc_glWindowPos3sv = (PFNGLWINDOWPOS3SVPROC)LoadOpenGLProc("glWindowPos3sv");
        csc_glBlendColor = (PFNGLBLENDCOLORPROC)LoadOpenGLProc("glBlendColor");
        csc_glBlendEquation = (PFNGLBLENDEQUATIONPROC)LoadOpenGLProc("glBlendEquation");
    }
}

internal void
Load_GL_VERSION_1_5(CSCLoadProc LoadOpenGLProc)
{
    if(CSC_GL_VERSION_1_5)
    {
        csc_glGenQueries = (PFNGLGENQUERIESPROC)LoadOpenGLProc("glGenQueries");
        csc_glDeleteQueries = (PFNGLDELETEQUERIESPROC)LoadOpenGLProc("glDeleteQueries");
        csc_glIsQuery = (PFNGLISQUERYPROC)LoadOpenGLProc("glIsQuery");
        csc_glBeginQuery = (PFNGLBEGINQUERYPROC)LoadOpenGLProc("glBeginQuery");
        csc_glEndQuery = (PFNGLENDQUERYPROC)LoadOpenGLProc("glEndQuery");
        csc_glGetQueryiv = (PFNGLGETQUERYIVPROC)LoadOpenGLProc("glGetQueryiv");
        csc_glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)LoadOpenGLProc("glGetQueryObjectiv");
        csc_glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)LoadOpenGLProc("glGetQueryObjectuiv");
        csc_glBindBuffer = (PFNGLBINDBUFFERPROC)LoadOpenGLProc("glBindBuffer");
        csc_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)LoadOpenGLProc("glDeleteBuffers");
        csc_glGenBuffers = (PFNGLGENBUFFERSPROC)LoadOpenGLProc("glGenBuffers");
        csc_glIsBuffer = (PFNGLISBUFFERPROC)LoadOpenGLProc("glIsBuffer");
        csc_glBufferData = (PFNGLBUFFERDATAPROC)LoadOpenGLProc("glBufferData");
        csc_glBufferSubData = (PFNGLBUFFERSUBDATAPROC)LoadOpenGLProc("glBufferSubData");
        csc_glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)LoadOpenGLProc("glGetBufferSubData");
        csc_glMapBuffer = (PFNGLMAPBUFFERPROC)LoadOpenGLProc("glMapBuffer");
        csc_glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)LoadOpenGLProc("glUnmapBuffer");
        csc_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)LoadOpenGLProc("glGetBufferParameteriv");
        csc_glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)LoadOpenGLProc("glGetBufferPointerv");
    }
}

internal void
Load_GL_VERSION_2_0(CSCLoadProc LoadOpenGLProc)
{
    if(CSC_GL_VERSION_2_0)
    {
        csc_glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)LoadOpenGLProc("glBlendEquationSeparate");
        csc_glDrawBuffers = (PFNGLDRAWBUFFERSPROC)LoadOpenGLProc("glDrawBuffers");
        csc_glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)LoadOpenGLProc("glStencilOpSeparate");
        csc_glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)LoadOpenGLProc("glStencilFuncSeparate");
        csc_glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)LoadOpenGLProc("glStencilMaskSeparate");
        csc_glAttachShader = (PFNGLATTACHSHADERPROC)LoadOpenGLProc("glAttachShader");
        csc_glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)LoadOpenGLProc("glBindAttribLocation");
        csc_glCompileShader = (PFNGLCOMPILESHADERPROC)LoadOpenGLProc("glCompileShader");
        csc_glCreateProgram = (PFNGLCREATEPROGRAMPROC)LoadOpenGLProc("glCreateProgram");
        csc_glCreateShader = (PFNGLCREATESHADERPROC)LoadOpenGLProc("glCreateShader");
        csc_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)LoadOpenGLProc("glDeleteProgram");
        csc_glDeleteShader = (PFNGLDELETESHADERPROC)LoadOpenGLProc("glDeleteShader");
        csc_glDetachShader = (PFNGLDETACHSHADERPROC)LoadOpenGLProc("glDetachShader");
        csc_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)LoadOpenGLProc("glDisableVertexAttribArray");
        csc_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)LoadOpenGLProc("glEnableVertexAttribArray");
        csc_glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)LoadOpenGLProc("glGetActiveAttrib");
        csc_glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)LoadOpenGLProc("glGetActiveUniform");
        csc_glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)LoadOpenGLProc("glGetAttachedShaders");
        csc_glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)LoadOpenGLProc("glGetAttribLocation");
        csc_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)LoadOpenGLProc("glGetProgramiv");
        csc_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)LoadOpenGLProc("glGetProgramInfoLog");
        csc_glGetShaderiv = (PFNGLGETSHADERIVPROC)LoadOpenGLProc("glGetShaderiv");
        csc_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)LoadOpenGLProc("glGetShaderInfoLog");
        csc_glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)LoadOpenGLProc("glGetShaderSource");
        csc_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)LoadOpenGLProc("glGetUniformLocation");
        csc_glGetUniformfv = (PFNGLGETUNIFORMFVPROC)LoadOpenGLProc("glGetUniformfv");
        csc_glGetUniformiv = (PFNGLGETUNIFORMIVPROC)LoadOpenGLProc("glGetUniformiv");
        csc_glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)LoadOpenGLProc("glGetVertexAttribdv");
        csc_glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)LoadOpenGLProc("glGetVertexAttribfv");
        csc_glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)LoadOpenGLProc("glGetVertexAttribiv");
        csc_glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)LoadOpenGLProc("glGetVertexAttribPointerv");
        csc_glIsProgram = (PFNGLISPROGRAMPROC)LoadOpenGLProc("glIsProgram");
        csc_glIsShader = (PFNGLISSHADERPROC)LoadOpenGLProc("glIsShader");
        csc_glLinkProgram = (PFNGLLINKPROGRAMPROC)LoadOpenGLProc("glLinkProgram");
        csc_glShaderSource = (PFNGLSHADERSOURCEPROC)LoadOpenGLProc("glShaderSource");
        csc_glUseProgram = (PFNGLUSEPROGRAMPROC)LoadOpenGLProc("glUseProgram");
        csc_glUniform1f = (PFNGLUNIFORM1FPROC)LoadOpenGLProc("glUniform1f");
        csc_glUniform2f = (PFNGLUNIFORM2FPROC)LoadOpenGLProc("glUniform2f");
        csc_glUniform3f = (PFNGLUNIFORM3FPROC)LoadOpenGLProc("glUniform3f");
        csc_glUniform4f = (PFNGLUNIFORM4FPROC)LoadOpenGLProc("glUniform4f");
        csc_glUniform1i = (PFNGLUNIFORM1IPROC)LoadOpenGLProc("glUniform1i");
        csc_glUniform2i = (PFNGLUNIFORM2IPROC)LoadOpenGLProc("glUniform2i");
        csc_glUniform3i = (PFNGLUNIFORM3IPROC)LoadOpenGLProc("glUniform3i");
        csc_glUniform4i = (PFNGLUNIFORM4IPROC)LoadOpenGLProc("glUniform4i");
        csc_glUniform1fv = (PFNGLUNIFORM1FVPROC)LoadOpenGLProc("glUniform1fv");
        csc_glUniform2fv = (PFNGLUNIFORM2FVPROC)LoadOpenGLProc("glUniform2fv");
        csc_glUniform3fv = (PFNGLUNIFORM3FVPROC)LoadOpenGLProc("glUniform3fv");
        csc_glUniform4fv = (PFNGLUNIFORM4FVPROC)LoadOpenGLProc("glUniform4fv");
        csc_glUniform1iv = (PFNGLUNIFORM1IVPROC)LoadOpenGLProc("glUniform1iv");
        csc_glUniform2iv = (PFNGLUNIFORM2IVPROC)LoadOpenGLProc("glUniform2iv");
        csc_glUniform3iv = (PFNGLUNIFORM3IVPROC)LoadOpenGLProc("glUniform3iv");
        csc_glUniform4iv = (PFNGLUNIFORM4IVPROC)LoadOpenGLProc("glUniform4iv");
        csc_glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)LoadOpenGLProc("glUniformMatrix2fv");
        csc_glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)LoadOpenGLProc("glUniformMatrix3fv");
        csc_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)LoadOpenGLProc("glUniformMatrix4fv");
        csc_glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)LoadOpenGLProc("glValidateProgram");
        csc_glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)LoadOpenGLProc("glVertexAttrib1d");
        csc_glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)LoadOpenGLProc("glVertexAttrib1dv");
        csc_glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)LoadOpenGLProc("glVertexAttrib1f");
        csc_glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)LoadOpenGLProc("glVertexAttrib1fv");
        csc_glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)LoadOpenGLProc("glVertexAttrib1s");
        csc_glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)LoadOpenGLProc("glVertexAttrib1sv");
        csc_glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)LoadOpenGLProc("glVertexAttrib2d");
        csc_glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)LoadOpenGLProc("glVertexAttrib2dv");
        csc_glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)LoadOpenGLProc("glVertexAttrib2f");
        csc_glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)LoadOpenGLProc("glVertexAttrib2fv");
        csc_glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)LoadOpenGLProc("glVertexAttrib2s");
        csc_glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)LoadOpenGLProc("glVertexAttrib2sv");
        csc_glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)LoadOpenGLProc("glVertexAttrib3d");
        csc_glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)LoadOpenGLProc("glVertexAttrib3dv");
        csc_glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)LoadOpenGLProc("glVertexAttrib3f");
        csc_glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)LoadOpenGLProc("glVertexAttrib3fv");
        csc_glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)LoadOpenGLProc("glVertexAttrib3s");
        csc_glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)LoadOpenGLProc("glVertexAttrib3sv");
        csc_glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)LoadOpenGLProc("glVertexAttrib4Nbv");
        csc_glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)LoadOpenGLProc("glVertexAttrib4Niv");
        csc_glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)LoadOpenGLProc("glVertexAttrib4Nsv");
        csc_glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)LoadOpenGLProc("glVertexAttrib4Nub");
        csc_glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)LoadOpenGLProc("glVertexAttrib4Nubv");
        csc_glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)LoadOpenGLProc("glVertexAttrib4Nuiv");
        csc_glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)LoadOpenGLProc("glVertexAttrib4Nusv");
        csc_glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)LoadOpenGLProc("glVertexAttrib4bv");
        csc_glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)LoadOpenGLProc("glVertexAttrib4d");
        csc_glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)LoadOpenGLProc("glVertexAttrib4dv");
        csc_glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)LoadOpenGLProc("glVertexAttrib4f");
        csc_glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)LoadOpenGLProc("glVertexAttrib4fv");
        csc_glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)LoadOpenGLProc("glVertexAttrib4iv");
        csc_glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)LoadOpenGLProc("glVertexAttrib4s");
        csc_glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)LoadOpenGLProc("glVertexAttrib4sv");
        csc_glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)LoadOpenGLProc("glVertexAttrib4ubv");
        csc_glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)LoadOpenGLProc("glVertexAttrib4uiv");
        csc_glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)LoadOpenGLProc("glVertexAttrib4usv");
        csc_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)LoadOpenGLProc("glVertexAttribPointer");
    }
}

internal void
Load_GL_VERSION_2_1(CSCLoadProc LoadOpenGLProc)
{
    if(CSC_GL_VERSION_2_1)
    {
        csc_glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)LoadOpenGLProc("glUniformMatrix2x3fv");
        csc_glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)LoadOpenGLProc("glUniformMatrix3x2fv");
        csc_glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)LoadOpenGLProc("glUniformMatrix2x4fv");
        csc_glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)LoadOpenGLProc("glUniformMatrix4x2fv");
        csc_glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)LoadOpenGLProc("glUniformMatrix3x4fv");
        csc_glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)LoadOpenGLProc("glUniformMatrix4x3fv");
    }
}

internal void
Load_GL_VERSION_3_0(CSCLoadProc LoadOpenGLProc)
{
    if(CSC_GL_VERSION_3_0)
    {
        csc_glColorMaski = (PFNGLCOLORMASKIPROC)LoadOpenGLProc("glColorMaski");
        csc_glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)LoadOpenGLProc("glGetBooleani_v");
        csc_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)LoadOpenGLProc("glGetIntegeri_v");
        csc_glEnablei = (PFNGLENABLEIPROC)LoadOpenGLProc("glEnablei");
        csc_glDisablei = (PFNGLDISABLEIPROC)LoadOpenGLProc("glDisablei");
        csc_glIsEnabledi = (PFNGLISENABLEDIPROC)LoadOpenGLProc("glIsEnabledi");
        csc_glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)LoadOpenGLProc("glBeginTransformFeedback");
        csc_glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)LoadOpenGLProc("glEndTransformFeedback");
        csc_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)LoadOpenGLProc("glBindBufferRange");
        csc_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)LoadOpenGLProc("glBindBufferBase");
        csc_glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)LoadOpenGLProc("glTransformFeedbackVaryings");
        csc_glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)LoadOpenGLProc("glGetTransformFeedbackVarying");
        csc_glClampColor = (PFNGLCLAMPCOLORPROC)LoadOpenGLProc("glClampColor");
        csc_glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)LoadOpenGLProc("glBeginConditionalRender");
        csc_glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)LoadOpenGLProc("glEndConditionalRender");
        csc_glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)LoadOpenGLProc("glVertexAttribIPointer");
        csc_glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)LoadOpenGLProc("glGetVertexAttribIiv");
        csc_glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)LoadOpenGLProc("glGetVertexAttribIuiv");
        csc_glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)LoadOpenGLProc("glVertexAttribI1i");
        csc_glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)LoadOpenGLProc("glVertexAttribI2i");
        csc_glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)LoadOpenGLProc("glVertexAttribI3i");
        csc_glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)LoadOpenGLProc("glVertexAttribI4i");
        csc_glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)LoadOpenGLProc("glVertexAttribI1ui");
        csc_glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)LoadOpenGLProc("glVertexAttribI2ui");
        csc_glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)LoadOpenGLProc("glVertexAttribI3ui");
        csc_glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)LoadOpenGLProc("glVertexAttribI4ui");
        csc_glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)LoadOpenGLProc("glVertexAttribI1iv");
        csc_glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)LoadOpenGLProc("glVertexAttribI2iv");
        csc_glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)LoadOpenGLProc("glVertexAttribI3iv");
        csc_glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)LoadOpenGLProc("glVertexAttribI4iv");
        csc_glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)LoadOpenGLProc("glVertexAttribI1uiv");
        csc_glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)LoadOpenGLProc("glVertexAttribI2uiv");
        csc_glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)LoadOpenGLProc("glVertexAttribI3uiv");
        csc_glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)LoadOpenGLProc("glVertexAttribI4uiv");
        csc_glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)LoadOpenGLProc("glVertexAttribI4bv");
        csc_glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)LoadOpenGLProc("glVertexAttribI4sv");
        csc_glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)LoadOpenGLProc("glVertexAttribI4ubv");
        csc_glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)LoadOpenGLProc("glVertexAttribI4usv");
        csc_glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)LoadOpenGLProc("glGetUniformuiv");
        csc_glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)LoadOpenGLProc("glBindFragDataLocation");
        csc_glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)LoadOpenGLProc("glGetFragDataLocation");
        csc_glUniform1ui = (PFNGLUNIFORM1UIPROC)LoadOpenGLProc("glUniform1ui");
        csc_glUniform2ui = (PFNGLUNIFORM2UIPROC)LoadOpenGLProc("glUniform2ui");
        csc_glUniform3ui = (PFNGLUNIFORM3UIPROC)LoadOpenGLProc("glUniform3ui");
        csc_glUniform4ui = (PFNGLUNIFORM4UIPROC)LoadOpenGLProc("glUniform4ui");
        csc_glUniform1uiv = (PFNGLUNIFORM1UIVPROC)LoadOpenGLProc("glUniform1uiv");
        csc_glUniform2uiv = (PFNGLUNIFORM2UIVPROC)LoadOpenGLProc("glUniform2uiv");
        csc_glUniform3uiv = (PFNGLUNIFORM3UIVPROC)LoadOpenGLProc("glUniform3uiv");
        csc_glUniform4uiv = (PFNGLUNIFORM4UIVPROC)LoadOpenGLProc("glUniform4uiv");
        csc_glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)LoadOpenGLProc("glTexParameterIiv");
        csc_glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)LoadOpenGLProc("glTexParameterIuiv");
        csc_glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)LoadOpenGLProc("glGetTexParameterIiv");
        csc_glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)LoadOpenGLProc("glGetTexParameterIuiv");
        csc_glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)LoadOpenGLProc("glClearBufferiv");
        csc_glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)LoadOpenGLProc("glClearBufferuiv");
        csc_glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)LoadOpenGLProc("glClearBufferfv");
        csc_glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)LoadOpenGLProc("glClearBufferfi");
        csc_glGetStringi = (PFNGLGETSTRINGIPROC)LoadOpenGLProc("glGetStringi");
        csc_glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)LoadOpenGLProc("glIsRenderbuffer");
        csc_glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)LoadOpenGLProc("glBindRenderbuffer");
        csc_glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)LoadOpenGLProc("glDeleteRenderbuffers");
        csc_glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)LoadOpenGLProc("glGenRenderbuffers");
        csc_glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)LoadOpenGLProc("glRenderbufferStorage");
        csc_glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)LoadOpenGLProc("glGetRenderbufferParameteriv");
        csc_glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)LoadOpenGLProc("glIsFramebuffer");
        csc_glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)LoadOpenGLProc("glBindFramebuffer");
        csc_glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)LoadOpenGLProc("glDeleteFramebuffers");
        csc_glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)LoadOpenGLProc("glGenFramebuffers");
        csc_glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)LoadOpenGLProc("glCheckFramebufferStatus");
        csc_glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)LoadOpenGLProc("glFramebufferTexture1D");
        csc_glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)LoadOpenGLProc("glFramebufferTexture2D");
        csc_glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)LoadOpenGLProc("glFramebufferTexture3D");
        csc_glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)LoadOpenGLProc("glFramebufferRenderbuffer");
        csc_glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)LoadOpenGLProc("glGetFramebufferAttachmentParameteriv");
        csc_glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)LoadOpenGLProc("glGenerateMipmap");
        csc_glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)LoadOpenGLProc("glBlitFramebuffer");
        csc_glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)LoadOpenGLProc("glRenderbufferStorageMultisample");
        csc_glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)LoadOpenGLProc("glFramebufferTextureLayer");
        csc_glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)LoadOpenGLProc("glMapBufferRange");
        csc_glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)LoadOpenGLProc("glFlushMappedBufferRange");
        csc_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)LoadOpenGLProc("glBindVertexArray");
        csc_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)LoadOpenGLProc("glDeleteVertexArrays");
        csc_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)LoadOpenGLProc("glGenVertexArrays");
        csc_glIsVertexArray = (PFNGLISVERTEXARRAYPROC)LoadOpenGLProc("glIsVertexArray");
    }
}

internal void
Load_GL_VERSION_3_1(CSCLoadProc LoadOpenGLProc)
{
    if(CSC_GL_VERSION_3_1)
    {
        csc_glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)LoadOpenGLProc("glDrawArraysInstanced");
        csc_glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)LoadOpenGLProc("glDrawElementsInstanced");
        csc_glTexBuffer = (PFNGLTEXBUFFERPROC)LoadOpenGLProc("glTexBuffer");
        csc_glPrimitiveRestartIndex = (PFNGLPRIMITIVERESTARTINDEXPROC)LoadOpenGLProc("glPrimitiveRestartIndex");
        csc_glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC)LoadOpenGLProc("glCopyBufferSubData");
        csc_glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)LoadOpenGLProc("glGetUniformIndices");
        csc_glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)LoadOpenGLProc("glGetActiveUniformsiv");
        csc_glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)LoadOpenGLProc("glGetActiveUniformName");
        csc_glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)LoadOpenGLProc("glGetUniformBlockIndex");
        csc_glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)LoadOpenGLProc("glGetActiveUniformBlockiv");
        csc_glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)LoadOpenGLProc("glGetActiveUniformBlockName");
        csc_glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)LoadOpenGLProc("glUniformBlockBinding");
        csc_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)LoadOpenGLProc("glBindBufferRange");
        csc_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)LoadOpenGLProc("glBindBufferBase");
        csc_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)LoadOpenGLProc("glGetIntegeri_v");
    }
}

//
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
        CSC_GL_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
        CSC_GL_VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
        CSC_GL_VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
        CSC_GL_VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
        CSC_GL_VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;
        CSC_GL_VERSION_1_5 = (major == 1 && minor >= 5) || major > 1;
        CSC_GL_VERSION_2_0 = (major == 2 && minor >= 0) || major > 2;
        CSC_GL_VERSION_2_1 = (major == 2 && minor >= 1) || major > 2;
        CSC_GL_VERSION_3_0 = (major == 3 && minor >= 0) || major > 3;
        CSC_GL_VERSION_3_1 = (major == 3 && minor >= 1) || major > 3;
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